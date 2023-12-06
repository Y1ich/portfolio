#include "funktions.h"//файл с данными и функциями
#define _CRT_SECURE_NO_WARNINGS//для успешной работы консоли
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (true)//цикл для работы менюшки
    {
        system("cls");
        cout << "\n                    МЕНЮ : \n"
            << "\n         Создание файла------------------------- 1"
            << "\n         Запись в бинарный файл----------------- 2"
            << "\n         Чтение файла----------------------------3"
            << "\n         Сортировка файла----------------------- 4"
            << "\n         Удаление данных из файла--------------- 5"
            << "\n         Вывод диаграмм по заданным критериям--- 6"
            << "\n         Выход----------------------------- другое";

        cout << "\n\n Для выполнения операции введите нужную цифру\n";
        switch (_getch())//обработчки символа с клавиатуры, выполненный в виде switch
        {
       // case '1': makeData("data.txt"); cout << "Файл создан\n"; system("pause"); break;
        case '2': makeBin("brak.txt", "brakbin.txt", "razv.txt", "razvbin.txt"); cout << "Файл записан\n"; system("pause"); break;
        case '3': readBin("brakbin.txt", "razvbin.txt"); cout << "Файл прочитан\n"; system("pause"); break;
        //case '4': makeSort("bin.txt", "binnew.txt"); system("pause"); break;
      //  case '5': cleanBin("bin.txt", "search.txt"); cout << "Данные удалены\n"; system("pause"); break;
      //  case '6': cout << "Диаграммы представлены\n"; system("pause"); break;
        default: return 0;
        }
    }
}