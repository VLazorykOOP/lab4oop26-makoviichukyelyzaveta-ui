#include "MatrixUInt.h"
#include <iostream>

// Ініціалізація статичного члена (обов'язково з нового рядка)
int MatrixUInt::num_matrix = 0;

// ================= КОНСТРУКТОРИ =================

MatrixUInt::MatrixUInt() : UIntArray(nullptr), n(0), size(0), codeError(OK) {
    num_matrix++;
}

MatrixUInt::MatrixUInt(int n_) : n(n_), size(n_), codeError(OK) {
    UIntArray = new VectorUInt[n];
    if (UIntArray) {
        for (int i = 0; i < n; i++) {
            UIntArray[i] = VectorUInt(n, 0);
            UIntArray[i][i] = 1; // створюємо одиничну матрицю
        }
    }
    else {
        codeError = ERR_NO_MEM;
    }
    num_matrix++;
}

MatrixUInt::MatrixUInt(int n_, int m_) : n(n_), size(m_), codeError(OK) {
    UIntArray = new VectorUInt[n];
    if (UIntArray) {
        for (int i = 0; i < n; i++)
            UIntArray[i] = VectorUInt(m_, 0);
    }
    else {
        codeError = ERR_NO_MEM;
    }
    num_matrix++;
}

MatrixUInt::MatrixUInt(int n_, int m_, unsigned int val) : n(n_), size(m_), codeError(OK) {
    UIntArray = new VectorUInt[n];
    if (UIntArray) {
        for (int i = 0; i < n; i++)
            UIntArray[i] = VectorUInt(m_, val);
    }
    else {
        codeError = ERR_NO_MEM;
    }
    num_matrix++;
}

MatrixUInt::MatrixUInt(const MatrixUInt& other) : n(other.n), size(other.size), codeError(other.codeError) {
    UIntArray = new VectorUInt[n];
    if (UIntArray) {
        for (int i = 0; i < n; i++)
            UIntArray[i] = other.UIntArray[i];
    }
    else {
        codeError = ERR_NO_MEM;
    }
    num_matrix++;
}

MatrixUInt::~MatrixUInt() {
    delete[] UIntArray;
    num_matrix--;
}

// ================= ДОСТУП =================

int MatrixUInt::getN() const { return n; }
int MatrixUInt::getSize() const { return size; }
int MatrixUInt::getError() const { return codeError; }

// ================= ПРИСВОЄННЯ =================

MatrixUInt& MatrixUInt::operator=(const MatrixUInt& rhs) {
    if (this == &rhs) return *this;

    delete[] UIntArray;

    n = rhs.n;
    size = rhs.size;
    codeError = rhs.codeError;

    UIntArray = new VectorUInt[n];
    if (UIntArray) {
        for (int i = 0; i < n; i++)
            UIntArray[i] = rhs.UIntArray[i];
    }
    return *this;
}

// ================= УНАРНІ =================

MatrixUInt& MatrixUInt::operator++() {
    if (UIntArray) {
        for (int i = 0; i < n; i++) ++UIntArray[i];
    }
    return *this;
}

MatrixUInt MatrixUInt::operator++(int) {
    MatrixUInt tmp(*this);
    ++(*this);
    return tmp;
}

MatrixUInt& MatrixUInt::operator--() {
    if (UIntArray) {
        for (int i = 0; i < n; i++) --UIntArray[i];
    }
    return *this;
}

MatrixUInt MatrixUInt::operator--(int) {
    MatrixUInt tmp(*this);
    --(*this);
    return tmp;
}

bool MatrixUInt::operator!() const {
    return (n == 0 || size == 0 || UIntArray == nullptr);
}

// ================= АРИФМЕТИКА =================

MatrixUInt& MatrixUInt::operator+=(const MatrixUInt& rhs) {
    if (n != rhs.n || size != rhs.size) {
        codeError = ERR_SIZE_MISMATCH;
        return *this;
    }
    if (UIntArray && rhs.UIntArray) {
        for (int i = 0; i < n; i++)
            UIntArray[i] += rhs.UIntArray[i];
    }
    return *this;
}

MatrixUInt& MatrixUInt::operator*=(unsigned int val) {
    if (UIntArray) {
        for (int i = 0; i < n; i++)
            UIntArray[i] *= val;
    }
    return *this;
}

// ================= ІНДЕКС =================

VectorUInt& MatrixUInt::operator[](int i) {
    if (i < 0 || i >= n) {
        codeError = ERR_OUT_OF_RANGE;
        return UIntArray[0]; // Повертаємо перший рядок як страховку
    }
    return UIntArray[i];
}

const VectorUInt& MatrixUInt::operator[](int i) const {
    return UIntArray[i];
}

// ================= ВИКЛИК =================

unsigned int MatrixUInt::operator()() const {
    unsigned int sum = 0;
    if (UIntArray) {
        for (int i = 0; i < n; i++)
            sum += UIntArray[i]();
    }
    return sum;
}

// ================= ДРУЖНІ ТА ІНШІ =================

std::ostream& operator<<(std::ostream& os, const MatrixUInt& m) {
    if (m.UIntArray) {
        for (int i = 0; i < m.n; i++)
            os << m.UIntArray[i] << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, MatrixUInt& m) {
    if (m.UIntArray) {
        for (int i = 0; i < m.n; i++)
            is >> m.UIntArray[i];
    }
    return is;
}

int MatrixUInt::getCount() {
    return num_matrix;
}

// Приклад реалізації бінарного додавання
MatrixUInt operator+(const MatrixUInt& a, const MatrixUInt& b) {
    MatrixUInt res(a);
    res += b;
    return res;
}