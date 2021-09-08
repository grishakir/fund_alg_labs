#include <iostream>
#include <vector>
#include <stdarg.h>

std::vector<std::string> FindSubstrInFiles(
	bool FindSubstrInStr(std::string, std::string),
	std::string substr, ...) {
	int numOfArgs = 0;
	va_list args;
	va_start(args, numOfArgs);

	for (int i = 0; i < numOfArgs;)



}

bool FindSubstrInStr(std::string substr, std::string str) { // 0 -- false, 1 -- true
	if (str.find(substr) == std::string::npos) {
		return 0;
	}
	else {
		return 1;
	}
}