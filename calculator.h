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

int isp(char a);//栈内优先级
int icp(char a);//栈外优先级
double calculator(string expression, bool& zero, bool& count);//对栈进行调整和计算
bool dooperator(double* arr, int& n, char op);//进行双目和单目计算
double get_data(string expression, int& index, bool& count);//判断多个字符的含义，提取浮点数
int judge_expression(string expression, int& index);//判断等式是否合法
bool BracketValid(string str, int& index);//括号匹配
bool DataValid(string str, int& index);//数据有效性
bool CharValid(string str, int& index);//字符有效性
string show_error(int flag);//报错
string useCal(string input);//进行计算
bool is_double(char ch);
bool is_arc(char ch);
