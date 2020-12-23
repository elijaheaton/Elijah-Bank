#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
using namespace std;

class Member {
private:
	string first_name;
	string last_name;
	string user_name;
	int account_no;
	int amount;

public:
	void set_name(string first_name, string last_name);
	void set_user_name(string user_name);
	void set_account_no(int account_no);
	void set_balance(int amount);
	string get_name();
	string get_user_name();
	int get_account_no();
	int get_balance();
};

#endif
