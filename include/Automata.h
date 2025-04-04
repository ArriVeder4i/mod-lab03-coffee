// Copyright 2025 ArriVeder4i
#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
private:
    int cash;
    std::vector<std::string> menu;
    std::vector<int> prices;
    STATES state;
    int selectedDrink;

public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    std::vector<std::string> getMenu();
    STATES getState();
    void choice(int drinkIndex);
    bool check();
    void cancel();
    void cook();
    void finish();
    int getChange();
};

#endif  // AUTOMATA_H
