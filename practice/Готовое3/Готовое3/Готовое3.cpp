#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <string>

using namespace std;

ofstream fout, f;
ifstream fin;
fstream io;

char sh[][256] = {
	"|                          holod                        |",
	"|------------------|--------------------|----------------|",
	"|    Название      |       Страна       | Емкость камеры |",
	"|------------------|--------------------|----------------|",
};

struct holod {
	char name[20];
	int amount;
	char firm[20];

}t_obj;

const int sz = sizeof(holod);

void filter(char* str) {
	int x;
	int xLeft = 0,
		xRight = strlen(str) - 1;
	while (str[xLeft] == ' ') xLeft++;
	while (str[xRight] == ' ') xRight--;
	for (x = xLeft; x <= xRight; x++)
		str[x - xLeft] = str[x];
	str[x - xLeft] = '\0';
}

void sh_output() {
	for (int i = 0; i < 4; i++)
	{
		f << sh[i] << endl;
		cout << sh[i] << endl;
	}
}

istream& operator >> (istream& in, holod& obj) {
	char T[100];
	in.getline(obj.name, 20); filter(obj.name);
	in.getline(obj.firm, 20); filter(obj.firm);
	in >> obj.amount;
	in.getline(T, 100);
	return in;
}
ifstream& operator >> (ifstream& in, holod& obj) {
	char T[100];
	in.get(obj.name, 20); filter(obj.name);
	in.get(obj.firm, 20); filter(obj.firm);
	in >> obj.amount;
	in.getline(T, 100);
	return in;
}
ostream& operator << (ostream& out, const holod& obj) {
	out.setf(ios::left);
	out << setw(20) << obj.name
		<< setw(17) << obj.firm
		<< setw(21) << setprecision(2) << fixed << obj.amount;
	out.unsetf(ios::left);
	return out;
}

//-----------ф-ция создания txt файла------------------------//

void sozdat(const char* file) {
	fout.open(file);
	char c = '1';
	while (c == '1') {
		cout << "Введите данные одной структуры: " << endl;
		cout << "Введите название города: " << endl;
		cin >> t_obj.name;
		cout << "Введите страну: " << endl;
		cin >> t_obj.firm;
		cout << "Введите кол-во улиц: " << endl;
		cin >> t_obj.amount;
		fout << t_obj << endl;
		cout << "Нажмите 1 если хотите продолжить и 0 если нет" << endl;
		cin >> c;
	}
	fout.close();
	return;

}

//-----------ф-ция создания бин. файла------------------------//


void create_bin_file(const char* file, const char* binary) {
	fin.open(file);
	if (!fin) { cout << "Ошибка открытия файла \"sozd.dat\""; exit(0); }
	io.open(binary, ios::out | ios::binary);
	while (fin.peek() != EOF) {
		fin >> t_obj;
		io.write((char*)&t_obj, sz);
	}
	cout << "\nBinary file created\n";
	f << "\nBinary file created\n";
	io.close();
	fin.close();
}

//-----------ф-ция чтения бин. файла------------------------//

void read_bin_file(const char* binary) {
	io.open(binary, ios::in | ios::binary);
	if (!io) { cout << "Error opening binary file\n"; system("pause"); exit(0); }
	sh_output();
	while (io.read((char*)&t_obj, sz)) {
		f << t_obj << endl;
		f << sh[1] << endl;
		cout << t_obj << endl;
		cout << sh[1] << endl;
	}
	io.close();
	system("pause");
}


//-----------ф-ция удаления из бин. файла------------------------//

