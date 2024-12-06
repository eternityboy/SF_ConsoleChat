//
// Created by Nikita Tryaskin on 28.11.2024.
//

#include <vector>
#include "Chat.h"
#include "Error.h"
#include <sstream>
#include "loadtxt.hpp"

void Chat::usersDB() {
	std::cout << "Loading users database...\n";
	std::string pwd = std::filesystem::current_path();
	std::string path = pwd + "/../data/users.txt";
	auto data = loadtxt(path)();
	for(int i=0; i < data.size(); i++)
	{
		usersDB_.push_back(std::vector<std::string>());
		for(int j=0; j < data[0].size(); j++)
		{
			usersDB_[i].push_back(data[i][j]);
		}
	}
	return;
}

void Chat::messagesDB() {
	std::cout << "Loading messages database...\n";
	std::string pwd = std::filesystem::current_path();
	std::string path = pwd + "/../data/messages.txt";
	auto data = loadtxt(path).delimiter("|")();
	for(int i=0; i < data.size(); i++)
	{
		messagesDB_.push_back(std::vector<std::string>());
		for(int j=0; j < data[0].size(); j++)
		{
			messagesDB_[i].push_back(data[i][j]);
		}
	}
	return;
}

bool Chat::userExists(std::string& userName)
{
	for (int i = 0; i < usersDB_[0].size(); i++) {
		if (userName == usersDB_[0][i]) {
			return true;
		}
	}
	return false;
}

bool Chat::badSymbol(std::string& string, const char symbol)
{
	for (int i = 0; i < string.length(); i++) {
		if (string[i] == symbol) {
			return true;
		}
	}
	return false;
}

std::string Chat::question(std::string quest) {
	std::string variable;
	std::cout << quest;
	std::cin >> variable;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return variable;
}

bool Chat::tryAgain() {
	std::string again = question("Try again (y/n)? ");
	if (again == "y" or again == "Y" or again == "yes")
		return true;
	else
		return false;
}

std::vector<std::string> Chat::stringSplit(std::string& string, char del) {
	std::stringstream ss(string);
	std::string tmp;
	std::vector<std::string> arrayData;
	int k = 0;
	while(std::getline(ss, tmp, del)) {
		if (k < 2) {
			arrayData.push_back(tmp);
			k++;
		} else { break; }
	}
	return arrayData;
}

void Chat::signUp() {
	std::string userName;
	std::string password;
	std::string realName;

	bool repeat = true;
	std::cout << "\x1B[31m" << "Sign up for the chat" << "\033[0m\n";
	while (repeat) {
		repeat = false;
		userName = question("Enter username: ");
		password = question("Enter password: ");
		realName = question("Enter Your Name: ");

		try {
			if (userExists(userName))
				throw UserNameBusy();
			else if (badSymbol(userName, '|') or badSymbol(password, '|') or badSymbol(realName, '|'))
				throw WrongSymbols();
			else {
				std::cout << "\x1B[31m" << "Saving user here" << "\033[0m\n";
				std::string newElement = "1";
				for (auto &row: usersDB_) {
					row.push_back(newElement);

					int last = usersDB_[0].size() - 1;
					usersDB_[0][last] = userName;
					usersDB_[1][last] = password;
					usersDB_[2][last] = realName;
					saveUser();
				}
			}
		}
		catch (std::exception& e)
		{
			std::cout << "\x1B[31m" << e.what() << "\033[0m\n";
			repeat = tryAgain();
		}
	}
	return;
}

void Chat::saveUser() {
	std::string pwd = std::filesystem::current_path();
	std::string path = pwd + "/../data/users.txt";
	std::fstream File;
	try {
		File.open(path, std::ios::out);
		for (auto i = 0; i < usersDB_[0].size(); i++) {
			File << usersDB_[0][i] << "|" << usersDB_[1][i] << "|" << usersDB_[2][i] << "\n";
		}
	}
	catch (const std::ios::failure& e) {
		std::cout << "The file was not opened\n";
	}
	File.close();
}

void Chat::signIn() {
	std::string userName;
	std::string password;

	bool proceed = true;
	std::cout << "\x1B[36m" << "Sign in for the chat" << "\033[0m\n";
	while (proceed) {
		proceed = false;
		userName = question("Enter user name: ");
		password = question("Enter password: ");

		try {
			if (!isValidUserNamePassword(userName, password)) {
				throw IncorrectUserNameOrPassword();
			}
			std::cout << "Login success\n";
		}
		catch (std::exception& e)
		{
			std::cout << "\x1B[31m" << e.what() << "\033[0m\n";
		}
	}
}

bool Chat::isValidUserNamePassword(std::string& userName, std::string& password) {
	for (auto i = 0; i < usersDB_[0].size(); i++) {
		if (usersDB_[0][i] == userName and usersDB_[1][i] == password) {
			currentUser_ = usersDB_[0][i];
			return true;
		}
	}
	return false;
}

bool Chat::isValidUserName(std::string& userName) {
	for (auto i = 0; i < usersDB_[0].size(); i++) {
		if (usersDB_[0][i] == userName) {
			return true;
		}
	}
	return false;
}

