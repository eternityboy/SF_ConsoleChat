//
// Created by Nikita Tryaskin on 28.11.2024.
//

#pragma once
#include <iostream>
#include <vector>

class Chat {
private:
	std::string currentUser_;
	std::vector<std::vector<std::string>> usersDB_;
	std::vector<std::vector<std::string>> messagesDB_;
//	bool newMessages;

public:
	//Load data bases
	void usersDB();
	void messagesDB();

	//Users operations
	void signUp();
	void saveUser();
	void signIn();

	//Check users
	bool userExists(std::string&);
	bool badSymbol(std::string&, const char);
	bool isValidUserNamePassword(std::string&, std::string&);
	bool isValidUserName(std::string&);
	bool userLoggedIn();
	void listUsers();
	bool tryAgain();

	std::string question(std::string);
	std::string getRealName(std::string&);
	std::vector<std::string> stringSplit(std::string&, char);

	//Messages operations
	void messageBoard();
	void showMessages();
	bool sendMessage();
	void saveMessages();

	void chatMenu();
};
