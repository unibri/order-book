#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
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
	//MUTATOR FUNCTIONS
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
	//ACCESSOR FUNCTIONS
	int getType() {
		return type;
	}
	int getAction() {
		return action;
	}
	double getPrice() {
		return price;
	}
	int getNumShares(){
		return numShares;
	}
	string getID() {
		return ID;
	}
	//OVERLOADED OPERATORS
	friend ostream& operator << (ostream& os, const Order&);
	friend istream& operator >> (istream& is, Order* O) {
		is >> O->type >> O->action>> O->price >>
			O->numShares >> O->ID;
		return is;
	}
};

