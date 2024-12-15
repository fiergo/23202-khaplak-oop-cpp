#include "BitArray.h"

Container::Container(unsigned int value) {
    this->value = value;
    lastIndex = 0;
    next = nullptr;
}

Container& Container::operator=(bool bit) {
    if (bit) {
        this->value |= (1 << (BITS_COUNT - lastIndex % BITS_COUNT - 1));
    }
    else {
        this->value &= ~(1 << (BITS_COUNT - lastIndex % BITS_COUNT - 1));
    }
    return *this;
}

Container::operator bool() const {
    return (this->value & (1 << (BITS_COUNT - lastIndex % BITS_COUNT - 1))) != 0;
}

BitArray::BitArray() {
    basePtr = nullptr;
    endPtr = nullptr;
    numBits = 0;
}

BitArray::~BitArray() {
    clear();
}

BitArray::BitArray(int numBits, unsigned long value) {
    this->numBits = -1;
    basePtr = nullptr;
    endPtr = nullptr;
    resize(numBits, value);
}

BitArray::BitArray(const BitArray& b) {
    *this = BitArray(b.numBits, false);
    Container* curPtrBitArray = (*this).basePtr;
    Container* curPtrBitArrayToCopy = b.basePtr;
    while (curPtrBitArrayToCopy) {
        curPtrBitArray->value = curPtrBitArrayToCopy->value;
        curPtrBitArray = curPtrBitArray->next;
        curPtrBitArrayToCopy = curPtrBitArrayToCopy->next;
    }
}

void BitArray::swap(BitArray& b) {
    int size = (*this).size() <= b.size() ? (*this).size() : b.size();
    for (int i = 0; i < size; i++) {
        bool a = b[i];
        b.set(i, (*this)[i]);
        set(i, a);
    }
}

BitArray& BitArray::operator=(const BitArray& b) {
    int size = b.size();
    resize(size);
    for (int i = 0; i < size; i++) {
        set(i, b[i]);
    }
    return (*this);
}

void BitArray::resize(int newNumBits, bool value) {
    // Check if bits amount is the same.
    if (newNumBits == this->numBits)
        return;
    // Check if we should not change bit array memory Containers.
    if ((newNumBits / BITS_COUNT == this->numBits / BITS_COUNT) && this->numBits != -1) {
        this->numBits = newNumBits;
        return;
    }
    // Check if we should delete bit array memory Containers.
    if (newNumBits < this->numBits) {
        Container* ContainersToDelete = basePtr;
        Container* prev = ContainersToDelete;
        for (int i = 0; i < alignBits(newNumBits) / BITS_COUNT; i++) {
            prev = ContainersToDelete;
            ContainersToDelete = ContainersToDelete->next;
        }
        endPtr = prev;
        endPtr->next = nullptr;
        do {
            Container* ContainerToDelete = ContainersToDelete;
            ContainersToDelete = ContainersToDelete->next;
            delete(ContainerToDelete);
        } while (ContainersToDelete);
        this->numBits = newNumBits;
        return;
    }
    // Check for value input.
    unsigned int byteValue;
    if (!value)
        byteValue = FALSE_CONTAINER;
    else
        byteValue = TRUE_CONTAINER;
    // Add more bit array memory Containers.
    int i = 0;
    if (!basePtr) {
        basePtr = new Container(byteValue);
        endPtr = basePtr;
        i++;
    }
    for (; i < alignBits(newNumBits) / BITS_COUNT - alignBits(this->numBits) / BITS_COUNT; i++) {
        auto* newContainer = new Container(byteValue);
        endPtr->next = newContainer;
        endPtr = newContainer;
    }
    this->numBits = newNumBits;
}

void BitArray::clear() {
    resize(0);
}

