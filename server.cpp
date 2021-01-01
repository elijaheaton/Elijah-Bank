#include <iostream>
#include <mysqlx/xdevapi.h>
#include "server.h"
#include "member.h"
#include <string>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
using ::std::cout;
using ::std::end;
using ::std::cin;
using ::std::endl;
using ::std::exception;
using ::mysqlx::Session;
using ::mysqlx::Schema;
using ::mysqlx::Result;
using ::mysqlx::Error;
using ::mysqlx::SessionOption;
using ::mysqlx::DocResult;
using ::mysqlx::Table;
using ::mysqlx::RowResult;
using ::mysqlx::Row;

#define usernameForDB "elijah"
#define passwordForDB ""

	// returns true if empty
	bool Server::checkEmpty(string s) {
		return s.size() < 1;
	}

	// a case-insensitive string comparison
	bool Server::strcmpin(string a, string b) {
		bool cmp = true;
		if (a.length() == b.length()) {
			for (int i = 0; i < a.length(); i++) {
				if (toupper(a[i]) == toupper(b[i])) {
					continue;
				}
				else {
					cmp = false;
					break;
				}
			}
		}
		return cmp;
	}


	// functions to access DB

	/** A function to add a user to the database
	 *  @params firstName
	 *  @params lastName
	 *  @params userName
	 *  @params amount
	 *
	 *  @returns userId if works out
	 *  @returns -1 if a field is empty
	 *  @returns -2 if username already exists
	 *  @returns -3 if amount you're adding will break DB
	 *  @returns -4 if account added improperly
	 *  @returns -5 if general error occurs
	 *  @returns -6 if STD exception occurs
	 *  @returns -7 if general exception occurs
	 */
	int Server::addUser(string firstName, string lastName, string userName, float amount) {
		int userId;

		// check for empty strings
		if (checkEmpty(firstName) || checkEmpty(lastName) || checkEmpty(userName)) {
			return -1;
		}

		try {
			Session session(SessionOption::HOST, "localhost",
							SessionOption::PORT, 33060,
							SessionOption::USER, usernameForDB,
							SessionOption::PWD, passwordForDB);
			Table users = session.getSchema("bank").getTable("Accounts");

			// check if username is in db already
			RowResult res = users.select("UserName")
							 	 .where("UserName = :u")
							 	 .bind("u", userName)
							 	 .execute();
			if (res.count() > 0) {
				return -2;
			}
			// check that amount is reasonable and wont break system
			// TODO: figure out reasonable amount
			if (amount > 1e8 || amount < 0) {
				return -3;
			}

			users.insert("FirstName", "LastName", "UserName", "amount")
			     .values(firstName, lastName, userName, amount).execute();
			Row row = users.select("UserName", "ID").where("UserName = :u")
						   .bind("u", userName).execute().fetchOne();
			
			// check that it was added
			if (!strcmpin(string(row[0]), userName)) {
				return -4;
			}
			userId = row[1];
		}
		catch (const Error &err) {
			cout << "ERROR: " << err << endl;
			return -5;
		} 
		catch (exception &ex) {
			cout << "STD EXCEPTION: " << ex.what() << endl;
			return -6;
		} 
		catch (const char *ex) {
			cout << "EXCEPTION: " << ex << endl;
			return -7;
		}

		return userId;
	}


	int Server::userExists(string username) {
		if (checkEmpty(username)) {
			return -1;
		}
		try {
			Session session(SessionOption::HOST, "localhost",
							SessionOption::PORT, 33060,
							SessionOption::USER, usernameForDB,
							SessionOption::PWD, passwordForDB);
			Table users = session.getSchema("bank").getTable("Accounts");

			// check if username is in db
			RowResult res = users.select("UserName")
							 	 .where("UserName = :u")
							 	 .bind("u", username)
							 	 .execute();
			return res.count();
		}
		catch (const Error &err) {
			cout << "ERROR: " << err << endl;
			return -5;
		} 
		catch (exception &ex) {
			cout << "STD EXCEPTION: " << ex.what() << endl;
			return -6;
		} 
		catch (const char *ex) {
			cout << "EXCEPTION: " << ex << endl;
			return -7;
		}

		return -8;

	}


	Member Server::findUser(string username) {
		Member member;

		if (checkEmpty(username)) {
			return member;
		}
		try {
			Session session(SessionOption::HOST, "localhost",
							SessionOption::PORT, 33060,
							SessionOption::USER, usernameForDB,
							SessionOption::PWD, passwordForDB);
			Table users = session.getSchema("bank").getTable("Accounts");

			// check if username is in db
			RowResult res = users.select("UserName")
							 	 .where("UserName = :u")
							 	 .bind("u", username)
							 	 .execute();
			
			if (res.count() == 1) {
				Row row = users.select("UserName", "FirstName", "LastName", "ID", "amount").where("UserName = :u")
						   .bind("u", username).execute().fetchOne();
			

				// do stuff with row array
				member.set_user_name(string(row[0]));
				member.set_name(string(row[1]), string(row[2]));
				member.set_account_no(row[3]);
				member.set_balance(row[4]);
				
			}
		}
		catch (const Error &err) {
			cout << "ERROR: " << err << endl;
		} 
		catch (exception &ex) {
			cout << "STD EXCEPTION: " << ex.what() << endl;
		} 
		catch (const char *ex) {
			cout << "EXCEPTION: " << ex << endl;
		}

		return member;
	}
