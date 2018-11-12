#ifndef ORDER_H
#define ORDER_H
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
using std::string;

class Order{
private:
	int type; // 0:market order, 1:limited order
	int action; //1:bid(buy), -1:ask(sell)
	double price;
	int numShares; //stores number of shares
	string ID;

public:
	Order();
	~Order();
	void setType(int t) {
		type = t;
	}
	void setAction(int t) {
		action = t;
	}
	void setPrice(double t) {
		price = t;
	}
	void setNumShares(int t) {
		numShares = t;
	}
	void setID(string s) {
		ID = s;
	}
	int getType() {
		return type;
	}
	int getAction() {
		return action;
	}
	double getPrice() {
		return price;
	}
	int getNumShares{
		return numShares;
	}
	string getID() {
		return ID;
	}
};

#endif