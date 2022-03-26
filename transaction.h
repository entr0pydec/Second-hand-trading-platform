#pragma once
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Commodity {
private:
	string cid;//商品id
	string name;//名称
	double price;//价格
	int quantity;//数量
	string description;//描述
	string sellerID;//卖家id
	string releaseTime;//上架时间
	bool state;//商品状态 0:已下架 1:销售中
public:
	Commodity(string inCid,string inName,double inPrice,int inQtt,string inDpt,string inSid,string time);
	void setState(bool flag);
	void printInfo(char type);//打印信息
	void pushTo(ostream& file);//输出信息到文件
	bool match(char type, string info);//对商品信息进行匹配筛选
	bool update(string column, string value);//更新商品信息
	int compare(int count);//比较数量
	string getSid();//获取卖家ID
	string getCid();//获取商品ID
	string getPrice();//获取商品ID
};

class Order {
private:
	friend class Interface;
	string oid;//订单id
	string cid;//商品id
	double price;//交易单价
	int quantity;//数量
	string time;//交易时间
	string buyerID;//买家id
	string sellerID;//卖家id
public:
	Order(string orderID, string commodityID, double unitPrice, int number, string date, string inSellerID, string inBuyerID);
	void printInfo(char type);//打印信息
	void pushTo(ostream& fime);//输出信息到文件
	bool match(char type, string info);//对订单信息进行匹配筛选
	string getPrice();//获取单价
};