#include <iostream>
#include <vector>
#include <fstream>
#include <stdarg.h>
#include "fileException.h"

namespace subs {
	void fillBuffer(std::ifstream& in, std::string& str, size_t strSize) {

		char c;
		str.clear();


		for (size_t i = 0; i < strSize; i++) {
			if (in) {
				in.get(c);
				str += c;
			}
			else {
				throw FileException::FileException(("Small file\n"));
			}


		}
	}

	void shiftBuffer(std::ifstream& in, std::string& buffer) {
		char c;
		buffer.erase(0, 1);
		in >> c;

		buffer.push_back(c);
	}

	bool findSubstrInStr(std::string substr, std::string str) { // 0 -- false, 1 -- true

		if (str.find(substr) == std::string::npos) {
			return 0;
		}
		return 1;
	}
	std::vector<std::string> FindSubstrInFiles(
		bool findSubstrInStr(std::string, std::string),
		std::string substr, ...) {
		va_list args;
		std::ifstream file;
		std::string buffer;
		std::string path;
		std::vector<std::string> result;
		int numOfArgs = 2;
		va_start(args, substr);
		
		for (int i = 0; i < numOfArgs; i++) {
			
			path = va_arg(args, std::string);
			file.open(path);

			if (file.good()) {
				fillBuffer(file, buffer, substr.size());

				while (file){
					if (findSubstrInStr(substr, buffer)) {
						result.push_back(path);
						break;
					}

					shiftBuffer(file, buffer);
				} 
			}
			else {
				throw FileException::FileException(("Can't get acces to file " + path + "\n").c_str());
			}
		}

		return result;

	}
}


int main(){
	std::vector<std::string> vecStr = 
		subs::FindSubstrInFiles(
			subs::findSubstrInStr,
			"dsgsk df lfpsdf",
			std::string("test1.txt"),
			std::string("Test2.txt"));
	
	for (auto i : vecStr) {
		std::cout << i << std::endl;
	}
	system("pause");
	return 0;
}