#include <iostream>
#include <stdexcept>

using namespace std;

class ExceptionSize // Класс исключения
{
public:
	virtual const char* what() const throw()
	{
		return "Слишком большой запрашиваемый объем памяти";
	}
};

class Vector
{
private:
	int size;  // Фактический объем памяти
	int* data; // Указатель на динамический массив

public:
	enum { max = 1000 };

	Vector(int size) //конструктор
	{
		if (size<0 || size>max)
			throw ExceptionSize();
		data = new int[size];;
	}

	~Vector() //деструктор
	{
		delete[] data;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int size;
	cin >> size;
	try
	{
		Vector v(size);
		cout << "Выделена память: " << size << endl;
	}
	catch (const ExceptionSize& e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

