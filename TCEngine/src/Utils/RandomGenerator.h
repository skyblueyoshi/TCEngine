#pragma once

#include <cstdint>
#include <random>

namespace Tce {

    enum EnumRandomGeneratorStrategy {
        RGS_LINER,
        RGS_MT19937
    };

    class RandomGeneratorStrategy {
    protected:
        unsigned long _seed{};
    public:
        RandomGeneratorStrategy() = default;

        RandomGeneratorStrategy(unsigned long seed)
                : _seed(seed) {}

        // 返回0~n-1的随机整数
        virtual size_t GetNext(size_t n) = 0;
    };

    class RandomGeneratorLiner : public RandomGeneratorStrategy {
    public:
        RandomGeneratorLiner() = default;

        RandomGeneratorLiner(unsigned long seed)
                : RandomGeneratorStrategy(seed) {}

        size_t GetNext(size_t n);

    private:
        uint16_t _GetNextWord(uint16_t n);
    };

    class RandomGeneratorMT19937 : public RandomGeneratorStrategy {
    private:
        std::mt19937_64 m_mtRand;
    public:
        RandomGeneratorMT19937() = default;

        RandomGeneratorMT19937(unsigned long seed)
                : m_mtRand(seed) {}

        size_t GetNext(size_t n);
    };

    class RandomGenerator {
    private:
        RandomGeneratorStrategy *mpStrategy{nullptr};
    public:
        RandomGenerator(EnumRandomGeneratorStrategy eStrategy = RGS_LINER, unsigned long seed = 0);
        ~RandomGenerator();
        // 返回0~n-1的随机整数
        size_t GetNext(size_t n);

        // 返回随机字节
        uint8_t GetNextByte();

        // 返回[0,1)的随机小数
        bool GetNextTry(size_t n);

        // 返回[begin, begin+n)的随机整数
        int GetNextArea(int begin, size_t n);

        // 返回[0,1)的随机小数
        double GetNextDouble();

        // 返回[0,value)的随机小数
        double GetNextDouble(double value);

        // 返回[0,value)的随机小数
        double GetNextDoubleArea(double begin, double len);

        // 返回[-value,value)的随机小数
        double GetNextSym(double value);
    };

}

#include "RandomGenerator.inl"