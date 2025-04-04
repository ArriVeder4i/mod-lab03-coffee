#include "Automata.h"
#include <gtest/gtest.h>
#include <locale>

TEST(AutomataTest, InitialState) {
    Automata vendingMachine;
    EXPECT_EQ(vendingMachine.getState(), STATES::OFF);
}

TEST(AutomataTest, TurnOn) {
    Automata vendingMachine;
    vendingMachine.on();
    EXPECT_EQ(vendingMachine.getState(), STATES::WAIT);
}

TEST(AutomataTest, TurnOff) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.off();
    EXPECT_EQ(vendingMachine.getState(), STATES::OFF);
}

TEST(AutomataTest, CoinInWaitState) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(10);
    EXPECT_EQ(vendingMachine.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, CoinInAcceptState) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(10);
    vendingMachine.coin(5);
    EXPECT_EQ(vendingMachine.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, Choice) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(10);
    vendingMachine.choice(0);
    EXPECT_EQ(vendingMachine.getState(), STATES::CHECK);
}

TEST(AutomataTest, CheckSufficientFunds) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(20);
    vendingMachine.choice(0);
    EXPECT_TRUE(vendingMachine.check());
}

TEST(AutomataTest, CheckInsufficientFunds) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(5);
    vendingMachine.choice(0);
    EXPECT_FALSE(vendingMachine.check());
}

TEST(AutomataTest, Cook) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(20);
    vendingMachine.choice(0);
    if (vendingMachine.check()) {
        vendingMachine.cook();
        EXPECT_EQ(vendingMachine.getState(), STATES::COOK);
    }
}

TEST(AutomataTest, FinishAfterCook) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(20);
    vendingMachine.choice(0);
    if (vendingMachine.check()) {
        vendingMachine.cook();
        vendingMachine.finish();
        EXPECT_EQ(vendingMachine.getState(), STATES::WAIT);
    }
}

TEST(AutomataTest, Cancel) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(10);
    vendingMachine.cancel();
    EXPECT_EQ(vendingMachine.getState(), STATES::WAIT);
}

TEST(AutomataTest, OffInAcceptState) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(10);
    vendingMachine.off();
    EXPECT_EQ(vendingMachine.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, CoinInOffState) {
    Automata vendingMachine;
    vendingMachine.coin(10);
    EXPECT_EQ(vendingMachine.getState(), STATES::OFF);
}

TEST(AutomataTest, ChoiceWithoutCoin) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.choice(0);
    EXPECT_EQ(vendingMachine.getState(), STATES::WAIT);
}

TEST(AutomataTest, GetMenu) {
    Automata vendingMachine;
    auto menu = vendingMachine.getMenu();
    EXPECT_FALSE(menu.empty());
    EXPECT_EQ(menu.size(), 3);
}

TEST(AutomataTest, ReturnChange) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(25); 
    vendingMachine.choice(1);
    if (vendingMachine.check()) {
        vendingMachine.cook();
        EXPECT_EQ(vendingMachine.getChange(), 10);
        vendingMachine.finish();
        EXPECT_EQ(vendingMachine.getChange(), 0);
    }
}

TEST(AutomataTest, NoChange) {
    Automata vendingMachine;
    vendingMachine.on();
    vendingMachine.coin(15); 
    vendingMachine.choice(1);
    if (vendingMachine.check()) {
        vendingMachine.cook();
        EXPECT_EQ(vendingMachine.getChange(), 0);
        vendingMachine.finish();
        EXPECT_EQ(vendingMachine.getChange(), 0);
    }
}

int main(int argc, char** argv) {
    std::setlocale(LC_ALL, "Russian");
    std::cout.imbue(std::locale());
    std::wcout.imbue(std::locale());
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}