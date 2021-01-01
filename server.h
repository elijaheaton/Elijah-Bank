#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <mysqlx/xdevapi.h>
#include <string>
#include "member.h"
using ::mysqlx::Schema;
using ::std::string;

class Server {
private:
	bool checkEmpty(string s);
	bool strcmpin(string a, string b);
public:
	int addUser(string first, string last, string user, float amount);
	int userExists(string username);
	Member findUser(string username);
};

#endif