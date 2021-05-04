
#include "RandomGenerator.h"
#include "Utils/Memory.h"

namespace Tce {

    inline size_t RandomGeneratorLiner::GetNext(size_t n) {
        if (n > 0xFFFF) {
            uint16_t r1 = _GetNextWord(n >> 16);
            uint16_t r2 = _GetNextWord(n & 0xFFFF);
            return (size_t)((r1 << 16) | r2);
        }
        else {
            return (size_t)_GetNextWord(n);
        }
    }

    inline uint16_t RandomGeneratorLiner::_GetNextWord(uint16_t n) {
        if (n != 0) {
            _seed = 1194211693L * _seed + 12345L;
            return (uint16_t) ((_seed >> 16) % n);
        }
        return 0;
    }

    inline size_t RandomGeneratorMT19937::GetNext(size_t n) {
        return (size_t)m_mtRand() % n;
    }

    inline RandomGenerator::RandomGenerator(EnumRandomGeneratorStrategy eStrategy, unsigned long seed) {
        switch (eStrategy) {
            case EnumRandomGeneratorStrategy::RGS_MT19937:
                mpStrategy = new RandomGeneratorMT19937(seed);
                break;
            default:        // in case
                mpStrategy = new RandomGeneratorLiner(seed);
                break;
        }
    }

    inline RandomGenerator::~RandomGenerator() {
        Memory::SafeDelete(mpStrategy);
    }

    inline size_t RandomGenerator::GetNext(size_t n) {
        if (n == 0) return 0;
        return mpStrategy->GetNext(n);
    }

    inline double RandomGenerator::GetNextDouble() {
        return GetNext(65535L) / double(65535L);
    }

    inline bool RandomGenerator::GetNextTry(size_t n) {
        return GetNext(n) == 0;
    }

    inline int RandomGenerator::GetNextArea(int begin, size_t n) {
        return begin + GetNext(n);
    }

    inline double RandomGenerator::GetNextDouble(double value) {
        return GetNextDouble() * value;
    }

    inline double RandomGenerator::GetNextDoubleArea(double begin, double len) {
        return begin + GetNextDouble(len);
    }

    inline double RandomGenerator::GetNextSym(double value) {
        return GetNextDouble(value * 2) - value;
    }

    inline uint8_t RandomGenerator::GetNextByte() {
        return (uint8_t)(GetNext(65535L) & 0xff);
    }
}