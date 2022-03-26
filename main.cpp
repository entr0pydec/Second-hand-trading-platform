#include"calculator.h"
#include"interface.h"

#define _INTERFACE//控制应用或者计算器

int main(int arg,char** argv) {
#ifdef _INTERFACE
	Interface itf;
	itf.mainInterface();
#else
	string exp;
	cin>>exp;
	cout<<useCal(exp);
#endif
	return 0;
}