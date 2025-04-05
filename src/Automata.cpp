// Copyright 2025 ArriVeder4i
#include "Automata.h"
#include <iostream>
#include <string>
#include <vector>

Automata::Automata() {
  cash = 0;
  state = STATES::OFF;
  selectedDrink = -1;
  menu = {"Tea", "Coffee", "Milk"};
  prices = {10, 15, 20};
}

void Automata::on() {
  if (state == STATES::OFF) {
    state = STATES::WAIT;
    std::cout << "Machine turned on.\n";
  }
}

void Automata::off() {
  if (state == STATES::WAIT) {
    state = STATES::OFF;
    cash = 0;
    selectedDrink = -1;
    std::cout << "Machine turned off.\n";
  }
}

void Automata::coin(int amount) {
  if (amount <= 0) return;
  if (state == STATES::WAIT) {
    state = STATES::ACCEPT;
    cash += amount;
    std::cout << "Deposited: " << amount << "\n";
  } else if (state == STATES::ACCEPT) {
    cash += amount;
    std::cout << "Deposited: " << amount << "\n";
  }
}

std::vector<std::string> Automata::getMenu() {
  std::vector<std::string> menuWithPrices;
  for (size_t i = 0; i < menu.size(); ++i) {
    menuWithPrices.push_back(menu[i] + " - " +
                             std::to_string(prices[i]));
  }
  return menuWithPrices;
}

STATES Automata::getState() {
  return state;
}

void Automata::choice(int drinkIndex) {
  if (state == STATES::ACCEPT && drinkIndex >= 0 &&
      drinkIndex < static_cast<int>(menu.size())) {
    selectedDrink = drinkIndex;
    state = STATES::CHECK;
    std::cout << "Selected: " << menu[drinkIndex] << "\n";
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
    std::cout << "Operation canceled. Refund: " << cash << "\n";
    cash = 0;
    selectedDrink = -1;
    state = STATES::WAIT;
  }
}

void Automata::cook() {
  if (state == STATES::CHECK && check()) {
    state = STATES::COOK;
    cash -= prices[selectedDrink];
    std::cout << "Preparing " << menu[selectedDrink] << " - "
              << prices[selectedDrink] << "\n";
  }
}

void Automata::finish() {
  if (state == STATES::COOK) {
    state = STATES::WAIT;
    std::cout << "Drink is ready!\n";
    if (cash > 0) {
      std::cout << "Your change: " << cash << "\n";
    }
    cash = 0;
    selectedDrink = -1;
  }
}

int Automata::getChange() {
  return cash;
}
