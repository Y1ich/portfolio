#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

//структура для хранения данных из файла
struct Data {
    double value;
};

//функция для сравнения элементов по убыванию
bool cmp(Data a, Data b) {
    return a.value > b.value;
}

int main() {
    setlocale(LC_ALL, "RUS");
    stack<Data> st; //создание стека
    queue<Data> q; //создание очереди
    vector<Data> v; //создание вектора для хранения элементов, удовлетворяющих условию

    //чтение данных из файла в стек
    ifstream fin("stack.txt");
    double num;
    while (fin >> num) {
        Data d = { num };
        st.push(d);
    }
    fin.close(); //закрытие файла

    //сортировка стека по убыванию
    vector<Data> temp;
    while (!st.empty()) {
        temp.push_back(st.top());
        st.pop();
    }
    sort(temp.begin(), temp.end(), [](Data a, Data b) {return a.value < b.value; });
    for (auto it : temp) {
        st.push(it);
    }

    //просмотр стека
    cout << "Stack: ";
    stack<Data> st_copy = st; //добавлено копирование стека
    while (!st_copy.empty()) {
        cout << st_copy.top().value << " ";
        st_copy.pop();
    }
    cout << endl;

    //чтение данных из файла в очередь
    fin.open("deque.txt");
    while (fin >> num) {
        Data d = { num };
        q.push(d);
    }
    fin.close(); //закрытие файла

    //поиск элемента, удовлетворяющего условию
    double condition = 0;
    queue<Data> tempq;
    while (!q.empty()) {
        if (q.front().value == condition) {
            v.push_back(q.front());
        }
        else {
            tempq.push(q.front());
        }
        q.pop();
    }
    q = tempq; //замена исходной очереди временной очередью

    //перемещение элементов, удовлетворяющих условию, в другую очередь
    queue<Data> q2;
    while (!q.empty()) {
        if (q.front().value > condition) {
            q2.push(q.front());
        }
        q.pop();
    }

    //просмотр второй очереди
    cout << "Queue: ";
    queue<Data> q2_copy = q2; //добавлено копирование очереди q2
    while (!q2_copy.empty()) {
        cout << q2_copy.front().value << " ";
        q2_copy.pop();
    }
    cout << endl;

    //сортировка стека по возрастанию
    vector<Data> temp2;
    while (!st.empty()) {
        temp2.push_back(st.top());
        st.pop();
    }
    sort(temp2.begin(), temp2.end(), [](Data a, Data b) {return a.value > b.value; }); //изменена функция сортировки
    for (auto it : temp2) {
        st.push(it);
    }

    //вывод отсортированного стека
    cout << "Sorted stack: ";
    stack<Data> st_copy2 = st; //добавлено копирование стека st
    while (!st_copy2.empty()) {
        cout << st_copy2.top().value << " ";
        st_copy2.pop();
    }
    cout << endl;

    //сортировка очереди по возрастанию
    temp.clear();
    while (!q2.empty()) {
        temp.push_back(q2.front());
        q2.pop();
    }
    sort(temp.begin(), temp.end(), [](Data a, Data b) {return a.value < b.value; });
    for (auto it : temp) {
        q2.push(it);
    }

    //вывод отсортированной очереди
    cout << "Sorted queue: ";
    queue<Data> q2_copy1 = q2; //добавлено копирование очереди q2
    while (!q2_copy1.empty()) {
        cout << q2_copy1.front().value << " ";
        q2_copy1.pop();
    }
    cout << endl;

    //объединение очередей
    queue<Data> q3 = q; //копирование первой очереди в третью
    while (!q2.empty()) {
        q3.push(q2.front());
        q2.pop();
    }

    //сортировка объединенного стека и очереди по возрастанию
    temp.clear();
    while (!q3.empty()) {
        temp.push_back(q3.front());
        q3.pop();
    }
    sort(temp.begin(), temp.end(), [](Data a, Data b) {return a.value < b.value; });
    for (auto it : temp) {
        q3.push(it);
    }

    // объединение стека и очереди в один вектор
    vector<Data> sv;
    while (!st.empty()) {
        sv.push_back(st.top());
        st.pop();
    }
    while (!q3.empty()) {
        sv.push_back(q3.front());
        q3.pop();
    }

    // сортировка вектора по возрастанию
    sort(sv.begin(), sv.end(), [](Data a, Data b) {return a.value < b.value; });

    // вывод отсортированного вектора
    cout << "Sorted stack and queue in one container: ";
    for (auto it : sv) {
        cout << it.value << " ";
    }
    cout << endl;


    //подсчет количества элементов, удовлетворяющих условию, в векторе
    int count = 0;
    for (auto it : sv) {
        if (it.value > condition) { //исправлено условие
            count++;
        }
    }
    cout << "Количество элементов, удовлетворяющих условию: " << count << endl;

    //проверка наличия элемента, удовлетворяющего заданному условию, в векторе
    bool found = any_of(v.begin(), v.end(), [](Data d) {return d.value > 5.0; });
    if (found) {
        cout << "Element satisfying the condition found" << endl;
    }
    else {
        cout << "Element satisfying the condition not found" << endl;
    }

    return 0;
}
