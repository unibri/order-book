#include "order.h"

Order::Order() {
	type = 0;
	action = 0;
	price = 0;
	numShares = 0;
	ID = "";
}

istream& operator >> (istream& is, Order* O) { 
	is >> O->type >> O->action >> O->price >>
		O->numShares >> O->ID;
	return is;
}

