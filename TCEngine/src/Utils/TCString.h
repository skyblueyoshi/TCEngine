#pragma once

#include "SysConfig.h"

namespace Tce {


    inline int _VSNPrintf(char* b, size_t bc, const char* f, va_list l) {
        return vsnprintf(b, bc, f, l);
    }

    inline int _VSNPrintf(wchar_t* b, size_t bc, const wchar_t* f, va_list l) {
        //return _vsnwprintf(b, bc, f, l);
        return vswprintf(b, bc, f, l);
    }

    inline size_t StrLength(const char *text) {
        return strlen(text);
    }

    inline size_t StrLength(const wchar_t *text) {
        return wcslen(text);
    }

    inline int StrToInt(const char *text) {
        return atoi(text);
    }

    inline int StrToInt(const wchar_t *text) {
#ifdef _TC_WINDOWS
        return _wtoi(text);
#else
        int offset = StrLength(text);
        return wcstol(text, (wchar_t **) (&(text[offset])), 0);
#endif
    }

    inline double StrToDouble(const char *text) {
        return atof(text);
    }

    inline double StrToDouble(const wchar_t *text) {
#ifdef _TC_WINDOWS
        return _wtof(text);
#else
        int offset = StrLength(text);
        return wcstof(text, (wchar_t **) (&(text[offset])));
#endif
    }

    inline long long StrToLongLong(const char *text) {
        return atoll(text);
    }

    inline long long StrToLongLong(const wchar_t *text) {
#ifdef _TC_WINDOWS
        return _wtoll(text);
#else
        int offset = StrLength(text);
        return wcstoll(text, (wchar_t **) (&(text[offset])), 0);
#endif
    }

    template<typename TCHAR, typename TS, typename ITER>
    class IString {
    public:
        IString() = default;

        virtual ~IString() = default;

        IString(const TCHAR *text) : _s(text) {}

        IString(const IString &str) : _s(str._s) {}

        IString(IString &&str) : _s(std::move(str._s)) {}

        IString(const TS &s) : _s(s) {}

        IString(TS &&s) : _s(std::move(s)) {}

        IString &operator=(const IString &str) {
            if (this != &str) {
                _s = str._s;
            }
            return *this;
        }

        IString &operator=(IString &&str) {
            if (this != &str) {
                _s = std::move(str._s);
            }
            return *this;
        }

        IString &operator=(const TS &s) {
            _s = s;
            return *this;
        }

        IString &operator=(TS &&s) {
            _s = std::move(s);
            return *this;
        }

        IString &operator=(const TCHAR *text) {
            _s = text;
            return *this;
        }

        bool operator==(const IString &str) const {
            if (this != &str) {
                return _s == str._s;
            }
            return true;
        }

        bool operator==(const TS &s) const {
            return _s == s;
        }

        bool operator==(const TCHAR *text) const {
            return _s == text;
        }

        bool operator!=(const IString &str) const {
            return !(*this == str);
        }

        bool operator!=(const TCHAR *text) const {
            return !(*this == text);
        }

        bool operator!=(const TS &s) const {
            return !(*this == s);
        }

        IString &operator+=(const IString &str) {
            _s += str._s;
            return *this;
        }

        IString &operator+=(const TS &s) {
            _s += s;
            return *this;
        }

        IString &operator+=(const TCHAR *text) {
            _s += text;
            return *this;
        }

        TCHAR &operator[](size_t index) {
            return _s[index];
        }

        TCHAR operator[](size_t index) const {
            return _s[index];
        }

        const TCHAR *Data() const {
            return _s.data();
        }

        size_t Length() const {
            return _s.length();
        }

        void SetCapacity(size_t capacity) {
            _s.reserve(capacity);
        }

        bool Empty() const {
            return _s.empty();
        }

        bool HasText() const {
            return !Empty();
        }

        ITER begin() {
            return _s.begin();
        }

        ITER end() {
            return _s.end();
        }

        ITER begin() const {
            return _s.begin();
        }

        ITER end() const {
            return _s.end();
        }

        static IString Format(const TCHAR *format, ...) {
            va_list args;
            va_start(args, format);
            IString result = FormatFromList(format, args);
            va_end(args);
            return std::move(result);
        }

        static IString FormatFromList(const TCHAR *format, va_list list) {
            int res = _VSNPrintf(nullptr, 0, format, list);
            TS formatted;
            if (res > 0) {
                auto size = (size_t) res;
                formatted.resize(size);
                vsnprintf(&formatted[0], size + 1, format, list);
            }
            return IString<TCHAR, TS, ITER>(std::move(formatted));
        }

        static IString GetEmpty() {
            return IString();
        }

        int IndexOf(TCHAR value) const {
            return _s.find_first_of(value);
        }

        int IndexOf(TCHAR value, size_t startIndex) const {
            return _s.find_first_of(value, startIndex);
        }

        int IndexOf(const IString &value) const {
            return IndexOf(value.Data());
        }

        int IndexOf(const TCHAR *text) const {
            return _s.find_first_of(text);
        }

        int IndexOf(const IString &value, size_t startIndex) const {
            return IndexOf(value.Data(), startIndex);
        }

        int IndexOf(const TCHAR *text, size_t startIndex) const {
            return _s.find_first_of(text, startIndex);
        }

