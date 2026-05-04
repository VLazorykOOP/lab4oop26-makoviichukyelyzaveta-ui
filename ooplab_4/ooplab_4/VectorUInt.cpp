#include "VectorUInt.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>   // Необхідно для std::memcpy
#include <iostream>

// Визначення статичного члена
int VectorUInt::objectCount = 0;

// ═══════════════════════════════════════════════════════════
//  Конструктори / деструктор
// ═══════════════════════════════════════════════════════════

VectorUInt::VectorUInt() : size(1), codeError(OK) {
    data = new(std::nothrow) unsigned int[1] {0};
    if (!data) {
        size = 0;
        codeError = ERR_NO_MEM;
    }
    else {
        objectCount++;
    }
}

VectorUInt::VectorUInt(int n) : size(n > 0 ? n : 1), codeError(OK) {
    data = new(std::nothrow) unsigned int[size]();
    if (!data) {
        size = 0;
        codeError = ERR_NO_MEM;
    }
    else {
        objectCount++;
    }
}

VectorUInt::VectorUInt(int n, unsigned int val) : size(n > 0 ? n : 1), codeError(OK) {
    data = new(std::nothrow) unsigned int[size];
    if (!data) {
        size = 0;
        codeError = ERR_NO_MEM;
        return; // КРИТИЧНО: виходимо, щоб не було NULL pointer dereference у циклі нижче
    }
    for (int i = 0; i < size; i++) data[i] = val;
    objectCount++;
}

VectorUInt::VectorUInt(const VectorUInt& other) : size(other.size), codeError(other.codeError) {
    data = new(std::nothrow) unsigned int[size];
    if (!data) {
        size = 0;
        codeError = ERR_NO_MEM;
    }
    else {
        // Копіюємо дані тільки якщо пам'ять виділена
        std::memcpy(data, other.data, size * sizeof(unsigned int));
        objectCount++;
    }
}

VectorUInt::~VectorUInt() {
    if (data) {
        delete[] data;
        objectCount--; // Зменшуємо лічильник тільки якщо об'єкт був реально створений
    }
}

// ═══════════════════════════════════════════════════════════
//  Присвоєння =
// ═══════════════════════════════════════════════════════════

VectorUInt& VectorUInt::operator=(const VectorUInt& rhs) {
    if (this == &rhs) return *this;

    delete[] data; // Видаляємо стару пам'ять

    size = rhs.size;
    codeError = rhs.codeError;
    data = new(std::nothrow) unsigned int[size];

    if (!data) {
        size = 0;
        codeError = ERR_NO_MEM;
    }
    else {
        std::memcpy(data, rhs.data, size * sizeof(unsigned int));
    }
    return *this;
}

// ═══════════════════════════════════════════════════════════
//  Унарні оператори
// ═══════════════════════════════════════════════════════════

VectorUInt& VectorUInt::operator++() {
    if (data) {
        for (int i = 0; i < size; i++) data[i]++;
    }
    return *this;
}

VectorUInt VectorUInt::operator++(int) {
    VectorUInt tmp(*this);
    ++(*this);
    return tmp;
}

VectorUInt& VectorUInt::operator--() {
    if (data) {
        for (int i = 0; i < size; i++) data[i]--;
    }
    return *this;
}

VectorUInt VectorUInt::operator--(int) {
    VectorUInt tmp(*this);
    --(*this);
    return tmp;
}

// Перевірка чи вектор НЕ порожній
bool VectorUInt::operator!() const {
    return (size == 0 || data == nullptr);
}

VectorUInt VectorUInt::operator~() const {
    VectorUInt res(size);
    if (res.data && data) {
        for (int i = 0; i < size; i++) res.data[i] = ~data[i];
    }
    return res;
}

VectorUInt VectorUInt::operator-() const {
    VectorUInt res(size);
    if (res.data && data) {
        for (int i = 0; i < size; i++) {
            res.data[i] = static_cast<unsigned int>(-static_cast<int>(data[i]));
        }
    }
    return res;
}

// ═══════════════════════════════════════════════════════════
//  Присвоєння з операціями
// ═══════════════════════════════════════════════════════════

VectorUInt& VectorUInt::operator+=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    if (data && rhs.data) {
        for (int i = 0; i < size; i++) data[i] += rhs.data[i];
    }
    return *this;
}

VectorUInt& VectorUInt::operator-=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    if (data && rhs.data) {
        for (int i = 0; i < size; i++) data[i] -= rhs.data[i];
    }
    return *this;
}

VectorUInt& VectorUInt::operator*=(unsigned int val) {
    if (data) for (int i = 0; i < size; i++) data[i] *= val;
    return *this;
}

VectorUInt& VectorUInt::operator/=(unsigned int val) {
    if (val == 0) { codeError = ERR_OUT_OF_RANGE; return *this; }
    if (data) for (int i = 0; i < size; i++) data[i] /= val;
    return *this;
}

