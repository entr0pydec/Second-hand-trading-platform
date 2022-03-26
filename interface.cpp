#include<cstdio>
#include"interface.h"
#include"person.h"
#include"calculator.h"

char myGetch() {
    char c;
	system("stty -echo");
	system("stty -icanon");
	c=getchar();
	system("stty icanon");
	system("stty echo");
	return c;
}

void createFile(string fileName) {
	ifstream input(fileName);
	if (!input) {
		ofstream newFile(fileName);
		if (fileName == "user.txt")
			newFile << "userID,username,password,phoneNumber,address,balance,userState";
		else if (fileName == "commodity.txt")
			newFile << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
		else if (fileName == "order.txt")
			newFile << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
		newFile.close();
	}
}

vector<User> Interface::users = {};
vector<Order> Interface::orders = {};
vector<Commodity> Interface::commodities = {};
map<string,vector<recharge>> Interface::records = {};

Interface::Interface() {
	createFile("user.txt");
	createFile("commodity.txt");
	createFile("order.txt");
	createFile("commands.txt");
	createFile("recharge.txt");

	//读取users
	ifstream userTxt("user.txt");
	if (!userTxt.is_open()) exit(-1);
	string line;
	getline(userTxt,line);
	while (!userTxt.eof()) {
		getline(userTxt, line);
		vector<string> data;
		for (int i = 0; i < 7; i++) {
			int index = line.find(",");
			data.push_back(line.substr(0, index));
			line = line.substr(index+1, line.length() - index-1);
		}
		User user(data[0],data[1],data[2],data[3],data[4]);
		double m = atof(data[5].c_str());
		bool s = data[6] == "active";
		user.setMoney(m);
		user.setState(s);
		users.push_back(user);
	}

	//读取commodities
	ifstream commTxt("commodity.txt");
	if (!userTxt.is_open()) exit(-1);
	getline(commTxt, line);
	while (!commTxt.eof()) {
		getline(commTxt, line);
		vector<string> data;
		for (int i = 0; i < 8; i++) {
			int index = line.find(",");
			data.push_back(line.substr(0, index));
			line = line.substr(index + 1, line.length() - index - 1);
		}
		double p = atof(data[2].c_str());
		int n = atof(data[3].c_str());
		bool s = data[7] == "onSale";
		Commodity comm(data[0], data[1], p, n, data[4], data[5], data[6]);
		comm.setState(s);
		commodities.push_back(comm);
	}

	//读取订单
	ifstream orderTxt("order.txt");
	if (!orderTxt.is_open()) exit(-1);
	getline(orderTxt, line);
	while (!orderTxt.eof()) {
		getline(orderTxt, line);
		vector<string> data;
		for (int i = 0; i < 7; i++) {
			int index = line.find(",");
			data.push_back(line.substr(0, index));
			line = line.substr(index + 1, line.length() - index - 1);
		}
		double p = atof(data[2].c_str());
		int n = atof(data[3].c_str());
		Order order(data[0], data[1], p, n, data[4], data[5], data[6]);
		orders.push_back(order);
	}

	//读取充值记录
	ifstream rechargeTxt("recharge.txt");
	if (!rechargeTxt.is_open()) exit(-1);
	while (!rechargeTxt.eof()) {
		getline(rechargeTxt, line);
		if (line.length()) {
			vector<string> data;
			for (int i = 0; i < 3; i++) {
				int index = line.find(",");
				data.push_back(line.substr(0, index));
				line = line.substr(index + 1, line.length() - index - 1);
			}
			recharge record;
			record.money = data[1];
			record.time = data[2];
			if (records.find(data[0]) == records.end()) {
				vector<recharge> first;
				first.push_back(record);
				records.insert(pair<string, vector<recharge>>(data[0], first));
			}
			else {
				auto it = records.find(data[0]);
				it->second.push_back(record);
			}
		}
	}
}

void Interface::pushTxt(string fileName) {
	if (fileName == "user.txt") {
		ofstream txt(fileName);
		txt << "userID,username,password,phoneNumber,address,balance,userState";
		for (int i = 0; i < users.size(); i++) {
			users[i].pushTo(txt);
		}
		txt.close();
	}
	else if (fileName == "commodity.txt") {
		ofstream txt(fileName);
		txt << "commodityID,commodityName,price,number,description,sellerID,addedDate,state";
		for (int i = 0; i < commodities.size(); i++) {
			commodities[i].pushTo(txt);
		}
		txt.close();
	}
	else if (fileName == "order.txt") {
		ofstream txt(fileName);
		txt << "orderID,commodityID,unitPrice,number,date,sellerID,buyerID";
		for (int i = 0; i < orders.size(); i++) {
			orders[i].pushTo(txt);
		}
		txt.close();
	}
}

