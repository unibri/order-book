#include "orderBook.h"

/*DEFINITIONS FOR Queue FUNCTIONS*/

Queue::Queue(){
	bidFront = nullptr;
	bidRear = nullptr;
	askFront = nullptr;
	askRear = nullptr;
	aSize = 0;
	bSize = 0;
}
/*
Queue::~Queue(){
	clearQ();
}
*/
//basically a pop function, deletes first in queue
void Queue::deleteOrder(int action) {
	queueNode* temp;
	if (action == 1) {
		temp = askFront;
		askFront = askFront->next;
		delete temp;
	}
	else {
		temp = bidFront;
		bidFront = bidFront->next;
		delete temp;
	}
}
//deletes specified node from queue
void Queue::deleteOrder(queueNode* orderPtr) {
	cout << "hey using delete lmaooo" << endl;
}
//inserts into bid book in descending order
void Queue::insertBidBook(Order* order) {
	queueNode* newNode;
	queueNode* nodePtr;
	queueNode* prevNode;
	newNode = new queueNode;
	newNode->p = order;
	cout << "hey using insert lmaooo" << endl;

	if (!bidFront) { //if there are no nodes
		bidFront = newNode; //sets bidFront
		newNode->next = nullptr; //there is no next node; 
	}
	else {
		nodePtr = bidFront; //start at the head
		prevNode = nullptr;
		while (nodePtr != nullptr &&  order->getPrice() <= nodePtr->p->getPrice()) { //order price is < book price
			prevNode = nodePtr; //prevNode is the node nodePtr is pointing to
			nodePtr = nodePtr->next;  //nodePtr moves on to the next node
		}
		if (prevNode == nullptr) { //meaning order o has the highest price
			bidFront = newNode;  //the newNode becomes the bidFront
			newNode->next = nodePtr;
		}
		else {
			prevNode->next = newNode; //insert newNode next to prevNode
			newNode->next = nodePtr;
		}
	}
}
//inserts into ask book in ascending order
void Queue::insertAskBook(Order* order) {
	display();
	queueNode* newNode;
	queueNode* nodePtr;
	queueNode* prevNode;
	newNode = new queueNode;
	newNode->p = order;

	if (!askFront) { //if there are no nodes
		askFront = newNode; //sets askfront
		newNode->next = nullptr; //there is no next node; 
	}
	else {
		nodePtr = askFront; //start at the head
		prevNode = nullptr;
		while (nodePtr != nullptr &&  order->getPrice() >= nodePtr->p->getPrice()) { //order price is >= book price
			prevNode = nodePtr; //prevNode is the node nodePtr is pointing to
			nodePtr = nodePtr->next;  //nodePtr moves on to the next node
		}
		if (prevNode == nullptr) { //meaning order o has the highest price
			askFront = newNode;  //the newNode becomes the askFront
			newNode->next = nodePtr;
		}
		else {
			prevNode->next = newNode; //insert newNode next to prevNode
			newNode->next = nodePtr;
		}
	}
}


/*DEFINITIONS FOR ORDERBOOK FUNCTIONS*/

void OrderBook::grabdata() {
	ifstream data;
	string fileName;
	//Asks user to type file name and opens file
	cout << "Enter file name: ";
	cin >> fileName;
	data.open(fileName.c_str());
	//Checking for error
	if (data.fail()) {
		cerr << "Error opening file";
		exit(3);
	}
	Order *orderPtr; //OrderPtr
	string line;
	if (data) {
		while (data) {
			orderPtr = new Order; //new Order 
			data >> orderPtr;
			if (orderPtr->getAction() == 0) { //if market order action =(0)
			}
			else { //if it is a limited order (1)
				//search for match search for match
				cout << "using function lmao" << endl;
				matchLimited(orderPtr);
			}
			getline(data, line); //moves on to the next line	
		}
	}
	queueNode *ptr = askFront;
	while (ptr != nullptr) {
		cout << ptr->p->getID() << endl;
			ptr = ptr->next;
	}
}
//action=1, this is a buy order and check the AskBook
//action=-1, this is a sell order and check the BidBook
void OrderBook::matchMarket(Order* currentPtr)
{	
	queueNode *Front, *Rear;
	bool match;

	// decide which book to check
	if (currentPtr->getAction() == 1) {
		Front = askFront;
		Rear = askRear;
	}
	else {
		Front = bidFront;
		Rear = bidRear;
	}
	// step 1: check if the book is empty
	if (Front == nullptr) { inbalance(currentPtr); } // there is not match, display messeage "Market Inbalance - XXX order ID: XXX Volume: XXX - unmatched"
	else {
		// step 2: making match	
		match = true;
		while (currentPtr->getNumShares() > Front->p->getNumShares())
		{
			display(currentPtr, Front->p);  //record the transaction;
			currentPtr->setNumShares(currentPtr->getNumShares() - Front->p->getNumShares());

			deleteOrder(currentPtr->getAction());

			if (Front = nullptr) {
				if (currentPtr->getNumShares() != 0)
				{//nothing in the book but there're remaining shares		
					inbalance(currentPtr);
				}
				match = false;
				break;
			}

		};//match going on
		if (match)
		{
			display(currentPtr, Front->p);
			if (currentPtr->getNumShares() == Front->p->getNumShares()) {
				deleteOrder(currentPtr->getAction());
			} //perfect match, just delete the book order
			else {
				int t;
				t = Front->p->getNumShares() - currentPtr->getNumShares();
				Front->p->setNumShares(t);			
			} //imperfect match, need to update the share info of book order
		}
	}
	}

