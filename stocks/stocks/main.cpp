#include "orderBook.h" //which already includes order.h

int main() {
	OrderBook *book;
	book = new OrderBook;
	book->grabdata();

	return 0;
}