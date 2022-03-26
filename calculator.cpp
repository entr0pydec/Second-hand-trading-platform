#include"calculator.h"

string digital = "1234567890.";
string datachar = "";
string all_char = "1234567890.+-*/() ";

int isp(char a)//栈内优先级
{
	switch (a)
	{
	case '(':return 1;
	case '_':
	case 's':
	case 't':
	case 'c':return 6;
	case '*':
	case '/':return 5;
	case '+':
	case '-':return 3;
	case ')':return 8;
	default:return 0;
	}
}

int icp(char a)//栈外优先级
{
	switch (a)
	{
	case '(':return 8;
	case '_':
	case 's':
	case 't':
	case 'c':return 7;
	case '*':
	case '/':return 4;
	case '+':
	case '-':return 2;
	case ')':return 1;
	default:return 0;
	}
}

bool dooperator(double* arr, int& n, char op)
{
	double i = arr[n - 2], j = arr[n - 1];
	n = n - 2;
	switch (op)
	{
	case '+':arr[n++] = i + j; break;
	case '-':arr[n++] = i - j; break;
	case '*':arr[n++] = i * j; break;
	case '/':if (j == 0)return 0; arr[n++] = i / j; break;
	case '_':n++; arr[n++] = -j; break;
	case 's':n++; arr[n++] = sin(j); break;
	case 'c':n++; arr[n++] = cos(j); break;
	case 't':n++; arr[n++] = tan(j); break;
	}
	return 1;
}

double calculator(string expression, bool& zero, bool &count)
{
	char stack[1000];
	elem output[1000];
	double newstack[1000] = { 0 };
	char ch;
	int n = 0, top = -1;
	int i;
	for (i = 0; i < expression.length(); i++)
	{
		int temp = i - 1;
		while (expression[i] == ' ')
		{
			i++;
		}
		if (expression[i] == '-' && (temp == -1 || expression[temp] == '(' || expression[temp] == 'n' || expression[temp] == 's' || expression[temp] == 'S' || expression[temp] == 'N'))expression[i] = '_';
		if (expression[i] <= '9' && expression[i] >= '0' || expression[i] == 'p' || expression[i] == 'P')
		{
			output[n++].data = get_data(expression, i, count);
			if (!count) return 0;
			output[n - 1].flag = 1;
		}
		else
		{
			if (top == -1)
			{
				if (expression[i] == 's' || expression[i] == 'S')
				{
					stack[++top] = 's';
					i = i + 2;
				}
				else if (expression[i] == 'c' || expression[i] == 'C')
				{
					stack[++top] = 'c';
					i = i + 2;
				}
				else if (expression[i] == 't' || expression[i] == 'T')
				{
					stack[++top] = 't';
					i = i + 2;
				}
				else stack[++top] = expression[i];
			}
			else
			{
				char temp = 0;
				while (icp(expression[i]) < isp(stack[top]))
				{
					output[n++].op = stack[top--];
					output[n - 1].flag = 0;
				}
				while (icp(expression[i]) == isp(stack[top]))
					if (stack[top--] == '(' || top == -1)
					{
						temp = stack[top + 1];
						if (temp == '(')break;
						stack[top + 1] = 0;
						break;
					}
				if (temp == '(')continue;
				if (icp(expression[i]) > isp(stack[top]))
					if (expression[i] == 's' || expression[i] == 'S')
					{
						stack[++top] = 's';
						i = i + 2;
					}
					else if (expression[i] == 'c' || expression[i] == 'C')
					{
						stack[++top] = 'c';
						i = i + 2;
					}
					else if (expression[i] == 't' || expression[i] == 'T')
					{
						stack[++top] = 't';
						i = i + 2;
					}
					else stack[++top] = expression[i];
			}
		}
	}
	while (top >= 0)
	{
		output[n++].op = stack[top--];
		output[n - 1].flag = 0;
	}
	top = 0;
	for (int i = 0; i < n; i++)
	{
		if (output[i].flag == 0)
		{
			zero = dooperator(newstack, top, output[i].op);
			if (zero == 0)return 0;
		}
		else newstack[top++] = output[i].data;
	}
	return newstack[0];
}

