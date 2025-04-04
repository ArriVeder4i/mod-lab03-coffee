#include "Automata.h"
#include <iostream>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::cout.imbue(std::locale());
    std::wcout.imbue(std::locale());

    Automata vendingMachine;

    // Включение автомата
    vendingMachine.on();

    // Просмотр меню
    std::cout << "Меню:\n";
    auto menu = vendingMachine.getMenu();
    for (const auto& item : menu) {
        std::cout << item << "\n";
    }

    //внесение денег
    vendingMachine.coin(50);
    //выбор напитка
    vendingMachine.choice(1);

    // Проверка достаточности средств и приготовление напитка
    if (vendingMachine.check()) {
        vendingMachine.cook();
        vendingMachine.finish();
    }
    else {
        std::cout << "Недостаточно средств для покупки.\n";
        vendingMachine.cancel();
    }

    // Выключение автомата
    vendingMachine.off();

    return 0;
}