void BitArray::push_back(bool bit) {
    int numBitsCopy = numBits;
    resize(numBits + 1);
    set(numBitsCopy, bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (size() != b.size() || b.empty() || empty()) {
        return *this;
    }
    for (int i = 0; i < b.size(); i++) {
        set(i, (*this)[i] && b[i]);
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (size() != b.size() || b.empty() || empty()) {
        return *this;
    }
    for (int i = 0; i < b.size(); i++) {
        set(i, (*this)[i] || b[i]);
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (size() != b.size() || b.empty() || empty()) {
        return *this;
    }
    for (int i = 0; i < b.size(); i++) {
        set(i, (*this)[i] ^ b[i]);
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n == 0 || (*this).empty()) {
        return *this;
    }
    if (n < 0) {
        return (*this) >>= (-1) * n;
    }
    n %= numBits;
    for (int i = n; i < numBits; i++) {
        set(i - n, (*this)[i]);
        set(i, false);
    }
    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n == 0 || (*this).empty()) {
        return *this;
    }
    if (n < 0) {
        return (*this) <<= (-1) * n;
    }
    n %= numBits;
    for (int i = numBits - n; i > 0; i--) {
        set(i + n, (*this)[i]);
        set(i, false);
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray bitArray = BitArray(*this);
    bitArray <<= n;
    return bitArray;
}

BitArray BitArray::operator>>(int n) const {
    BitArray bitArray = BitArray(*this);
    bitArray >>= n;
    return bitArray;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= numBits) {
        return *this;
    }
    int positionInBitArray = n / BITS_COUNT;
    if (val) {
        (*getContainer(positionInBitArray)).value = (*getContainer(positionInBitArray)).value | getTrueMask(n % BITS_COUNT);
    }
    else {
        (*getContainer(positionInBitArray)).value = (*getContainer(positionInBitArray)).value & getFalseMask(n % BITS_COUNT);
    }
    getContainer(positionInBitArray)->lastIndex = n % 8;
    return *this;
}

BitArray& BitArray::set() {
    Container* positionPtr = basePtr;
    while(positionPtr) {
        positionPtr->value = TRUE_CONTAINER;
        positionPtr = positionPtr->next;
    }
    return *this;
}

BitArray& BitArray::reset(int n) {
    set(n, false);
    return *this;
}

BitArray& BitArray::reset() {
    Container* positionPtr = basePtr;
    while (positionPtr) {
        positionPtr->value = FALSE_CONTAINER;
        positionPtr = positionPtr->next;
    }
    return *this;
}

bool BitArray::any() const {
    bool flag = false;
    for (int i = 0; i < numBits; i++) {
        flag = (*this)[i];
        if (flag) {
            break;
        }
    }
    return flag;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray bitArray = BitArray(*this);
    for (int i = 0; i < bitArray.size(); i++) {
        if (bitArray[i]) {
            bitArray.set(i, false);
        }
        else {
            bitArray.set(i, true);
        }
    }
    return bitArray;
}

int BitArray::count() const {
    int res = 0;
    for (int i = 0; i < numBits; i++) {
        if ((*this)[i]) {
            res++;
        }
    }
    return res;
}

Container& BitArray::operator[](int i) {
    if (i >= numBits) {
        resize(i + 1, false);
    }
    else if (i < 0) {
        throw 1;
    }
    Container* Container = getContainer(i / BITS_COUNT);
    Container->lastIndex = i;
    return *Container;
}

int BitArray::size() const {
    return numBits;
}

bool BitArray::empty() const {
    return numBits == 0;
}

std::string BitArray::to_string() const {
    std::string res;
    for (int i = 0; i < numBits; i++) {
        int ind = (*this)[i] ? 1 : 0;
        res.push_back(ind + '0');
    }
    return res;
}

int BitArray::alignBits(int numBits) {
    if (numBits <= 0) {
        return 0;
    }
    if (numBits % BITS_COUNT == 0) {
        numBits += BITS_COUNT;
    }
    if (numBits % BITS_COUNT != 0) {
        numBits += (BITS_COUNT - numBits % BITS_COUNT);
    }
    return numBits;
}

unsigned int BitArray::getTrueMask(int position) {
    unsigned int mask = FIRST_BYTE;
    return mask >> position;
}

unsigned int BitArray::getFalseMask(int position) const {
    return TRUE_CONTAINER - logPow(2, BITS_COUNT - 1 - position);
}

Container* BitArray::getContainer(int position) const{
    Container* positionPtr = basePtr;
    for (int i = 0; i < position; i++) {
        positionPtr = positionPtr->next;
    }
    return positionPtr;
}

unsigned int BitArray::logPow(int num, int pow) const {
    if (pow == 0) {
        return 1;
    }
    if (pow == 1) {
        return num;
    }
    if (pow % 2 == 0) {
        return logPow(num * num, pow / 2);
    }
    return logPow(num, pow - 1) * num;
}

bool BitArray::operator[](int i) const {
    Container* Container = getContainer(i / BITS_COUNT);
    Container->lastIndex = i;
    return *Container;
}

int BitArray::getContainerAmount() const {
    Container* positionPtr = basePtr;
    int count = 0;
    while (positionPtr) {
        count++;
        positionPtr = positionPtr->next;
    }
    return count;
}

bool operator==(const BitArray& a, const BitArray& b) {
    int sizeA = a.size();
    int sizeB = b.size();
    if (sizeA != sizeB) {
        return false;
    }
    for (int i = 0; i < sizeA; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray bitArray = BitArray(b1);
    bitArray &= b2;
    return bitArray;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray bitArray = BitArray(b1);
    bitArray |= b2;
    return bitArray;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray bitArray = BitArray(b1);
    bitArray ^= b2;
    return bitArray;
}