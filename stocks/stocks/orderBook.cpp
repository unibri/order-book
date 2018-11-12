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
				if (orderPtr->getType() == 1) { //if type = bid(buy) (1)
					//call matchMBid()
				}
				else { //type = sell(ask) (-1_
					//call matchMAsk()
				}
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
	while (currentPtr->getNumShares > Front->p->getNumShares)
		{
		display(currentPtr,Front->p);  //record the transaction;
		currentPtr->setNumShares(currentPtr->getNumShares - Front->p->getNumShares);

		deleteOrder(action);
		
		if (Front->next = nullptr) {
			match = false;
			int t;
			t = currentPtr->getNumShares - Front->p->getNumShares;
			currentPtr->setNumShares(t);
			inbalance(currentPtr);
			break;
		}

		

		} //match finish, there're remained shares, display message and break 

	};//match going on
	
	if (currentPtr->getNumShares == nowFront->p->getNumShares) & (match) {} //match finish, break
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