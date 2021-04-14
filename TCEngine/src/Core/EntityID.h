#pragma once

namespace Tce {

    // 实体ID
    // 用于索引实体管理器的实体对象
    struct EntityID {
        uint32_t _index{};		// 实体在管理器内的索引
        uint64_t _unique{};		// 实体的唯一标记
        EntityID() = default;
        EntityID(uint32_t index, uint64_t unique)
                : _index(index), _unique(unique) {}
        bool operator==(const EntityID& other) const {
            return _index == other._index && _unique == other._unique;
        }
        bool operator!=(const EntityID& other) const {
            return _index != other._index || _unique != other._unique;
        }
    };

}