#include "orderBook.h"

/*DEFINITIONS FOR ORDERBOOK FUNCTIONS*/

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

/*
void Queue::enqueue(Order *info){
	queueNode *newNode = nullptr;

	newNode = new queueNode;
	newNode->p = info;
	newNode->next = nullptr;

	if (isEmpty()){
		front = newNode;
		rear = newNode;
	}
	else {
		rear->next = newNode;
		rear = newNode;
	}
	size++;
}
*/
/*
void Queue::dequeue(Order &info){// not quite sure &info
	queueNode *temp = nullptr;
	if (!isEmpty()){
		info = front->p;
		temp = front;
		front = front->next;
		delete temp;
		size--;
	}
}
*/

// i indicates order action. i=1, this is a buy order, check if the Askbook is empty
bool Queue::isEmpty(int i) const{
	bool status;
	int size;
	if (i == 1) size = aSize;
	else size = bSize;

	if (size > 0) 
		status = false;
	else 
		status = true;
	return status;
}

/*
void Queue::clearQ(){    // not quite sure p or *p
	Order p;
	while (!isEmpty()) dequeue(p);
}
*/

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
				matchMarket(orderPtr);
			}
			else { //if it is a limited order (1)
				//search for match search for match
			}
			getline(data, line); //moves on to the next line	
		}
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
	if (isEmpty(action)) {} // there is not match, display messeage "Market Inbalance - XXX order ID: XXX Volume: XXX - unmatched"

	// step 2: making match	
	match = true;
	while (currentPtr->getNumShares() > Front->p->getNumShares())
		{
		display(currentPtr,Front->p);  //record the transaction;
		currentPtr->setNumShares(currentPtr->getNumShares() - Front->p->getNumShares());

		deleteOrder(action);
		
		if (Front = nullptr) {
			if (currentPtr->getNumShares() != 0)
			{//nothing in the book but there're remaining shares
				match = false; 
				inbalance(currentPtr);
			}
			break;  
		}

	};//match going on
	
	if (currentPtr->getNumShares == Front->p->getNumShares) & (match=true) {
	
	} //match finish, break
	else {} //match finish and display message:market inbalance
	

	}

void OrderBook::inbalance(Order* p)
{
	//display messeage "Market Inbalance - XXX order ID: XXX Volume: XXX - unmatched"
	if (p->getAction() = 1)
		cout << "Market Inbalance - Buy Order ID:" << p->getID()<< " Volume:" << p->getNumShares << " - unmatched";
	else 
		cout << "Market Inbalance - Ask Order ID:" << p->getID() << " Volume:" << p->getNumShares << " - unmatched";
};
//basically a pop function, deletes first in queue
void OrderBook::deleteOrder(int action) {
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
void OrderBook::deleteOrder(queueNode* orderPtr) {

}
//inserts into bid book in descending order
void OrderBook::insertBidBook(Order* order) {
	queueNode* newNode;
	queueNode* nodePtr;
	queueNode* prevNode;
	newOrder = new queueNode; 
	newOrder->p = order; 

	if (!gradeHead) { //if there are no nodes
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
void OrderBook::insertAskBook(Order* order) {
	queueNode* newNode;
	queueNode* nodePtr;
	queueNode* prevNode;
	newOrder = new queueNode;
	newOrder->p = order;

	if (!gradeHead) { //if there are no nodes
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
void OrderBook::matchLimited(Order* order) {
	bool match = false;
	if (order->getAction() == 1) {//it is a bid/buy
		if (askHead == nullptr) //then there is nothing to buy from, so we queue it!
			insertBidBook(order);  //**NEED TO DEFINE
		else {
			//we look through the ask queue
			queueNode* ptr = askHead; //used to go through queue
			queueNode* prev = nullptr;
			while (ptr != nullptr && ptr->p->getPrice() >= order->getPrice()) {
				//moves through the queue until we get to the limit price (wont pay more)
				prev = ptr;
				ptr = ptr->next;
			}
			//once we found the match, we check if the ask is exact number of shares
			if(ptr->p->getNumShares()== order->getNumShares()){ //if it is
				display(); //we display a match, **NEED TO DEFINE
				deleteOrder(ptr); //deletes the node we matched with **NEED OVERLOAD FUNCTION
				match = true; //because we had exact match
			}
			else if(ptr->p->getNumShares() > order->getNumShares()){ //it is not an exact match
				display(); //display what we matched
				order->setNumShares(order->getNumShares() - ptr->p->getNumShares()); //update order
				matchLimited(order); //we send order back to check for another match
			}
			else if (ptr->p->getNumShares() < order->getNumShares()) { //it is not exact BUT we matched, so we update what the ptr is pointing to
				display(); //display what we matched
				ptr->p->setNumShares(ptr->p->getNumShares() - order->getNumShares()); //update order
				//no need send anything back because we updated the order ptr was pointing to
				match = true; //because we had more shares than we needed
			}
			if (match == false)//we exhausted all possibilities and still no match
				insertBidBook(order);

		}
	}
	else { //it is a ask/sell
		if (bidFront = nullptr)//it is empty
			insertAskBook(order);
		else {
			//we look through the bid queue
			queueNode* ptr = bidHead; //used to go through queue
			queueNode* prev = nullptr;
			//descending queue, so we go through until we find price thats less than or equal
			while (ptr != nullptr && order->getPrice() <= ptr->p->getPrice()) {
				prev = ptr;
				ptr = ptr->next;
			}
			if (ptr->p->getNumShares() == order->getNumShares()) { //if it is
				display(); //we display a match, **NEED TO DEFINE
				deleteOrder(ptr); //deletes the node we matched with **NEED OVERLOAD FUNCTION
				match = true; //because we had exact match
			}
			else if (ptr->p->getNumShares() > order->getNumShares()) { //it is not an exact match
				display(); //display what we matched
				order->setNumShares(order->getNumShares() - ptr->p->getNumShares()); //update order
				matchLimited(order); //we send order back to check for another match
			}
			else if (ptr->p->getNumShares() < order->getNumShares()) { //it is not exact BUT we matched, so we update what the ptr is pointing to
				display(); //display what we matched
				ptr->p->setNumShares(ptr->p->getNumShares() - order->getNumShares()); //update order
				//no need send anything back because we updated the order ptr was pointing to
				match = true; //because we had more shares than we needed
			}
			if (match == false)//we exhausted all possibilities and still no match
				insertAskBook(order);
		}
	}
}