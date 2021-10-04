#include "fileException.h"

FileException::FileException(std::string error) : errorStr(error)
{
}

const char* FileException::what() const noexcept
{
	return errorStr.c_str();
}
