#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
// Base class: CasinoGame
class CasinoGame {
protected:
    string gameName; 
public:
    CasinoGame(const string& name) : gameName(name) {}
    virtual void playGame() = 0;
    virtual ~CasinoGame() {}
};
class Player {
private:
    string name; 
    int balance; 
public:
    Player(const string& playerName, int initialBalance)
        : name(playerName), balance(initialBalance)
    string getName() const { return name; }
    int getBalance() const { return balance; }
    void updateBalance(int amount) { balance += amount; }
    void displayInfo() const {
        cout << "Player: " << name << ", Balance: $" << balance << "\n";
    }
    bool canContinue() const { return balance > 0; }
};
class NumberGuessingGame : public CasinoGame {
private:
    Player& player;
    void drawLine(int n, char symbol) const {
        for (int i = 0; i < n; i++) cout << symbol;
        cout << "\n";
    }
    void showRules() const {
        drawLine(80, '_');
        cout << "\t\tRULES OF THE GAME\n";
        drawLine(80, '_');
        cout << "\t1. Choose any number between 1 to 10\n";
        cout << "\t2. If you win, you will get 10 times the money you bet\n";
        cout << "\t3. If you bet on the wrong number, you will lose your bet amount\n";
        drawLine(80, '_');
    }
    int getValidBet() const {
        int bet;
        do {
            cout << player.getName() << ", enter money to bet: $";
            cin >> bet;
            if (bet > player.getBalance()) {
                cout << "Your betting amount exceeds your current balance. Try again.\n";
            }
        } while (bet > player.getBalance());
        return bet;
    }
    int getValidGuess() const {
        int guess;
        do {
            cout << "Guess your number to bet (between 1 to 10): ";
            cin >> guess;
            if (guess <= 0 || guess > 10) {
                cout << "Invalid number! Please guess between 1 and 10.\n";
            }
        } while (guess <= 0 || guess > 10);
        return guess;
    }
public:
    NumberGuessingGame(Player& p)
        : CasinoGame("Number Guessing Game"), player(p) {}
    void playGame() override {
        showRules();
        cout << "\nYour current balance: $" << player.getBalance() << "\n";
        int bet = getValidBet();
        int guess = getValidGuess();
        srand(static_cast<unsigned>(time(0)));
        int dice = rand() % 10 + 1;
        if (guess == dice) {
            cout << "Congratulations! You guessed correctly and won $" << bet * 10 << "!\n";
            player.updateBalance(bet * 10);
        } else {
            cout << "Bad luck! The correct number was " << dice << ". You lost $" << bet << ".\n";
            player.updateBalance(-bet);
        }
        player.displayInfo();
    }
};
int main() {
    srand(static_cast<unsigned>(time(0)));
    string playerName;
    int initialBalance;
    cout << "Enter your name: ";
    cin >> playerName;
    cout << "Enter your deposit amount to play: $";
    cin >> initialBalance;
    Player player(playerName, initialBalance);
    NumberGuessingGame game(player);
    char choice;
    do {
        game.playGame();
        if (!player.canContinue()) {
            cout << "You are out of money! Game over.\n";
            break;
        }
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}

