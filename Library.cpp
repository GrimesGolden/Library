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

bool operator!=(const Book& a, const Book& b) {
	return !(a == b);
}





