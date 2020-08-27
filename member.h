#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
using namespace std;

class Member {
private:
	string first_name = "";
	string last_name = "";
	int account_no = 0;

public:
	void set_name(string first_name, string last_name);
	void set_account_no(int account_no);
	string get_name();
	int get_account_no();
};

#endif
