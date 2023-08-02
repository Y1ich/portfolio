#include <stack>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;
int main() {
	setlocale(LC_ALL, "RUS");
	ifstream in;
	ifstream in2;
	queue<double> a;
	stack<double> b;
	double c;
	// открываем файл на чтение
	in.open("stack.txt");
	in2.open("deque.txt");
	// считываем данные из файла в стек
	while (!in.eof()) {
		in >> c;
		b.push(c);
	}
	// создаем копию стека и выводим на экран
	stack<double> d = b;
	while (!d.empty()) {
		cout << d.top() << " ";
		d.pop();
	}
	cout << endl;
	// запрашиваем позицию и количество элементов, которые нужно удалить
	// создаем временный стек и переносим элементы до указанной позиции
	// удаляем указанное количество элементов
	// переносим оставшиеся элементы из начального стека во временный
	// перезаписываем начальный стек временным и выводим оставшиеся элементы на экран
	int pos, count;
	cin >> pos >> count;
	d = b;
	stack<double> e;
	while (pos > 0) {
		e.push(d.top());
		d.pop();
		pos--;
	}
	while (count > 0) {
		d.pop();
		count--;
	}
	while (!d.empty()) {
		e.push(d.top());
		d.pop();
	}
	d = e;
	cout << "Результат удаления: " << endl;
	while (!d.empty()) {
		cout << d.top() << " ";
		d.pop();
	}
	cout << endl;
	// считываем данные из второго файла в очередь и выводим на экран
	while (!in2.eof()) {
		in2 >> c;
		a.push(c);
	}
	cout << "Очередь: " << endl;
	queue<double> f = a;
	while (!f.empty()) {
		cout << f.front() << " ";
		f.pop();
	}
	cout << endl;
	// переносим элементы из очереди в стек и суммируем их
	f = a;
	while (!f.empty()) {
		b.push(f.front());
		f.pop();
	}
	while (!b.empty()) {
		cout << b.top() << " ";
		b.pop();
	}
	cout << endl;
}
