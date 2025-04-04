#include "Automata.h"
#include <iostream>

Automata::Automata() {
    cash = 0;
    state = STATES::OFF;
    selectedDrink = -1;
    menu = { "Чай", "Кофе", "Молоко" };
    prices = { 10, 15, 20 };
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        std::cout << "Автомат включён.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        state = STATES::OFF;
        cash = 0;
        selectedDrink = -1;
        std::cout << "Автомат выключен.\n";
    }
}

void Automata::coin(int amount) {
    if (amount <= 0) return;
    if (state == STATES::WAIT) {
        state = STATES::ACCEPT;
        cash += amount;
        std::cout << "Внесено: " << amount << "\n";
    }
    else if (state == STATES::ACCEPT) {
        cash += amount;
        std::cout << "Внесено: " << amount << "\n";
    }
}

std::vector<std::string> Automata::getMenu() {
    std::vector<std::string> menuWithPrices;
    for (size_t i = 0; i < menu.size(); ++i) {
        menuWithPrices.push_back(menu[i] + " - " + std::to_string(prices[i]));
    }
    return menuWithPrices;
}

STATES Automata::getState() {
    return state;
}

void Automata::choice(int drinkIndex) {
    if (state == STATES::ACCEPT && drinkIndex >= 0 && drinkIndex < (int)menu.size()) {
        selectedDrink = drinkIndex;
        state = STATES::CHECK;
        std::cout << "Выбран: " << menu[drinkIndex] << "\n";
    }
}

bool Automata::check() {
    if (state == STATES::CHECK && selectedDrink != -1) {
        return cash >= prices[selectedDrink];
    }
    return false;
}

void Automata::cancel() {
    if (state == STATES::ACCEPT || state == STATES::CHECK) {
        std::cout << "Операция отменена. Возврат: " << cash << "\n";
        cash = 0;
        selectedDrink = -1;
        state = STATES::WAIT;
    }
}

void Automata::cook() {
    if (state == STATES::CHECK && check()) {
        state = STATES::COOK;
        cash -= prices[selectedDrink];
        std::cout << "Готовится " << " - " << prices[selectedDrink] << "\n";
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        state = STATES::WAIT;
        std::cout << "Напиток готов!\n";
        if (cash > 0) {
            std::cout << "Ваша сдача: " << cash << "\n";
        }
        cash = 0;
        selectedDrink = -1;
    }
}

int Automata::getChange() {
    return cash;
}