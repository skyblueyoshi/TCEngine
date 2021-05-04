#pragma once

#include <vector>
#include "Memory.h"
#include <cstring>

namespace Tce {

    class ByteStream {
    private:
        std::vector<uint8_t> m_arr;
        size_t m_readPos{};        //读取点
    public:
        ByteStream() = default;

        ByteStream(const ByteStream &bs) = default;

        ByteStream(ByteStream &&bs) = default;

        ByteStream(const std::vector<uint8_t> &arr)
                : m_arr(arr) {}

        ByteStream(std::vector<uint8_t> &&arr)
                : m_arr(std::move(arr)) {}

        ~ByteStream() = default;

        //从某个指针位置开始，加入一段空间到字节流
        template<typename T2>
        void WriteBatch(const T2 *p, int count) {
            assert(count > 0);
            int addByteSize = count * sizeof(T2);
            //拓容
            int oldLength = m_arr.size();
            m_arr.resize(oldLength + addByteSize);
            Memory::CopyArray((uint8_t *) &m_arr[oldLength], (uint8_t *) p, addByteSize);
        }

        //还有可读数据
        bool CanRead() const {
            return m_readPos < m_arr.size();
        }

        //判断是否可读接下来的长度（长度必需大于0）
        bool CanReadNextLength(int nextLength) const {
            assert(nextLength > 0);
            return m_readPos + nextLength <= m_arr.size();
        }

        uint8_t *GetBase() {
            return m_arr.data();
        }

        const uint8_t *GetBase() const {
            return m_arr.data();
        }

        size_t GetLength() const {
            return m_arr.size();
        }

        //设置长度，注意如果长度为0，则会清空读取点
        void SetLength(size_t nNewLength, bool freeMemory = false) {
            if (nNewLength == 0)
                m_readPos = 0;
            if (nNewLength > 0) {
                m_arr.resize(nNewLength);
            } else if (freeMemory) {
                FreeMemory();
            } else {
                m_arr.resize(nNewLength);
            }
            if (m_readPos > m_arr.size())
                m_readPos = m_arr.size();
        }

        void FreeMemory() {
            std::vector<uint8_t> temp;
            m_arr.swap(temp);
            m_readPos = 0;
        }

        void Reset() {
            SetLength(0);
        }

    private:
        //批量获取元素到指定位置
        template<typename T2>
        void InnerGetBatch(T2 *p, int begin, int count) const {
            if ((int) (begin + count * sizeof(T2)) <= m_arr.size()) {
                Memory::CopyArray((uint8_t *) p, (uint8_t *) &m_arr.at(begin), count * sizeof(T2));
            } else {
                throw std::overflow_error("ByteStream.GetBatch() overflow!");
            }
        }

    public:
        //获取读取位置指针
        size_t GetReadPos() const {
            return m_readPos;
        }

        //设置读取位置指针
        void SetReadPos(int x) {
            m_readPos = x;
        }

        //读取位置指针清零
        void ZeroReadPos() {
            m_readPos = 0;
        }

        //推进读取位置指针
        void MoveReadPos(int n) {
            m_readPos += n;
        }

        //加入一个变量到字节流
        template<typename T2>
        void WriteVar(const T2 &x) {
            WriteBatch(&x, 1);
        }

        //读取指针批量获取变量，并使读取指针自动跳过读取部分
        template<typename T2>
        void ReadBatch(T2 *p, int count) {
            InnerGetBatch(p, m_readPos, count);
            MoveReadPos(count * sizeof(T2));
        }

        //读取指针获取一个变量，并使读取指针自动跳过读取部分
        template<typename T2>
        void ReadVar(T2 &x) {
            ReadBatch(&x, 1);
        }

        //批量读取并拷贝到新动态数组中，并使读取指针自动跳过读取部分
        template<typename T2>
        void ReadArrayList(std::vector<T2> &arr, int count) {
            arr.resize(count);
            InnerGetBatch(arr.GetBasePointer(), m_readPos, count);
            MoveReadPos(count * sizeof(T2));
        }

        template<typename T2>
        void Write(const T2 &value) {
            WriteVar(value);
        }

        template<typename T2>
        void Read(T2 &value) {
            ReadVar(value);
        }

        template<>
        void Write<bool>(const bool &value) {
            uint8_t temp = 0x00;
            if (value) temp = 0x01;
            WriteVar(temp);
        }

        template<>
        void Read<bool>(bool &value) {
            uint8_t temp = 0;
            ReadVar(temp);
            value = (temp != 0);
        }

        template<>
        void Write<ByteStream>(const ByteStream &bs) {
            size_t len = bs.GetLength();
            WriteVarInt(len);
            if (len > 0) {
                WriteBatch(bs.GetBase(), len);
            }
        }

        template<>
        void Read<ByteStream>(ByteStream &bs) {
            size_t len = 0;
            ReadVarInt(len);
            bs.SetLength(len);
            if (len > 0) {
                ReadBatch(bs.GetBase(), len);
            }
        }

//        template<>
//        void Write<std::string>(const std::string &value) {
//            size_t len = value.size();
//            WriteVarInt(len);
//            if (len != 0) {
//                WriteBatch(value.data(), len);
//            }
//        }
//
//        template<>
//        void Read<std::string>(std::string &value) {
//            size_t len = 0;
//            ReadVarInt(len);
//            value.resize(len);
//            if (len > 0) {
//                ReadBatch(value.data(), len);
//            }
//        }

        template<typename T2>
        void WriteArray(const std::vector<T2> &_arr) {
            size_t len = _arr.size();
            WriteVarInt(len);
            if (len != 0) {
                for (size_t i = 0; i < len; i++) {
                    Write(_arr[i]);
                }
            }
        }

        template<typename T2>
        void ReadArray(std::vector<T2> &_arr) {
            size_t len = 0;
            ReadVarInt(len);
            _arr.resize(len);
            if (len != 0) {
                for (size_t i = 0; i < len; i++) {
                    Read(_arr[i]);
                }
            }
        }

        void WriteVarInt(int value) {
            unsigned int v = (unsigned int) value;
            do {
                uint8_t temp = (uint8_t) (v & 0b01111111);
                v = v >> 7;
                if (v != 0) {
                    temp |= 0b10000000;
                }
                Write(temp);
            } while (v != 0);
        }

        void ReadVarInt(size_t &value) {
            int _value;
            ReadVarInt(_value);
            value = (size_t) _value;
        }

        void ReadVarInt(int &value) {
            int numRead = 0;
            int result = 0;
            uint8_t read = 0;
            do {
                Read(read);
                int temp = (read & 0b01111111);
                result |= (temp << (7 * numRead));
                numRead++;
                if (numRead > 5) {
                    throw std::overflow_error(
                            "ByteStream.ReadVarInt(int&) overflow! VarLong is too big!");
                }
            } while ((read & 0b10000000) != 0);
            value = result;
        }

    };

}