void Interface::pushCmd(string cmdStr) {
	ofstream file("commands.txt",ios::app);
	file << getDate() << " " << getTime() << ": " << cmdStr << endl;
	file.close();
}

void Interface::pushRecharge(string uid,double account) {
	ofstream file("recharge.txt", ios::app);
	file << uid << "," << setiosflags(ios::fixed) << setprecision(1) << account << "," << getDate() << endl;
	file.close();
	pushTxt("user.txt");
}

string Interface::getDate() {
	time_t t = time(NULL);
	struct tm* local = localtime(&t);

	string month = to_string(local->tm_mon);
	if (month.length() == 1) month = "0" + month;

	string day = to_string(local->tm_mday);
	if (day.length() == 1) day = "0" + day;

	string sTime = to_string(local->tm_year + 1900) + "-" + month + "-" + day;
	return sTime;
}

string Interface::getTime() {
	time_t t = time(NULL);
	struct tm* local = localtime(&t);

	string hour = to_string(local->tm_hour);
	if (hour.length() == 1) hour = "0" + hour;

	string minute = to_string(local->tm_min);
	if (minute.length() == 1) minute = "0" + minute;

	string second = to_string(local->tm_sec);
	if (second.length() == 1) second = "0" + second;

	string sTime = hour + ":" + minute + ":" + second;
	return sTime;
}

void Interface::mainInterface() {
	while (1) {
		system("clear");
		cout << "######################################################################" << endl;
		cout << "#欢迎来到冬奥纪念品二手交易平台，请按下键盘上的按键选择你要进行的操作#" << endl;
		cout << "#                      （之后的界面也是如此）                        #" << endl;
		cout << "#                          1，管理员登录                             #" << endl;
		cout << "#                          2，用户注册                               #" << endl;
		cout << "#                          3，用户登录                               #" << endl;
		cout << "#                          4，退出程序                               #" << endl;
		cout << "######################################################################" << endl;
		char ch;
		ch = myGetch();
		if (ch == '1') {
			adminSignIn();
		}
		else if (ch == '2') {
			userCreate();
		}
		else if (ch == '3') {
			userSignIn();
		}
		else if (ch == '4') {
			exit(-1);
		}
	}
}

void Interface::adminSignIn() {
	while (1) {
		system("clear");
		Administer admin;
		string inName, inPwd;
		cout << "             管理员登录            " << endl;
		cout << "(按下1返回主菜单，按其他任意键继续)" << endl;
		char ch = myGetch();
		if (ch == '1') return;
		cout << "请输入用户名：";
		cin >> inName;
		cout << "请输入密码：";
		cin >> inPwd;
		if (admin.signIn(inName, inPwd)){
			system("clear");
			admin.showInterface();
		}
		else{
			system("clear");
			cout << "用户名或密码错误！按任意键回到登录页面";
			myGetch();
			myGetch();
		}
	}
}

void Interface::userCreate() {
	system("clear");
	int num = users.size()+1;
	if (num > 999) {
		cout << "用户已满，按任意键返回" << endl;
		myGetch();
		myGetch();
		return;
	}
	cout << "               注册用户            " << endl;
	cout << "(按下1返回主菜单，按其他任意键继续)" << endl;
	char ch = myGetch();
	if (ch == '1') return;
	string name, addr, pwd, phoneNum;
	while (1) {
		cout << "请输入用户名：";
		cin >> name;
		if (name.length() > 10) {
			cout << "用户名不能超过10个字符！请重新输入" << endl;
			continue;
		}
		if (!judgeStr(name, 0)) {
			cout << "用户名只能包含英文字母！请重新输入" << endl;
			continue;
		}
		bool succ = 1;
		for (int i = 0; i < Interface::users.size(); i++) {
			if (Interface::users[i].match(1, name)) {
				cout << "该用户名被占用！请重新输入" << endl;
				succ = 0;
				break;
			}
		}
		if (succ) break;
	}
	cout << "------------------------" << endl;
	while (1) {
		cout << "请输入密码：";
		cin >> pwd;
		if (pwd.length() > 20) {
			cout << "密码不能超过20个字符！请重新输入" << endl;
			continue;
		}
		if (!judgeStr(pwd, 1)) {
			cout << "密码只能包含小写字母和数字！请重新输入" << endl;
			continue;
		}
		break;
	}
	cout << "------------------------" << endl;
	while (1) {
		cout << "请输入联系方式：";
		cin >> phoneNum;
		if (phoneNum.length() > 20) {
			cout << "联系方式不能超过20个字符！请重新输入" << endl;
			continue;
		}
		if (!judgeStr(phoneNum, 2)) {
			cout << "联系方式只能包含数字！请重新输入" << endl;
			continue;
		}
		break;
	}
	cout << "------------------------" << endl;
	while (1) {
		cout << "请输入地址：";
		cin >> addr;
		if (addr.length() > 40) {
			cout << "地址不能超过40个字符！请重新输入" << endl;
			continue;
		}
		if (!judgeStr(addr, 0)) {
			cout << "地址只能包含英文字母！请重新输入" << endl;
			continue;
		}
		break;
	}

	char buffer[4];
	string sid;
	sprintf(buffer, "%d", num);
	sid = buffer;
	while (sid.length() < 3) {
		sid = "0" + sid;
	}
	sid = "U" + sid;
	User newUser(sid,name,pwd,phoneNum,addr);
	users.push_back(newUser);
	pushTxt("user.txt");
	cout << "注册成功！按任意键返回主页面...";
	myGetch();
	myGetch();
}

