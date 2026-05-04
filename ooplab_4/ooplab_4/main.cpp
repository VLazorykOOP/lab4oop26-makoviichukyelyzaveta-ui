#include <iostream>
#include <string>
#include <Windows.h>
#include "VectorUInt.h"
#include "BankMap.h"
#include "MatrixUInt.h"

void showMenu() {
    std::cout << "                ЛАБОРАТОРНА РОБОТА №4\n";
    std::cout << "1. Завдання 1: Клас VectorUInt (Вектор цілих)\n";
    std::cout << "2. Завдання 2: Клас BankMap (Банківські рахунки)\n";
    std::cout << "3. Завдання 3: Клас MatrixUInt (Матриця цілих)\n";
    std::cout << "0. Вихід\n";
    std::cout << "Ваш вибір: ";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;
    do {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1: {
            int n;
            std::cout << "\n>>> ЗАВДАННЯ 1: ВЕКТОР <<<\n";
            std::cout << "Введіть розмір вектора: ";
            std::cin >> n;
            VectorUInt v1(n);
            std::cout << "Введіть " << n << " елементів вектора:\n";
            std::cin >> v1;

            std::cout << "Ваш вектор: " << v1 << "\n";
            std::cout << "Збільшуємо всі елементи на 1 (++v1): ";
            ++v1;
            std::cout << v1 << "\n";
            std::cout << "Сума елементів (оператор ()): " << v1() << "\n";
            break;
        }
        case 2: {
            std::cout << "\n>>> ЗАВДАННЯ 2: БАНКІВСЬКА КАРТОТЕКА <<<\n";
            BankMap myBank;
            std::cin >> myBank; // Використовує ваш метод введення декількох записів

            std::cout << "\nПоточна база записів:\n" << myBank;

            std::string searchAcc;
            std::cout << "\nВведіть номер рахунку для пошуку ПІБ: ";
            std::getline(std::cin >> std::ws, searchAcc);
            std::cout << "Результат: " << myBank[searchAcc] << "\n";

            if (myBank.getError() != 0) std::cout << "[!] Повідомлення: " << myBank.errorText() << "\n";
            break;
        }
        case 3: {
            int rows, cols;
            std::cout << "\n>>> ЗАВДАННЯ 3: МАТРИЦЯ <<<\n";
            std::cout << "Введіть кількість рядків: ";
            std::cin >> rows;
            std::cout << "Введіть кількість стовпців: ";
            std::cin >> cols;

            MatrixUInt m1(rows, cols);
            std::cout << "Введіть елементи матриці (" << rows << "x" << cols << "):\n";
            std::cin >> m1;

            std::cout << "\nВаша матриця:\n" << m1;
            std::cout << "Загальна сума всіх елементів матриці: " << m1() << "\n";

            unsigned int val;
            std::cout << "Введіть число для множення матриці: ";
            std::cin >> val;
            m1 *= val;
            std::cout << "Результат множення:\n" << m1;
            break;
        }
        case 0:
            std::cout << "Завершення роботи. До побачення!\n";
            break;
        default:
            std::cout << "Помилка: невірний вибір.\n";
        }
    } while (choice != 0);

    return 0;
}