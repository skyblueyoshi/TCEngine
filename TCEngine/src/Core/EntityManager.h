#pragma once

#include "ObjectPool.h"
#include "EntityID.h"

namespace Tce {

    // 实体管理器
    // 这是一个使用内存池维护多个实体对象的管理器，用于维护实体运行情况
    // 每个实体使用对应的EntityID进行索引
    // 遍历每个实体的方法：
    // for (auto entityID : entityManager)
    //     auto& entity = entityManager.Get(entityID);
    // 实体加入到管理器时，实体已加入到内存池，并处在预加入阶段，并未加入到遍历列表
    // 经过一次Flush()操作，所有欲加入阶段的实体会被正式加入到遍历列表
    // 实体从管理器卸载时，实体将会被标记为死亡，并在遍历时自动忽略被标记死亡的实体
    // 经过一次Flush()操作，所有被标记死亡的实体会正式析构，并从内存池中移除
    // 若希望遍历时也遍历被标记死亡的实体，可进行如下操作
    // 请在遍历前使用SetForRange(FOR_ALL)，在遍历后使用SetForRange(FOR_EXIST_ONLY)还原遍历方式
    // 实体管理器在每个游戏循环的生命周期结尾时，请执行Flush()函数以更新每个实体的临时状态
    // T_boundToServer表示当前管理器为客户端管理器，与服务端管理器共用相同的EntityID
    // 客户端管理器请使用CreateFromBound(xxx, serverEntityID)来建立一个与服务端EntityID一致的实体对象
    template<typename T, bool T_boundToServer = false>
    class EntityManager {
        friend class Iterator;

        struct Element {
            T *pEntity{nullptr};
            EntityID entityID;
            uint32_t preIndex{};
            uint32_t nextIndex{};
            bool exist{};

            void SetEntity(EntityID _entityID, T *_pEntity, uint64_t _unique) {
                this->pEntity = _pEntity;
                this->entityID = _entityID;
                preIndex = 0U;
                nextIndex = 0U;
                exist = true;
            }

            void Free() {
                pEntity = nullptr;
                entityID = EntityID();
                preIndex = 0U;
                nextIndex = 0U;
                exist = false;
            }
        };

    public:
        class Iterator {
        public:
            Iterator(EntityManager *pManager, uint32_t index) {
                m_pManager = pManager;
                m_index = index;
            }

            Iterator &operator++() {
                m_index = m_pManager->_GetNextIndex(m_index);
                return *this;
            }

            bool operator!=(const Iterator &other) {
                return m_index != other.m_index;
            }

            EntityID operator*() {
                return m_pManager->_GetElement(m_index).entityID;
            }

        private:
            EntityManager *m_pManager;
            uint32_t m_index;
        };

        enum FOR_RANGE_STYLE {
            FOR_EXIST_ONLY,
            FOR_ALL
        };

    public:

        // 构造函数
        EntityManager() {
            m_elements.emplace_back(Element());
        }

        // 析构函数
        virtual ~EntityManager() {
            Clear();
        }

        // 创建一个实体
        // @param args 实体构造函数参数列表
        // @return 实体ID
        template<typename ... Args>
        EntityID Create(Args &&... args) {
            assert(!T_boundToServer);
            return _DeferCreate(
                    _EmAddObject(T(std::forward<Args>(args)...)));
        }

        // 创建一个实体
        // @param entity 实体拷贝
        // @return 实体ID
        EntityID Create(const T &entity) {
            assert(!T_boundToServer);
            return _DeferCreate(_AddObject(entity));
        }

        // 创建一个实体
        // @param entity 移动实体
        // @return 实体ID
        EntityID EmCreate(T &&entity) {
            assert(!T_boundToServer);
            return _DeferCreate(_EmAddObject(std::move(entity)));
        }

        // 从绑定的服务端端口创建一个实体
        // @param entity 实体拷贝
        // @param serverEntityID 服务端实体ID
        // @return 实体ID，与服务端实体ID一致
        EntityID CreateFromBound(const T &entity, const EntityID &serverEntityID) {
            assert(T_boundToServer);
            return _DeferCreate(_AddObject(entity), serverEntityID);
        }

