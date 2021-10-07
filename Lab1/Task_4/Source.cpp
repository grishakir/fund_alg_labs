#include<iostream>
#include<vector>
#include<fstream>

void getNum(std::ifstream& in, std::string& number, int* base);
void fromStringToDeceminal(long long* numInDec, const std::string& number, int base);

int main(int argc, char* argv[]){

	std::ifstream in;
	std::string path;
	std::string number;
	std::ofstream out;
	int base;
	long long numInDec;


	try {
		if (argc != 2) {
			throw std::invalid_argument("Too small args\n");
		}
	}
	catch (std::invalid_argument ex) {
		std::cout << ex.what() << std::endl;
		return 1;
	}
	
	try {
		path = argv[1];
		in.open(path);
		out.open("out.txt");

		if (in.good()) {

		}
		else {
			throw std::invalid_argument("Can't get access to" + path + "\n");
		}

		while (in) {
			getNum(in, number, &base);
			fromStringToDeceminal(&numInDec, number, base);
			out << number << " " << base << "->" << numInDec << std::endl;
		}
	}
	return 0;
}

void getNum(std::ifstream& in, std::string& number, int* base) {
	char c;
	bool flag = 1;
	char maxChar = 0;

	c = in.peek();
	while ((c == ' ' || c == '\t' || c == '\n') && in) {
		in.get(c);
		c = in.peek();
	}

	while (!(c == ' ' || c == '\t' || c == '\n') && in) {
		in.get(c);
		number += c;

		if (c > maxChar) {
			maxChar = c;
		}
		
		c = in.peek();
	}

	if (maxChar <= '9') {
		*base = '9' - '0' + 1;
	}
	else
	{
		*base = maxChar - 'A' + 1 + 10;
	}
}

void fromStringToDeceminal(long long* numInDec, const std::string& number, int base) {
	long long int multiplier = 1;
	long long int numLen = number.length();


	for (int i = 1; i < number.length(); i++)
}