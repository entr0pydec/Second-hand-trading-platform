#include"command.h"
#include"interface.h"
#include"person.h"
#include"transaction.h"

Command::Command(string cmdStr) {
	users = {};
	orders = {};
	commodities = {};

	content = cmdStr;
	condition = NONE;
	if (cmdStr.find("INSERT") != cmdStr.npos) {
		type = INSERT;
	}
	else {
		if (cmdStr.find("SELECT") != cmdStr.npos) {
			type = SELECT;
		}
		else type = UPDATE;
		if (cmdStr.find("WHERE") != cmdStr.npos) {
			if (cmdStr.rfind("=") != cmdStr.npos
				&& cmdStr.rfind("=") > cmdStr.find("WHERE"))
				condition = EQUAL;
			else condition = CONTAIN;
		}
	}
	
	if (cmdStr.find("user") != cmdStr.npos) {
		target = USER;
	}
	else if (cmdStr.find("commodity") != cmdStr.npos) {
		target = COMMODITY;
	}
	else
		target = ORDER;
}

bool Command::process() {
	if (type == SELECT) {
		if (target == USER) {
			if (condition == NONE) {
				for (int i = 0; i < Interface::users.size(); i++)
					users.push_back(Interface::users[i]);
				return 1;
			}
		}
		else if (target == COMMODITY) {
			if (condition == NONE) {
				for (int i = 0; i < Interface::commodities.size(); i++)
					commodities.push_back(Interface::commodities[i]);
				return 1;
			}
			else if (condition == CONTAIN) {
				int index = content.find("CONTAINS") + 9;
				string subName = content.substr(index, content.length() - index);
				for (int i = 0; i < Interface::commodities.size(); i++) {
					Commodity cmmd = Interface::commodities[i];
					if (cmmd.match(0, subName)) {
						commodities.push_back(cmmd);
					}
				}
				return 1;
			}
			else if (condition == EQUAL) {
				int whereLoc = content.find("WHERE");
				string sCond = content.substr(whereLoc + 6, content.length() - whereLoc - 5);
				int equalLoc = sCond.find("=");
				string column = sCond.substr(0, equalLoc - 1);
				string value = sCond.substr(equalLoc + 2, sCond.length() - equalLoc - 2);
				int matchType = -1;
				if (column == "cid") matchType = 1;
				else if (column == "uid") matchType = 2;
				for (int i = 0; i < Interface::commodities.size(); i++) {
					Commodity cmmd = Interface::commodities[i];
					if (cmmd.match(matchType, value)) {
						commodities.push_back(cmmd);
					}
				}
				return 1;
			}
		}
		else if (target == ORDER) {
			if (condition == NONE) {
				for (int i = 0; i < Interface::orders.size(); i++)
					orders.push_back(Interface::orders[i]);
				return 1;
			}
		}
	}
	else if (type == INSERT) {
		if (target == COMMODITY) {
			string line = content.substr(content.find("(") + 1, content.find(")") - content.find("(") - 1);
			vector<string> data;
			for (int i = 0; i < 7; i++) {
				int index = line.find(",");
				data.push_back(line.substr(0, index));
				line = line.substr(index + 1, line.length() - index - 1);
			}
			double p = atof(data[1].c_str());
			int n = atof(data[2].c_str());
			Commodity comm(data[4], data[0], p, n, data[3], data[5], data[6]);
			Interface::commodities.push_back(comm);
			Interface::pushTxt("commodity.txt");
			return 1;
		}
		else if (target == ORDER) {
			string line = content.substr(content.find("(") + 1, content.find(")") - content.find("(") - 1);
			vector<string> data;
			for (int i = 0; i < 7; i++) {
				int index = line.find(",");
				data.push_back(line.substr(0, index));
				line = line.substr(index + 1, line.length() - index - 1);
			}
			double p = atof(data[2].c_str());
			int n = atof(data[3].c_str());
			Order order(data[0], data[1], p, n, data[4], data[5], data[6]);
			Interface::orders.push_back(order);
			Interface::pushTxt("order.txt");
			return 1;
		}
	}
	else if (type == UPDATE) {
		bool flag = 0;
		if (target == COMMODITY) {
			if (condition == EQUAL) {
				int whereLoc = content.find("WHERE");
				int setLoc = content.find("SET");

				string sChange = content.substr(setLoc + 4, whereLoc - setLoc - 5);

				string sCond = content.substr(whereLoc + 6, content.length() - whereLoc - 5);
				int equalLoc = sCond.find("=");
				string column = sCond.substr(0, equalLoc - 1);
				string value = sCond.substr(equalLoc + 2, sCond.length() - equalLoc - 2);

				vector<string> changes;
				while (sChange.length()) {
					int index = sChange.find(",");
					if (index == sChange.npos) {
						changes.push_back(sChange);
						break;
					}
					else{
						changes.push_back(sChange.substr(0, index));
						sChange = sChange.substr(index + 1, sChange.length() - index - 2);
					}
				}
				int matchType = -1;
				if (column == "cid") matchType = 1;
				else if (column == "uid") matchType = 2;
				for (int i = 0; i < Interface::commodities.size(); i++) {
					if (Interface::commodities[i].match(matchType, value)) {
						for (int j = 0; j < changes.size(); j++) {
							int equalLoc_i = changes[j].find("=");
							string column_i = changes[j].substr(0, equalLoc_i - 1);
							string value_i = changes[j].substr(equalLoc_i + 2, changes[j].length() - equalLoc_i - 2);
							if (Interface::commodities[i].update(column_i, value_i)) {
								Interface::pushTxt("commodity.txt");
								flag = 1;
							}
						}
					}
				}
			}
		}
		else if (target == USER) {
			if (condition == EQUAL) {
				int whereLoc = content.find("WHERE");
				int setLoc = content.find("SET");

				string sChange = content.substr(setLoc + 4, whereLoc - setLoc - 5);

				string sCond = content.substr(whereLoc + 6, content.length() - whereLoc - 5);
				int equalLoc = sCond.find("=");
				string column = sCond.substr(0, equalLoc - 1);
				string value = sCond.substr(equalLoc + 2, sCond.length() - equalLoc - 2);

				vector<string> changes;
				while (sChange.length()) {
					int index = sChange.find(",");
					if (index == sChange.npos) {
						changes.push_back(sChange);
						break;
					}
					else {
						changes.push_back(sChange.substr(0, index));
						sChange = sChange.substr(index + 1, sChange.length() - index - 2);
					}
				}

				int matchType = -1;
				if (column == "uid") matchType = 0;
				for (int i = 0; i < Interface::users.size(); i++) {
					if (Interface::users[i].match(matchType, value)) {
						for (int j = 0; j < changes.size(); j++) {
							int equalLoc_i = changes[j].find("=");
							string column_i = changes[j].substr(0, equalLoc_i - 1);
							string value_i = changes[j].substr(equalLoc_i + 2, changes[j].length() - equalLoc_i - 2);
							if (Interface::users[i].update(column_i, value_i)) {
								Interface::pushTxt("user.txt");
								flag=1;
							}
						}
					}
				}
			}
		}
		return flag;
	}
	return 0;
}
