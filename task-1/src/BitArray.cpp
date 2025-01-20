#include "BitArray.h"

#include <iostream>

using namespace std;

BitArray::BitArray() : bits(nullptr), sizeArray(0) {}

BitArray::BitArray(int num_bits, unsigned long value) {
    if (num_bits < 0) {
        bits = nullptr;
        throw invalid_argument("Invalid argument");
    }
    sizeArray = num_bits;
    int sizeByte = (sizeArray + 7) / 8;
    bits = new unsigned char[sizeByte];
    memset(bits, 0, sizeByte);
    for (int i = 0; i < sizeof(long) * 8 && i < num_bits; ++i) {
        if (value & (1UL << i)) {
            set(i, true);
        }
    }
}

BitArray::BitArray(const BitArray& b) : sizeArray(b.sizeArray) {
    if (b.sizeArray < 0) {
        bits = nullptr;
        throw invalid_argument("Invalid argument");
    }
    int sizeByte = (sizeArray + 7) / 8;
    bits = new unsigned char[sizeByte];
    memcpy(bits, b.bits, sizeByte);
}

BitArray::~BitArray() {
    delete[] bits;
}

BitArray::Wrapper::Wrapper(int index, BitArray& array) : index(index), array(array) {}

BitArray::Wrapper::operator bool() const {
    return (array.bits[index / 8] & (1 << (index % 8))) != 0;
}

BitArray::Wrapper& BitArray::Wrapper::operator=(bool value) {
    if (index >= array.sizeArray) {
        throw out_of_range("index out of range");
    }
    if (value) {
        array.bits[index / 8] |= (1 << (index % 8));
    } else {
        array.bits[index / 8] &= ~(1 << (index % 8));
    }
    return *this;
}

BitArray::Wrapper& BitArray::Wrapper::operator=(const Wrapper& another) const {
    if (&array != &another.array) {
        throw invalid_argument("wrapper is not the same");
    }
    return *const_cast<Wrapper*>(&another);
}

void BitArray::PrintBitArray() {
    for (int i = 0; i < sizeArray; ++i) {
        cout << ((*this)[i] ? '1' : '0');
    }
    cout << endl;
}

void BitArray::swap(BitArray& b) {
    std::swap(this->sizeArray, b.sizeArray);
    std::swap(this->bits, b.bits);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (b.sizeArray < 0) {
        bits = nullptr;
        throw invalid_argument("Invalid argument");
    }
    if (this != &b) {
        delete[] bits;
        sizeArray = b.sizeArray;
        int sizeByte = (sizeArray + 7) / 8;
        bits = new unsigned char[sizeByte];
        memcpy(bits, b.bits, sizeByte);
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits < 0) {
        bits = nullptr;
        throw invalid_argument("Invalid argument");
    }

    if (num_bits == sizeArray) {
        return;
    }
    int sizeByte = (sizeArray + 7) / 8;
    auto* new_bits = new unsigned char[sizeByte];
    memcpy(new_bits, bits, min(sizeByte, (num_bits + 7) / 8));
    if (num_bits > sizeArray) {
        if (value) {
            for (int i = sizeArray; i < num_bits; ++i) {
                new_bits[i / 8] |= (1 << (i % 8));
            }
        }
    }
    delete[] bits;
    bits = new_bits;
    sizeArray = num_bits;
}

void BitArray::clear() {
    delete[] bits;
    bits = nullptr;
    sizeArray = 0;
}

void BitArray::push_back(bool bit) {
    resize(sizeArray + 1, bit);
    set(sizeArray - 1, bit);
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= sizeArray) {
        throw invalid_argument("Invalid argument");
    }
    if (val) {
        bits[n / 8] |= (1 << (n % 8));
    } else {
        bits[n / 8] &= ~(1 << (n % 8));
    }
    return *this;
}

BitArray& BitArray::set() {
    int sizeByte = (sizeArray + 7) / 8;
    memset(bits, 255, sizeByte);
    return *this;
}

BitArray& BitArray::reset(int n) {
    if (n < 0 || n >= sizeArray) {
        throw invalid_argument("Invalid argument");
    }
    bits[n / 8] &= ~(1 << (n % 8));
    return *this;
}

