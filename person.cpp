#include"person.h"
#include"interface.h"
#include"command.h"
#include"transaction.h"
using namespace std;

Administer::Administer(){
	name = "admin";
	password = "123456";
}

bool Administer::signIn(string inname, string inPassword){
	if (inname == name && inPassword == password)
		return 1;
	else 
		return 0;
}

void Administer::showComms() {
	system("clear");
	bool succ = 1;
	Command cmd=doCmd("SELECT * FROM commodity",succ);
	if (succ) {
		if (cmd.commodities.size() > 0) {
			cout << "商品信息如下" << endl;
			cout.setf(ios::left);
			cout << setw(14) << "commodityID" << setw(16) << "commodityName"
				<< setw(10) << "price" << setw(11) << "addedDate"
				<< setw(10) << "sellerID" << setw(8) << "number" << "state" << endl;
			for (int i = 0; i < cmd.commodities.size(); i++)
				cmd.commodities[i].printInfo(0);
		}
		else cout << "暂时没有商品发布...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
}

void Administer::searchComm() {
	bool succ = 1;
	cout << "#########################" << endl;
	cout << "请输入商品名称：";
	string cmmdName;
	cin >> cmmdName;
	Command cmd=doCmd("SELECT * FROM commodity WHERE name CONTAINS " + cmmdName,succ);
	if (succ) {
		if (cmd.commodities.size() > 0) {
			system("clear");
			cout << "搜索到的商品信息如下" << endl;
			cout.setf(ios::left);
			cout << setw(14) << "commodityID" << setw(16) << "commodityName"
				<< setw(10) << "price" << setw(11) << "addedDate"
				<< setw(10) << "sellerID" << setw(8) << "number" << "state" << endl;
			for (int i = 0; i < cmd.commodities.size(); i++)
				cmd.commodities[i].printInfo(0);
		}
		else cout << "未找到符合要求的商品...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
	myGetch();
}

void Administer::banComm() {
	bool succ = 0;
	cout << "###########################" << endl;
	cout << "请输入要下架的商品ID：";
	string cid;
	cin >> cid;
	Commodity* comm = NULL;
	for (int i = 0; i < Interface::commodities.size(); i++) {
		comm = &Interface::commodities[i];
		if (comm->match(1, cid)) {
			succ = 1;
			break;
		}
	}
	if (succ) {
		cout << "确认要下架这个商品吗？" << endl;
		cout.setf(ios::left);
		cout << setw(14) << "commodityID" << setw(16) << "commodityName"
			<< setw(10) << "price" << setw(11) << "addedDate"
			<< setw(10) << "sellerID" << setw(8) << "number" << "state" << endl;
		comm->printInfo(0);
		cout << "请选择（y/n）:";
		string select;
		cin >> select;
		if (select == "y") {
			doCmd("UPDATE commodity SET state = removed WHERE cid = " + cid, succ);
			if (succ) cout << "操作成功,按下任意键返回";
		}
		else {
			cout << "取消下架,按下任意键返回";
		}
	}
	else cout << "未找到指定商品，按下任意键返回";
	myGetch();
	myGetch();
}

void Administer::showOrders() {
	system("clear");
	bool succ = 1;
	Command cmd = doCmd("SELECT * FROM order", succ);
	if (succ) {
		if (cmd.orders.size() > 0) {
			cout << "订单信息如下" << endl;
			cout.setf(ios::left);
			cout << setw(10) << "orderID" << setw(14) << "commodityID"
				<< setw(12) << "unitPrice" << setw(9) << "number"
				<< setw(11) << "date" << setw(10) << "sellerID" << "buyerID" << endl;
			for (int i = 0; i < cmd.orders.size(); i++)
				cmd.orders[i].printInfo(0);
		}
		else cout << "暂时没有订单...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
}

void Administer::showUsers() {
	system("clear");
	bool succ = 1;
	Command cmd = doCmd("SELECT * FROM user", succ);
	if (succ) {
		if (cmd.users.size() > 0) {
			cout << "用户信息如下" << endl;
			cout.setf(ios::left);
			cout << setw(9) << "userID" << setw(11) << "username"
				<< setw(21) << "phoneNumber" << setw(max(User::maxAddrLen + 1, 10)) << "address"
				<< setw(10) << "balance" << "userState" << endl;
			for (int i = 0; i < cmd.users.size(); i++)
				cmd.users[i].printInfo(0);
		}
		else cout << "暂时没有用户...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
}

void Administer::banUser() {
	bool succ = 0, succ2;
	cout << "###########################" << endl;
	cout << "请输入要封禁的用户ID：";
	string uid;
	cin >> uid;
	User* user = nullptr;
	for (int i = 0; i < Interface::users.size(); i++) {
		user = &Interface::users[i];
		if (user->match(0, uid)) {
			succ = 1;
			break;
		}
	}
	if (succ) {
		cout << "确定要封禁该用户吗？" << endl;
		cout.setf(ios::left);
		cout << setw(9) << "userID" << setw(11) << "username"
			<< setw(21) << "phoneNumber" << setw(max(User::maxAddrLen + 1, 10)) << "address"
			<< setw(10) << "balance" << endl;
		user->printInfo(1);
		cout << "请选择（y/n）:";
		string select;
		cin >> select;
		if (select == "y") {
			doCmd("UPDATE user SET state = inactive WHERE uid = " + uid, succ);
			doCmd("UPDATE commodity SET state = removed WHERE uid = " + uid, succ2);
			if (succ) cout << "操作成功，按下任意键返回";
		}
		else {
			cout << "取消封禁，按下任意键返回";
		}
	}
	else cout << "未找到指定用户，按下任意键返回";
	myGetch();
	myGetch();
}

void Administer::showInterface() {
	while (1) {
		system("clear");
		cout << "欢迎您，" << name << endl;
		cout << "1，查看所有商品" << endl;
		cout << "2，搜索商品" << endl;
		cout << "3，下架商品" << endl;
		cout << "4，查看所有订单" << endl;
		cout << "5，查看所有用户" << endl;
		cout << "6，封禁用户" << endl;
		cout << "7，注销" << endl;
		char ch=myGetch();
		if (ch == '1') showComms();
		else if (ch == '2') searchComm();
		else if (ch == '3') banComm();
		else if (ch == '4') showOrders();
		else if (ch == '5') showUsers();
		else if (ch == '6') banUser();
		else if (ch == '7') return;
	}
}

Command Administer::doCmd(string cmdStr,bool &succ) {
	Interface::pushCmd(cmdStr);
	Command cmd(cmdStr);
	succ=cmd.process();
	return cmd;
}

int User::maxAddrLen = 0;

User::User(string inUid, string inName, string inPassword, string inPhoneNumber, string inAddress) {
	uid = inUid;
	name = inName;
	password = inPassword;
	phoneNumber = inPhoneNumber;
	address = inAddress;
	maxAddrLen = maxAddrLen > inAddress.length() ? maxAddrLen : inAddress.length();
	money = 0.0;
	state = 1;
}

User* User::signIn(string inName, string inPwd) {
	if (inName == name && inPwd == password && state==1)
		return this;
	return NULL;
}

void User::showInfo() {
	cout.setf(ios::left);
	cout << "##############################" << endl;
	cout << setw(12) << "userName:" << name << endl;
	cout << setw(12) << "phoneNumber:" << phoneNumber << endl;
	cout << setw(12) << "address:" << address << endl;
	//TODO 重新计算balance
	string balance = Interface::getBalance(uid);
	if (money != atof(balance.c_str()))
		exit(2);
	cout << setw(12) << setiosflags(ios::fixed) << setprecision(1) << "balance:" << balance << endl;
	cout << "按下任意键返回" << endl;
	myGetch();
}

void User::changeInfo() {
	char ch;
	cout << "#################################################" << endl;
	cout << "请选择修改的属性（1，用户名  2，联系方式  3，地址）：";
	cin >> ch;
	if (ch == '1') {
		string newName;
		while (1) {
			cout << "请输入修改后的用户名：";
			cin >> newName;
			if (newName.length() > 10) {
				cout << "用户名不能超过10个字符！请重新输入" << endl;
				continue;
			}
			if (!judgeStr(newName, 0)) {
				cout << "用户名只能包含英文字母！请重新输入" << endl;
				continue;
			}
			bool succ = 1;
			for (int i = 0; i < Interface::users.size(); i++) {
				if (Interface::users[i].match(1, newName)) {
					succ = 0;
					break;
				}
			}
			if (name == newName) succ = 1;
			if (!succ) cout << "该用户名被占用！请重新输入" << endl; 
			else break;
		}
		name = newName;
		Interface::pushTxt("user.txt");
		cout << "修改成功，按任意键返回" << endl;
	}
	else if (ch == '2') {
		string newPhone;
		while (1) {
			cout << "请输入修改后的联系方式：" << endl;
			cin >> newPhone;
			if (newPhone.length() > 20) {
				cout << "联系方式不能超过20个字符！请重新输入" << endl;
				continue;
			}
			if (!judgeStr(newPhone, 2)) {
				cout << "联系方式只能包含数字！请重新输入" << endl;
				continue;
			}
			break;
		}
		phoneNumber = newPhone;
		Interface::pushTxt("user.txt");
		cout << "修改成功，按任意键返回" << endl;
	}
	else if (ch == '3') {
		string newAddr;
		while (1) {
			cout << "请输入修改后的地址：" << endl;
			cin >> newAddr;
			if (newAddr.length() > 40) {
				cout << "地址不能超过40个字符！请重新输入" << endl;
				continue;
			}
			if (!judgeStr(newAddr, 0)) {
				cout << "地址只能包含英文字母！请重新输入" << endl;
				continue;
			}
			break;
		}
		address = newAddr;
		Interface::pushTxt("user.txt");
		cout << "修改成功，按任意键返回" << endl;
	}
	myGetch();
	myGetch();
}

void User::charge() {
	string recharge;
	cout << "########################" << endl;
	while (1) {
		cout << "请输入充值金额（最多保留一位小数）：";
		cin >> recharge;
		if (!judgeStr(recharge, 3)) {
			cout << "充值金额不合法！请重新输入" << endl;
			continue;
		}
		break;
	}
	money += atof(recharge.c_str());
	Interface::pushRecharge(uid, atof(recharge.c_str()));
	cout << "充值成功，当前余额：" << setiosflags(ios::fixed) << setprecision(1) << money << endl;
	cout << "按下任意键返回" << endl;
	myGetch();
	myGetch();
}

void User::infoItf() {
	while (1) {
		system("clear");
		cout << "欢迎您，" << name << endl;
		cout << "1，查看信息" << endl;
		cout << "2，修改信息" << endl;
		cout << "3，充值" << endl;
		cout << "4，返回用户主界面" << endl;
		char ch=myGetch();
		if (ch == '1') {
			showInfo();
		}
		else if (ch == '2') {
			changeInfo();
		}
		else if (ch == '3') {
			charge();
		}
		else if (ch == '4') {
			return;
		}
	}
}

void User::showInterface() {
	while (1) {
		system("clear");
		cout << "欢迎您，" << name << endl;
		cout << "1，我是买家" << endl;
		cout << "2，我是卖家" << endl;
		cout << "3，个人信息管理" << endl;
		cout << "4，注销登录" << endl;
		char ch=myGetch();
		if (ch == '1') {
			buyerItf();
		}
		else if (ch == '2') {
			sellerItf();
		}
		else if (ch == '3') {
			infoItf();
		}
		else if (ch == '4') {
			return;
		}
	}
}

void User::pushTo(ostream& file) {
	string sState = "inactive";
	if (state == 1)
		sState = "active";
	file << endl << uid << "," << name << "," << password << "," 
		<< phoneNumber << "," << address << "," 
		<< setiosflags(ios::fixed) << setprecision(1) << money << "," << sState;
}

void User::setState(bool flag) {
	state = flag;
}

void User::setMoney(double inMoney) {
	money = inMoney;
}

void User::printInfo(char type) {
	string sState = "inactive";
	if (state == 1)
		sState = "active";
	if (type == 0) {
		cout << setw(9) << uid << setw(11) << name
			<< setw(21) << phoneNumber << setw(max(maxAddrLen + 1, 10)) << address
			<< setw(10) << setiosflags(ios::fixed) << setprecision(1) << money
			<< sState << endl;
	}
	else if (type == 1) {
		cout << setw(9) << uid << setw(11) << name
			<< setw(21) << phoneNumber << setw(max(maxAddrLen + 1, 10)) << address
			<< setw(10) << setiosflags(ios::fixed) << setprecision(1) << money<<endl;
	}
}

bool User::match(char type, string info) {
	//uid equal
	if (type == 0) {
		return uid == info;
	}
	//name equal
	else if (type == 1) {
		return name == info;
	}
	return 0;
}

bool User::update(string column, string value) {
	if (column == "state") {
		state = (value == "active");
		return 1;
	}

	return 0;
}

void User::releaseComm() {
	system("clear");
	int num = Interface::commodities.size() + 1;
	if (num > 999) {
		cout << "商品已满，按任意键返回"; 
		myGetch();
		myGetch();
		return;
	}

	string name, dpt, sPrice, count;
	double price;

	while (1) {
		cout << "请输入商品名称：" << endl;
		cin >> name;
		if (name.length() > 20) {
			cout << "商品名称不能超过20个字符！请重新输入" << endl;
			continue;
		}
		if (!judgeStr(name, 0)) {
			cout << "商品名称只能包含英文字母！请重新输入" << endl;
			continue;
		}
		break;
	}
	while (1) {
		cout << "请输入商品价格（最多保留一位小数）：" << endl;
		cin >> sPrice;
		if (!judgeStr(sPrice, 3)) {
			cout << "输入价格不合法，请重新输入" << endl;
			continue;
		}
		break;
	}
	while (1) {
		cout << "请输入商品数量：" << endl;
		cin >> count;
		if (!judgeStr(count, 2)) {
			cout << "输入数量不合法，请重新输入" << endl;
			continue;
		}
		break;
	}

	while (1) {
		cout << "请输入商品描述：" << endl;
		getchar();
		getline(cin,dpt);
		if (dpt.length() > 200) {
			cout << "商品描述不能超过200个字符，请重新输入" << endl;
			continue;
		}
		/*if (!judgeStr(dpt, 0)) {
			cout << "商品描述只能包含英文字符，请重新输入" << endl;
			continue;
		}*/
		break;
	}

	cout << "请确认发布的商品无误：" << endl;
	cout << "#########" << endl;
	cout << "商品名称：" << name << endl;
	cout << "商品价格：" << sPrice << endl;
	cout << "商品数量：" << count << endl;
	cout << "商品描述：" << dpt << endl;
	cout << "##########" << endl;
	cout << "您确认要发布商品吗？（y/n）：";
	string select;
	cin >> select;
	if (select == "y") {
		string cmdStr = "INSERT INTO commodity VALUES (" + name + "," + sPrice + "," + count + "," + dpt + ")";
		bool succ=0;
		sellerCmd(cmdStr, succ);
		if (succ) cout << "发布成功，按任意键返回" << endl;
	}
	else {
		cout << "取消发布，按任意键返回" << endl;
	}
	myGetch();
	myGetch();
}

void User::showComm(bool type) {
	system("clear");
	bool succ = 1;
	Command cmd = sellerCmd("SELECT * FROM commodity", succ);
	if (succ) {
		bool flag = 0;
		if (cmd.commodities.size() > 0) {
			if (!type) {
				for (int i = 0; i < cmd.commodities.size(); i++)
					if (cmd.commodities[i].match(2, uid)) {
						flag = 1;
						break;
					}
				if (flag) {
					cout << "商品信息如下" << endl;
					cout.setf(ios::left);
					cout << setw(14) << "commodityID" << setw(16) << "commodityName"
						<< setw(10) << "price" << setw(11) << "addedDate"
						<< setw(8) << "number" << "state" << endl;
					for (int i = 0; i < cmd.commodities.size(); i++)
						if (cmd.commodities[i].match(2, uid)) {
							flag = 1;
							cmd.commodities[i].printInfo(1);
						}
				}
				else cout << "你还没有发布商品...";
			}
			else {
				for (int i = 0; i < cmd.commodities.size(); i++)
					if (cmd.commodities[i].match(3, uid)) {
						flag = 1;
						break;
					}
				if (flag) {
					cout << "商品信息如下" << endl;
					cout.setf(ios::left);
					cout << setw(14) << "commodityID" << setw(16) << "commodityName"
						<< setw(10) << "price" << setw(11) << "addedDate"
						<< setw(8) << "number" << "sellerID" << endl;
					for (int i = 0; i < cmd.commodities.size(); i++)
						if (cmd.commodities[i].match(3, uid)) {
							flag = 1;
							cmd.commodities[i].printInfo(2);
						}
				}
				else cout << "暂时没有商品...";
			}	
		}
		else cout << "暂时没有商品发布...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
}

void User::changeComm() {
	string cid, type;
	bool flag = 0;
	cout << "############################################" << endl;
	cout << "请输入被修改商品的ID：";
	cin >> cid;
	for(int i=0;i<Interface::commodities.size();i++)
		if (Interface::commodities[i].match(1, cid) && Interface::commodities[i].match(2, uid)) {
			flag = 1;
		}
	if (!flag) {
		cout << "无法修改这个商品...按任意键返回";
		myGetch();
		myGetch();
		return;
	}
	cout << "请输入被修改商品的属性（1，价格  2，描述）：";
	cin >> type;
	if (type == "1") {
		string sPrice;
		while (1) {
			cout << "请输入被修改商品的价格（最多保留一位小数）：" << endl;
			cin >> sPrice;
			if (!judgeStr(sPrice, 3)) {
				cout << "输入价格不合法，请重新输入" << endl;
				continue;
			}
			break;
		}
		cout << "请确认修改的商品信息无误" << endl;
		cout << "#############" << endl;
		cout << "修改后的价格：" << sPrice << endl;
		cout << "#############" << endl;
		cout << "确认修改？（y/n）：";
		string select;
		cin >> select;
		if (select == "y") {
			bool succ = 0;
			sellerCmd("UPDATE commodity SET price = " + sPrice + " WHERE cid = " + cid, succ);
			if (succ)
				cout << "修改成功！按任意键返回";
			else exit(0);
		}
		else {
			cout << "取消修改，按任意键返回";
		}
		myGetch();
		myGetch();
		return;
	}
	else if (type == "2") {
		string dpt;
		while (1) {
			cout << "请输入被修改商品的描述：" << endl;
			cin >> dpt;
			if (dpt.length() > 200) {
				cout << "商品描述不能超过200个字符，请重新输入" << endl;
				continue;
			}
			if (!judgeStr(dpt, 0)) {
				cout << "商品描述只能包含英文，请重新输入" << endl;
				continue;
			}
			break;
		}
		cout << "请确认修改的商品信息无误" << endl;
		cout << "#############" << endl;
		cout << "修改后的描述：" << dpt << endl;
		cout << "#############" << endl;
		cout << "确认修改？（y/n）：";
		string select;
		cin >> select;
		if (select == "y") {
			bool succ = 0;
			sellerCmd("UPDATE commodity SET description = " + dpt + " WHERE cid = " + cid, succ);
			if (succ)
				cout << "修改成功！按任意键返回";
			else exit(0);
		}
		else {
			cout << "取消修改，按任意键返回";
		}
		myGetch();
		myGetch();
		return;
	}
}

void User::banComm() {
	cout << "###########################" << endl;
	cout << "请输入要下架的商品ID：";
	string cid;
	cin >> cid;

	Commodity* comm = nullptr;
	bool flag = 0;
	for (int i = 0; i < Interface::commodities.size(); i++)
		if (Interface::commodities[i].match(1, cid) && Interface::commodities[i].match(2, uid)) {
			flag = 1;
			comm = &Interface::commodities[i];
		}
	if (!flag) {
		cout << "无法修改这个商品...按任意键返回";
		myGetch();
		myGetch();
		return;
	}

	cout << "确认要下架这个商品吗？" << endl;
	cout.setf(ios::left);
	cout << setw(14) << "commodityID" << setw(16) << "commodityName"
		<< setw(10) << "price" << setw(11) << "addedDate"
		<< setw(10) << "sellerID" << setw(8) << "number" << "state" << endl;
	comm->printInfo(0);
	cout << "请选择（y/n）:";
	string select;
	cin >> select;
	if (select == "y") {
		bool succ = 1;
		sellerCmd("UPDATE commodity SET state = removed WHERE cid = " + cid, succ);
		if (succ) cout << "操作成功,按下任意键返回";
		else cout << "未找到指定商品，按下任意键返回";
	}
	else {
		cout << "取消下架，按任意键返回";
	}
	myGetch();
	myGetch();
}

void User::showOrders(bool type) {
	system("clear");
	bool succ = 1;
	Command cmd = sellerCmd("SELECT * FROM order", succ);
	if (succ) {
		bool flag = 0;
		if (cmd.orders.size() > 0) {
			if (!type) {
				for (int i = 0; i < cmd.orders.size(); i++)
					if (cmd.orders[i].match(0, uid)) {
						flag = 1;
						break;
					}
				if (flag) {
					cout.setf(ios::left);
					cout << setw(10) << "orderID" << setw(14) << "commodityID"
						<< setw(12) << "unitPrice" << setw(9) << "number"
						<< setw(11) << "date" << "buyerID" << endl;
					for (int i = 0; i < cmd.orders.size(); i++)
						if (cmd.orders[i].match(0, uid)) {
							flag = 1;
							cmd.orders[i].printInfo(1);
						}
				}
				else cout << "暂时没有订单...";
			}
			else {
				for (int i = 0; i < cmd.orders.size(); i++)
					if (cmd.orders[i].match(1, uid)) {
						flag = 1;
						break;
					}
				if (flag) {
					cout.setf(ios::left);
					cout << setw(10) << "orderID" << setw(14) << "commodityID"
						<< setw(12) << "unitPrice" << setw(9) << "number"
						<< setw(11) << "date" << "sellerID" << endl;
					for (int i = 0; i < cmd.orders.size(); i++)
						if (cmd.orders[i].match(1, uid)) {
							flag = 1;
							cmd.orders[i].printInfo(2);
						}
				}
				else cout << "暂时没有订单...";
			}
		}
		else cout << "暂时没有订单...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
}

Command User::sellerCmd(string cmdStr, bool& succ) {
	Interface::pushCmd(cmdStr);
	if (cmdStr.find("INSERT") != cmdStr.npos) {
		cmdStr = cmdStr.substr(0, cmdStr.length() - 1);

		char buffer[4];
		string cid;
		int num = Interface::commodities.size() + 1;
		sprintf(buffer, "%d", num);
		cid = buffer;
		while (cid.length() < 3) {
			cid = "0" + cid;
		}
		cid = "M" + cid;

		cmdStr = cmdStr + "," + cid + "," + uid + "," + Interface::getDate() + ")";

		Command cmd(cmdStr);
		succ = cmd.process();
		return cmd;
	}
	Command cmd(cmdStr);
	succ = cmd.process();
	return cmd;
}

void User::sellerItf() {
	while (1) {
		system("clear");
		cout << "1，发布商品" << endl;
		cout << "2，查看发布商品" << endl;
		cout << "3，修改商品信息" << endl;
		cout << "4，下架商品" << endl;
		cout << "5，查看历史订单" << endl;
		cout << "6，返回用户主界面" << endl;
		char ch=myGetch();
		if (ch == '1') {
			releaseComm();
		}
		else if (ch == '2') {
			showComm(0);
		}
		else if (ch == '3') {
			changeComm();
		}
		else if (ch == '4') {
			banComm();
		}
		else if (ch == '5') {
			showOrders(0);
		}
		else if (ch == '6') {
			return;
		}
	}
}

void User::searchComm() {
	bool succ = 1;
	cout << "#########################" << endl;
	cout << "请输入商品名称：";
	string cmmdName;
	cin >> cmmdName;
	Command cmd = buyerCmd("SELECT * FROM commodity WHERE name CONTAINS " + cmmdName, succ);
	if (succ) {
		bool flag = 0;
		if (cmd.commodities.size() > 0) {
			for (int i = 0; i < cmd.commodities.size(); i++)
				if (cmd.commodities[i].match(3, uid)) {
					flag = 1;
					break;
				}
			if (flag) {
				system("clear");
				cout << "搜索到的商品信息如下" << endl;
				cout.setf(ios::left);
				cout << setw(14) << "commodityID" << setw(16) << "commodityName"
					<< setw(10) << "price" << setw(11) << "addedDate"
					<< setw(8) << "number" << setw(8) << "sellerID" << endl;
				for (int i = 0; i < cmd.commodities.size(); i++)
					if (cmd.commodities[i].match(3, uid)) {
						flag = 1;
						cmd.commodities[i].printInfo(2);
					}
			}
			else cout << "未找到符合要求的商品...";
		}
		else cout << "未找到符合要求的商品...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
	myGetch();
}

void User::showDetail() {
	bool succ = 1;
	cout << "#############################" << endl;
	cout << "请输入您想要查看的商品ID：";
	string cid;
	cin >> cid;
	Command cmd = buyerCmd("SELECT * FROM commodity WHERE cid = " + cid, succ);
	if (succ) {
		bool flag = 0;
		if (cmd.commodities.size() > 0) {
			for (int i = 0; i < cmd.commodities.size(); i++)
				if (cmd.commodities[i].match(3, uid)) {
					flag = 1;
					break;
				}
			if (flag) {
				cout << "商品详细信息如下" << endl;
				for (int i = 0; i < cmd.commodities.size(); i++)
					if (cmd.commodities[i].match(3, uid)) {
						flag = 1;
						cmd.commodities[i].printInfo(3);
					}
			}
			else cout << "未找到符合要求的商品...";
		}
		else cout << "未找到符合要求的商品...";
		cout << "按任意键返回" << endl;
	}
	else exit(0);
	myGetch();
	myGetch();
}

void User::buyComm() {
	cout << "####################" << endl;
	cout << "请输入商品ID：";
	string cid;
	cin >> cid;
	Commodity* comm = nullptr;
	for (int i = 0; i < Interface::commodities.size(); i++) {
		if (Interface::commodities[i].match(1, cid) && Interface::commodities[i].match(3, uid))
			comm = &Interface::commodities[i];
	}
	if (comm == nullptr) {
		cout << "没有相应的商品...按任意键返回";
		myGetch();
		myGetch();
		return;
	}
	else {
		string qtt;
		while (1) {
			cout << "请输入购买数量：";
			cin >> qtt;
			if (!judgeStr(qtt, 2)) {
				cout << "输入的数量不合法，请重新输入" << endl;
				continue;
			}
			break;
		}
		int count = atoi(qtt.c_str());
		int surplus = comm->compare(count);
		if (surplus<0) {
			cout << "商品余量不足...按任意键返回";
			myGetch();
			myGetch();
			return;
		}
		else {
			int num = Interface::orders.size() + 1;
			if (num > 999) {
				cout << "订单已满，按任意键返回" << endl;
				myGetch();
				myGetch();
				return;
			}
			if (count * atof(comm->getPrice().c_str()) > money) {
				cout << "余额不足，按任意键返回" << endl;
				myGetch();
				myGetch();
				return;
			}

			string time = Interface::getDate();
			char buffer[4];
			string oid;
			sprintf(buffer, "%d", num);
			oid = buffer;
			while (oid.length() < 3) {
				oid = "0" + oid;
			}
			oid = "T" + oid;
			string cmdStr = "INSERT INTO order VALUES ("
				+ oid + ","
				+ comm->getCid() + ","
				+ comm->getPrice() + ","
				+ qtt + ","
				+ time + ","
				+ comm->getSid() + ","
				+ uid + ")";
			bool succ = 0;
			buyerCmd(cmdStr, succ);
			if (succ) {
				cmdStr = "UPDATE commodity SET number = " + to_string(surplus) + " WHERE cid = " + comm->getCid();
				buyerCmd(cmdStr, succ);
				if (succ) {
					if (surplus == 0) {
						cmdStr = "UPDATE commodity SET state = removed WHERE cid = " + cid;
						buyerCmd(cmdStr, succ);
						if (!succ) exit(0);
					}
					money -= count * atof(comm->getPrice().c_str());
					for (int i = 0; i < Interface::users.size(); i++) {
						if (Interface::users[i].match(0, comm->getSid())) {
							Interface::users[i].money += count*atof(comm->getPrice().c_str());
						}
					}
					Interface::pushTxt("user.txt");

					cout << "########################" << endl;
					cout << "购买成功!" << endl;
					cout << "交易时间：" << time << endl;
					cout << "交易单价：" << comm->getPrice() << endl;
					cout << "交易数量：" << qtt << endl;
					cout << "您的余额：" << setiosflags(ios::fixed) << setprecision(1) << money << endl;
					cout << "按任意键返回" << endl;
					myGetch();
					myGetch();
					return;
				}
				else exit(0);
			}
			else exit(0);
		}
	}
	return;
}

Command User::buyerCmd(string cmdStr, bool& succ) {
	Interface::pushCmd(cmdStr);

	Command cmd(cmdStr);
	succ = cmd.process();
	return cmd;
}

void User::buyerItf() {
	while (1) {
		system("clear");
		cout << "1，查看商品列表" << endl;
		cout << "2，购买商品" << endl;
		cout << "3，搜索商品" << endl;
		cout << "4，查看历史订单" << endl;
		cout << "5，查看商品详细信息" << endl;
		cout << "6，返回用户主界面" << endl;
		char ch=myGetch();
		if (ch == '1') {
			showComm(1);
		}
		else if (ch == '2') {
			buyComm();
		}
		else if (ch == '3') {
			searchComm();
		}
		else if (ch == '4') {
			showOrders(1);
		}
		else if (ch == '5') {
			showDetail();
		}
		else if (ch == '6') {
			return;
		}
	}
}
