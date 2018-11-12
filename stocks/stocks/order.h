//this is for the order class
#ifndef ORDER_H
#define ORDER_H
#include<string>
using namespace std;

class order
{
protected:
	int type; // 0:market order, 1:limited order
	int action; //1:bid(buy), -1:ask(sell)
	double price;
	string ID;
	long int share;
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
	long int getShare()
	{
		return share;
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

class ask : public order
{
public:
	bool operator >(order& r)
	{
		return share < r.getShare();  // adjust to askBook queue priority
	}
	
	bool operator =(order& r)
	{
		return share = r.getShare();
	}

class bid : public order
{
public:
	bool operator >(order& r)
	{
		return share > r.getShare();  
	}
	
	bool operator =(order& r)
	{
		return share = r.getShare();
	}

};
#endif