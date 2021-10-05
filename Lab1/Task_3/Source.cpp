#include<stdarg.h>
#include<iostream>
double findValueInPoint(double point, size_t degree, ...) {
	double result = 0;
	va_list args;

	va_start(args, degree);

	for (size_t i = 0; i < degree; i++) {
		result *= point;
		result += va_arg(args, double);
	}

	return result;
}
int main() {

	std::cout << findValueInPoint(1, 4, 1.0, 2.0, 3.0, 4.0);
	system("pause");
	return 0;
}