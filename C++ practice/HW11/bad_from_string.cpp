#include "bad_from_string.h"

bad_from_string::bad_from_string(const char* message) : message(message) {}

bad_from_string::bad_from_string(const std::string& message) : message(message) {}

const char* bad_from_string::what() const noexcept {
	return message.c_str();
}
