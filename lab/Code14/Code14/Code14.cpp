#include <iostream>
#include <vector>

template<typename T>
class Queue {
private:
    std::vector<T> data;
public:
    void push_back(const T& key) {
        data.push_back(key);
    }
    void pop_back() {
        if (!data.empty()) {
            data.pop_back();
        }
    }
    void push_front(const T& key) {
        data.insert(data.begin(), key);
    }
    void pop_front() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }
    void insert(int index, const T& key) {
        if (index >= 0 && index <= data.size()) {
            data.insert(data.begin() + index, key);
        }
    }
    void erase(int index) {
        if (index >= 0 && index < data.size()) {
            data.erase(data.begin() + index);
        }
    }
    T& operator[](int index) {
        return data[index];
    }
    const T& operator[](int index) const {
        return data[index];
    }
    void operator+(const T& item) {
        data.push_back(item);
    }
    void operator--() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }
    bool operator()() const {
        return data.empty();
    }
    void print() const {
        for (const auto& item : data) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Queue<int> q1;
    q1.push_back(1);
    q1.push_back(2);
    q1.push_back(3);
    q1.print(); // Output: 1 2 3
    q1.pop_back();
    q1.print(); // Output: 1 2
    q1.push_front(0);
    q1.print(); // Output: 0 1 2
    q1.pop_front();
    q1.print(); // Output: 1 2
    q1.insert(1, 4);
    q1.print(); // Output: 1 4 2
    q1.erase(2);
    q1.print(); // Output: 1 4
    std::cout << q1[1] << std::endl; // Output: 4

    Queue<std::string> q2;
    q2.push_back("hello");
    q2.push_back("world");
    q2.print(); // Output: hello world
    q2.pop_back();
    q2.print(); // Output: hello
    q2.push_front("hi");
    q2.print(); // Output: hi hello
    q2.pop_front();
    q2.print(); // Output: hello
    q2.insert(1, "there");
    q2.print(); // Output: hello there
    q2.erase(0);
    std::cout << q2[0] << std::endl; // Output: there
    return 0;
}
