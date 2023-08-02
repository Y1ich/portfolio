#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
using namespace std;
ofstream fout;
ifstream fin;
const int m = 5, n = 6;
char sh[6][120];
//---------------------функция ввода данных-------------------------------
void vvod(double a[m][n]) {
    int i, j;
    for (i = 0; i < 6; i++) {
        fin.getline(sh[i], 120, '\n');
        if (i < 4)
            fout << sh[i] << endl;
    }
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            fin >> a[i][j];
    fin.close();
}
//------------------------функция вывода данных-----------------------------------
void vivod(double a[m][n]) {
    int i, j;
    for (i = 0; i < m; i++) {
        fout << "||";
        fout.setf(ios::left);
        for (j = 0; j < n; j++)
            switch (j) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                fout.width(9);
                fout.unsetf(ios::scientific);
                fout.setf(ios::fixed);
                fout.precision(2);
                fout << a[i][j] << "||";
                break;
            case 5:
                fout.width(9);
                fout.unsetf(ios::fixed);
                fout.setf(ios::scientific);
                fout.precision(2);
                fout << a[i][j] << "||\n";
                break;
            }
        if (i == 4)
            fout << sh[5] << endl;
        else
            fout << sh[4] << endl;
    }
    fout.unsetf(ios::scientific);
}
//----------------------------Главная функция-------------------------------
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    double a[m][n];
    fin.open("Z:\\VisualStudio\\ConsoleApplication2\\data.txt");
    if (!fin) {
        cout << "Ошибка при открытии файла данных!";
        exit(0);
    }
    fout.open("l4.res");
    if (!fout) {
        cout << "Ошибка при открытии файла результатов!";
        exit(0);
    }
    vvod(a);
    vivod(a);
    fout.close();
    return 0;
}

