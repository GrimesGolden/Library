#include "Library.h"

int main() {

	Library library; 

	Book Alice{ "123A", "Alice's Adventures in Wonderland", "Lewis Carrol", Genre::children, Chrono::Date{1865, Chrono::Month::nov, 26} };
	cout << Alice; 

	Book ATLG{ "123B", "Through the Looking Glass", "Lewis Carroll", Genre::children, Chrono::Date{1871, Chrono::Month::dec, 27} };
	cout << ATLG;

	if (Alice == ATLG) {
		cout << "equal\n";
	}
	else {
		cout << "not equal\n";
	}

	Patron jordan{ "Jordan", "1234567", 0.00 };
	Patron terry{ "Terry Davis", "1234565", 0.00 };
	Patron danny{ "Danny Fathands", "1333333", 5.25 };
	Patron farter{ "Farts Often", "4444444", 100 };

	jordan.status();

	Chrono::Date todays_date{2023, Chrono::Month::aug, 16};

	library.add_book(Alice);
	library.add_book(ATLG);
	library.add_patron(jordan);
	library.add_patron(terry);
	library.add_patron(danny);
	library.add_patron(farter);

	library.check_out(Alice, jordan, todays_date);
	library.check_out(ATLG, terry, todays_date);

	vector<Patron> debts = library.debtors();

	for (Patron p : debts) {
		cout << "HEY! " << p.name() << " owes money to the library!\n";
	}
}