void OrderBook::inbalance(Order* p)
{
	//display messeage "Market Inbalance - XXX order ID: XXX Volume: XXX - unmatched"
	if (p->getAction() == 1)
		cout << "Market Inbalance - Buy Order ID:" << p->getID()<< " Volume:" << p->getNumShares() << " - unmatched";
	else 
		cout << "Market Inbalance - Ask Order ID:" << p->getID() << " Volume:" << p->getNumShares() << " - unmatched";
};

void OrderBook::matchLimited(Order* order) {
	bool match = false;
	cout << "hey using match lmaooo" << endl;

	if (order->getAction() == 1) {//it is a bid/buy
		if (askFront == nullptr) //then there is nothing to buy from, so we queue it!
			insertBidBook(order);  //**NEED TO DEFINE
		else {
			//we look through the ask queue
			queueNode* ptr = askFront; //used to go through queue
			queueNode* prev = nullptr;
			while (ptr != nullptr && ptr->p->getPrice() >= order->getPrice()) {
				//moves through the queue until we get to the limit price (wont pay more)
				prev = ptr;
				ptr = ptr->next;
			}
			//once we found the match, we check if the ask is exact number of shares
			if(ptr->p->getNumShares()== order->getNumShares()){ //if it is
				//display(); //we display a match, **NEED TO DEFINE
				deleteOrder(ptr); //deletes the node we matched with **NEED OVERLOAD FUNCTION
				match = true; //because we had exact match
			}
			else if(ptr->p->getNumShares() > order->getNumShares()){ //it is not an exact match
				//display(); //display what we matched
				order->setNumShares(order->getNumShares() - ptr->p->getNumShares()); //update order
				matchLimited(order); //we send order back to check for another match
			}
			else if (ptr->p->getNumShares() < order->getNumShares()) { //it is not exact BUT we matched, so we update what the ptr is pointing to
				//display(); //display what we matched
				ptr->p->setNumShares(ptr->p->getNumShares() - order->getNumShares()); //update order
				//no need send anything back because we updated the order ptr was pointing to
				match = true; //because we had more shares than we needed
			}
			else if (match == false) {//we exhausted all possibilities and still no match
				insertBidBook(order);
			}
		}
	}
	else { //it is a ask/sell
		if (bidFront = nullptr)//it is empty
			insertAskBook(order);
		else {
			//we look through the bid queue
			queueNode* ptr = bidFront; //used to go through queue
			queueNode* prev = nullptr;
			//descending queue, so we go through until we find price thats less than or equal
			while (ptr != nullptr && order->getPrice() <= ptr->p->getPrice()) {
				prev = ptr;
				ptr = ptr->next;
			}
			if (ptr->p->getNumShares() == order->getNumShares()) { //if it is
				//display(); //we display a match, **NEED TO DEFINE
				deleteOrder(ptr); //deletes the node we matched with **NEED OVERLOAD FUNCTION
				match = true; //because we had exact match
			}
			else if (ptr->p->getNumShares() > order->getNumShares()) { //it is not an exact match
				//display(); //display what we matched
				order->setNumShares(order->getNumShares() - ptr->p->getNumShares()); //update order
				matchLimited(order); //we send order back to check for another match
			}
			else if (ptr->p->getNumShares() < order->getNumShares()) { //it is not exact BUT we matched, so we update what the ptr is pointing to
				//display(); //display what we matched
				ptr->p->setNumShares(ptr->p->getNumShares() - order->getNumShares()); //update order
				//no need send anything back because we updated the order ptr was pointing to
				match = true; //because we had more shares than we needed
			}
			else if (match == false) //we exhausted all possibilities and still no match
				insertAskBook(order);
		}
	}
}

//process the transactions (matches) and record them in an audit (transaction) file as follows: Buyer ID, Seller ID, Price, Shares, Time Stamp 
void OrderBook::display(Order* current, Order* book) {
	if (current->getAction()==1){
		//1 means bid order, so display buyerID first
		cout << current->getID() << "  " << book->getID() << "  " << book->getPrice() << "  " << current->getNumShares() << "  " << "time stamp";
	}
	else{
		cout << book->getID() << "  " << current->getID() << "  " << book->getPrice() << "  " << current->getNumShares() << "  " << "time stamp";
	}
}


void Queue::display() {
	cout << "YEEEEER" << endl;
}