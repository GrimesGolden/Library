#pragma once
// file Chrono.h
#include "std_lib_facilities.h"
#include <cctype>

// Date class
namespace Chrono {

	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	class Date {
	public:
		class Invalid {}; // to throw as exception

		Date(int y, Month m, int d); // check for valid date and initialize.
		Date(); // default constructor
		// the default copy operations are fine.

		// non modifying operations.
		int day() const { return d; }
		Month month() const { return m; }
		int year() const { return y; }

		// modifying operations:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
	private:
		int y;
		Month m;
		int d;
	};

	bool is_date(int y, Month m, int d); // true for valid date
	bool leapyear(int y); // true if y is a leap year

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);

	//Day day_of_week(const Date& d); // day of week of d
	Date next_Sunday(const Date& d);
	Date next_weekday(const Date& d);
} // Chrono. End date class and Chrono namespace
//*********************************************************************************************
// Start book class
enum class Genre {
	fiction, nonfiction, periodical, biography, children
};

class Book {
public:
	Book(string I, string t, string a, Genre g, Chrono::Date d);

	//modifying operations;

	//non modifying operations
	string ISBN() const { return I; }
	string title() const { return t; }
	string author() const { return a;  }
	Genre genre() const { return g; }
	string genre_tostr() const;
	Chrono::Date date() const { return d; }

private:
	string I;
	string t;
	string a;
	Chrono::Date d;
	Genre g;
	

	void valid_isbn();
};

class Patron {
public:
	Patron(string n, string cn, double f);

	// non modifying function
	string name() const { return n; }
	string card_numb() const { return cn; }
	double fees() const { return f; }
	void status();

	// modifying
	void set_fee(double fee);
private:
	string n; //name
	string cn; //card number
	double f = 0.00; // fees
	void valid_card();
	bool owes_fee();
};

ostream& operator<<(ostream& os, const Book& k);
bool operator==(const Book& a, const Book& b);
bool operator!=(const Book& a, const Book& b);

struct Transaction {
	Book book;
	Patron patron;
	Chrono::Date date;

public:
	Transaction(Book b, Patron p, Chrono::Date d);
};

class Library {

	vector<Book> books;
	vector<Patron> patrons;
	vector<Transaction> transactions;

public:
	void add_book(const Book& b);
	void add_patron(const Patron& p);
	void check_out(const Book& b, const Patron& p, const Chrono::Date& d);
	vector<Patron> debtors();
private: 
	void check_patron(const Patron& p);
	void check_book(const Book& b);


	
};
