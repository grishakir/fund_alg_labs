#pragma once
#include<exception>
#include <string>

class FileException :
	public std::exception
{
private:
	std::string errorStr;

public:
	FileException(std::string error);

	const char* what() const noexcept;
};