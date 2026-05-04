#include "VectorUInt.h"
#include <algorithm>
#include <stdexcept>

// Визначення статичного члена — ТІЛЬКИ у .cpp
int VectorUInt::objectCount = 0;

// ═══════════════════════════════════════════════════════════
//  Конструктори / деструктор
// ═══════════════════════════════════════════════════════════
VectorUInt::VectorUInt() : size(1), codeError(OK) {
    data = new(std::nothrow) unsigned int[1] {0};
    if (!data) { size = 0; codeError = ERR_NO_MEM; }
    objectCount++;
}

VectorUInt::VectorUInt(int n) : size(n > 0 ? n : 1), codeError(OK) {
    data = new(std::nothrow) unsigned int[size]();
    if (!data) { size = 0; codeError = ERR_NO_MEM; }
    objectCount++;
}

VectorUInt::VectorUInt(int n, unsigned int val) : size(n > 0 ? n : 1), codeError(OK) {
    data = new(std::nothrow) unsigned int[size];
    if (!data) { size = 0; codeError = ERR_NO_MEM; return; }
    for (int i = 0; i < size; i++) data[i] = val;
    objectCount++;
}

VectorUInt::VectorUInt(const VectorUInt& other) : size(other.size), codeError(other.codeError) {
    data = new(std::nothrow) unsigned int[size];
    if (!data) { size = 0; codeError = ERR_NO_MEM; }
    else std::memcpy(data, other.data, size * sizeof(unsigned int));
    objectCount++;
}

VectorUInt::~VectorUInt() {
    delete[] data;
    objectCount--;
}

// ═══════════════════════════════════════════════════════════
//  Присвоєння =
// ═══════════════════════════════════════════════════════════
VectorUInt& VectorUInt::operator=(const VectorUInt& rhs) {
    if (this == &rhs) return *this;
    delete[] data;
    size = rhs.size;
    codeError = rhs.codeError;
    data = new(std::nothrow) unsigned int[size];
    if (!data) { size = 0; codeError = ERR_NO_MEM; }
    else std::memcpy(data, rhs.data, size * sizeof(unsigned int));
    return *this;
}

// ═══════════════════════════════════════════════════════════
//  Унарні оператори
// ═══════════════════════════════════════════════════════════
VectorUInt& VectorUInt::operator++() {
    for (int i = 0; i < size; i++) data[i]++;
    return *this;
}
VectorUInt VectorUInt::operator++(int) {
    VectorUInt tmp(*this);
    ++(*this);
    return tmp;
}
VectorUInt& VectorUInt::operator--() {
    for (int i = 0; i < size; i++) data[i]--;
    return *this;
}
VectorUInt VectorUInt::operator--(int) {
    VectorUInt tmp(*this);
    --(*this);
    return tmp;
}

// ✅ ВИПРАВЛЕНО: true якщо size != 0 (вектор не порожній)
bool VectorUInt::operator!() const {
    return size != 0;
}

VectorUInt VectorUInt::operator~() const {
    VectorUInt res(size);
    for (int i = 0; i < size; i++) res.data[i] = ~data[i];
    return res;
}

VectorUInt VectorUInt::operator-() const {
    VectorUInt res(size);
    for (int i = 0; i < size; i++) res.data[i] = static_cast<unsigned int>(-static_cast<int>(data[i]));
    return res;
}

// ═══════════════════════════════════════════════════════════
//  Присвоєння з операціями
// ═══════════════════════════════════════════════════════════
VectorUInt& VectorUInt::operator+=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    for (int i = 0; i < size; i++) data[i] += rhs.data[i];
    return *this;
}
VectorUInt& VectorUInt::operator-=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    for (int i = 0; i < size; i++) data[i] -= rhs.data[i];
    return *this;
}
VectorUInt& VectorUInt::operator*=(unsigned int val) {
    for (int i = 0; i < size; i++) data[i] *= val;
    return *this;
}
VectorUInt& VectorUInt::operator/=(unsigned int val) {
    if (val == 0) { codeError = ERR_OUT_OF_RANGE; return *this; }
    for (int i = 0; i < size; i++) data[i] /= val;
    return *this;
}
VectorUInt& VectorUInt::operator%=(unsigned int val) {
    if (val == 0) { codeError = ERR_OUT_OF_RANGE; return *this; }
    for (int i = 0; i < size; i++) data[i] %= val;
    return *this;
}
VectorUInt& VectorUInt::operator|=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    for (int i = 0; i < size; i++) data[i] |= rhs.data[i];
    return *this;
}
VectorUInt& VectorUInt::operator^=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    for (int i = 0; i < size; i++) data[i] ^= rhs.data[i];
    return *this;
}
VectorUInt& VectorUInt::operator&=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    for (int i = 0; i < size; i++) data[i] &= rhs.data[i];
    return *this;
}

// ═══════════════════════════════════════════════════════════
//  Індексація
// ═══════════════════════════════════════════════════════════
unsigned int& VectorUInt::operator[](int i) {
    if (i < 0 || i >= size) {
        codeError = ERR_OUT_OF_RANGE;
        return data[size - 1];
    }
    return data[i];
}
unsigned int VectorUInt::operator[](int i) const {
    if (i < 0 || i >= size) {
        codeError = ERR_OUT_OF_RANGE;
        return data[size - 1];
    }
    return data[i];
}

