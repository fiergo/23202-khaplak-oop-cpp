#include <cstdint>
#include <string>
#include <cstring>

using namespace std;

class BitArray {
    unsigned char* bits;
    int sizeArray;

public:
    class Wrapper {
    private:
        int index;
        BitArray& array;
    public:
        Wrapper(int index, BitArray& array);
        operator bool() const;
        Wrapper& operator=(const Wrapper& another) const;
        Wrapper& operator=(bool value);
    };

    BitArray();
    ~BitArray();

    //Конструирует массив, хранящий заданное количество бит.
    //Первые sizeof(long) бит можно инициализровать с помощью параметра value
    explicit BitArray(int num_bits, unsigned long value = 0);
    BitArray(const BitArray& b);

    void PrintBitArray();
    void swap(BitArray& b);

    BitArray& operator=(const BitArray& b);

    void resize(int num_bits, bool value = false);
    //Очищает массив.
    void clear();
    //Добавляет новый бит в конец массива. В случае необходимости
    //происходит перераспределение памяти.
    void push_back(bool bit);
    BitArray& operator&=(const BitArray& b);
    BitArray& operator|=(const BitArray& b);
    BitArray& operator^=(const BitArray& b);

    //Битовый сдвиг с заполнением нулями.
    BitArray& operator<<=(int n);
    BitArray& operator>>=(int n);
    BitArray operator<<(int n) const;
    BitArray operator>>(int n) const;

    //Устанавливает бит с индексом n в значение val.
    BitArray& set(int n, bool val = true);
    //Заполняет массив истиной.
    BitArray& set();

    //Устанавливает бит с индексом n в значение false.
    BitArray& reset(int n);

    //Заполняет массив ложью.
    BitArray& reset();

    //true, если массив содержит истинный бит.
    bool any() const;
    //true, если все биты массива ложны.
    bool none() const;
    //Битовая инверсия
    BitArray operator~() const;
    //Подсчитывает количество единичных бит.
    int count() const;

    //Возвращает значение бита по индексу i.
    bool operator[](int n) const;
    Wrapper operator[] (int n);
    int size() const;
    bool empty() const;

    //Возвращает строковое представление массива.
    string to_string() const;

    friend BitArray operator&(const BitArray& b1, const BitArray& b2);
    friend BitArray operator|(const BitArray& b1, const BitArray& b2);
    friend BitArray operator^(const BitArray& b1, const BitArray& b2);
    friend bool operator==(const BitArray& a, const BitArray& b);
    friend bool operator!=(const BitArray& a, const BitArray& b);
};
