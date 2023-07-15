#pragma once
#include <iostream>
#include <string>
#include <mysql.h>
#include <cppconn/prepared_statement.h>
#include <mysql_driver.h>

using namespace std;

class Interface
{
protected:
	string role; // admin or user


public:
	Interface(){}
	void Welcome();
	void Exit();

	void SetRole(const string& newRole) { this->role = newRole; }
	string const GetRole() { return role; }

};

class DB
{
public:
	// The function of connecting to the Mysql database
	sql::Connection* Connection(); 

	//The function of adding a new user to the database (db_user), table (users)
	void addUserToDatabase(const string& username, const string& password, const string& email);

	//The function of adding a new administrator to the database (db_user), table (users)
	void addAdminToDatabase(const string& username, const string& password, const string& email);

	// Function to get date in format: YYYY/MM/DD
	string GetDate();

	// User search function in the database
	bool searchUserInDB(const string& login, const string& password);

	// Admin search function in the database
	bool searchAdminInDB(const string& login, const string& password);

	// Checking whether the user's login (username) is free
	bool isUserNameAvailable(const string& login);

	// Checking whether the login (username) of the administrator is free
	bool isAdminNameAvailable(const string& login);
};

class Hashing
{
private:
	string hash;
	short lenHash; // the length of the hash, default = 16
	int gelControlSum(string password); // Sum of all characters in string, in ASCII table code 
	char receivingExistCodes(int);        //  Reduce a number to a real character in an ASCII table

public:
	Hashing() { this->lenHash = 16; }

	string GetHash(string password);
};

class Authentication : public Interface
{
private:
	DB database;
	Hashing hashing;
public:
	Authentication() {}

	// main menu
	void AuthenticationMenu();

	void registerUser();
	void registerAdmin();

	bool userAuthorization();
	bool adminAuthorization();

	string const GetRole() { return role; }
};
