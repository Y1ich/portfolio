#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<conio.h>
#include <cstring>
#include <stdio.h>
#include<cmath>
#include<Windows.h>
#include<fstream>

using namespace std;

const int m = 5, n = 6;
ifstream fin;
ofstream fout;
char c[6][150];
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	fin.open("C:\\Users\\student\\source\\repos\\VisualStudio\\Ylia\\Text.txt");
	if (!fin) { cout << "Ошибка при открытии файла данных"; system("pause");  exit(0); }
	fout.open("l.res");
	if (!fout) { cout << "Ошибка при открытии файла результатов"; system("pause"); exit(0); }
	double a[m][n];
	double b[3][6];
	void vvod(double a[m][n]);
	void vivod(double a[m][n]);
	void obr(double a[m][n], double b[3][6], double&, double&);
	vvod(a);
	vivod(a);

	int i, j;
	double sum, pr;
	obr(a, b, pr, sum);

	fout << "\n\n\nNew array:\n";
	for (i = 0; i < 3; i++)
	{
		fout << '\n';

		for (j = 0; j < 6; j++)
			fout << setw(12) << b[i][j];
	}
	fout << "\n\nСумма положительных min элементов = " << sum
		<< "\nПроизведение отрицательных min элементов = " << pr << endl;

	fout.close();
	system("pause");
	return 0;
}

void vvod(double a[m][n])
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		fin.getline(c[i], 150, '\n');
		if (i < 4)
			fout << c[i] << endl;
	}

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			fin >> a[i][j];
	fin.close();
}

void vivod(double a[m][n])
{
	int i, j;

	for (i = 0; i < m; i++) {
		fout << '|'; fout.setf(ios::left);
		for (j = 0; j < n; j++)
			switch (j)
			{
			case 0: case 1: case 3:case 4: fout.width(14);
				fout.unsetf(ios::scientific); fout.setf(ios::fixed);
				fout.precision(2); fout << a[i][j] << '|';
				break;
			case 2:  fout.width(14); fout.unsetf(ios::fixed);
				fout.setf(ios::scientific); fout.precision(3);
				fout << a[i][j] << '|';
				break;
			case 5: fout.width(14);  fout << a[i][j] << "|\n"; break;
			}
		if (i == 4) fout << c[5] << endl;
		else fout << c[4] << endl;
	}
}

void obr(double a[m][n], double b[3][6], double& pr, double& sum)
{
	int i, j, k, l;
	double min1, min2, jmin1, jmin2;
	pr = 1;  sum = 0;

	for (i = 0, l = 0; i < m; i = i + 2, l += 2)
	{
		min1 = a[i][0];

		for (j = 0; j < 6; j++)
			if (a[i][j] < min1)
			{
				min1 = a[i][j]; jmin1 = j;
			}

		if (min1 < 0) pr *= min1;
		else if (min1 > 0) sum += min1;

		for (j = 0; j < 6; j++)

			if (a[i][j] != min1) {
				min2 = a[i][j]; jmin2 = j;
				break;
			}

		for (j = 0; j < 6; j++)
			if (a[i][j] < min2 && a[i][j] != min1)

			{
				min2 = a[i][j]; jmin2 = j;
			}

		if (min2 < 0) pr *= min2;
		else if (min2 > 0) sum += min2;

		b[0][l] = min1;
		b[1][l] = i;
		b[2][l] = jmin1;
		b[0][l + 1] = min2;
		b[1][l + 1] = i;
		b[2][l + 1] = jmin2;
	}

	int imin1, imin2;

	min1 = a[0][0]; imin1 = 0;
	for (i = 0; i < m; i = i + 2)
		for (j = 0; j < n; j++)
			if (a[i][j] < min1)
			{
				min1 = a[i][j]; imin1 = i;
			}

	for (i = 0; i < m; i = i + 2) {
		for (j = 0; j < n; j++)

			if (a[i][j] != min1) { min2 = a[i][j]; imin2 = i; break; }
		break;
	}
	for (i = 0; i < m; i = i + 2)
		for (j = 0; j < n; j++)
			if (a[i][j] < min2 && a[i][j] != min1)

			{
				min2 = a[i][j]; imin2 = i;
			}

	fout << "\n\nПервый мин. элемент: " << min1 << " , номер строки: " << imin1;
	fout << "\nВторой мин. элемент: " << min2 << " , номер строки: " << imin2;

	double t;
	for (j = 0; j < n; j++)
	{
		t = a[imin1][j]; a[imin1][j] = a[imin2][j]; a[imin2][j] = t;
	}
	fout << "\n\n                 Исходный массив после перестановки\n";
	fout << c[1] << endl;
	vivod(a);

}