bool be_in(char a, string target)
{
	int i;
	for (i = 0; i < target.length(); i++)
		if (a == target[i])return 1;
	return 0;
}

double get_data(string expression, int& index, bool& count)
{
	if (expression[index] == 'p' || expression[index] == 'P')
		if (expression[index + 1] == 'i' || expression[index + 1] == 'I')
		{
			index++;
			return 3.1415926535;
		}
	int start = index, mark = -1;
	while (be_in(expression[index], digital))
	{
		index++;
		if (expression[index] == '.')mark = index;
	}
	double ans = 0, ans2 = 0;
	int i;
	if (mark == -1)
		for (i = start; i < index; i++)
			ans = ans * 10 + expression[i] - '0';
	else
	{
		for (i = start; i < mark; i++)
			ans = ans * 10 + expression[i] - '0';
		for (i = index - 1; i > mark; i--)
			ans2 = ans2 / 10 + expression[i] - '0';
		if (index - mark > 2) {
			count = 0;
			return 0;
		}
		ans += ans2 / 10;
	}
	index--;
	return ans;
}

bool BracketValid(string str, int& index)
{
	int top = 0;
	int start = -1;
	char stack[100];
	for (int i = 0; i < str.length(); i++)
	{
		index = i;
		if (top == 0 && str[i] == ')')
		{
			return 0;
		}
		else
		{
			if (top != 0)
			{
				char chTop = stack[top - 1];
				if (chTop != '(')
				{
					return 0;
				}
			}
			if (str[i] == '(')
			{
				if (start == -1)start = i;
				stack[top++] = str[i];
			}
			else if (str[i] == ')')top--;
		}
	}
	index = start;
	if (top == 0)
		return 1;
	else
		return 0;
}

bool DataValid(string str, int& index)
{
	int i;
	for (i = 0; i < str.length(); i++)
	{
		index = i;
		if (!be_in(str[i], digital))continue;
		if (str[i] == '.')return 0;
		int count = 0;
		while (be_in(str[i], digital))
		{
			i++;
			if (str[i] == '.')count++;
		}
		if (count > 1 || str[i - 1] == '.')return 0;
		i--;
	}
	return 1;
}

bool CharValid(string str, int& index)
{
	int i;
	for (i = 0; i < str.length(); i++)
	{
		index = i;
		if (be_in(str[i], datachar))
		{
			if ((str[i] == 's') || (str[i] == 'S'))
			{
				if (i > str.length() - 3)return 0;
				else if (((str[++i] == 'i') || (str[i] == 'I')) && ((str[++i] == 'n') || (str[i] == 'N')))continue;
				return 0;
			}
			if ((str[i] == 'c') || (str[i] == 'C'))
			{
				if (i > str.length() - 3)return 0;
				else if (((str[++i] == 'o') || (str[i] == 'O')) && ((str[++i] == 's') || (str[i] == 'S')))continue;
				return 0;
			}
			if ((str[i] == 't') || (str[i] == 'T'))
			{
				if (i > str.length() - 3)return 0;
				else if (((str[++i] == 'a') || (str[i] == 'A')) && ((str[++i] == 'n' || str[i] == 'N')))continue;
				return 0;
			}
			if (str[i] == 'p' || str[i] == 'P')
			{
				if (i > str.length() - 2)return 0;
				else if ((str[++i] == 'i') || (str[i] == 'I'))continue;
				return 0;
			}
			return 0;
		}
	}
	return 1;
}

bool is_double(char ch)
{
	if (ch == 'p' || ch == 'P' || be_in(ch, digital))return 1;
	return 0;
}

bool is_arc(char ch)
{
	switch (ch)
	{
	case's':
	case'S':
	case'c':
	case'C':
	case't':
	case'T':return 1;
	default:return 0;
	}
}

