#pragma once
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Commodity {
private:
	string cid;//��Ʒid
	string name;//����
	double price;//�۸�
	int quantity;//����
	string description;//����
	string sellerID;//����id
	string releaseTime;//�ϼ�ʱ��
	bool state;//��Ʒ״̬ 0:���¼� 1:������
public:
	Commodity(string inCid,string inName,double inPrice,int inQtt,string inDpt,string inSid,string time);
	void setState(bool flag);
	void printInfo(char type);//��ӡ��Ϣ
	void pushTo(ostream& file);//�����Ϣ���ļ�
	bool match(char type, string info);//����Ʒ��Ϣ����ƥ��ɸѡ
	bool update(string column, string value);//������Ʒ��Ϣ
	int compare(int count);//�Ƚ�����
	string getSid();//��ȡ����ID
	string getCid();//��ȡ��ƷID
	string getPrice();//��ȡ��ƷID
};

class Order {
private:
	friend class Interface;
	string oid;//����id
	string cid;//��Ʒid
	double price;//���׵���
	int quantity;//����
	string time;//����ʱ��
	string buyerID;//���id
	string sellerID;//����id
public:
	Order(string orderID, string commodityID, double unitPrice, int number, string date, string inSellerID, string inBuyerID);
	void printInfo(char type);//��ӡ��Ϣ
	void pushTo(ostream& fime);//�����Ϣ���ļ�
	bool match(char type, string info);//�Զ�����Ϣ����ƥ��ɸѡ
	string getPrice();//��ȡ����
};