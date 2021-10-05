/*  Очевидно, что:
Проверка на выпуклость.
Можно пройтись по сторонам многоугольника и проверять векторным произведением,
что мы поворачиваем всегда в одну сторону (то есть если у нас последовательные
точки a, b и c, то  (b−a)×(c−a)>0 ).
a×b = a1*b2 + a2*b1
*/

#include<iostream>
#include<stdarg.h>
#include"Point.h"

bool checkСonvexity(size_t numOfPoints, ...) {
	Point pointBuffer[3];
	va_list args;
	va_start(args, numOfPoints);

	if (numOfPoints > 2) {

		for (size_t i = 0; i < numOfPoints; i++) {

			if (i > 2) {
				pointBuffer[2] = va_arg(args, Point);

				if (((pointBuffer[1] - pointBuffer[0]).x * (pointBuffer[2] - pointBuffer[0]).y +
					(pointBuffer[1] - pointBuffer[0]).x * (pointBuffer[2] - pointBuffer[0]).y) <= 0) {
					return false;
				}

				pointBuffer[0] = pointBuffer[1];
				pointBuffer[1] = pointBuffer[2];
			}
			else {
				pointBuffer[i] = va_arg(args, Point);
			}
		}
	}
	else {
		throw std::invalid_argument("Less then 3 points\n");
	}

	return true;
}

int main() {
	Point fig[3];
	fig[0].x = 0;
	fig[1].x = 2;
	fig[2].x = 4;
	fig[0].y = 0;
	fig[1].y = 4;
	fig[2].y = 0;

	std::cout << checkСonvexity(3, fig[0], fig[1], fig[2]) << std::endl;
	system("pause");
	return 0;
}