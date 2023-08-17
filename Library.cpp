// Chrono.cpp
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

} // chrono

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
	if (I.size() != 4) {
		error("Invalid ISBN, format must be n-n-n-x, n is an integer, x is letter or int");
	}

	for (int i = 0; i <= 2; ++i) {
		if (isdigit(I[i]) == 0) {
			error("Invalid ISBN, format must be n-n-n-x, n is an integer, x is letter or int");
		}
	}
}

string Book::genre_tostr() const {
	// Returns the string version of the enumerated Genre.
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

// Operator overloading...

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
	: n{ name }, cn{ card }, f{ fee } {
	valid_card();

	cout << "Welcome to the library, " << name << ".\n";
}

void Patron::valid_card() {
	// Throw error if ISBN does not match format.
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
	f = fee;
}

bool Patron::owes_fee() {
	if (f > 0.00) {
		return true;
	}
	else {
		return false;
	}
}

void Patron::status() {
	cout << "Patron Name: " << n << "\n";

	if (owes_fee()) {
		cout << "Owes: $" << f << " in library fees.\n";
	}
	else {
		cout << "Has no outstanding fees.\n";
	}

	cout << "Card #:" << cn << "\n";
}

void  Library::add_book(const Book& b) { 
	books.push_back(b);
	cout << b.title() << " added successfully\n";
}
void Library::add_patron(const Patron& p) {
	patrons.push_back(p);
	cout << p.name() << " added successfully\n";
}

void Library::check_patron(const Patron& p) {

	for (Patron patron : patrons) {
		// utilize the card number, to verify if patron is the same. 
		// This also means all library card numbers must be unique. 
		if (patron == p) {
			patrons.erase(remove(patrons.begin(), patrons.end(), p));
			return;
		}
		
	}
	error("Error: patron's card number is not in the system");
}

void Library::check_book(const Book& b) {
	
	for (Book book : books) {
		if (book == b) {
			books.erase(remove(books.begin(), books.end(), b));
			return;
		}
	}
	error("Error: this book is not in the library system");

}

void Library::check_out(const Book& b, const Patron& p) {

	
	check_book(b);
	check_patron(p);

	cout << b.title() << " checked out by " << p.name() << " succesfully.\n";
}





