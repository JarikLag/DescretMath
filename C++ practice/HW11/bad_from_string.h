#pragma once

#include <exception>
#include <string>

class bad_from_string :	public std::exception {
public:
	bad_from_string (const char* message);
	bad_from_string(const std::string&);

	const char* what() const noexcept;
private:
	std::string message;
};