        int IndexOf(const IString &value, size_t startIndex, size_t count) const {
            return IndexOf(value.Data(), startIndex, count);
        }

        int IndexOf(const TCHAR *text, size_t startIndex, size_t count) const {
            return _s.find_first_of(text, startIndex, count);
        }

        int LastIndexOf(TCHAR value) const {
            return _s.find_last_of(value);
        }

        int LastIndexOf(TCHAR value, size_t startIndex) const {
            return _s.find_last_of(value, startIndex);
        }

        int LastIndexOf(const IString &value) const {
            return LastIndexOf(value.Data());
        }

        int LastIndexOf(const TCHAR *text) const {
            return _s.find_last_of(text);
        }

        int LastIndexOf(const IString &value, size_t startIndex) const {
            return LastIndexOf(value.Data(), startIndex);
        }

        int LastIndexOf(const TCHAR *text, size_t startIndex) const {
            return _s.find_last_of(text, startIndex);
        }

        int LastIndexOf(const IString &value, size_t startIndex, size_t count) const {
            return LastIndexOf(value.Data(), startIndex, count);
        }

        int LastIndexOf(const TCHAR *text, size_t startIndex, size_t count) const {
            return _s.find_last_of(text, startIndex, count);
        }

        IString SubString(size_t startIndex) const {
            return _s.substr(startIndex);
        }

        IString SubString(size_t startIndex, size_t count) const {
            return _s.substr(startIndex, count);
        }

        IString ToUpper() const {
            TS s = _s;
            for (auto &c : s) c = (TCHAR) toupper(c);
            return IString(std::move(s));
        }

        IString ToLower() const {
            TS s = _s;
            for (auto &c : s) c = (TCHAR) tolower(c);
            return IString(std::move(s));
        }

        bool EndsWith(TCHAR value) const {
            return (Length() > 0 && _s[Length() - 1] == value);
        }

        bool StartsWith(const IString &value, bool ignoreCase = false) const {
            return StartsWith(value.Data(), ignoreCase);
        }

        bool StartsWith(const TCHAR *text, bool ignoreCase = false) const {
            size_t valueLength = StrLength(text);
            if (Length() >= valueLength) {
                for (size_t i = 0; i < valueLength; i++) {
                    TCHAR c1 = _s[i];
                    TCHAR c2 = text[i];
                    if (ignoreCase) {
                        c1 = (TCHAR) toupper(c1);
                        c2 = (TCHAR) toupper(c2);
                    }
                    if (c1 != c2) return false;
                }
                return true;
            }
            return false;
        }

        bool EndsWith(const IString &value, bool ignoreCase = false) const {
            return EndsWith(value.Data(), ignoreCase);
        }

        bool EndsWith(const TCHAR *text, bool ignoreCase = false) const {
            size_t valueLength = StrLength(text);
            if (Length() >= valueLength) {
                for (size_t i = 0, j = Length() - valueLength;
                     i < valueLength; i++, j++) {
                    TCHAR c1 = _s[j];
                    TCHAR c2 = text[i];
                    if (ignoreCase) {
                        c1 = (TCHAR) toupper(c1);
                        c2 = (TCHAR) toupper(c2);
                    }
                    if (c1 != c2) return false;
                }
                return true;
            }
            return false;
        }

        static int ToInt(const TCHAR *text) {
            return StrToInt(text);
        }

        static double ToDouble(const TCHAR *text) {
            return StrToDouble(text);
        }

        static long long ToLongLong(const TCHAR *text) {
            return StrToLongLong(text);
        }

        int ToInt() const {
            return ToInt(Data());
        }

        double ToDouble() const {
            return ToDouble(Data());
        }

        long long ToLongLong() const {
            return ToLongLong(Data());
        }

        IString Replace(const IString &oldStr, const IString &newStr) const {
            return Replace(oldStr.Data(), newStr.Data());
        }

        IString Replace(const TCHAR *oldStr, const TCHAR *newStr) const {
            TS s = _s;
            size_t oldLength = StrLength(oldStr);
            while (true) {
                typename TS::size_type pos(0);
                if ((pos = s.find(oldStr)) != TS::npos) {
                    s.replace(pos, oldLength, newStr);
                } else { break; }
            }
            return IString(std::move(s));
        }

        IString Replace(TCHAR oldChar, TCHAR newChar) const {
            TS s = _s;
            for (auto &c : s) {
                if (c == oldChar) c = newChar;
            }
            return IString(std::move(s));
        }

        std::vector<IString> Split(const TCHAR *separator) const {
            std::vector<IString> v;
            if (!Empty()) {
                int pos1 = 0, pos2 = 0;
                size_t sepLen = StrLength(separator);
                pos2 = IndexOf(separator);
                pos1 = 0;
                while (pos2 != -1) {
                    v.push_back(SubString(pos1, pos2 - pos1));
                    pos1 = pos2 + sepLen;
                    pos2 = IndexOf(separator, pos1);
                }
                if (pos1 != Length()) {
                    v.push_back(SubString(pos1));
                }
            }
            return std::move(v);
        }

        TS & StdStr() {
            return _s;
        }

        const TS & StdStr() const {
            return _s;
        }

    private:
        TS _s;
    };

    typedef IString<char, std::string, std::string::iterator> String;
    typedef IString<wchar_t, std::wstring, std::wstring::iterator> WString;

}