BitArray& BitArray::reset() {
    int sizeByte = (sizeArray + 7) / 8;
    memset(bits, 0, sizeByte);
    return *this;
}

bool BitArray::any() const {
    for (int i = 0; i < (sizeArray + 7) / 8; ++i) {
        if (bits[i]) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    for (int i = 0; i < (sizeArray + 7) / 8; ++i) {
        if (bits[i]) {
            return false;
        }
    }
    return true;
}

int BitArray::count() const {
    int counter = 0;
    for (int i = 0; i < sizeArray; ++i) {
        if ((*this)[i]) {
            counter++;
        }
    }
    return counter;
}

int BitArray::size() const {
    return sizeArray;
}

bool BitArray::empty() const {
    return sizeArray == 0;
}

string BitArray::to_string() const {
    string result(sizeArray, '0');
    for (int i = 0; i < sizeArray; ++i) {
        if ((*this)[i]) {
            result[i] = '1';
        }
    }
    return result;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (sizeArray != b.sizeArray) {
        throw invalid_argument("Invalid argument");
    }
    for (int i = 0; i < sizeArray; ++i) {
        bits[i] &= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (sizeArray != b.sizeArray) {
        throw invalid_argument("Wrong size");
    }
    for (int i = 0; i < sizeArray; ++i) {
        bits[i] |= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (sizeArray != b.sizeArray) {
        throw invalid_argument("Wrong size");
    }
    for (int i = 0; i < sizeArray; ++i) {
        bits[i] ^= b.bits[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw invalid_argument("Invalid argument");
    }
    if (n >= sizeArray) {
        reset();
        return *this;
    }
    for (int i = 0; i < sizeArray - n; ++i) {
        set(i, (*this)[i + n]);
    }
    for (int i = sizeArray - n; i < sizeArray; ++i) {
        reset(i);
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw invalid_argument("Negative shift");
    }
    if (n >= sizeArray) {
        reset();
        return *this;
    }
    for (int i = sizeArray - 1; i >= n; --i) {
        set(i, (*this)[i - n]);
    }
    for (int i = 0; i < n; ++i) {
        reset(i);
    }
    return *this;
}

BitArray BitArray::operator>>(int n) const {
    if (n < 0) {
        throw invalid_argument("Invalid argument");
    }
    BitArray temp(*this);
    temp >>= n;
    return temp;
}

BitArray BitArray::operator<<(int n) const {
    if (n < 0) {
        throw invalid_argument("Invalid argument");
    }
    BitArray temp(*this);
    temp <<= n;
    return temp;
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    int sizeByte = (sizeArray + 7) / 8;
    for (int i = 0; i < sizeByte; ++i) {
        result.bits[i] = ~result.bits[i];
    }

    return result;
}
bool BitArray::operator[](int n) const {
    if (n < 0 || n >= sizeArray) {
        throw invalid_argument("Wrong index");
    }
    return (bits[n / 8] >> (n % 8)) & 1;
}

BitArray::Wrapper BitArray::operator[](int n) {
    if (n < 0 || n >= sizeArray) {
        throw invalid_argument("Wrong index");
    }
    return Wrapper(n, *this);
}

bool operator==(const BitArray& a, const BitArray& b) {
    if (a.sizeArray != b.sizeArray) {
        throw invalid_argument("Invalid argument");
    }
    return memcmp(a.bits, b.bits, (a.sizeArray + 7) / 8) == 0;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& a, const BitArray& b) {
    if (a.sizeArray != b.sizeArray) {
        throw invalid_argument("Wrong size");
    }
    BitArray result(a);
    for (int i = 0; i < a.sizeArray; ++i) {
        result.bits[i] = a.bits[i] & b.bits[i];
    }
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b) {
    if (b1.sizeArray != b.sizeArray) {
        throw invalid_argument("Wrong size");
    }
    BitArray result(b1);
    for (int i = 0; i < b1.sizeArray; ++i) {
        result.bits[i] = b1.bits[i] | b.bits[i];
    }
    return result;
}

BitArray operator^(const BitArray& a, const BitArray& b) {
    if (a.sizeArray != b.sizeArray) {
        throw invalid_argument("Wrong size");
    }
    BitArray result(a);
    for (int i = 0; i < a.size(); ++i) {
        result.bits[i] = a.bits[i] ^ b.bits[i];
    }
    return result;
}
