#include "BitArray.h"

using namespace std;

int main() {
    BitArray a(8, 5);
    a[1] = true;
    a.PrintBitArray();
    return 0;
}