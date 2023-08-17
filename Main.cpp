#include "Library.h"

int main() {

	// Create the library object.
	Library library; 

	// Create two book objects.
	Book Alice{ "123A", "Alice's Adventures in Wonderland", "Lewis Carrol", Genre::children, Chrono::Date{1865, Chrono::Month::nov, 26} };
	cout << Alice; 
	Book ATLG{ "123B", "Through the Looking Glass", "Lewis Carroll", Genre::children, Chrono::Date{1871, Chrono::Month::dec, 27} };
	cout << ATLG;
	cout << "\n\n";

	// Demonstrate overloaded == operator.
	if (Alice == ATLG) {
		cout << "equal\n";
	}
	else {
		cout << "not equal\n";
	}
	cout << "\n\n";

	// Create 4 unique patrons. 
	Patron jordan{ "Jordan", "1234567", 0.00 };
	Patron terry{ "Terry Davis", "1234565", 0.00 };
	Patron danny{ "Danny Fathands", "1333333", 5.25 };
	Patron farter{ "Farts Often", "4444444", 100 };
	cout << "\n\n";

	// Demonstrate Patron class's status() member function. 
	jordan.status();
	cout << "\n\n";

	//Create a Date object representing todays date.
	Chrono::Date todays_date{2023, Chrono::Month::aug, 16};

	// Add the 2 Books and 4 Patrons to the library. 
	library.add_book(Alice);
	library.add_book(ATLG);
	library.add_patron(jordan);
	library.add_patron(terry);
	library.add_patron(danny);
	library.add_patron(farter);
	cout << "\n\n";

	// Check out both books with two seperate Patrons. 
	library.check_out(Alice, jordan, todays_date);
	library.check_out(ATLG, terry, todays_date);
	cout << "\n\n";

	// Obtain a vector containing Patrons who owe fees, using Library class debtors() member function. 
	vector<Patron> debts = library.debtors();

	// Proof that the vector does in fact contain this data. 
	for (Patron p : debts) {
		cout << "HEY! " << p.name() << " owes $" << p.fees() << " in fees to the library.\n";
	}
}