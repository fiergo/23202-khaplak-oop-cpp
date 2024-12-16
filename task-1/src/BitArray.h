#pragma once

#include <iostream>

const unsigned int FIRST_BYTE = 0x80000000;
const unsigned int TRUE_CONTAINER = 0xffffffff;
const unsigned int FALSE_CONTAINER = 0;
const int BITS_COUNT = sizeof(int) * 8;

class Container {
public:
    Container* next;
    unsigned int value;
    unsigned int lastIndex;
    explicit Container(unsigned int data);
    Container& operator=(bool value);
    operator bool() const;
};

class BitArray
{
private:
    // Указатель на первые 8 элементов (unsigned int)
    Container* basePtr{};

    // Указатель на последние 8 элементов (unsigned int)
    Container* endPtr{};

    // Количество битов в массиве
    int numBits{};

    // Выравнивание количества битов по числу, кратному 8
    static int alignBits(int numBits) ;

    // Возвращает битовую маску: true бит, установленный в позиции zero unsigned int
    static unsigned int getTrueMask(int position) ;

    // Возвращает битовую маску: zero бит, установленный в позиции true unsigned int
    unsigned int getFalseMask(int position) const;

    // Возвращает позицию контейнера в массиве
    Container* getContainer(int position) const;

    unsigned int logPow(int num, int pow) const;
public:
    BitArray();

    ~BitArray();

    explicit BitArray(int numBits, unsigned long value = 0);

    BitArray(const BitArray& b);

    void swap(BitArray& b);

    BitArray& operator=(const BitArray& b);

    void resize(int numBits, bool value = false);

    void clear();

    void push_back(bool bit);

    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    BitArray& set(int n, bool val = true);

    BitArray& set();

    BitArray& reset(int n);

    BitArray& reset();

    bool any() const;

    bool none() const;

    BitArray operator~() const;

    int count() const;

    Container& operator[](int i);
        
    bool operator[](int i) const;

    int size() const;

    bool empty() const;

    std::string to_string() const;

    int getContainerAmount() const;
};

bool operator==(const BitArray& a, const BitArray& b);
bool operator!=(const BitArray& a, const BitArray& b);

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);
