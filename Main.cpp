#include "Library.h"

int main() {
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
	jordan.status();
}