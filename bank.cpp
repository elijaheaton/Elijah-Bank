#include <iostream>
#include <mysqlx/xdevapi.h>
#include "member.h"
#include "server.h"
#include <string>
#include <unistd.h>
using ::std::cout;
using ::std::end;
using ::std::cin;
using ::std::endl;



Member create_account(Server server) {
	string first_name;
	string last_name;
	string user;
	float amount;
	Member member;

	cout << "Thank you for choosing Elijah Bank!" << endl;
	cout << "Please enter your first name: ";
	cin >> first_name;
	cout << "Please enter your last name: ";
	cin >> last_name;
	cout << "What would you like your username to be? ";
	cin >> user; 
	cout << "How much would you like to deposit initially? ";
	cin >> amount;

	int ans = server.addUser(first_name, last_name, user, amount);
	if (ans >= 0) {
		// access the new member to return
		member.set_name(first_name, last_name);
		member.set_user_name(user);
		member.set_account_no(ans);
		member.set_balance(amount);
	}
	else {
		cout << "Error number " << ans << endl;
	}

	return member;

}

int main() {

	cout << "Welcome to the Elijah Bank." << endl;
	string response;
	Server server;
	bool good_response = false;
	

	do {
		cout << "Do you have an account already or would you like to make one?" << endl;
		cout << " -- Print 'access', or 'make' to continue, or 'quit' to leave. -- " << endl;
		cin >> response;

		if (response.compare("access") == 0) {
			good_response = true;
		}
		else if (response.compare("make") == 0) {
			good_response = true;
			Member new_member = create_account(server);
			if (new_member.get_account_no() >= 0) {
				cout << "Welcome, " << new_member.get_name() << "!" << endl;
			}
			else {
				cout << "I'm sorry, it appears that something went wrong." << endl;
			}
		}
		else if (response.compare("quit") == 0) {
			good_response = true;
		}
		else {
			cout << "I'm sorry, that isn't an accepted answer. Please try again." << endl;
		}
	} while (!good_response);



	return 0;
}
