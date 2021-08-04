#pragma once

#include "TCUtils.h"

namespace Tce {

    template <typename TKEY, typename TVALUE>
    class Dictionary {
    public:
        void Add(const TKEY& key, const TVALUE& value) {
            _map.insert(std::pair<TKEY, TVALUE>(key, value));
        }
        void EmAdd(const TKEY& key, TVALUE&& value) {
            _map.insert(std::pair<TKEY, TVALUE>(key, std::move(value)));
        }
        size_t Count() const {
            return _map.size();
        }
        bool Empty() const {
            return _map.empty();
        }
        void Clear() {
            _map.clear();
        }
        void FreeMemory() {
            std::unordered_map<TKEY, TVALUE> temp;
            _map.swap(temp);
        }
        bool ContainsKey(const TKEY& key) const {
            return !(_map.find(key) == _map.end());
        }
        void Remove(const TKEY& key) {
            _map.erase(key);
        }
        const TVALUE * TryGetValue(const TKEY& key) const {
            auto it = _map.find(key);
            if (it != _map.end()) return &it->second;
            return nullptr;
        }
        TVALUE * TryGetValue(const TKEY& key) {
            auto it = _map.find(key);
            if (it != _map.end()) return &it->second;
            return nullptr;
        }
        TVALUE & GetValue(const TKEY& key) {
            TVALUE *p = TryGetValue(key);
            _CheckResultValid(p);
            return *p;
        }
        const TVALUE & GetValue(const TKEY& key) const {
            const TVALUE *p = TryGetValue(key);
            _CheckResultValid(p);
            return *p;
        }
        typename std::unordered_map<TKEY, TVALUE>::iterator begin() const {
            return _map.begin();
        }
        typename std::unordered_map<TKEY, TVALUE>::iterator end() const {
            return _map.end();
        }
        typename std::unordered_map<TKEY, TVALUE>::iterator begin() {
            return _map.begin();
        }
        typename std::unordered_map<TKEY, TVALUE>::iterator end() {
            return _map.end();
        }
    private:
        void _CheckResultValid(TVALUE * p) {
            if (p == nullptr) {
                throw std::runtime_error(String::Format("Cannot get key from dictionary.").Data());
            }
        }
    private:
        std::unordered_map<TKEY, TVALUE> _map;
    };

}