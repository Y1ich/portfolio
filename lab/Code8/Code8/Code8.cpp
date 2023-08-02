#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string.h>


using namespace std;

class fridge
{
    char* name;
    char* country;
    float camera;

public:
    fridge()
    {
        name = new char[100];
        strcpy(name, "НЕТ ДАННЫХ");
        country = 0;
        camera = 0;
        cout << "Создан объект  " << this << "  конструктором с умалчиваемыми параметрами" << endl;
    };

    fridge(const char* name2, char* country, float camera)
    {
        name = new char[100];
        strcpy(name, name2);
        this->country = country;
        this->camera = camera;
        cout << "Создан объект  " << this << "  конструктором с параметрами" << endl;

    };
    fridge(const fridge& other)
    {
        name = new char[100];
        strcpy(name, other.name);
        this->country = other.country;
        this->camera = other.camera;
        cout << "Coздан объект  " << this << "  конструктором копирования " << endl;
    }
    ~fridge()
    {
        delete[] name;
        cout << "Вызван деструктор для объекта  " << this << endl;
    };

    void SetName(char* _name);
    void Setcountry(char* _country);
    void Setcamera(float _camera);
    void Show();
    int p();

};

void fridge::SetName(char* _name)
{
    name = _name;
};
void fridge::Setcountry(char* _country)
{
    country = _country;
};
void fridge::Setcamera(float _camera)
{
    camera = _camera;
};
void fridge::Show()
{
    cout << "Название: " << name << endl;
    cout << "Страна производитель: " << country << endl;
    cout << "Емкость камеры " << camera << endl << endl;
}
int fridge::p()
{
    return 145 - camera;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    cout << "ЛАБОРАТОРНАЯ РАБОТА № 8" << endl << "Классы и объекты. Создание и разрушение объектов пользовательского класса, статических и динамических" << endl << endl;

    char n1[20] = "Samsung";
    char n2[20] = "Корея";
    fridge PPP;
    PPP.SetName(n1);
    PPP.Setcountry(n2);
    PPP.Setcamera(184);
    PPP.Show();

    char nameA[20] = "Haier";
    char nameB[20] = "LG Electronics";
    char nameA2[20] = "США";
    char nameB2[20] = "Германия";
    fridge AAA(nameA, nameA2, 285);
    AAA.Show();
    AAA.SetName(nameB);
    AAA.Setcountry(nameB2);
    AAA.Setcamera(184);

    char nameE[20] = "Bosch";
    char nameE2[20] = "Россия";
    fridge EEE(AAA);
    EEE.Show();
    AAA.SetName(nameE);
    AAA.Setcountry(nameE2);
    AAA.Setcamera(128);
    fridge* forD = &AAA;
    cout << "Вызов объекта  " << &AAA << "  с помощью указателя" << endl;
    forD->Show();

    fridge F = EEE;
    F.Show();

    int(fridge:: * ptShow)();
    ptShow = &fridge::p;
    cout << (AAA.*ptShow)() << " не хватило баллов до хорошего холодильника использование указателя на объект и указателя на компоненту-функцию, которая возращает оценку за экзамен" << endl << endl;

    fridge* kekw = new fridge[1];
    kekw[0].SetName(n1);
    kekw[0].Setcountry(n2);
    kekw[0].Setcamera(285);
    kekw[0].Show();
    cout << &kekw << " - адрес динмического объекта и последующий вызов его деструктора " << endl;
    delete[]kekw;

}

