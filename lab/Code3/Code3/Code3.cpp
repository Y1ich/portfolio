#include<iostream>
#include<iomanip>
#include<windows.h>
using namespace std;
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    double M[5][6];
    int i, j, a, b;
    //-----------Ввод/вывод элементов массива------------------------------------
    double s = 0;		// переменная для нахождения суммы элементов
    cout << "\n Массив M: ";
    for (i = 0; i < 5; i++) {
        cout << "\n";
        for (j = 0; j < 6; j++) {         //ввод/вывод элементов и подсчет суммы
            M[i][j] = rand();            //cin >> M[i][j];                    
            cout << setw(12) << M[i][j];  s += M[i][j];
        }
    }
    cout << "\nСумма массива =" << s << endl;
    //------------------Вывод массива в таблицу-------------------------------
    //Массив строк шапки таблицы:

    char sh[][99] = { "		Массив в таблице 			",
"||==========||==========||==========||==========||==========||==========||",
"||  Данные 1|| Данные 2 || Данные 3 || Данные 4 || Данные 5 || Данные 6 ||",
"||==========||==========||==========||==========||==========||==========||",
"||----------||----------||----------||----------||----------||----------||",
"||==========||==========||==========||==========||==========||==========||" };

    for (i = 0; i < 4; i++)              //Вывод на экран строк шапки
        cout << sh[i] << endl;
    for (i = 0; i < 5; i++) {           //Цикл for по индексам строк массива
        cout << "||";
        for (j = 0; j < 6; j++)	    //Цикл for по индексам столбцов массива
            //форматный вывод элементов, отличающийся для разных столбцов 
            switch (j) {
            case 0: case 1: case 2: case 3: case 4: cout.unsetf(ios::fixed);
                cout.setf(ios::scientific); cout << setprecision(2) << setw(12)
                    << M[i][j] << "||";
                break;
            case 5: cout.unsetf(ios::scientific); cout.setf(ios::fixed);
                cout << setprecision(2) << setw(12) << M[i][j] << "||\n";
                break;
            }
        if (i == 4) 	cout << sh[5] << endl;
        else	cout << sh[4] << endl;
    }
    cout << "\nВведите промежуток (a, b)\n";
    cin >> a >> b;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++)
            if ((i == 0 or i == 2 or i == 4) and j == 0)
                if (a <= M[i][j] and M[i][j] <= b)
                    cout << setprecision(0) << M[i][j] << "\t" << i + 1 << " " << j + 1 << endl;
    }
    cout << endl << endl;
    system("pause");
    return 0;
}
