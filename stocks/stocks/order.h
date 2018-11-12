//this is for the order class
#ifndef ORDER_H
#define ORDER_H
#include<string>
using namespace std;

class order
{
private:
	int type; // 0:market order, 1:limited order
	int action; //1:bid(buy), -1:ask(sell)
	double price;
	string ID;

public:
	order();
	~order();
	int getType()
	{
		return type;
	}
	int getAction()
	{
		return action;
	}
	double getPrice()
	{
		return price;
	}
	string getID()
	{
		return ID;
	}

	void setType(int t)
	{
		type = t;
	}
	void setAction(int t)
	{
		action = t;
	}
	void setprice(double t)
	{
		price = t;
	}
	void setID(string s)
	{
		ID = s;
	}

};
#endif