#include"Error.h"

const char* UserNameBusy::what() const noexcept {
    return "This user name is busy.\n";
}

const char* IncorrectUserNameOrPassword::what() const noexcept {
    return "Incorrect user name or password.\n";
}

const char* UserNameNotFound::what() const noexcept {
    return "There is no such user name.\n";
}

const char* WrongSymbols::what() const noexcept {
	return "You can't use \"|\" symbol";
}

const char* LoginFirst::what() const noexcept {
	return "Please, login first";
}