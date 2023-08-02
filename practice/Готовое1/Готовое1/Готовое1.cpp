#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<share.h>
#include<Windows.h>

using namespace std;
#pragma warning (disable:4996)

struct holod {
	char name[15];		//название холодильника
	char firm[10];		//страна
	int amount;            //емкость

} st;                                                 //указатель на данный структурный тип вместо объекта 
int z = sizeof(holod);
char sh[][256] =
{ "                     Холодильники ",
	"|=================|=================|=================|",
	"|Название         | Страна          |Емкость камеры   |",
	"|=================|=================|=================|",
	"|-----------------|-----------------|-----------------|"
};


ifstream fin;
ofstream fout, fout2;
fstream io;

void psh() {// вывод щапули
	for (int i = 0; i < 5; i++)
		cout << sh[i] << endl;
}

//Функция удаления пробелов (ведущих и замыкающих) в строковых данных
void filtr(char* Stroka) {
	char Source[255] = "";
	int x1 = 0, x2 = strlen(Stroka) - 1;
	while (Stroka[x1] == ' ' || Stroka[x1] == '|') x1++;
	while (Stroka[x2] == ' ' || Stroka[x2] == '\n' || Stroka[x2] == '|') x2--;
	int x = x1;
	for (x; x <= x2; x++)
		Source[x - x1] = Stroka[x];
	Source[x - x1] = '\0';
	strcpy(Stroka, Source);
}

// Перегрузка операци вывода "<<"
ostream& operator << (ostream& out, holod& st) {
	out.setf(ios::left, ios::adjustfield); // Сбросили правое выравнивание и установили левое
	out << setw(17) << st.name << setw(15) << st.firm << setw(15) << st.amount << setw(7) << endl;
	return out;
}

// Перегрузка операции ввода ">>"
istream& operator >> (istream& in, holod& st) {
	char T[80];
	in.getline(st.name, 15); filtr(st.name); in.clear();
	in.getline(st.firm, 10); filtr(st.firm); in.clear();
	in >> st.amount;
	in.getline(T, 80);
	return in;
}

//Функция создания текстового файла данных
void sozdata(char* fname) {
	fout.open(fname, ios::out); //открываем файл с исходными данными
	if (!fout) {
		cout << "Ошибка при открытии файла данных (sozdata) \n"; system("pause"); exit(0);
	}
	fout2 << "СОЗДАНИЕ ФАЙЛА ДАННЫХ \n";
m:
	cout << "Введите данные одной структуры:" << endl;
	cin >> st; fout << st; fout2 << st;
	cout << "Нажмите любую клавишу, если хотите продолжить запись и 0 - , если нет\n";
	char a = getch();
	if (a == '0') {
		fout.close();
		fout2 << "файл данных успешно создан!\n"; return;
	}
	else goto m;
}

//Функция создания бинарного файла
void sozbin(char* fname, char* bname) {
	fin.open(fname, ios::in);
	if (!fin) {
		cout << "Ошибка при открытии файла данных (sozbin) \n"; system("pause"); exit(0);
	}
	io.open(bname, ios::trunc | ios::out | ios::binary);
	if (!io) {
		cout << "Ошибка при открытии файла данных (sozbin) \n"; system("pause"); exit(0);
	}
	fout2 << "\nCоздание бинарного файла \n";
	while (fin >> st) io.write((char*)&st, z);
	fin.close(); io.close();
	fout2 << "Бинарный файл создан! \n";
}
// Функция удаления
void del(char* dname, char* bname) {
	char name[15] = "";
	int k = 0, t = 0;
	int fh = _open(bname, O_BINARY | O_RDWR);
	fout2 << "\nУдаление записей из бинарного файла\n";
	cout << "\nУдаление записей из бинарного файла\n";
	fin.open(dname, ios::in);
	if (!fin) {
		cout << "Ошибка при открытии текстового файла\n";
		system("pause");
		exit(0);
	}
	while (!fin.eof()) {
		fin.getline(name, 15);
		filtr(name);
		fout2 << "Поиск:" << name << endl;
		cout << "Поиск:" << name << endl;
		if (!strcmp(name, "")) {
			fout2 << "Нет данных\n";
			cout << "Нет данных\n";
			continue;
		}
		t = 0;
		do {
			k = 0;
			_lseek(fh, 0, 0);
			while (!_eof(fh)) {
				_read(fh, (char*)&st, z);
				filtr(st.name);
				if (!strcmp(st.name, name)) {
					k = 1;
					t++;
					while (!_eof(fh)) {
						_read(fh, (char*)&st, z);
						cout << st << endl;
						_lseek(fh, -2 * z, 1);
						_write(fh, (char*)&st, z);
						_lseek(fh, z, 1);
					}
				}
			}

			if (k == 1) {
				fout2 << "Удаление:" << name << endl;
				cout << "Удаление:" << name << endl;
				_chsize(fh, _filelength(fh) - z);
			}
		} while (k != 0);
		if (t == 0) {
			fout2 << "Не найдено:" << name << endl;
			cout << "Не найдено:" << name << endl;
		}
	}
	_close(fh);
	fin.close();
}
// Функция коррекции
void kor(char* fname, char* bname) {
	io.open(bname, ios::in | ios::binary);
	if (!io) {
		cout << "Ошибка при открытии бинарного файла\n";
		system("pause");
		exit(0);
	}
	fout.open(fname, ios::trunc | ios::out);
	if (!fout) {
		cout << "Ошибка при открытии текстового файла\n";
		system("pause");
		exit(0);
	}
	fout2 << "\nКоррекция файла данных\n";
	while (io.read((char*)&st, z)) {
		fout << st;
	}
	io.close();
	fout.close();
	fout2 << "Файл данных успешно откорректирован!\n";
}
// Чтение бинарного файла
void cht(char* bname) {
	cout << "Чтение файла: " << endl;
	fout2 << "\nЧтение файла: " << endl;
	io.open(bname, ios::in | ios::binary);
	if (!io) {
		cout << "Ошибка при открытии бинарного файла\n";
		system("pause");
		exit(0);
	}
	psh();
	while (io.read((char*)&st, z)) {
		fout2 << st;
		cout << setiosflags(ios::left) << "| " << setw(16) << st.name << "| " << setw(16) << st.firm << "| " << setw(16) << st.amount << "| " << endl;
	}
	cout << sh[4] << endl;
	io.close();
}

// Функция переписывания записей из рабочего файла в основной бинарный файл
void rewrite(char* fname, char* bname) {
	fin.open(fname, ios::in);
	if (!fin) {
		cout << "Ошибка при открытии файла данных (rewrite) \n";
		system("pause");
		exit(0);
	}

	io.open(bname, ios::out | ios::binary | ios::app);
	if (!io) {
		cout << "Ошибка при открытии бинарного файла (rewrite) \n";
		system("pause");
		exit(0);
	}

	while (fin >> st) {
		io.write((char*)&st, z);
	}

	fin.close();
	io.close();
}

// Главная функция
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fname[20];
	char bname[20] = "bin.txt";
	char dname[20] = "del.txt";
	fout2.open("fout2.txt", ios::out);
	if (!fout2) {
		cout << "Ошибка при открытии файла протокола\n";
		system("pause");
		exit(0);
	}
	cout << "Введите имя файла данных: ";
	cin.getline(fname, 20);
	sozdata(fname);
	sozbin(fname, bname);
	cht(bname);
	del(dname, bname);
	kor(fname, bname);
	cht(bname);
	cout << "После удаления из текстового записываем в бинарный:" << endl;
	rewrite(fname, bname);
	cht(bname);
	fout2.close();
	system("pause");
	return 0;
}

