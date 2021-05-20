#pragma once

#include "TCArrayList.h"

namespace Tce {

    class ByteStream : public ArrayList<uint8_t> {
    private:
        size_t _readPos{};        //读取点
    public:
        ByteStream() = default;

        ByteStream(const ByteStream &bs) = default;

        ByteStream(ByteStream &&bs) = default;

        virtual ~ByteStream() = default;


        ByteStream& operator=(const ByteStream& bs) {
            if (this != &bs) {
                _arr = bs._arr;
                _readPos = bs._readPos;
            }
            return *this;
        }

        ByteStream& operator=(ByteStream &&bs) {
            if (this != &bs) {
                _arr = std::move(bs._arr);
                _readPos = bs._readPos;
            }
            return *this;
        }

        //从某个指针位置开始，加入一段空间到字节流
        template<typename T2>
        void WriteBatch(const T2 *p, size_t count) {
            assert(count > 0);
            size_t addByteSize = count * sizeof(T2);
            //拓容
            size_t oldLength = Count();
            SetCount(oldLength + addByteSize);
            Memory::CopyArray((uint8_t *) &GetAt(oldLength), (uint8_t *) p, addByteSize);
        }

        //还有可读数据
        bool CanRead() const {
            return _readPos < Count();
        }

        //判断是否可读接下来的长度（长度必需大于0）
        bool CanReadNextLength(int nextLength) const {
            assert(nextLength > 0);
            return _readPos + nextLength <= Count();
        }

        void SetCount(size_t count) {
            ArrayList<uint8_t>::SetCount(count);
            if (_readPos > Count()) _readPos = Count();
        }

        void FreeMemory() {
            ArrayList<uint8_t>::FreeMemory();
            _readPos = 0;
        }

        void Clear() {
            ArrayList<uint8_t>::Clear();
            _readPos = 0;
        }

    private:
        //批量获取元素到指定位置
        template<typename T2>
        void InnerGetBatch(T2 *p, size_t begin, size_t count) const {
            if ((begin + count * sizeof(T2)) <= Count()) {
                Memory::CopyArray((uint8_t *) p, (uint8_t *) &GetAt(begin), count * sizeof(T2));
            } else {
                throw std::overflow_error("ByteStream.GetBatch() overflow!");
            }
        }

    public:
        //获取读取位置指针
        size_t GetReadPos() const {
            return _readPos;
        }

        //设置读取位置指针
        void SetReadPos(size_t x) {
            _readPos = x;
        }

        //读取位置指针清零
        void ZeroReadPos() {
            _readPos = 0;
        }

        //推进读取位置指针
        void MoveReadPos(size_t n) {
            _readPos += n;
        }

        //加入一个变量到字节流
        template<typename T2>
        void WriteVar(const T2 &x) {
            WriteBatch(&x, 1);
        }

        //读取指针批量获取变量，并使读取指针自动跳过读取部分
        template<typename T2>
        void ReadBatch(T2 *p, size_t count) {
            InnerGetBatch(p, _readPos, count);
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
            InnerGetBatch(arr.GetBasePointer(), _readPos, count);
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
            size_t len = bs.Count();
            WriteVarInt((uint32_t)len);
            if (len > 0) {
                WriteBatch(bs.Data(), len);
            }
        }

        template<>
        void Read<ByteStream>(ByteStream &bs) {
            uint32_t len = 0;
            ReadVarInt(len);
            bs.SetCount((size_t)len);
            if (len > 0) {
                ReadBatch(bs.Data(), (size_t)len);
            }
        }

//        template<>
//        void Write<std::string>(const std::string &value) {
//            size_t len = value.size();
//            WriteVarInt((uint32_t)len);
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
            WriteVarInt((uint32_t)len);
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

        void WriteVarInt(uint32_t value) {
            WriteVarInt((int)value);
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

        void ReadVarInt(uint32_t &value) {
            int _value;
            ReadVarInt(_value);
            value = (uint32_t) _value;
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