        // 从绑定的服务端端口创建一个实体
        // @param entity 移动实体
        // @param serverEntityID 服务端实体ID
        // @return 实体ID，与服务端实体ID一致
        EntityID EmCreateFromBound(T &&entity, const EntityID &serverEntityID) {
            assert(T_boundToServer);
            return _DeferCreate(_EmAddObject(std::move(entity)), serverEntityID);
        }

        // 移除一个实体
        // @param entityID 实体ID
        void Delete(const EntityID &entityID) {
            _DeferDelete(entityID);
        }

        // 判断实体是否存在
        // @param entityID 实体ID
        // @return 实体是否存在
        bool IsExist(const EntityID &entityID) {
            auto *pElement = _TryGetElement(entityID);
            if (pElement) {
                return pElement->exist;
            }
            return false;
        }

        // 获取实体
        // @param entityID 实体ID
        // @return 实体引用
        T &Get(const EntityID &entityID) {
            T *pEntity = TryGet(entityID);
            assert(pEntity != nullptr);
            return *pEntity;
        }

        // 尝试获取实体
        // @param entityID 实体ID
        // @return 实体指针，若实体不存在则返回nullptr
        T *TryGet(const EntityID &entityID) {
            auto *pElement = _TryGetElement(entityID);
            if (pElement) {
                return pElement->pEntity;
            }
            return nullptr;
        }

        // 刷新实体管理器，应在每个循环帧结束前执行
        // 将所有刚添加的实体正式添加到实体列表
        // 将所有刚删除的实体正式从内存中删除
        void Flush() {
            for (auto &entityID : m_nextAdds) {
                auto &element = _GetElement(entityID._index);
                _AddLink(element);
            }
            m_nextAdds.clear();

            for (auto &entityID : m_nextDeletes) {
                auto &element = _GetElement(entityID._index);
                _DeleteLink(element);
                _DeleteElement(element);
            }
            m_nextDeletes.clear();
        }

        // 清空实体管理器
        void Clear() {
            Flush();
            auto oldForRange = m_eForRange;
            m_eForRange = FOR_EXIST_ONLY;
            for (auto entityID : (*this)) {
                Delete(entityID);
            }
            m_eForRange = oldForRange;
            Flush();
        }

        // 设置遍历方式
        // @param style 遍历方式
        void SetForRange(FOR_RANGE_STYLE style) {
            m_eForRange = style;
        }

        // 获取遍历方式
        // @return 遍历方式
        FOR_RANGE_STYLE GetForRange() {
            return m_eForRange;
        }

        inline Iterator begin() {
            if (m_eForRange == FOR_EXIST_ONLY) {
                if (m_headIndex != 0) {
                    if (_GetElement(m_headIndex).exist)
                        return Iterator(this, m_headIndex);
                    else
                        return Iterator(this, _GetNextExistIndex(m_headIndex));
                } else {
                    assert(m_tailIndex == 0);
                    return Iterator(this, 0);
                }
            } else {
                return Iterator(this, m_headIndex);
            }
        }

        inline Iterator end() {
            return Iterator(this, 0);
        }

    private:

        T *_AddObject(const T &object) {
            return m_entityPool.Add(object);
        }

        T *_EmAddObject(T &&object) {
            return m_entityPool.EmAdd(std::move(object));
        }

        void _DeleteObject(T *pObject) {
            m_entityPool.Remove(pObject);
        }

        void _AddLink(Element &element) {
            uint32_t index = element.entityID._index;
            if (m_headIndex == 0) {
                assert(m_tailIndex == 0);
                m_headIndex = m_tailIndex = index;
            } else {
                element.preIndex = m_tailIndex;
                _GetElement(m_tailIndex).nextIndex = index;
                m_tailIndex = index;
            }
        }

        void _SetNotExist(Element &element) {
            assert(element.pEntity);
            assert(element.exist);
            element.exist = false;
        }