bool Chat::userLoggedIn() {
	if (!currentUser_.empty()) {
		return true;
	}
	return false;
}

void Chat::listUsers() {
	for (auto i = 0; i < usersDB_[0].size(); i++) {
		std::cout << "\x1B[36m" << usersDB_[0][i] << "\033[0m\n";
	}
}

void Chat::messageBoard() {
	if(!currentUser_.empty()) {
		std::string realName = getRealName(currentUser_);
		std::cout << "Good day, " << realName << "! You are at the smart console now.\n Type in \x1B[31m1!\033[0m to"
												 " list all users, \x1B[31m2!\033[0m \x1B[36muserName\033[0m to send"
												 " message to specific user, \x1B[31m3!\033[0m to show new/all "
												 "messages, \x1B[31m0!\033[0m to exit.\n";

		bool cont = true;
		while(cont) {
			Chat::showMessages();
			cont = Chat::sendMessage();
			Chat::saveMessages();
		}
	}
}

void Chat::showMessages() {
    for (auto i = 0; i < messagesDB_[0].size(); i++) {
		if (messagesDB_[2][i] == "all") {
			if (messagesDB_[0][i] == "1") {
				std::cout << "\x1B[34m" << "NEW! " << "\033[0m";
				messagesDB_[0][i] = "0";
			}

			std::cout << messagesDB_[1][i] << ": " << messagesDB_[3][i] << "\n";
		}
		if (messagesDB_[2][i] == currentUser_) {
			if (messagesDB_[0][i] == "1") {
				std::cout << "\x1B[34m" << "NEW! " << "\033[0m";
				messagesDB_[0][i] = "0";
			}
			std::cout << "\x1B[32m" << messagesDB_[1][i] << " (DM): " << messagesDB_[3][i] << "\033[0m\n";
		}
	}
}

void Chat::saveMessages() {
	std::string pwd = std::filesystem::current_path();
	std::string path = pwd + "/../data/messages.txt";
	std::fstream File;
	try {
		File.open(path, std::ios::out);
		for (auto i = 0; i < messagesDB_[0].size(); i++) {
			File << messagesDB_[0][i] << "|" << messagesDB_[1][i] << "|" << messagesDB_[2][i] << "|" <<
			messagesDB_[3][i] <<
				 "\n";
		}
	}
	catch (const std::ios::failure& e) {
		std::cout << "The file was not opened\n";
	}
	File.close();
}

bool Chat::sendMessage() {
	bool repeat = true;
	while(repeat) {
		std::string message;
		std::cout << "Message: ";
		std::getline(std::cin, message);

		if (badSymbol(message, '|') == false and !message.empty()) {

			bool foundSpecial = false;
			std::string destUserName = "all";
			std::vector<std::string> splitMessage = stringSplit(message, ' ');
			if (splitMessage[0] == "1!") {
				foundSpecial = true;
				listUsers();
			}
			else if (splitMessage[0] == "2!") {
				destUserName = splitMessage[1];
				try {
					if (!isValidUserName(destUserName)) {
						throw UserNameNotFound();
					}
					message.erase(0,3 + destUserName.size() + 1);
				}
				catch (std::exception& e)
				{
					std::cout << "\x1B[31m" << e.what() << "\033[0m\n";
					foundSpecial = true;
					repeat = true;
				}
			}
			else if (splitMessage[0] == "0!") {
				foundSpecial = true;
				std::cout << "Exiting\n";
				repeat = false;
				return false;
			}
			else {
				foundSpecial = false;
			}

			if (!foundSpecial) {
				std::string newElement = "1";
				for (auto &row: messagesDB_) {
					row.push_back(newElement);
				}

				int last = messagesDB_[0].size() - 1;
				messagesDB_[1][last] = currentUser_;
				messagesDB_[2][last] = destUserName;
				messagesDB_[3][last] = message;

				repeat = false;
				return true;
			}
		}
	}
	return true;
}

void Chat::chatMenu() {
	bool chatMenuLoop = true;
	while(chatMenuLoop) {
		std::string greetingsUser;
		if (currentUser_.empty()) {greetingsUser = "stranger";}
		else {greetingsUser = currentUser_;}
		std::cout << "Hello, "<< greetingsUser <<"!\nPress 1 for Registration,\nPress 2 for Login,\nPress 3 to enter chat "
									   "board,\n"
					 "Press 0 for exit.\n";
		std::string chatOption = question("Enter: ");
		if (chatOption == "1") {
			signUp();
		} else if (chatOption == "2") {
			signIn();
		} else if (chatOption == "3") {
			try {
				if(!userLoggedIn()) {
					throw LoginFirst();
				}
				messageBoard();
			}
			catch (std::exception& e) {
				std::cout << "\x1B[31m" << e.what() << "\033[0m\n";
			}
		} else if (chatOption == "0") {
			chatMenuLoop = false;
		} else {
			chatMenuLoop = true;
		}
	}
}

std::string Chat::getRealName(std::string& userName) {
	for (auto i = 0; i < usersDB_[0].size(); i++) {
		if (usersDB_[0][i] == userName)
			return usersDB_[2][i];
	}
	return userName;
}