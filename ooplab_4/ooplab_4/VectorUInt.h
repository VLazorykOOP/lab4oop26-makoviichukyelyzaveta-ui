#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>

class VectorUInt {
private:
    unsigned int* data;
    int size;
    mutable int codeError;

    static int objectCount; // тільки оголошення, БЕЗ визначення

public:
    enum ErrorCode {
        OK = 0,
        ERR_NO_MEM,
        ERR_OUT_OF_RANGE,
        ERR_SIZE_MISMATCH
    };

    // ── Конструктори / деструктор ──────────────────────────
    VectorUInt();
    VectorUInt(int n);
    VectorUInt(int n, unsigned int val);
    VectorUInt(const VectorUInt& other);
    ~VectorUInt();

    // ── Присвоєння ─────────────────────────────────────────
    VectorUInt& operator=(const VectorUInt& rhs);

    // ── Унарні ────────────────────────────────────────────
    VectorUInt& operator++();
    VectorUInt  operator++(int);
    VectorUInt& operator--();
    VectorUInt  operator--(int);

    bool       operator!()  const;
    VectorUInt operator~()  const;
    VectorUInt operator-()  const;

    // ── Присвоєння з операціями ───────────────────────────
    VectorUInt& operator+=(const VectorUInt& rhs);
    VectorUInt& operator-=(const VectorUInt& rhs);
    VectorUInt& operator*=(unsigned int val);
    VectorUInt& operator/=(unsigned int val);
    VectorUInt& operator%=(unsigned int val);
    VectorUInt& operator|=(const VectorUInt& rhs);
    VectorUInt& operator^=(const VectorUInt& rhs);
    VectorUInt& operator&=(const VectorUInt& rhs);

    // ── Індексація ────────────────────────────────────────
    unsigned int& operator[](int i);
    unsigned int  operator[](int i) const;

    // ── Виклик функції ────────────────────────────────────
    unsigned int operator()()             const;
    unsigned int operator()(int i, int j) const;

    // ── Перевантаження new / delete ───────────────────────
    void* operator new(size_t sz);
    void  operator delete(void* ptr);
    void* operator new[](size_t sz);
    void  operator delete[](void* ptr);

    // ── Статичний лічильник ───────────────────────────────
    static int getObjectCount();
    int getError() const { return codeError; }
    void clearError() { codeError = OK; }

    // ── Дружні функції ────────────────────────────────────
    friend VectorUInt operator+(const VectorUInt& a, const VectorUInt& b);
    friend VectorUInt operator-(const VectorUInt& a, const VectorUInt& b);
    friend VectorUInt operator*(const VectorUInt& v, unsigned int x);
    friend VectorUInt operator*(unsigned int x, const VectorUInt& v); //  симетричне
    friend VectorUInt operator/(const VectorUInt& v, unsigned int x);
    friend VectorUInt operator%(const VectorUInt& v, unsigned int x);

    friend VectorUInt operator|(const VectorUInt& a, const VectorUInt& b);
    friend VectorUInt operator^(const VectorUInt& a, const VectorUInt& b);
    friend VectorUInt operator&(const VectorUInt& a, const VectorUInt& b);

    // ✅ побітові зсуви елементів
    friend VectorUInt operator>>(const VectorUInt& v, int shift);
    friend VectorUInt operator<<(const VectorUInt& v, int shift);

    // потокове введення/виведення
    friend std::ostream& operator<<(std::ostream& os, const VectorUInt& v);
    friend std::istream& operator>>(std::istream& is, VectorUInt& v);

    friend bool operator==(const VectorUInt& a, const VectorUInt& b);
    friend bool operator!=(const VectorUInt& a, const VectorUInt& b);
    friend bool operator> (const VectorUInt& a, const VectorUInt& b);
    friend bool operator< (const VectorUInt& a, const VectorUInt& b);
    friend bool operator>=(const VectorUInt& a, const VectorUInt& b);
    friend bool operator<=(const VectorUInt& a, const VectorUInt& b);
};