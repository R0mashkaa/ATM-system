#include <iostream>
#include <vector>
#include <locale>

using namespace std;

void line() {
	cout << "==========================================" << endl;
}


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

	Banknote getBanknote() const {
		return banknote;
	}

	int getCount() const {
		return count;
	}

	void addCount(int c) {
		count += c;
	}

	void subtractCount(int c) {
		count -= c;
	}
};

class ATM {
private:
	vector<Pair> banknotes;
	int capacity;

public:
	ATM(int cap) : capacity(cap) {}
	void addBanknotes(const Pair& p) {
		if (p.getCount() <= capacity) {
			bool found = false;
			for (Pair& existing : banknotes) {
				if (existing.getBanknote() == p.getBanknote()) {
					existing.addCount(p.getCount());
					found = true;
					break;
				}
			}
			if (!found) {
				banknotes.push_back(p);
			}
			capacity -= p.getCount();
		}
	}

	int getTotalAmount() const {
		int total = 0;
		for (const Pair& p : banknotes) {
			total += static_cast<int>(p.getBanknote()) * p.getCount();
		}
		return total;
	}

	void printBanknotes() const {
		for (const Pair& p : banknotes) {
			cout << "Банкнот " << static_cast<int>(p.getBanknote()) << " : " << p.getCount() << " шт." << endl;
		}
	}

	vector<Pair> withdraw(int amount) {
		if (amount > getTotalAmount()) {
			cout << "Неможливо зняти " << amount << " ГРН з банкомату" << endl;
			return vector<Pair>();
		}

		vector<Pair> withdrawn;
		int remaining = amount;
		for (int i = banknotes.size() - 1; i >= 0; i--) {
			Pair& p = banknotes[i];
			int count = min(remaining / static_cast<int>(p.getBanknote()), p.getCount());
			if (count > 0) {
				withdrawn.push_back(Pair(p.getBanknote(), count));
				remaining -= static_cast<int>(p.getBanknote()) * count;
				p.subtractCount(count);
				if (remaining == 0) {
					break;
				}
			}
		}
		if (remaining == 0) {
			return withdrawn;
		}
		else {
			for (const Pair& p : withdrawn) {
				addBanknotes(Pair(p.getBanknote(), p.getCount()));
			}
			cout << "Неможливо зняти " << amount << " ГРН з банкомату" << endl;
			return vector<Pair>();
		}
	}
};


int main() {
	setlocale(0, "");

	int atmSize = 0;
	int numberMenu = 0;

	cout << "Введiть кiлькiсть можливих купюр в банкоматi: ";
	cin >> atmSize;

	ATM atm(atmSize);

	while (numberMenu != 4) {
		line();
		cout << "1.Внести кошти\n2.Зняти кошти\n3.Переглянути баланс банкомату\n4.Вихiд" << endl;
		line();

		cout << "-> ";
		cin >> numberMenu;

		switch (numberMenu) {

		case 1: {
			int par = 0;
			int count = 0;

			line();
			cout << "Введiть кiлькiсть купюр: ";
			cin >> count;
			cout << "Введiть номiнал купюр: ";
			cin >> par;

			if (par == 1) {
				Pair p1(Banknote::ONE, count);
				atm.addBanknotes(p1);
			}
			else if (par == 2) {
				Pair p2(Banknote::TWO, count);
				atm.addBanknotes(p2);
			}
			else if (par == 5) {
				Pair p3(Banknote::FIVE, count);
				atm.addBanknotes(p3);
			}
			else if (par == 10) {
				Pair p4(Banknote::TEN, count);
				atm.addBanknotes(p4);
			}
			else if (par == 50) {
				Pair p5(Banknote::FIFTY, count);
				atm.addBanknotes(p5);
			}
			else if (par == 100) {
				Pair p6(Banknote::HUNDRED, count);
				atm.addBanknotes(p6);
			}
			else if (par == 1000) {
				Pair p7(Banknote::THOUSAND, count);
				atm.addBanknotes(p7);
			}
			else if (par == 5000) {
				Pair p8(Banknote::FIVE_THOUSAND, count);
				atm.addBanknotes(p8);
			}
			else {
				line();
				cout << "Не вiрний номiнал купюри! Можливi купюри:\n\'1, 2, 5, 10, 50, 100, 1000, 5000\'\n\a";
			}

			break;
		}

		case 2: {
			int moneyCount = 0;

			line();
			cout << "Введiть необхiдну суму: ";
			cin >> moneyCount;

			vector<Pair> withdrawn = atm.withdraw(moneyCount);
			if (!withdrawn.empty()) {
				cout << "Знято:" << endl;
				for (const Pair& p : withdrawn) {
					cout << static_cast<int>(p.getBanknote()) << " ГРН x " << p.getCount() << endl;
				}
				cout << "Баланс банкомата: " << atm.getTotalAmount() << " ГРН" << endl;
			}
			break;
		}

		case 3: {
			line();
			cout << "Загальна кiлькiсть: " << atm.getTotalAmount() << endl;
			cout << "Купюри в банкоматi: " << endl;
			atm.printBanknotes();
			break;
		}

		case 4:
			line();
			cout << "До зустрiчi!\n";
			line();
			break;

		}
	}

	return 0;
}
