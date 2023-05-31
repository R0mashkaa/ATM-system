#include <iostream>
#include <vector>

enum class Banknote {
    ONE = 1,
    TWO = 2,
    FIVE = 5,
    TEN = 10,
    FIFTY = 50,
    HUNDRED = 100,
    THOUSAND = 1000,
    FIVE_THOUSAND = 5000
};

class Pair {
private:
    Banknote banknote;
    int count;
public:
    Pair(Banknote bn, int c) : banknote(bn), count(c) {}
    int getBanknote() const { return static_cast<int>(banknote); }
    int getCount() const { return count; }
};

class ATM {
private:
    std::vector<Pair> banknotes;
    int capacity;
public:
    ATM(int cap) : capacity(cap) {}
    void addBanknotes(const Pair& p) {
        if (p.getCount() <= capacity) {
            banknotes.push_back(p);
            capacity -= p.getCount();
        }
    }
    int getTotalAmount() const {
        int total = 0;
        for (const Pair& p : banknotes) {
            total += p.getBanknote() * p.getCount();
        }
        return total;
    }
    void printBanknotes() const {
        for (const Pair& p : banknotes) {
            std::cout << "Banknote " << p.getBanknote() << " : " << p.getCount() << " pcs" << std::endl;
        }
    }
};

int main() {
    Pair p1(Banknote::FIFTY, 10);
    Pair p2(Banknote::HUNDRED, 5);
    Pair p3(Banknote::FIVE_HUNDRED, 3);
    ATM atm(100);
    atm.addBanknotes(p1);
    atm.addBanknotes(p2);
    atm.addBanknotes(p3);
    std::cout << "Total amount: " << atm.getTotalAmount() << std::endl;
    std::cout << "Banknotes in ATM: " << std::endl;
    atm.printBanknotes();

    // Withdraw money
    int amount = 500;
    std::vector<Pair> withdrawn = atm.withdraw(amount);
    if (withdrawn.empty()) {
        std::cout << "Unable to withdraw " << amount << " UAH from the ATM" << std::endl;
    }
    else {
        std::cout << "Withdrawn " << amount << " UAH from the ATM: " << std::endl;
        for (const Pair& p : withdrawn) {
            std::cout << "Banknote " << p.getBanknote() << " : " << p.getCount() << " pcs" << std::endl;
        }
    }

    std::cout << "Banknotes in ATM after withdrawal: " << std::endl;
    atm.printBanknotes();
 
    return 0;
}
