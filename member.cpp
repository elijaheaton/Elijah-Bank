#include <iostream>
#include "member.h"
using namespace std;

void Member::set_name(string first_name, string last_name) {
	this->first_name = first_name;
	this->last_name = last_name;
}

void Member::set_user_name(string user_name) {
	this->user_name = user_name;
}

void Member::set_account_no(int account_no) {
	this->account_no = account_no;
}

void Member::set_balance(float amount) {
	this->amount = amount;
}

string Member::get_name() {
	return this->first_name + " " + this->last_name;
}

string Member::get_user_name() {
	return this->user_name;
}

int Member::get_account_no() {
	return this->account_no;
}

float Member::get_balance() {
	return this->amount;
}