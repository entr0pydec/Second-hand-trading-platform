#pragma once
#include<iostream>
#include"person.h"
#include"transaction.h"
using namespace std;

enum {
	SELECT = 0, INSERT, UPDATE
};

enum {
	USER = 0, COMMODITY, ORDER
};

enum {
	NONE = 0, EQUAL, CONTAIN
};

class Command {
private:
	string content;//指令内容
	char type;//指令类型
	char target;//目标表
	char condition;//条件类型
public:
	Command(string cmdStr);
	bool process();
	vector<User> users;//用户表
	vector<Commodity> commodities;//商品表
	vector<Order> orders;//订单表
};
