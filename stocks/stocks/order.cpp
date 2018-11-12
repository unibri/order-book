#include "order.h"

istream& operator >> (istream& is, Order* O) {
	is >> O->type >> O->action >> O->price >>
		O->numShares >> O->ID;
	return is;
}