void del(const char* del, const char* binary) {
	char name[20];
	bool is_found;
	fin.open(del);
	if (!fin) {
		cout << " Ошибка открытия файла \"del.txt\" "; system("pause"); exit(0);
	}
	cout << "\nRemoving data from a file\n";
	f << "\nRemoving data from a file\n";
	io.open(binary, ios::binary | ios::in | ios::out);
	ofstream Fileout("name.cpp", ios::binary);
	while (fin.peek() != EOF) {
		fin.getline(name, 20); filter(name);
		if (!strcmp(name, "")) {
			cout << "Data line is empty\n";
			f << "Data line is empty\n";
			continue;
		}
		cout << "Search: " << name << endl;
		f << "Search: " << name << endl;
		io.seekg(0, ios::beg);
		is_found = false;
		while (io.peek() != EOF) {
			io.read((char*)&t_obj, sz);
			if (!strcmp(t_obj.name, name))
			{
				is_found = true;
				strcpy(t_obj.name, "*");
				io.seekg(-sz, ios::cur);
				io.write((char*)&t_obj, sz);
				io.seekg(sz, ios::cur);
			}
		}
		if (!is_found)
		{
			cout << name << " data not found\n";
			f << name << " data not found\n";
		}
		else
		{
			cout << name << " data removed\n";
			f << name << " data removed\n";
		}
	}
	io.seekg(0, ios::beg);
	while (io.peek() != EOF) {
		io.read((char*)&t_obj, sz);
		if (strcmp(t_obj.name, "*"))
			Fileout.write((char*)&t_obj, sz);
	}
	Fileout.close();
	fin.close();
	io.close();

	io.open("name.cpp", ios::binary | ios::in);
	Fileout.open(binary, ios::binary);
	while (io.peek() != EOF) {
		io.read((char*)&t_obj, sz);
		Fileout.write((char*)&t_obj, sz);
	}
	Fileout.close();
	io.close();
	remove("name.cpp");
}

// Функция сортировки массива структур методом пузырькового включения
void bubbleSort(holod arr[], int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0 && strcmp(arr[j - 1].name, arr[j].name) > 0; j--) {
			holod temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
			cout << temp << endl;
		}
	}
}

// Функция упорядочения бинарного файла
void orderBinaryFile(const char* filename) {
	ifstream fin(filename, ios::in | ios::binary);
	if (!fin) {
		cout << "Ошибка открытия бинарного файла для чтения" << endl;
		return;
	}

	// Определение количества записей структур в бинарном файле
	fin.seekg(0, ios::end);
	int fileSize = fin.tellg();
	int numRecords = fileSize / sizeof(holod);
	fin.seekg(0, ios::beg);

	// Выделение динамической памяти под массив структур
	holod* records = new holod[numRecords];

	// Чтение структур из бинарного файла в массив
	fin.read(reinterpret_cast<char*>(records), fileSize);
	fin.close();

	// Сортировка массива структур
	bubbleSort(records, numRecords);

	// Создание нового бинарного файла с тем же именем
	ofstream fout(filename, ios::out | ios::binary);
	if (!fout) {
		cout << "Ошибка открытия бинарного файла для записи" << endl;
		delete[] records;
		return;
	}

	// Запись отсортированного массива структур в новый бинарный файл
	fout.write(reinterpret_cast<const char*>(records), fileSize);
	fout.close();

	delete[] records;
}

void menu() {
	cout << "\n                    МЕНЮ: \n"
		<< "\n         Создание файла--------------------------------- 1"
		<< "\n         Чтение файла----------------------------------- 2"
		<< "\n         Сортировка файла------------------------------- 3"
		<< "\n         Удаление данных из файла----------------------- 4"
		<< "\n         Выход------------------------------------------ 0\n";

}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int p = 0;
	char file[15];
	menu();
	cin >> p;
	cin.get();
	f.open("end.txt");
	while (p <= 4) {
		switch (p)

		{
		case 1:
			cout << "\nСоздание файла\n";
			sozdat("sssozd.txt");
			create_bin_file("sssozd.txt", "binary.cpp");
			break;
		case 2:
			cout << "\nЧтение файла\n";
			read_bin_file("binary.cpp");
			break;
		case 3:
			cout << "\nСортировка файла\n";
			orderBinaryFile("binary.cpp");
			break;
		case 4:
			cout << "\nУдаление данных из файла\n";
			del("del.txt", "binary.cpp");

			break;
		default:
			exit(0);
		}
		system("cls");
		menu();
		cin >> p;
		fout.close();
	}
	sozdat("sssozd.txt");
	create_bin_file("sssozd.txt", "binary.cpp");
	read_bin_file("binary.cpp");
	cout << endl;
	const char* filename = "binary.bin";
	orderBinaryFile(filename);
	read_bin_file("binary.cpp");
	return 0;
}

