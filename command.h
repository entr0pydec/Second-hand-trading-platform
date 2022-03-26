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
	string content;//ָ������
	char type;//ָ������
	char target;//Ŀ���
	char condition;//��������
public:
	Command(string cmdStr);
	bool process();
	vector<User> users;//�û���
	vector<Commodity> commodities;//��Ʒ��
	vector<Order> orders;//������
};