VectorUInt& VectorUInt::operator%=(unsigned int val) {
    if (val == 0) { codeError = ERR_OUT_OF_RANGE; return *this; }
    if (data) for (int i = 0; i < size; i++) data[i] %= val;
    return *this;
}

VectorUInt& VectorUInt::operator|=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    if (data && rhs.data) for (int i = 0; i < size; i++) data[i] |= rhs.data[i];
    return *this;
}

VectorUInt& VectorUInt::operator^=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    if (data && rhs.data) for (int i = 0; i < size; i++) data[i] ^= rhs.data[i];
    return *this;
}

VectorUInt& VectorUInt::operator&=(const VectorUInt& rhs) {
    if (size != rhs.size) { codeError = ERR_SIZE_MISMATCH; return *this; }
    if (data && rhs.data) for (int i = 0; i < size; i++) data[i] &= rhs.data[i];
    return *this;
}

// ═══════════════════════════════════════════════════════════
//  Індексація
// ═══════════════════════════════════════════════════════════

unsigned int& VectorUInt::operator[](int i) {
    if (i < 0 || i >= size) {
        codeError = ERR_OUT_OF_RANGE;
        static unsigned int dummy = 0; // Для безпечного повернення при помилці
        return (data) ? data[size - 1] : dummy;
    }
    return data[i];
}

unsigned int VectorUInt::operator[](int i) const {
    if (i < 0 || i >= size) {
        codeError = ERR_OUT_OF_RANGE;
        return (data) ? data[size - 1] : 0;
    }
    return data[i];
}

// ═══════════════════════════════════════════════════════════
//  Виклик функції (оператор суми)
// ═══════════════════════════════════════════════════════════

unsigned int VectorUInt::operator()() const {
    unsigned int sum = 0;
    if (data) for (int i = 0; i < size; i++) sum += data[i];
    return sum;
}

unsigned int VectorUInt::operator()(int i, int j) const {
    if (i < 0) i = 0;
    if (j >= size) j = size - 1;
    unsigned int sum = 0;
    if (data) for (int k = i; k <= j; k++) sum += data[k];
    return sum;
}

// ═══════════════════════════════════════════════════════════
//  Перевантаження new / delete
// ═══════════════════════════════════════════════════════════

void* VectorUInt::operator new(size_t sz) {
    void* ptr = std::malloc(sz);
    if (!ptr) throw std::bad_alloc();
    return ptr;
}

void VectorUInt::operator delete(void* ptr) {
    std::free(ptr);
}

void* VectorUInt::operator new[](size_t sz) {
    void* ptr = std::malloc(sz);
    if (!ptr) throw std::bad_alloc();
    return ptr;
}

void VectorUInt::operator delete[](void* ptr) {
    std::free(ptr);
}

int VectorUInt::getObjectCount() {
    return objectCount;
}

// ═══════════════════════════════════════════════════════════
//  Дружні оператори
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

VectorUInt operator*(unsigned int x, const VectorUInt& v) {
    return v * x;
}

VectorUInt operator/(const VectorUInt& v, unsigned int x) {
    VectorUInt res(v); return res /= x;
}

VectorUInt operator%(const VectorUInt& v, unsigned int x) {
    VectorUInt res(v); return res %= x;
}

VectorUInt operator|(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res |= b;
}

VectorUInt operator^(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res ^= b;
}

VectorUInt operator&(const VectorUInt& a, const VectorUInt& b) {
    VectorUInt res(a); return res &= b;
}

VectorUInt operator>>(const VectorUInt& v, int shift) {
    VectorUInt res(v.size);
    if (res.data && v.data) {
        for (int i = 0; i < v.size; i++) res.data[i] = v.data[i] >> shift;
    }
    return res;
}

VectorUInt operator<<(const VectorUInt& v, int shift) {
    VectorUInt res(v.size);
    if (res.data && v.data) {
        for (int i = 0; i < v.size; i++) res.data[i] = v.data[i] << shift;
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const VectorUInt& v) {
    os << "[ ";
    if (v.data) {
        for (int i = 0; i < v.size; i++) os << v.data[i] << " ";
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, VectorUInt& v) {
    if (v.data) {
        for (int i = 0; i < v.size; i++) is >> v.data[i];
    }
    return is;
}

bool operator==(const VectorUInt& a, const VectorUInt& b) {
    if (a.size != b.size) return false;
    for (int i = 0; i < a.size; i++)
        if (a.data[i] != b.data[i]) return false;
    return true;
}

bool operator!=(const VectorUInt& a, const VectorUInt& b) {
    return !(a == b);
}

bool operator>(const VectorUInt& a, const VectorUInt& b) {
    int n = std::min(a.size, b.size);
    for (int i = 0; i < n; i++)
        if (a.data[i] != b.data[i]) return a.data[i] > b.data[i];
    return a.size > b.size;
}

bool operator<(const VectorUInt& a, const VectorUInt& b) { return b > a; }
bool operator>=(const VectorUInt& a, const VectorUInt& b) { return !(a < b); }
bool operator<=(const VectorUInt& a, const VectorUInt& b) { return !(a > b); }