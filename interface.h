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
	void adminSignIn();//����Ա��¼����
	void userCreate();//�û�ע�����
	void userSignIn();//�û���¼����
public:
	static vector<User> users;//�û���
	static vector<Commodity> commodities;//��Ʒ��
	static vector<Order> orders;//������
	static map<string,vector<recharge>> records;//��ֵ��¼��
	static void pushTxt(string fileName);
	static void pushCmd(string cmdStr);
	static void pushRecharge(string uid, double account);
	static string getBalance(string uid);//���ü����������û����
	static string getDate();//�������
	static string getTime();//���ʱ��
	Interface();
	void mainInterface();//������
};