#include "BankMap.h"
#include <algorithm>
#include <stdexcept>
// ── Визначення статичного лічильника ──────────────────────
int BankMap::objectCount = 0;

// ─────────────────────────────────────────────────────────
//  Приватний метод: розширення масиву
// ─────────────────────────────────────────────────────────
bool BankMap::resize(int newCap) {
    BankRecord* tmp = new(std::nothrow) BankRecord[newCap];
    if (!tmp) { codeError = ERR_NO_MEM; return false; }
    for (int i = 0; i < size; i++) tmp[i] = records[i];
    delete[] records;
    records = tmp;
    capacity = newCap;
    return true;
}

// ─────────────────────────────────────────────────────────
//  Конструктори / деструктор
// ─────────────────────────────────────────────────────────
BankMap::BankMap() : size(0), capacity(4), codeError(OK) {
    records = new(std::nothrow) BankRecord[capacity];
    if (!records) { capacity = 0; codeError = ERR_NO_MEM; }
    objectCount++;
}

BankMap::BankMap(int initCapacity)
    : size(0), capacity(initCapacity > 0 ? initCapacity : 4), codeError(OK)
{
    records = new(std::nothrow) BankRecord[capacity];
    if (!records) { capacity = 0; codeError = ERR_NO_MEM; }
    objectCount++;
}

BankMap::BankMap(const BankMap& other)
    : size(other.size), capacity(other.capacity), codeError(other.codeError)
{
    records = new(std::nothrow) BankRecord[capacity];
    if (!records) { size = 0; capacity = 0; codeError = ERR_NO_MEM; }
    else for (int i = 0; i < size; i++) records[i] = other.records[i];
    objectCount++;
}

BankMap::~BankMap() {
    delete[] records;
    objectCount--;
}

// ─────────────────────────────────────────────────────────
//  Присвоєння
// ─────────────────────────────────────────────────────────
BankMap& BankMap::operator=(const BankMap& rhs) {
    if (this == &rhs) return *this;
    delete[] records;
    size = rhs.size;
    capacity = rhs.capacity;
    codeError = rhs.codeError;
    records = new(std::nothrow) BankRecord[capacity];
    if (!records) { size = 0; capacity = 0; codeError = ERR_NO_MEM; }
    else for (int i = 0; i < size; i++) records[i] = rhs.records[i];
    return *this;
}

// ─────────────────────────────────────────────────────────
//  Додавання запису
// ─────────────────────────────────────────────────────────
bool BankMap::addRecord(const std::string& account, const std::string& fullName) {
    // перевірка дублікату
    for (int i = 0; i < size; i++) {
        if (records[i].account == account) {
            codeError = ERR_DUPLICATE;
            return false;
        }
    }
    // розширення якщо потрібно
    if (size == capacity) {
        if (!resize(capacity * 2)) return false;
    }
    records[size++] = BankRecord(account, fullName);
    return true;
}

// ─────────────────────────────────────────────────────────
//  Видалення
// ─────────────────────────────────────────────────────────
bool BankMap::removeByAccount(const std::string& account) {
    for (int i = 0; i < size; i++) {
        if (records[i].account == account) {
            for (int j = i; j < size - 1; j++) records[j] = records[j + 1];
            size--;
            return true;
        }
    }
    codeError = ERR_NOT_FOUND;
    return false;
}

bool BankMap::removeByName(const std::string& fullName) {
    for (int i = 0; i < size; i++) {
        if (records[i].fullName == fullName) {
            for (int j = i; j < size - 1; j++) records[j] = records[j + 1];
            size--;
            return true;
        }
    }
    codeError = ERR_NOT_FOUND;
    return false;
}

// ─────────────────────────────────────────────────────────
//  Пошук
// ─────────────────────────────────────────────────────────
std::string BankMap::findByAccount(const std::string& account) const {
    for (int i = 0; i < size; i++)
        if (records[i].account == account) return records[i].fullName;
    codeError = ERR_NOT_FOUND;
    return "";
}

std::string BankMap::findByName(const std::string& fullName) const {
    for (int i = 0; i < size; i++)
        if (records[i].fullName == fullName) return records[i].account;
    codeError = ERR_NOT_FOUND;
    return "";
}

// ─────────────────────────────────────────────────────────
//  operator[] — пошук за номером рахунку → ПІБ
// ─────────────────────────────────────────────────────────
std::string& BankMap::operator[](const std::string& account) {
    for (int i = 0; i < size; i++)
        if (records[i].account == account) return records[i].fullName;
    // не знайдено — додаємо порожній запис і повертаємо посилання
    codeError = ERR_NOT_FOUND;
    addRecord(account, "");
    return records[size - 1].fullName;
}

std::string BankMap::operator[](const std::string& account) const {
    for (int i = 0; i < size; i++)
        if (records[i].account == account) return records[i].fullName;
    codeError = ERR_NOT_FOUND;
    return "";
}

// ─────────────────────────────────────────────────────────
//  operator() — пошук за ПІБ → номер рахунку
// ─────────────────────────────────────────────────────────
std::string BankMap::operator()(const std::string& fullName) const {
    for (int i = 0; i < size; i++)
        if (records[i].fullName == fullName) return records[i].account;
    codeError = ERR_NOT_FOUND;
    return "";
}

// ─────────────────────────────────────────────────────────
//  Текст помилки
// ─────────────────────────────────────────────────────────
std::string BankMap::errorText() const {
    switch (codeError) {
    case OK:            return "OK";
    case ERR_NOT_FOUND: return "Запис не знайдено";
    case ERR_NO_MEM:    return "Не вистачає пам'яті";
    case ERR_DUPLICATE: return "Рахунок вже існує";
    default:            return "Невідома помилка";
    }
}

// ─────────────────────────────────────────────────────────
//  Виведення
// ─────────────────────────────────────────────────────────
void BankMap::print(std::ostream& os) const {
    os << "┌─────────────────────────────┬──────────────────────────────────┐\n";
    os << "│ Номер рахунку               │ ПІБ                              │\n";
    os << "├─────────────────────────────┼──────────────────────────────────┤\n";
    for (int i = 0; i < size; i++) {
        os << "│ ";
        // вирівнювання акаунту (27 символів)
        std::string acc = records[i].account;
        if ((int)acc.size() > 27) acc = acc.substr(0, 27);
        os << acc;
        for (int s = (int)acc.size(); s < 28; s++) os << ' ';
        os << "│ ";
        std::string nm = records[i].fullName;
        if ((int)nm.size() > 32) nm = nm.substr(0, 32);
        os << nm;
        for (int s = (int)nm.size(); s < 33; s++) os << ' ';
        os << "│\n";
    }
    os << "└─────────────────────────────┴──────────────────────────────────┘\n";
    os << "Записів: " << size << "\n";
}

// ─────────────────────────────────────────────────────────
//  Дружні оператори
// ─────────────────────────────────────────────────────────
std::ostream& operator<<(std::ostream& os, const BankMap& bm) {
    bm.print(os);
    return os;
}

std::istream& operator>>(std::istream& is, BankMap& bm) {
    int n;
    std::cout << "Скільки записів ввести? ";
    is >> n;
    is.ignore();
    for (int i = 0; i < n; i++) {
        std::string acc, name;
        std::cout << "  Рахунок " << (i + 1) << ": ";
        std::getline(is, acc);
        std::cout << "  ПІБ     " << (i + 1) << ": ";
        std::getline(is, name);
        if (!bm.addRecord(acc, name))
            std::cout << "  [!] " << bm.errorText() << "\n";
    }
    return is;
}