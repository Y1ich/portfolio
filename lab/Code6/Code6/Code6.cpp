#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include <fstream>

using namespace std;

ofstream fout;

double stx(double x, int n)//Вычисление xn 
{
    if (n == 0) return 1;
    if (x == 0) return 0;
    if (n == 1) return x;
    if (n > 0) return (x * stx(x, n - 1));
    if (n < 0) return (stx(x, n + 1) / x);
}

double next(double x, int n) //Функция вычисления очередного члена ряда
{
    return 1 / ((2 * n + 1) * stx(x, 2 * n + 1));
}
typedef double (*func) (double, int);

double S1(int n, double x, double e) //Вычисление суммы с помощью while и рекуррентной формулы
{
    double a = 1 / x, s = 0;
    while (fabs(a) > e)
    {
        s += a; a *= (2 * n + 1) / (x * x * (2 * n + 3));
        n++;
    }
    return (s + a);
}

double S2(int n, double x, double e) //Вычисление суммы с помощью do-while и рекуррентной формулы
{
    double a = 1 / x, s = 0;
    do
    {
        s += a;
        a *= (2 * n + 1) / (x * x * (2 * n + 3));
        n++;;
    } while (fabs(a) > e);
    return (s + a);
}

double S3(int n, double x, double e, func fn) //Вычисление суммы с помощью while и параметра – функции
{
    double f = fn(x, n), s = 0;
    while (fabs(f) > e)
    {
        s += f;
        n++;
        f = fn(x, n);
    }
    return ((s + f));
}

double S4(int n, double x, double e, func fn) //Вычисление суммы с помощью do-while и параметра – функции
{
    double f = fn(x, n), s = 0;
    do
    {
        s += f;
        n++;
        f = fn(x, n);
    } while (fabs(f) > e);
    return ((s + f));
}

double S5(int n, double x, double e, func fn) //С помощью рекурсивного суммирования и параметра – функции
{
    double f = fn(x, n);
    if (fabs(f) < e)
        return f;

    else return ((f + S5(n + 1, x, e, fn)));
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    double e = 1.e-5;
    fout.open("1.res");
    if (!fout)
    {
        cout << "Ошибка открытия файла результатов";
        exit(0);
    }

    fout << "\t\t\tResults for e = " << e << '\n'
        << "|-----|--------|--------|--------|--------|--------|--------|" << '\n'
        << "|  x  |  arcth |   S1   |    S2  |    S3  |    S4  |    S   |" << '\n'
        << "|-----|--------|--------|--------|--------|--------|--------|";
    //-Вывод значений
    for (double x = 1.5; x < 10; x += 0.2)
    {
        fout << endl << '|' << setw(4) << x << setw(2) << '|' << setw(10) << (0.5 * log((x + 1) / (x - 1))) << '|'
            << setw(10) << S1(0, x, e) << '|'
            << setw(10) << S2(0, x, e) << '|'
            << setw(10) << S3(0, x, e, next) << '|'
            << setw(10) << S4(0, x, e, next) << '|'
            << setw(10) << S5(0, x, e, next) << '|';
    }
    fout << '\n' << "|-----|--------|--------|--------|--------|--------|------|";
    fout.close();
}

