#include "Library.h"  

namespace Chrono {
	// member function definitions:

	Date::Date(int yy, Month mm, int dd)
		: y{ yy }, m{ mm }, d{ dd } // note: member initializers
	{
		if (!is_date(yy, mm, dd)) throw Invalid{};
	}

	const Date& default_date()
		// Creates and returns (only once) a default_date
	{
		static Date dd {2001, Month::jan, 1}; // Start of 21st century
		return dd;
	}

	Date::Date()
		:y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{

	}

	void Date::add_day(int n)
	{
		d += n;
	}

	void Date::add_month(int n)
	{
		// ...
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) { // beware of leap years!
			m = Month::mar; // Use March 1 instead of February 29
			d = 1;
		}
		y += n;
	}
	// helper functions;

	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid

		if (d <= 0) return false; // day must be positive
		if (m < Month::jan || Month::dec < m) return false;

		int days_in_month = 31; // Most months have 31 days.

		switch (m)
		{
		case Month::feb: // But the length of Feb varies
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov: // the rest have 30 days
			days_in_month = 30;
			break;
		}

		if (days_in_month < d) return false;

		return true;
	}

	bool leapyear(int y)
	{
		// see exercise 10.
		return y;
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year()
			<< ',' << int(d.month())
			<< ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // oops format error, set the fail bit.
			is.clear(ios_base::failbit);
			return is;
		}

		dd = Date(y, Month(m), d);

		return is;
	}

	enum class Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};

	//Day day_of_week(const Date& d)
	//{
		//...
	//}

	Date next_Sunday(const Date& d)
	{
		//...
		return d;
	}

	Date next_weekday(const Date& d)
	{
		//...
		return d;
	}

} // chrono. End Date class and Chrono namespace. 

// Start the library.

Book::Book(string IS, string title, string author, Genre genre, Chrono::Date cd)
// Stores a book with formatted ISBN, title, author and an object of Date class. 
	: I{ IS }, t{ title }, a{ author }, g{ genre }, d { cd } {
	//Is the ISBN valid?
	valid_isbn();
	// Then print message, we intialize object. 
	cout << t << ": intialized succesfully.\n";
}

void Book::valid_isbn(){
	// Throw error if ISBN does not match format.
	// Verify the ISBN is 4 characters. 
	if (I.size() != 4) {
		error("Invalid ISBN, format must be n-n-n-x, n is an integer, x is letter or int");
	}

	// Verify the first 3 characters are digits. 
	for (int i = 0; i <= 2; ++i) {
		if (isdigit(I[i]) == 0) {
			error("Invalid ISBN, format must be n-n-n-x, n is an integer, x is letter or int");
		}
	}
}

string Book::genre_tostr() const {
	// Returns the string version of the enumerated Genre.
	// A number isn't much help here, is it Bjarne? 
	switch (g)
	{
	case Genre::fiction:
		return "fiction";
		break;
	case Genre::nonfiction:
		return "non-fiction";
		break;
	case Genre::periodical:
		return "periodical";
		break;
	case Genre::biography:
		return "biography";
		break;
	case Genre::children:
		return "children";
		break;
	default:
		return "";
		break;
	}
}

// Various operator overloading for Patron and Book class.

ostream& operator<<(ostream& os, const Book& k) {
	// Overloading the <<, prints all data concisely formatted. 
	return os << "ISBN: " << k.ISBN() << "\n"  << "Title: " << k.title() << "\n" << "Author: " <<  k.author() << "\n" << "Genre: " << k.genre_tostr() << "\n" << "Copyright: " << k.date() << "\n";
}

bool operator==(const Book& a, const Book& b) {
	return a.ISBN() == b.ISBN() &&
		a.title() == b.title() &&
		a.author() == b.author() &&
		a.genre() == b.genre() &&
		a.date() == b.date();
}

bool operator==(const Patron& a, const Patron& b) {
	return a.card_numb() == b.card_numb();
}

bool operator!=(const Book& a, const Book& b) {
	return !(a == b);
}

Patron::Patron(string name, string card, double fee)
// Initalize a Patron. 
// This class represents someone simply entering the library, but not yet registering. 
	: n{ name }, cn{ card }, f{ fee } {
	valid_card();

	cout << "Welcome to the library, " << name << ".\n";
}

