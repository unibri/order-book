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


//inserts into bid book in descending order
void Queue::insertBidBook(Order* order) {
	queueNode* newNode;
	queueNode* nodePtr;
	queueNode* prevNode;
	newNode = new queueNode;
	newNode->p = order;

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
	double seconds;
	cout << "Enter the simulation delay in fraction of a second: ";
	cin >> seconds;
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
			timeDelay(seconds);
			time_t timeD = time(NULL);
			orderPtr->setTime(timeD);
			if (orderPtr->getType() == 0) { //if market order action =(0)
				matchMarket(orderPtr);
			}
			else { //if it is a limited order (1)
				matchLimited(orderPtr);
			}
			getline(data, line); //moves on to the next line	
		}
	}
	queueNode *ptr = askFront;
	cout << "THIS IS WHATS LEFT ON THE ASk BOOK: " << endl;
	while (ptr != nullptr) {
		cout << "$" << ptr->p->getPrice() << " " << ptr->p->getID() << " " << ptr->p->getTime() << endl;
			ptr = ptr->next;
	}
	cout << "THIS IS WHATS LEFT ON THE BID BOOK: " << endl;
	ptr = bidFront;
	while (ptr != nullptr) {
		cout << "$"<< ptr->p->getPrice()<<" "<< ptr->p->getID() << " " << ptr->p->getTime() << endl;
		ptr = ptr->next;
	}
}
//action=1, this is a buy order and check the AskBook
//action=-1, this is a sell order and check the BidBook

void OrderBook::matchMarket(Order* currentPtr)
{	
	queueNode *Front, *Rear;
	bool match = false;

	// decide which book to check
	if (currentPtr->getAction() == 1) 
		Front = askFront;
	else 
		Front = bidFront;
	// step 1: check if the book is empty
	if (Front == nullptr) 
		inbalance(currentPtr);  // there is not match, display messeage "Market Inbalance - XXX order ID: XXX Volume: XXX - unmatched"
	else {
		// step 2: making match	
		match = true;
		while (currentPtr->getNumShares() > Front->p->getNumShares())
		{
			display(currentPtr, Front->p, Front->p->getNumShares());  //record the transaction;
			currentPtr->setNumShares(currentPtr->getNumShares() - Front->p->getNumShares());
			deleteOrder(currentPtr->getAction());

			
			//for debug
			if (currentPtr->getAction() == 1) {
				Front = askFront;
				Rear = askRear;
			}
			else {
				Front = bidFront;
				Rear = bidRear;
			}
			
		
			if (Front == nullptr) {
		//nothing in the book but there're remaining shares		
					inbalance(currentPtr);
				
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

void OrderBook::inbalance(Order* p){
	//display messeage "Market Inbalance - XXX order ID: XXX Volume: XXX - unmatched"
	if (p->getAction() == 1)
		cout << "Market Inbalance - Buy Order ID:" << p->getID()<< " Volume:" << p->getNumShares() << " - unmatched"<<endl;
	else 
		cout << "Market Inbalance - Ask Order ID:" << p->getID() << " Volume:" << p->getNumShares() << " - unmatched"<<endl;
};

//just wanna try the old way

void OrderBook::matchLimited(Order* currentPtr)
{
	queueNode *Front, *Rear;
	bool match,base;

	// decide which book to check
	if (currentPtr->getAction() == 1) {
		Front = askFront;
		Rear = nullptr;
	}
	else {
		Front = bidFront;
		Rear = nullptr;
	}
	// step 1: check if the book is empty
	match = false;
	if (Front == nullptr) {
		
		if (currentPtr->getAction() == 1) insertBidBook(currentPtr);
		else insertAskBook(currentPtr); //if no match, just add current order to orderBook
	} 
	else {
		// step 2: check if price match. If yes, set the bottom price 	
		
		base = false;
		if (currentPtr->getAction() == 1) //buy order
		{
			if (currentPtr->getPrice() < Front->p->getPrice()) {  //even the first order in the queue is not satisfied, no price match
				insertBidBook(currentPtr);
			}
			else {
				match = true;
				queueNode* ptr = askFront;
				queueNode* prev = nullptr;
				while (ptr != nullptr &&  currentPtr->getPrice()>= (ptr->p->getPrice())) {
					//moves through the queue until we get to the limit price (wont pay more)
					prev = ptr;
					ptr = ptr->next;
				}
				if (ptr != nullptr) { Rear = ptr; base = true; } // will be the bottom price
			}
		}
		else {//sell order
			if (currentPtr->getPrice() > Front->p->getPrice()) {  //even the first order in the queue is not satisfied, no price match
				insertAskBook(currentPtr);
			}
			else {
				match = true;
				queueNode* ptr = bidFront; //used to go through queue
				queueNode* prev = nullptr;
				//descending queue, so we go through until we find price thats less than or equal
				while (ptr != nullptr && currentPtr->getPrice() <= (ptr->p->getPrice())) {
					prev = ptr;
					ptr = ptr->next;
				}
				if (ptr != nullptr) { Rear = ptr; base = true; }
			}
		}

		//step 3: match the shares

		if (match){
			
			while (currentPtr->getNumShares() > Front->p->getNumShares() && match)
			{
				currentPtr->setNumShares(currentPtr->getNumShares() - Front->p->getNumShares());
				display(currentPtr, Front->p, Front->p->getNumShares());  //record the transaction;
				
				deleteOrder(currentPtr->getAction());
				
				//for debug, it seems the Front won't auto move as AskFront moves
				if (currentPtr->getAction() == 1) { Front = askFront; }
				else { Front = bidFront; }

				if ((base && Front == Rear)||(!base && Front == nullptr)) {							
							if (currentPtr->getAction() == 1) { insertBidBook(currentPtr); }
							else { insertAskBook(currentPtr); }					
						match = false;
						break;
					}
			}
		};
		
	
		//match going on
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

//process the transactions (matches) and record them in an audit (transaction) file as follows: Buyer ID, Seller ID, Price, Shares, Time Stamp 

void OrderBook::display(Order* current, Order* book) {
	time_t curTime;
	curTime = time(NULL);

	if (current->getAction()==1){
		//1 means bid order, so display buyerID first
		cout << current->getID() << "  " << book->getID() << "  $" << book->getPrice() << "  " << current->getNumShares() << "  " << curTime <<endl;
	}
	else{
		cout << book->getID() << "  " << current->getID() << "  " << book->getPrice() << "  " << current->getNumShares() << "  " << curTime <<endl;
	}
}

void OrderBook::display(Order* current, Order* book, int share) {
	time_t curTime;
	curTime = time(NULL);

	if (current->getAction() == 1) {
		//1 means bid order, so display buyerID first
		cout << current->getID() << "  " << book->getID() << "  " << book->getPrice() << "  " << share << "  " << curTime << endl;
	}
	else {
		cout << book->getID() << "  " << current->getID() << "  " << book->getPrice() << "  " << share << "  " << curTime << endl;
	}
};


void OrderBook::timeDelay(double t) {
	time_t initial, final;  
	time_t ltime;  
	
	initial = time(&ltime);  
	final = initial + t;

	while (time(&ltime) < final) {}

	return;
}




