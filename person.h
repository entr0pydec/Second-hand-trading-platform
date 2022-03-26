#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<string>
using namespace std;

class Command;

struct recharge {
	string money;
	string time;
};

class User {
private:
	string uid;//用户ID 
	string name;//用户名
	string password;//密码
	string phoneNumber;//联系方式
	string address;//地址
	double money;//钱包余额
	bool state;//用户状态 0:被封禁 1:未被封禁
public:
	static int maxAddrLen;
	User(string inUid, string inName, string inPassword, string inPhoneNumber, string inAddress);
	User* signIn(string inname, string inPwd);//用户登录
	void showInterface();//用户界面
	void pushTo(ostream& file);//输出信息到文件
	void setState(bool flag);//更改用户状态
	void setMoney(double inMoney);//更改余额
	void printInfo(char type);//打印信息
	bool match(char type, string info);//信息匹配
	bool update(string column, string value);//更新信息

	//管理信息
	void infoItf();//信息界面
	void showInfo();//查看信息
	void changeInfo();//修改信息
	void charge();//充值

	//买家
	void buyerItf();
	void searchComm();//搜索商品
	void showDetail();//显示商品详细信息
	void buyComm();//购买商品
	Command buyerCmd(string cmdStr, bool& succ);//执行买家命令

	//卖家
	void sellerItf();//卖家页面
	void releaseComm();//发布商品
	void showComm(bool type);//查看发布商品
	void changeComm();//修改商品信息
	void banComm();//下架商品
	void showOrders(bool type);//查看订单
	Command sellerCmd(string cmdStr,bool &succ);//执行卖家命令
};

class Administer
{
private:
	string name;//用户名
	string password;//密码
	Command doCmd(string cmdStr, bool &succ);//处理命令
	void showComms();//查看所有商品
	void searchComm();//搜索商品
	void banComm();//下架商品
	void showOrders();//查看所有订单
	void showUsers();//查看所有用户
	void banUser();//封禁用户
public:
	Administer();
	bool signIn(string inname, string inPwd);//管理员登录
	void showInterface();//管理员界面
};
