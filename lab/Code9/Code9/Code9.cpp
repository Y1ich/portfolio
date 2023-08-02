#include <iostream>
using namespace std;

//===============================================================
// Абстрактный класс "кадры", является базовым для других классов
class Cadr
{
public:
	/* У любого места обязательно есть название.
	*
	* Поскольку у класса явно определен один конструктор, все конструкторы
	* по-умолчанию не будут автоматически определяться компилятором, то есть
	* будут отсутствовать. Однако, оператор копирования будет определён
	* компилятором и его следует явно запретить, скрыв в кадры private,
	* поскольку данный класс не предусматривает разумной возможности
	* копирования экземпляров.
	*/
	Cadr(const char* Cadr_name) //конструктор с параметром
	{
		name = Cadr_name;
		next = 0;
		add_to_list(); //создается  объект вызывается этот конструктор 
		//и сразу объект встраивается в список, в его конец
	   //за ним нет объектов, поэтому next =0
	}
	//возвращает имя любого места, наследуется всеми производными классами
	const char* get_name()
	{
		return name;
	}

	/* Отсутствие виртуального деструктора у базового класса
	* может привести к серьезным проблемам (утечке памяти) при
	* вызове операции delete к указателю Cadr*. Очистится только базовая часть, производная останется
	* Достаточно объявить хотя бы пустой виртуальный деструктор.
	*/
	virtual ~Cadr() {}

	/* Чистая виртуальная функция.
	*
	* В производных классах функция должна быть обязательно переопределена
	* так, чтобы в stdout было выведено значение pos - это номер элемента в списке,
	* затем информация о классе, затем перенос строки.
	*/
	virtual void who_are_you(int pos) = 0; //можно было назвать show

	/* Обход списка */
	static void print_list()
	{
		Cadr* now = list_begin;
		int pos = 0;
		while (now != 0)
		{
			pos++;
			now->who_are_you(pos);
			// перемещаемся к следующему элементу списка
			now = now->next;
		}
	}
	// Удаление всех элементов списка как из списка, так и из памяти
	static void cleanup_list()
	{
		Cadr* now = list_begin;
		while (now != 0)
		{
			Cadr* x = now;
			now = now->next;
			delete x;
		}
		list_begin = 0;
	}
	// Статический (общий) указатель на начало однонаправленного списка
	static Cadr* list_begin;

private:

	/* Функция добавления элемента в список. Повторный вызов для одного
	* и того же объекта приведет к ошибке, поэтому функция размещена в
	* области private.
	*/
	void add_to_list()
	{
		// Добавляем объект в список
		if (list_begin == 0)
		{ // Если в списке еще нет ни одного элемента.
			list_begin = this;
		}
		else
		{ // Если в списке есть элементы, то добавим новый в конец.
			// Ищем указатель на конец списка
			Cadr* last = list_begin;
			while (last->next != 0) last = last->next;
			// Добавляем новый элемент в конец
			last->next = this;
		}
	}

	const char* name; // Название места

	// Указатель на следующий элемент в общем списке для текущего объекта
	Cadr* next;

	/* Оператор копирования и присваивание для класса запрещёны путем по-мещения в кадры
	* private.
	*/
	Cadr& operator=(const Cadr&);

	Cadr(const Cadr&);


};
//====================================================================================

// Класс "администрация", является производным от "кадры"
class Admin : public Cadr {
public:
	Admin(const char* name) : Cadr(name) {}
	virtual void who_are_you(int pos) //замещение
	{
		cout << pos << ": this is a Admin " << get_name() << endl;
		//cout << "Any Inginer is also a Cadrochi', but not every Ca-drochi' is a Inginer" << endl;
	}
};

// Класс "рабочий", является производным от "кадры"
class Raboch : public Cadr
{
public:
	Raboch(const char* name) : Cadr(name) {}
	virtual void who_are_you(int pos) //замещение
	{
		cout << pos << ": this is a Raboch " << get_name() << endl;
	}
};


// Класс "инженер", является производным от "рабочий"
class Inginer : public Raboch
{
public:
	Inginer(const char* name) : Raboch(name) {}
	virtual void who_are_you(int pos) //замещение функции в производном классе
	{
		cout << pos << ": this is a Inginer " << get_name() << endl;
	}
};

Cadr* Cadr::list_begin = 0;// инициализация вершины списка

//==========================================================
int main()
{
	setlocale(LC_CTYPE, "Russian");

	//создаются динамические объекты и сразу встраиваются в список

	new Raboch("Повар");
	new Admin("Городская администрация");
	new Inginer("Инженер-конструктор");
	new Inginer("Инженер-технолог");
	new Admin("Местная администрация");
	new Raboch("Сварщик");
	Cadr::print_list();
	cout << "Очистка списка" << endl;
	cout << endl;
	Cadr::cleanup_list();
	new Raboch("Токарь");
	new Admin("Районная администрация");
	new Inginer("Инженер-электроник");
	new Inginer("Инженер-геодезист");
	new Admin("Региональная администрация");
	new Raboch("Автомеханик");
	new Inginer("Инженер-сметчик");
	new Inginer("Инженер-прочнист");
	Cadr::print_list();
	cout << "Очистка списка" << endl;
	Cadr::cleanup_list();
	system("pause");
	return 0;
}
