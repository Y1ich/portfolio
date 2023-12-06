#include "begining.h"
#ifndef funktions_h
#define funktions_h
void zags::printStr()//функция для выведения данных в строчку
{
	cout.setf(ios::left);
	cout << '|' << setw(23) << zg.date << '|' << setw(23) << zg.numberofzags << '|' << setw(23) << zg.FIOh << '|' << setw(23) << zg.bh << '|' << setw(23) << zg.pasph 
		 << '|' << setw(23) << zg.FIOw << '|' << setw(23) << zg.bw << '|' << setw(23) << zg.paspw << "\n";
	cout.unsetf(ios::left);
}
void printTableHead()//функция для выведения шапки таблицы
{
	for (int i = 0; i < 4; i++) cout << tableHead[i] << endl;
}
void mySwap(zags& k1, zags& k2)//функция для перестановки двух структур (на всякий случай)
{
	zags t = k1;
	k1 = k2;
	k2 = t;
}/*
void makeData(const char* dname)//функция для создания записей о кинотеатрах
{
	ofstream fout(dname);
	if (!fout) { cout << "Error of open file for writing" << endl; return; }
	cout << "Введите структуры в одну строчку (Имя(8 символов на 2 слова)/Адресс(6 символов)/Стоимость/Места) через пробел" << endl;
	int choose;//число, по которому определям: продолжаем вводить данные или нет
	do {
		cin >> kn;
		fout << kn;
		cout << " Continue (1|0)? " << endl;
		cin >> choose;
		cin.get();
		cout << endl;
	} while (choose == 1);
	fout.close();
}
*/
void makeBin(const char* dname1, const char* bname1, const char* dname2, const char* bname2)//создаёт бинарный файл из файла с данными
{
	finb.open(dname1);
	finr.open(dname2);
	if (!finb) { cout << "Error of open data file(1)" << endl; return; }
	if (!finr) { cout << "Error of open data file(1)" << endl; return; }
	fiob.open(bname, ios::binary | ios::out);
	fior.open(bname, ios::binary | ios::out);
	if (!fiob) { cout << "Error of open bin file(1)" << endl; return; }
	if (!fior) { cout << "Error of open bin file(1)" << endl; return; }
	while (finb.peek() != EOF)
	{
		finb >> zg;
		fiob.write((char*)&zg, ZAGS_SIZE);
	}
	while (finr.peek() != EOF)
	{
		finr >> zg;
		fior.write((char*)&zg, ZAGS_SIZE);
	}
	finb.close();
	fiob.close();
	finr.close();
	fior.close();
}
void readBin(const char* bname1, const char* bname2)//функция для чтения бинарного файла
{
	finb.open(bname1, ios::binary);
	finr.open(bname2, ios::binary);
	if (!finb) { cout << "Error of open bin file(2)" << endl; return; }
	if (!finr) { cout << "Error of open bin file(2)" << endl; return; }
	printTableHead();
	while (finb.peek() != EOF)
	{
		finb.read((char*)&zg, ZAGS_SIZE);
		zg.printStr();
	}
	while (finz.peek() != EOF)
	{
		finz.read((char*)&zg, ZAGS_SIZE);
		zg.printStr();
	}
	cout << tableHead[3] << endl;
	fin.close();
}
/*
void cleanBin(const char* bname, const char* sname)//функция для очистки бинарного файла по названию кинотеатра
{
	fin.open(sname);
	if (!fin) { cout << "Error of open search file" << endl; return; }
	int fh, t = 0;//первое число - дескриптор бинарного файла для работы с ним на нижнем уровнем
	char sk[20];//массив символов - для взятия поискового значения
	bool is_found;//булевская переменная, указывающая о нахождение нужного значения поля
	_sopen_s(&fh, bname, _O_BINARY | _O_RDWR, _SH_DENYNO, _S_IWRITE);
	if (!fin || fh == -1) { cout << "Error of open bin file(3)" << endl; return; }
	while (fin.peek() != EOF)
	{
		fin.getline(sk, 21);
		filtr(sk);
		if (!strcmp(sk, " ")) { cout << "Строка для поиска пуста\n"; continue; }
		t = 0;
		do
		{
			is_found = false;
			_lseek(fh, 0, SEEK_SET);
			while (!_eof(fh))
			{
				_read(fh, (char*)&kn, KINO_SIZE);
				if ((!strcmp(kn.getName(), sk)))
				{
					is_found = true;
					t++;
					while (!_eof(fh))
					{
						_read(fh, (char*)&kn, KINO_SIZE);
						_lseek(fh, -2 * KINO_SIZE, SEEK_CUR);
						_write(fh, (char*)&kn, KINO_SIZE);
						_lseek(fh, KINO_SIZE, SEEK_CUR);
					}
				}

			}
			if (is_found)
			{
				_chsize(fh, _filelength(fh) - KINO_SIZE);
				cout << "Удалены кинотеатры с именем " << sk << endl;
			}
			if (t == 0) cout << "Кинотеатр с именем " << sk << " не найден\n";
		} while (is_found);
	}
	_close(fh);
	fin.close();
}
int opornyi(kino* a, int start, int end)//функиция для поиска опорного элемента: выбирается для начала самый правый, затем все, что меньше его помещаются назад
{
	double pravopor = a[end].getCost();//значение правого элемента в массиве. Предполагаем, что он самый большой
	int oporInd = start;//опорный индекс, то что ищем. Считаем, что с самого начала он находится в начале массива
	for (int i = start; i != end; i++)
	{
		if (a[i] < pravopor) { mySwap(a[i], a[oporInd]); oporInd++; }
	}
	mySwap(a[end], a[oporInd]);
	return oporInd;
}
void quicksort(kino* a, int start, int end)//функция быстрой сортировки.
{
	if (start >= end) return;
	int pivot = opornyi(a, start, end);
	quicksort(a, start, pivot - 1);
	quicksort(a, pivot + 1, end);
}
void makeSort(const char* bname1, const char* bname2)//функция для записи отсортированного массива в файл
{
	cout << "Подсчёт структур" << endl;
	fin.open(bname1, ios::binary);
	if (!fin) { cout << "Error of open bin file(4)" << endl; return; }
	while (fin.peek() != EOF)
	{
		fin.read((char*)&kn, KINO_SIZE);
		kn.printStr();
		masSize++;
	}
	cout << "Обнаружено " << masSize << " структур" << endl;
	cout << "Вывод несортированного файла" << endl;
	fin.clear();//чтобы не закрывать файл, переставляем курсор на начало файла
	fin.seekg(0);
	kino* k = new kino[masSize];//массив структур
	int i = 0;//счётчик для перемещения по массиву структур
	while (fin.peek() != EOF)
	{
		fin.read((char*)&k[i], KINO_SIZE);
		i++;
	}
	cout << "Производим сортировку " << endl;
	quicksort(k, 0, masSize - 1);
	cout << "Запись сортированного массива в новый файл" << endl;
	fin.clear();
	fin.seekg(0);
	i = 0;
	fio.open(bname2, ios::binary | ios::out);
	if (!fio) { cout << "Error of open new bin file" << endl; return; }
	while (i != masSize)
	{
		fio.write((char*)&k[i], KINO_SIZE);
		cout << k[i].getName() << " " << k[i].getCost() << endl;;
		i++;
	}
	delete[] k;
	masSize = 0;
	i = 0;
	fin.close();
	fio.close();
}
*/
#endif