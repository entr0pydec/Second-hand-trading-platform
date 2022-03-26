#include"transaction.h"
#include"command.h"

Commodity::Commodity(string inCid, string inName, double inPrice, int inQty, string inDpt, string inSid, string time) {
	cid = inCid;
	name = inName;
	price = inPrice;
	quantity = inQty;
	description = inDpt;
	sellerID = inSid;
	releaseTime = time;
	state = 1;
}

void Commodity::setState(bool flag) {
	state = flag;
}

void Commodity::printInfo(char type) {
	string sState = "removed";
	if (state == 1)
		sState = "onSale";
	if (type == 0) {
		cout << setw(14) << cid << setw(16) << name
			<< setw(10) << setiosflags(ios::fixed) << setprecision(1) << price
			<< setw(11) << releaseTime << setw(10) << sellerID
			<< setw(8) << quantity << sState << endl;
	}
	else if (type == 1) {
		cout << setw(14) << cid << setw(16) << name
			<< setw(10) << setiosflags(ios::fixed) << setprecision(1) << price
			<< setw(11) << releaseTime << setw(8) << quantity << sState << endl;
	}
	else if (type == 2) {
		cout << setw(14) << cid << setw(16) << name
			<< setw(10) << setiosflags(ios::fixed) << setprecision(1) << price
			<< setw(11) << releaseTime << setw(8) << quantity << sellerID << endl;
	}
	else if (type == 3) {
		cout.setf(ios::left);
		cout << setw(15) << "commodityID:" << cid << endl;
		cout << setw(15) << "commodityName:" << name << endl;
		cout << setw(15) << "price:" << price << endl;
		cout << setw(15) << "addedDate:" << releaseTime << endl;
		cout << setw(15) << "description:" << description << endl;
		cout << setw(15) << "sellerID:" << sellerID << endl;
	}
}

void Commodity::pushTo(ostream &file) {
	string sState = "removed";
	if (state == 1)
		sState = "onSale";
	file << endl << cid << "," << name << ","
		<< setiosflags(ios::fixed) << setprecision(1) << price << ","
		<< quantity << "," << description << ","
		<< sellerID << "," << releaseTime << "," << sState;
}

bool Commodity::match(char type,string info) {
	//name contain
	if (type == 0) {
		return name.find(info) != name.npos;
	}
	//cid equal
	else if (type == 1) {
		return cid == info;
	}
	//uid equal
	else if (type == 2) {
		return sellerID == info;
	}
	//state
	else if (type == 3) {
		return state;
	}

	return 0;
}

bool Commodity::update(string column, string value) {
	if (column == "state") {
		state = (value == "onSale");
		return 1;
	}
	if (column == "price") {
		price = atof(value.c_str());
		return 1;
	}
	if (column == "description") {
		description = value;
		return 1;
	}
	if (column == "number") {
		quantity = atoi(value.c_str());
		return 1;
	}

	return 0;
}

int Commodity::compare(int count) {
	return quantity - count;
}

string Commodity::getSid() {
	return sellerID;
}

string Commodity::getCid() {
	return cid;
}

string Commodity::getPrice(){
	string sPrice;
	char buffer[100];
	sprintf(buffer, "%.1f", price);
	sPrice = buffer;
	return sPrice;
}

Order::Order(string orderID, string commodityID, double unitPrice, int number, string date, string inSellerID, string inBuyerID) {
	oid = orderID;
	cid = commodityID;
	price = unitPrice;
	quantity = number;
	time = date;
	sellerID = inSellerID;
	buyerID = inBuyerID;
}

void Order::printInfo(char type) {
	if (type == 0) {
		cout << setw(10) << oid << setw(14) << cid
			<< setw(12) << setiosflags(ios::fixed) << setprecision(1) << price
			<< setw(9) << quantity << setw(11) << time
			<< setw(10) << sellerID << buyerID << endl;
	}
	else if (type == 1) {
		cout << setw(10) << oid << setw(14) << cid
			<< setw(12) << setiosflags(ios::fixed) << setprecision(1) << price
			<< setw(9) << quantity << setw(11) << time << buyerID << endl;
	}
	else if (type == 2) {
		cout << setw(10) << oid << setw(14) << cid
			<< setw(12) << setiosflags(ios::fixed) << setprecision(1) << price
			<< setw(9) << quantity << setw(11) << time << sellerID << endl;
	}
}

void Order::pushTo(ostream& file) {;
	file << endl << oid << "," << cid << ","
		<< setiosflags(ios::fixed) << setprecision(1) << price << ","
		<< quantity << "," << time << ","
		<< sellerID << "," << buyerID;
}

bool Order::match(char type, string info) {
	//sellerID equal
	if (type == 0) {
		return sellerID == info;
	}
	//buyerID equal
	else if (type == 1) {
		return buyerID == info;
	}

	return 0;
}

string Order::getPrice() {
	string sPrice;
	char buffer[100];
	sprintf(buffer, "%.1f", price);
	sPrice = buffer;
	return sPrice;
}
