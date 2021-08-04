#pragma once

#include "TCString.h"

namespace Tce {

    class Encode {
    public:
        class ASCII {
        public:
        };
        class UTF8 {
        public:
            static UString ToUTF16(const UString& str) {
                return std::move(ToUTF16(str.Data()));
            }
            static UString ToUTF16(const char* text) {
                return std::move(ToUTF16(text, StrLength(text)));
            }
            static UString ToUTF16(const char* text, size_t length, bool addBom = false, bool * ok = NULL) {
                UString u16str;
                u16str.base = new wchar_t[length + 1];
                ZeroDyArray(u16str.base, length + 1, length + 1);
                int uIndex = 0;
                if (addBom) {
                    u16str.base[uIndex++] = 0xFEFF;	//bom (字节表示为 FF FE)
                }

                int len = length;

                const unsigned char* p = (unsigned char*)(text);
                // 判断是否具有BOM(判断长度小于3字节的情况)
                if (len > 3 && p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF) {
                    p += 3;
                    len -= 3;
                }

                bool is_ok = true;
                // 开始转换
                for (int i = 0; i < len; ++i) {
                    uint32_t ch = p[i];	// 取出UTF8序列首字节
                    if ((ch & 0x80) == 0) {
                        // 最高位为0，只有1字节表示UNICODE代码点
                        u16str.base[uIndex++] = ((char16_t)ch);
                        continue;
                    }
                    switch (ch & 0xF0)
                    {
                    case 0xF0: // 4 字节字符, 0x10000 到 0x10FFFF
                    {
                        uint32_t c2 = p[++i];
                        uint32_t c3 = p[++i];
                        uint32_t c4 = p[++i];
                        // 计算UNICODE代码点值(第一个字节取低3bit，其余取6bit)
                        uint32_t codePoint = ((ch & 0x07U) << 18) | ((c2 & 0x3FU) << 12) | ((c3 & 0x3FU) << 6) | (c4 & 0x3FU);
                        if (codePoint >= 0x10000)
                        {
                            // 在UTF-16中 U+10000 到 U+10FFFF 用两个16bit单元表示, 代理项对.
                            // 1、将代码点减去0x10000(得到长度为20bit的值)
                            // 2、high 代理项 是将那20bit中的高10bit加上0xD800(110110 00 00000000)
                            // 3、low  代理项 是将那20bit中的低10bit加上0xDC00(110111 00 00000000)
                            codePoint -= 0x10000;
                            u16str.base[uIndex++] = ((char16_t)((codePoint >> 10) | 0xD800U));
                            u16str.base[uIndex++] = ((char16_t)((codePoint & 0x03FFU) | 0xDC00U));
                        }
                        else
                        {
                            // 在UTF-16中 U+0000 到 U+D7FF 以及 U+E000 到 U+FFFF 与Unicode代码点值相同.
                            // U+D800 到 U+DFFF 是无效字符, 为了简单起见，这里假设它不存在(如果有则不编码)
                            u16str.base[uIndex++] = ((char16_t)codePoint);
                        }
                    }
                    break;
                    case 0xE0: // 3 字节字符, 0x800 到 0xFFFF
                    {
                        uint32_t c2 = p[++i];
                        uint32_t c3 = p[++i];
                        // 计算UNICODE代码点值(第一个字节取低4bit，其余取6bit)
                        uint32_t codePoint = ((ch & 0x0FU) << 12) | ((c2 & 0x3FU) << 6) | (c3 & 0x3FU);
                        u16str.base[uIndex++] = ((char16_t)codePoint);
                    }
                    break;
                    case 0xD0: // 2 字节字符, 0x80 到 0x7FF
                    case 0xC0:
                    {
                        uint32_t c2 = p[++i];
                        // 计算UNICODE代码点值(第一个字节取低5bit，其余取6bit)
                        uint32_t codePoint = ((ch & 0x1FU) << 12) | ((c2 & 0x3FU) << 6);
                        u16str.base[uIndex++] = ((char16_t)codePoint);
                    }
                    break;
                    default:	// 单字节部分(前面已经处理，所以不应该进来)
                        is_ok = false;
                        break;
                    }
                }
                if (ok != NULL) { *ok = is_ok; }

                return std::move(u16str);
            }
        };
        class UTF16 {
        public:
            static String ToUTF8(const UString& str) {
                return std::move(ToUTF8(str.Data()));
            }
            static String ToUTF8(const wchar_t* text) {
                return std::move(ToUTF8(text, StrLength(text)));
            }
            static String ToUTF8(const wchar_t* text, size_t length) {
                if (text == NULL || length == 0) { return std::string(); }
                const char16_t* p = (const char16_t*)text;
                std::u16string::size_type len = length;
                if (p[0] == 0xFEFF) {
                    p += 1;	//带有bom标记，后移
                    len -= 1;
                }

                // 开始转换
                std::string u8str;
                u8str.reserve(len * 3);

                char16_t u16char;
                for (std::u16string::size_type i = 0; i < len; ++i) {
                    // 这里假设是在小端序下(大端序不适用)
                    u16char = p[i];

                    // 1字节表示部分
                    if (u16char < 0x0080) {
                        // u16char <= 0x007f
                        // U- 0000 0000 ~ 0000 07ff : 0xxx xxxx
                        u8str.push_back((char)(u16char & 0x00FF));	// 取低8bit
                        continue;
                    }
                    // 2 字节能表示部分
                    if (u16char >= 0x0080 && u16char <= 0x07FF) {
                        // * U-00000080 - U-000007FF:  110xxxxx 10xxxxxx
                        u8str.push_back((char)(((u16char >> 6) & 0x1F) | 0xC0));
                        u8str.push_back((char)((u16char & 0x3F) | 0x80));
                        continue;
                    }
                    // 代理项对部分(4字节表示)
                    if (u16char >= 0xD800 && u16char <= 0xDBFF) {
                        // * U-00010000 - U-001FFFFF: 1111 0xxx 10xxxxxx 10xxxxxx 10xxxxxx
                        uint32_t highSur = u16char;
                        uint32_t lowSur = p[++i];
                        // 从代理项对到UNICODE代码点转换
                        // 1、从高代理项减去0xD800，获取有效10bit
                        // 2、从低代理项减去0xDC00，获取有效10bit
                        // 3、加上0x10000，获取UNICODE代码点值
                        uint32_t codePoint = highSur - 0xD800;
                        codePoint <<= 10;
                        codePoint |= lowSur - 0xDC00;
                        codePoint += 0x10000;
                        // 转为4字节UTF8编码表示
                        u8str.push_back((char)((codePoint >> 18) | 0xF0));
                        u8str.push_back((char)(((codePoint >> 12) & 0x3F) | 0x80));
                        u8str.push_back((char)(((codePoint >> 06) & 0x3F) | 0x80));
                        u8str.push_back((char)((codePoint & 0x3F) | 0x80));
                        continue;
                    }
                    // 3 字节表示部分
                    {
                        // * U-0000E000 - U-0000FFFF:  1110xxxx 10xxxxxx 10xxxxxx
                        u8str.push_back((char)(((u16char >> 12) & 0x0F) | 0xE0));
                        u8str.push_back((char)(((u16char >> 6) & 0x3F) | 0x80));
                        u8str.push_back((char)((u16char & 0x3F) | 0x80));
                        continue;
                    }
                }

                return u8str;
            }
        };
    };

}