        void _DeleteLink(Element &element) {
            uint32_t index = element.entityID._index;
            if (index == m_headIndex && index == m_tailIndex) {
                m_headIndex = m_tailIndex = 0;
            } else if (index == m_headIndex) {
                m_headIndex = element.nextIndex;
                if (m_headIndex != 0) {
                    _GetElement(m_headIndex).preIndex = 0;
                }
            } else if (index == m_tailIndex) {
                m_tailIndex = element.preIndex;
                if (m_tailIndex != 0) {
                    _GetElement(m_tailIndex).nextIndex = 0;
                }
            } else {
                _GetElement(element.preIndex).nextIndex
                        = element.nextIndex;
                _GetElement(element.nextIndex).preIndex
                        = element.preIndex;
            }
            element.preIndex = 0;
            element.nextIndex = 0;
        }

        EntityID _DeferCreate(T *pEntity, const EntityID &serverEntityID = EntityID()) {
            EntityID entityID = _CreateElement(pEntity, serverEntityID);
            m_nextAdds.push_back(entityID);
            return entityID;
        }

        void _DeferDelete(const EntityID &entityID) {
            _SetNotExist(_GetElement(entityID._index));
            m_nextDeletes.push_back(entityID);
        }

        EntityID _CreateElement(T *pEntity, const EntityID &serverEntityID) {
            uint32_t index = 0;
            uint64_t unique = 0;
            if (!T_boundToServer) {
                if (!m_freeIndexs.empty()) {
                    index = m_freeIndexs.back();
                    m_freeIndexs.pop_back();
                } else {
                    m_elements.emplace_back(Element());
                    index = m_elements.size() - 1;
                }
                unique = m_maxUnique++;
            } else {
                index = serverEntityID._index;
                unique = serverEntityID._unique;
                while (index >= m_elements.size()) {
                    m_elements.emplace_back(Element());
                }
            }
            EntityID entityID{index, unique};
            assert(m_elements[index].pEntity == nullptr);
            assert(!m_elements[index].exist);
            assert(m_elements[index].entityID == EntityID());
            m_elements[index].SetEntity(entityID, pEntity, unique);
            m_total++;
            return entityID;
        }

        void _DeleteElement(Element &element) {
            assert(element.pEntity != nullptr);
            assert(!element.exist);
            if (!T_boundToServer) {
                m_freeIndexs.push_back(element.entityID._index);
            }
            _DeleteObject(element.pEntity);
            element.Free();
            assert(m_total > 0);
            m_total--;
        }

        Element *_TryGetElement(const EntityID &entityID) {
            auto *pElement = _TryGetElement(entityID._index);
            if (pElement &&
                pElement->entityID._unique == entityID._unique) {
                return pElement;
            }
            return nullptr;
        }

        inline Element &_GetElement(uint32_t index) {
            assert(index > 0);
            auto *p = _TryGetElement(index);
            assert(p != nullptr);
            assert(p->pEntity != nullptr);
            return *p;
        }

        inline Element *_TryGetElement(uint32_t index) {
            if (index > 0 && index < m_elements.size()) {
                if (m_elements[index].pEntity != nullptr)
                    return &m_elements[index];
            }
            return nullptr;
        }

        inline uint32_t _GetNextExistIndex(uint32_t index) {
            while (true) {
                index = _GetElement(index).nextIndex;
                if (index != 0) {
                    if (_GetElement(index).exist)
                        return index;
                } else break;
            }
            return 0;
        }

        inline uint32_t _GetNextIndex(uint32_t index) {
            if (m_eForRange == FOR_EXIST_ONLY) {
                return _GetNextExistIndex(index);
            } else {
                return _GetElement(index).nextIndex;
            }
        }

    private:

        ObjectPool<T> m_entityPool;
        std::vector<Element> m_elements;
        std::vector<EntityID> m_nextAdds;
        std::vector<EntityID> m_nextDeletes;
        std::vector<uint32_t> m_freeIndexs;
        FOR_RANGE_STYLE m_eForRange{};
        uint32_t m_headIndex{};
        uint32_t m_tailIndex{};
        uint64_t m_maxUnique{};
        size_t m_total{};
    };

}