#pragma once
#include<vector>
#include<map>
#include"person.h"
#include"command.h"
#include"transaction.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
using namespace std;

char judgeCh(char ch);
bool judgeStr(string info, char type);
char myGetch();

class Interface {
private:
	friend class Command;
	void adminSignIn();//管理员登录界面
	void userCreate();//用户注册界面
	void userSignIn();//用户登录界面
public:
	static vector<User> users;//用户表
	static vector<Commodity> commodities;//商品表
	static vector<Order> orders;//订单表
	static map<string,vector<recharge>> records;//充值记录表
	static void pushTxt(string fileName);
	static void pushCmd(string cmdStr);
	static void pushRecharge(string uid, double account);
	static string getBalance(string uid);//利用计算器计算用户余额
	static string getDate();//获得日期
	static string getTime();//获得时间
	Interface();
	void mainInterface();//主界面
};