#pragma once
#include <iostream>
#include <string>

// ═══════════════════════════════════════════════════════════
//  Структура одного запису: рахунок ↔ ПІБ
// ═══════════════════════════════════════════════════════════
struct BankRecord {
    std::string account;   // номер рахунку (ключ)
    std::string fullName;  // прізвище ім'я по-батькові

    BankRecord() = default;
    BankRecord(const std::string& acc, const std::string& name)
        : account(acc), fullName(name) {
    }
};

// ═══════════════════════════════════════════════════════════
//  Асоціативний клас BankMap
// ═══════════════════════════════════════════════════════════
class BankMap {
public:
    enum ErrorCode {
        OK = 0,
        ERR_NOT_FOUND,   // сутність не знайдена
        ERR_NO_MEM,      // не вистачає пам'яті
        ERR_DUPLICATE    // дублікат рахунку
    };

private:
    BankRecord* records;  // масив записів
    int         size;     // поточна кількість записів
    int         capacity; // виділена ємність
    mutable int codeError;

    static int objectCount;

    // розширення внутрішнього масиву
    bool resize(int newCap);

public:
    // ── Конструктори / деструктор ──────────────────────────
    BankMap();
    explicit BankMap(int initCapacity);
    BankMap(const BankMap& other);
    ~BankMap();

    // ── Присвоєння ─────────────────────────────────────────
    BankMap& operator=(const BankMap& rhs);

    // ── Додавання / видалення записів ─────────────────────
    bool addRecord(const std::string& account, const std::string& fullName);
    bool removeByAccount(const std::string& account);
    bool removeByName(const std::string& fullName);

    // ── Пошук ─────────────────────────────────────────────
    // за номером рахунку → повертає ПІБ
    std::string findByAccount(const std::string& account) const;
    // за ПІБ → повертає номер рахунку
    std::string findByName(const std::string& fullName) const;

    // ── Індексація [] ─────────────────────────────────────
    // v["UA123"] → ПІБ власника рахунку
    std::string& operator[](const std::string& account);
    // const-версія
    std::string  operator[](const std::string& account) const;

    // ── Виклик функції () ─────────────────────────────────
    // v("Іванов Іван Іванович") → номер рахунку
    std::string operator()(const std::string& fullName) const;

    // ── Утиліти ───────────────────────────────────────────
    int  getSize()      const { return size; }
    int  getError()     const { return codeError; }
    void clearError() { codeError = OK; }
    std::string errorText()   const;

    static int getObjectCount() { return objectCount; }

    void print(std::ostream& os = std::cout) const;

    // ── Дружні оператори введення/виведення ───────────────
    friend std::ostream& operator<<(std::ostream& os, const BankMap& bm);
    friend std::istream& operator>>(std::istream& is, BankMap& bm);
};