void Interface::userSignIn() {
	while (1) {
		system("clear");
		cout << "             用户登录            " << endl;
		cout << "(按下1返回主菜单，按其他任意键继续)" << endl;
		char ch = myGetch();
		if (ch == '1') return;
		string inName, inPwd;
		cout << "请输入用户名：";
		cin >> inName;
		cout << "请输入密码：";
		cin >> inPwd;
		User* user = NULL;
		bool succ = 0;
		for (int i = 0; i < users.size(); i++) {
			user=users[i].signIn(inName,inPwd);
			if (user != NULL) {
				succ = 1;
				user->showInterface();
			}
		}
		if (succ) continue;
		system("clear");
		cout << "用户名或密码错误！按任意键返回登录页面";
		myGetch();
		myGetch();
	}
}

string Interface::getBalance(string uid) {
	string exp = "0";
	auto it=records.find(uid);
	if (it != records.end()) {
		for (int i = 0; i < it->second.size(); i++) {
			exp += "+" + it->second[i].money;
		}
	}
	map<int, vector<string>> bill;
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i].match(0, uid)) {
			int qtt=orders[i].quantity;
			auto it = bill.find(qtt);
			if (it != bill.end()) 
				it->second.push_back(orders[i].getPrice());
			else {
				vector<string> second;
				second.push_back(orders[i].getPrice());
				bill.insert(pair<int, vector<string>>(qtt, second));
			}
		}
		if (orders[i].match(1, uid)) {
			int qtt = orders[i].quantity;
			auto it = bill.find(qtt);
			if (it != bill.end())
				it->second.push_back("-"+orders[i].getPrice());
			else {
				vector<string> second;
				second.push_back("-"+orders[i].getPrice());
				bill.insert(pair<int, vector<string>>(qtt, second));
			}
		}
	}
	string partExp = "0";
	for (auto i = bill.begin(); i != bill.end(); i++) {
		partExp += "+" + to_string(i->first) + "*(0";
		for (int j = 0; j < i->second.size(); j++) {
			if (i->second[j][0]=='-')
				partExp += i->second[j];
			else
				partExp += "+" + i->second[j];
		}
		partExp += ")";
	}
	return useCal(exp + "+" + partExp);
}

char judgeCh(char ch) {
	//小写英文
	if (ch >= 'a' && ch <= 'z') return 0;
	//大写英文
	if (ch >= 'A' && ch <= 'Z') return 1;
	//数字
	if (ch >= '0' && ch <= '9') return 2;
	//小数点
	if (ch == '.') return 3;
	return 4;
}

bool judgeStr(string info,char type) {
	//只有英文字母
	if (type == 0) {
		for (int i = 0; i < info.size(); i++)
			if (!(judgeCh(info[i]) == 0
				|| judgeCh(info[i]) == 1))
				return 0;
	}
	//只有小写字母和数字
	else if (type == 1) {
		for (int i = 0; i < info.size(); i++)
			if (!(judgeCh(info[i]) == 0
				|| judgeCh(info[i]) == 2))
				return 0;
	}
	//只有数字
	else if (type == 2) {
		for (int i = 0; i < info.size(); i++)
			if (judgeCh(info[i]) != 2)
				return 0;
	}
	//一位小数
	else if (type == 3) {
		for (int i = 0; i < info.size(); i++)
			if (!(judgeCh(info[i]) == 2
				|| judgeCh(info[i]) == 3))
				return 0;
		if (info.find(".") != info.npos) {
			if (info.length() - info.find(".") > 2)
				return 0;
		}
	}

	return 1;
}
