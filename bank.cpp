#include <iostream>
#include <mysqlx/xdevapi.h>
#include "member.h"
using namespace std;
using mysqlx::SessionOption;

Member create_account() {
	string first_name;
	string last_name;

	cout << "Thank you for choosing Elijah Bank!" << endl;
	cout << "Please enter your first name: ";
	cin >> first_name;
	cout << "Please enter your last name: ";
	cin >> last_name;

	Member new_member;
	new_member.set_name(first_name, last_name);
	new_member.set_account_no(8675309);

	return new_member;

}

int main() {

	try {
		cout << "Creating session..." << endl;
		mysqlx::Session sess(SessionOption::HOST, "localhost",
							 SessionOption::PORT, 33060,
							 SessionOption::USER, "root");
							 //SessionOption::PWD, "");
		cout << "We have a session. Creating schema..." << endl;
		mysqlx::Schema sch = sess.getSchema("users");
		cout << "We have a schema. Creating collection..." << endl;
		mysqlx::Collection coll = sch.createCollection("c1", true);
		cout << "We have a collection." << endl;
		coll.remove("true").execute();
	} catch (const mysqlx::Error &err) {
		cout << "ERROR: " << err << endl;
		return 1;
	} catch (exception &ex) {
		cout << "STD EXCEPTION: " << ex.what() << endl;
		return 1;
	} catch (const string ex) {
		cout << "EXCEPTION: " << ex << endl;
		return 1;
	}


	cout << "Welcome to the Elijah Bank." << endl;
	string response;
	bool good_response = false;
	

	do {
		cout << "Do you have an account already or would you like to make one?" << endl;
		cout << " -- Print 'access' or 'make' to continue. -- " << endl;
		cin >> response;

		if (response.compare("access") == 0) {
			good_response = true;
		}
		else if (response.compare("make") == 0) {
			good_response = true;
			Member new_member = create_account();
			cout << "Welcome, " << new_member.get_name() << "!" << endl;
		}
		else {
			cout << "I'm sorry, that isn't an accepted answer. Please try again." << endl;
		}
	} while (!good_response);



	return 0;
}