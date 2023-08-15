#include "Library.h"

int main() {
	Book Alice{ "123A", "Alice's Adventures in Wonderland", "Lewis Carrol", Chrono::Date{1865, Chrono::Month::nov, 26} };
	cout << Alice; 
}