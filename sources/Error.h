#pragma once
#include<exception>

class UserNameBusy final : public std::exception {
public:
    const char* what() const noexcept override;
};

class IncorrectUserNameOrPassword final : public std::exception {
public:
    const char* what() const noexcept override;
};

class UserNameNotFound final : public std::exception {
public:
    const char* what() const noexcept override;
};

class WrongSymbols final : public std::exception {
public:
	const char* what() const noexcept override;
};

class LoginFirst final : public std::exception {
public:
	const char* what() const noexcept override;
};