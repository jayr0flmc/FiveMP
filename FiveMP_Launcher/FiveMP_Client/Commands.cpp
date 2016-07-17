#include "stdafx.h"

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


vector<string> split(const string &s, char delim) {
	vector<string> elems;
	split(s, delim, elems);
	return elems;
}

int CommandProcessor(string command)
{
	vector<string> params = split(command, ' ');
	command = params[0];
	params.erase(params.begin());
	if (!command.compare("/test"))
	{
		CChat::Get()->AddChatMessage("Hello, World!");
		return true;
	}
	return false;
}