#ifndef ORDER_H
#define ORDER_H
#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <fstream>
#include <ctime> 
#include <random>

using namespace std;
using std::string;

class Order{
private:
	int type; // 0:market order, 1:limited order
	int action; //1:bid(buy), -1:ask(sell)
	double price;
	int numShares; //stores number of shares
	string ID;
	time_t time; //stores time stamp

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
	void setTime(time_t t) {
		time = t;
	}
	//ACCESSOR FUNCTIONS
	int getType() {
		return type;
	}
	int getAction() {
		return action;
	}
	double getPrice()const {
		return price;
	}
	int getNumShares(){
		return numShares;
	}
	string getID() {
		return ID;
	}
	time_t getTime() {
		return time;
	}
	//OVERLOADED OPERATORS
	friend ostream& operator << (ostream& os, const Order&);
	friend istream& operator >> (istream&, Order*);
	bool operator==(const Order&);
};


#endif