int judge_expression(string expression, int& index)
{
	int i;
	if (!BracketValid(expression, index))return 2;//括号不匹配
	if (!DataValid(expression, index))return 5;//输入的数据有问题
	if (!CharValid(expression, index))return 6;//输入的字符有问题
	for (i = 0; i < expression.length(); i++)
		if (!be_in(expression[i], all_char))
		{
			index = i;
			return 1;//有非法字符输入
		}
	for (i = 0; i < expression.length(); i++)
	{
		index = i;
		int j = i + 1;
		while (expression[j] == ' ')j++;
		index = j;
		if (expression[i] == ' ' && i != 0 && i != expression.length() - 1)
			if ((expression[i - 1] == 'i' || be_in(expression[i - 1], digital)) && (expression[j] == 'p' || be_in(expression[j], digital))) return 12;//不当的空格分隔
		if (i == 0 && !is_double(expression[i]) && !is_arc(expression[i]) && expression[i] != '-' && expression[i] != '(' && expression[i] != ' ')return 3;//开头有误
		if (i == expression.length() - 1 && !be_in(expression[i], digital) && expression[i] != ')' && expression[i] != 'i' && expression[i] != 'I' && expression[i] != ' ')return 4;//结尾有误
		if (expression[i] == '-' || expression[i] == '+' || expression[i] == '*' || expression[i] == '/')
			if (!is_double(expression[j]) && !is_arc(expression[j]) && expression[j] != '(' && expression[j] != ' ')return 7;//操作符后不能是右括号或者操作符
		if (expression[i] == 'n' || expression[i] == 's' || expression[i] == 'N' || expression[i] == 'S')
			if (expression[j] != 'i' && expression[j] != 'I' && !is_double(expression[j]) && !is_arc(expression[j]) && expression[j] != '(' && expression[j] != '-' && expression[j] != ' ')return 8;//三角函数后不能是右括号和除负号之外的其它操作符
		if (be_in(expression[i], digital) || expression[i] == 'i' || expression[i] == 'I')
			if (expression[j] == '(' || is_arc(expression[j]))return 9;//实数后面不能是左括号或者三角函数或者实数
		if (expression[i] == '(')
			if (expression[j] != '(' && !is_arc(expression[j]) && !is_double(expression[j]) && expression[j] != ' ' && expression[j] != '-')return 10;//左括号后面不可以是右括号或者除负号在外的操作符
		if (expression[i] == ')' && i != expression.length() - 1)
			if (expression[j] != '-' && expression[j] != '+' && expression[j] != '*' && expression[j] != '/' && expression[j] != ')' && expression[j] != ' ')return 11; //右括号后面不可以是左括号或者操作数或者三角函数	
	}
	return 0;
}

string show_error(int flag)
{
	switch (flag)
	{
	case 1:return "有非法字符输入"; break;
	case 2:return "括号不匹配"; break;
	case 3:return "开头必须是实数，三角函数，负号或者左括号"; break;
	case 4:return "结尾必须是实数或者右括号"; break;
	case 5:return "输入非法的数据"; break;
	case 6:return "输入非法的字符搭配"; break;
	case 7:return "操作符后不能是右括号或者操作符"; break;
	case 8:return "三角函数后不能是右括号和除负号之外的其它操作符"; break;
	case 9:return "实数后面不能是左括号或者三角函数或者实数"; break;
	case 10:return "左括号后面不可以是右括号或者除负号在外的操作符"; break;
	case 11:return "右括号后面不可以是左括号或者操作数或者三角函数"; break;
	case 12:return "不当的空格分隔"; break;
	}
	return "";
}

void spacedelete(string& str)
{
	int i = str.length() - 1;
	while (str[i] == ' ')i--;
	str.resize(i + 1);
}

string useCal(string input)
{
	int error;
	bool zero=1, count=1;
	spacedelete(input);
	int flag = judge_expression(input, error);
	double ans=0;
	string res = "";
	if (!flag) {
		ans = calculator(input, zero, count);
		if (!zero) 
			res	= "被除数不能为0";
		else if (!count)
			res = "小数点后不能超过2位";
		else {
			char buffer[100];
			sprintf(buffer, "%.1f", ans);
			res = buffer;
		}
	}
	else 
		res=show_error(flag);
	return res;
}
