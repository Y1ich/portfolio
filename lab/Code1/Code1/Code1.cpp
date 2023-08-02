#include <iostream> 
#include <windows.h> 
#include <cmath> 
using namespace std;
const double a = 3.44, b = 8.75;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	double x, y, z, t, q;
	cout << "Введите переменные\nx= ";
	cin >> x; cout << "y="; cin >> y;
	cout << "\nПромежуточные переменные:";
	t = tan(pow(a, 7)) + log10(pow(y, b)) + pow(x, 3.2);
	q = pow(abs(b), 3.2) * (exp(pow(abs(a + b / y), 1.0 / 3)));  z = (t / q) + 2.3 * pow(10, -4);
	cout << "\nt=" << t << "\nq=" << q
		<< "\n\nРезультат с промежуточными переменными: \nz=" << z;
	z = (a + pow(y, b)) / (exp(a * y + 1) - pow(sin(x), 3)) / (2.25e+02 - x * y / b);
	cout << "\n\nРезультат с помощью одного выражения:\nz=" << z;
	cout << "\n\nРезультат с помощью выражения в операторе вывода:\nz="
		<< ((tan(pow(a, 7)) + log10(pow(y, b)) + pow(x, 3.2)) / pow(abs(b), 3.2) * (exp(pow(abs(a + b / y), 1.0 / 3)))) + 2.3 * pow(10, -4);
	printf("\n\nРезультат с помощью выражения- параметра функции\ printf:\nz = % 12lf", ((tan(pow(a, 7)) + log10(pow(y, b)) + pow(x, 3.2)) / pow(abs(b), 3.2) * (exp(pow(abs(a + b / y), 1.0 / 3)))) + 2.3 * pow(10, -4));
	int i;
	cout << "\n\nВведите координаты точки\nx="; cin >> x; cout << "y="; cin >> y;
	//Вычисление выражения в операторе вывода cout «…; 
	cout << "\n\nЗначение:\n" << ((pow(x - 3, 2) + pow(y - 5, 2) <= 4) && (x >= 3));
	//Использование условной операции для вывода слов true или false 
	((pow(x - 3, 2) + pow(-5, 2) <= 4) && (x >= 3)) ? cout << "- true" : cout << "-false";
	// Вычисление выражения в операторе присваивания 
	printf("\n\nВведите координаты точки\nx= ");
	scanf_s(" %lf", &x);  printf("y="); scanf_s(" %lf", &y);
	i = ((pow(x - 3, 2) + pow(y - 5, 2) <= 4) && (x >= 3));
	printf("\nЗначение выражения: %d", i); cout << endl;
	system("pause");
	return 0;
}

