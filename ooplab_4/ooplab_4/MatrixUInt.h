#pragma once
#include "VectorUInt.h"
#include <iostream>

class MatrixUInt {
protected:
    VectorUInt* UIntArray;
    int n, size; // n - рядки, size - стовпці
    int codeError;

    static int num_matrix;

public:
    enum ErrorCode {
        OK = 0,
        ERR_NO_MEM,
        ERR_OUT_OF_RANGE,
        ERR_SIZE_MISMATCH
    };

    // Конструктори
    MatrixUInt();
    MatrixUInt(int n); // одинична
    MatrixUInt(int n, int m);
    MatrixUInt(int n, int m, unsigned int val);
    MatrixUInt(const MatrixUInt& other);

    ~MatrixUInt();

    // Доступ
    int getN() const;
    int getSize() const;
    int getError() const;

    // Присвоєння
    MatrixUInt& operator=(const MatrixUInt& rhs);

    // Унарні
    MatrixUInt& operator++();
    MatrixUInt operator++(int);
    MatrixUInt& operator--();
    MatrixUInt operator--(int);

    bool operator!() const;
    MatrixUInt operator~() const;
    MatrixUInt operator-() const;

    // Арифметика
    MatrixUInt& operator+=(const MatrixUInt& rhs);
    MatrixUInt& operator+=(unsigned int val);

    MatrixUInt& operator-=(const MatrixUInt& rhs);
    MatrixUInt& operator-=(unsigned int val);

    MatrixUInt& operator*=(unsigned int val);
    MatrixUInt& operator/=(unsigned int val);
    MatrixUInt& operator%=(unsigned int val);

    // Індекс
    VectorUInt& operator[](int i);
    const VectorUInt& operator[](int i) const;

    // Виклик
    unsigned int operator()() const;

    // Друзі
    friend MatrixUInt operator+(const MatrixUInt&, const MatrixUInt&);
    friend MatrixUInt operator+(const MatrixUInt&, unsigned int);

    friend MatrixUInt operator-(const MatrixUInt&, const MatrixUInt&);
    friend MatrixUInt operator-(const MatrixUInt&, unsigned int);

    friend MatrixUInt operator*(const MatrixUInt&, unsigned int);
    friend MatrixUInt operator/(const MatrixUInt&, unsigned int);
    friend MatrixUInt operator%(const MatrixUInt&, unsigned int);

    friend std::ostream& operator<<(std::ostream&, const MatrixUInt&);
    friend std::istream& operator>>(std::istream&, MatrixUInt&);

    friend bool operator==(const MatrixUInt&, const MatrixUInt&);
    friend bool operator!=(const MatrixUInt&, const MatrixUInt&);

    static int getCount();
};