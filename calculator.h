#pragma once
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<stdlib.h>
using namespace std;

struct elem{
	double data;
	char op;
	bool flag;
};

int isp(char a);//ջ�����ȼ�
int icp(char a);//ջ�����ȼ�
double calculator(string expression, bool& zero, bool& count);//��ջ���е����ͼ���
bool dooperator(double* arr, int& n, char op);//����˫Ŀ�͵�Ŀ����
double get_data(string expression, int& index, bool& count);//�ж϶���ַ��ĺ��壬��ȡ������
int judge_expression(string expression, int& index);//�жϵ�ʽ�Ƿ�Ϸ�
bool BracketValid(string str, int& index);//����ƥ��
bool DataValid(string str, int& index);//������Ч��
bool CharValid(string str, int& index);//�ַ���Ч��
string show_error(int flag);//����
string useCal(string input);//���м���
bool is_double(char ch);
bool is_arc(char ch);