void Patron::valid_card() {
	// Confirm a users library card number matches Bjarnes specified format.
	// Throw error() if ISBN does not match format.
	if (cn.size() != 7) {
		error("Invalid card number, format must be 7 digits, please leave the library now!");
	}

	for (int i = 0; i < cn.size(); ++i) {
		if (isdigit(cn[i]) == 0) {
			error("Invalid card number, format must be 7 digits, please leave the library now!");
		}
	}
}

void Patron::set_fee(double fee) {
	// A setter for fee.
	f = fee;
}

bool Patron::owes_fee() {
	// Helper function for Patron, return a bool if Patron owes a fee to library. 
	if (f > 0.00) {
		return true;
	}
	else {
		return false;
	}
}

void Patron::status() {
	// Prints various status reports on Patron object, such as name, fees owed and card number.
	cout << "Patron Name: " << n << "\n";

	if (owes_fee()) {
		cout << "Owes: $" << f << " in library fees.\n";
	}
	else {
		cout << "Has no outstanding fees.\n";
	}

	cout << "Card #:" << cn << "\n";
}

Transaction::Transaction(Book b, Patron p, Chrono::Date d)
// Represents a transaction, that is...
// A Patron object, checksout() a Book object, on a specified Date object
	:book{b}, patron{p}, date{d} {}

void  Library::add_book(const Book& b) { 
	// Add an already existing book to the library.
	books.push_back(b);
	cout << b.title() << " added successfully\n";
}
void Library::add_patron(const Patron& p) {
	// Represents registering a patron into the library system.
	// That is, recieving a library card.

	for (Patron patron : patrons) {
		// A user with the same card number cannot be added to the library.
		if (patron == p) {
			error("This card number is already in the system.");
		}
	}
	patrons.push_back(p);
	cout << p.name() << " registered successfully\n";
}

void Library::check_patron(const Patron& p) {
	// Verify that the patron is able to check out a book. 

	for (Patron patron : patrons) {
		// utilize the card number, to verify if patron is the same. 
		// This also means all library card numbers must be unique. 
		if (patron == p) {
			patrons.erase(remove(patrons.begin(), patrons.end(), p));
			return;
		}
		
	}
	// We would have returned by now if it was...
	error("Error: patron's card number is not in the system");
}

void Library::check_book(const Book& b) {
	// Verify that this book is in the library and can be checked out. 
	
	for (Book book : books) {
		if (book == b) {
			books.erase(remove(books.begin(), books.end(), b));
			return;
		}
	}
	error("Error: this book is not in the library system");

}

void Library::check_out(const Book& b, const Patron& p, const Chrono::Date& d) {

	// Whenever a user check out a book.
	// Have the library make sure that both the user and the book are in the library.

	check_book(b);
	check_patron(p);
	// If they aren't report an error.

	// Then check to make sure that the user owes no fees. If the user does report an error.
	if (p.fees() > 0) {
		error(p.name() + " owes money to the library");
	}

	// If not create a Transaction, and place it in the vector of Transactions.
	Transaction t{ b, p, d };
	transactions.push_back(t);

	// Print confirmation message with core info. 
	cout << b.title() << " checked out by " << p.name() << " on " << d << " succesfully.\n";
}

vector<Patron> Library::debtors() {
	//Write a function that will return a vector that contains the names of all Patrons who owe a fee. 

	vector<Patron> debtors;

	for (Patron p : patrons) {
		if (p.fees() > 0) {
			debtors.push_back(p);
		}
	}

	return debtors;
}

/*Notes: Most all of the functionality works on constant references, I suppose that makes sense in theory. 
A Patron checking out a book object from the library should not be able to modify a book in any way. 
But a gut instinct tells me this could cause problems down the line, for example...
What if a user needs to modify the date that a book was checked out or there was some mistake.
There is no room for modification, but I suppose in essence this is a good thing.

Yes there is far more room for functionality here, example, can we see all the books in the library like a catalogue.
I should be able to create a vector books and push them all to the library, by reading them in from user input. That would be nice
The whole user input needs to be cleaned up to make it like an actual library, and of course there is no GUI.
But other than that the basics are here. It demonstrates the power of OOP in C++

See exercise 9 on page 340 of PPP 2nd edition.*/



