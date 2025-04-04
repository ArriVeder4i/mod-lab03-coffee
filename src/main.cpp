// Copyright 2025 ArriVeder4i
#include "Automata.h"
#include <iostream>
#include <locale>

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    std::cout.imbue(std::locale());
    std::wcout.imbue(std::locale());

    Automata vendingMachine;

    vendingMachine.on();

    std::cout << "Menu:\n";
    auto menu = vendingMachine.getMenu();
    for (const auto& item : menu) {
        std::cout << item << "\n";
    }

    vendingMachine.coin(25);

    vendingMachine.choice(1);

    if (vendingMachine.check()) {
        vendingMachine.cook();
        vendingMachine.finish();
    }
    else {
        std::cout << "Insufficient funds for purchase.\n";
        vendingMachine.cancel();
    }

    vendingMachine.off();

    return 0;
}