// ═══════════════════════════════════════════════════════════
//  Виклик функції
// ═══════════════════════════════════════════════════════════
unsigned int VectorUInt::operator()() const {
    unsigned int sum = 0;
    for (int i = 0; i < size; i++) sum += data[i];
    return sum;
}
unsigned int VectorUInt::operator()(int i, int j) const {
    if (i < 0) i = 0;
    if (j >= size) j = size - 1;
    unsigned int sum = 0;
    for (int k = i; k <= j; k++) sum += data[k];
    return sum;
}

// ═══════════════════════════════════════════════════════════
//  Перевантаження new / delete  ✅
// ═══════════════════════════════════════════════════════════
void* VectorUInt::operator new(size_t sz) {
    void* ptr = std::malloc(sz);
    if (!ptr) throw std::bad_alloc();
    std::cout << "[new VectorUInt, " << sz << " байт]\n";
    return ptr;
}
void VectorUInt::operator delete(void* ptr) {
    std::cout << "[delete VectorUInt]\n";
    std::free(ptr);
}
void* VectorUInt::operator new[](size_t sz) {
    void* ptr = std::malloc(sz);
    if (!ptr) throw std::bad_alloc();
    std::cout << "[new[] VectorUInt, " << sz << " байт]\n";
    return ptr;
}
void VectorUInt::operator delete[](void* ptr) {
    std::cout << "[delete[] VectorUInt]\n";
    std::free(ptr);
}

// ═══════════════════════════════════════════════════════════
//  Статичний лічильник
// ═══════════════════════════════════════════════════════════
int VectorUInt::getObjectCount() {
    return objectCount;
}

// ═══════════════════════════════════════════════════════════
//  Бінарні арифметичні (дружні)
// ═══════════════════════════════════════════════════════════
VectorUInt operator+(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res += b;
}
VectorUInt operator-(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res -= b;
}
VectorUInt operator*(const VectorUInt& v, unsigned int x) {
    VectorUInt res(v); return res *= x;
}
// ✅ симетричне множення: 3u * v
VectorUInt operator*(unsigned int x, const VectorUInt& v) {
    return v * x;
}
VectorUInt operator/(const VectorUInt& v, unsigned int x) {
    VectorUInt res(v); return res /= x;
}
VectorUInt operator%(const VectorUInt& v, unsigned int x) {
    VectorUInt res(v); return res %= x;
}

// ═══════════════════════════════════════════════════════════
//  Бінарні побітові (дружні)
// ═══════════════════════════════════════════════════════════
VectorUInt operator|(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res |= b;
}
VectorUInt operator^(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res ^= b;
}
VectorUInt operator&(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res &= b;
}

// ═══════════════════════════════════════════════════════════
//  Побітові зсуви елементів (дружні) ✅
// ═══════════════════════════════════════════════════════════
VectorUInt operator>>(const VectorUInt& v, int shift) {
    VectorUInt res(v.size);
    for (int i = 0; i < v.size; i++) res.data[i] = v.data[i] >> shift;
    return res;
}
VectorUInt operator<<(const VectorUInt& v, int shift) {
    VectorUInt res(v.size);
    for (int i = 0; i < v.size; i++) res.data[i] = v.data[i] << shift;
    return res;
}

// ═══════════════════════════════════════════════════════════
//  Потокове введення / виведення (дружні)
// ═══════════════════════════════════════════════════════════
std::ostream& operator<<(std::ostream& os, const VectorUInt& v) {
    os << "[ ";
    for (int i = 0; i < v.size; i++) os << v.data[i] << " ";
    return os << "]";
}
std::istream& operator>>(std::istream& is, VectorUInt& v) {
    for (int i = 0; i < v.size; i++) is >> v.data[i];
    return is;
}

// ═══════════════════════════════════════════════════════════
//  Рівність / нерівність
// ═══════════════════════════════════════════════════════════
bool operator==(const VectorUInt& a, const VectorUInt& b) {
    if (a.size != b.size) return false;
    for (int i = 0; i < a.size; i++)
        if (a.data[i] != b.data[i]) return false;
    return true;
}
bool operator!=(const VectorUInt& a, const VectorUInt& b) {
    return !(a == b);
}

// ═══════════════════════════════════════════════════════════
//  Порівняння (лексикографічне)
// ═══════════════════════════════════════════════════════════
bool operator>(const VectorUInt& a, const VectorUInt& b) {
    int n = std::min(a.size, b.size);
    for (int i = 0; i < n; i++)
        if (a.data[i] != b.data[i]) return a.data[i] > b.data[i];
    return a.size > b.size;
}
bool operator<(const VectorUInt& a, const VectorUInt& b) { return b > a; }
bool operator>=(const VectorUInt& a, const VectorUInt& b) { return !(a < b); }
bool operator<=(const VectorUInt& a, const VectorUInt& b) { return !(a > b); }