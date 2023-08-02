#include <iostream>
#include <vector>

template<typename T>
class Queue {
private:
    std::vector<T> data;
public:
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
    q1 + 1;
    q1 + 2;
    q1 + 3;
    q1.print(); // Output: 1 2 3
    --q1;
    q1.print(); // Output: 2 3
    std::cout << std::boolalpha << q1() << std::endl; // Output: false

    Queue<std::string> q2;
    q2 + "hello";
    q2 + "world";
    q2.print(); // Output: hello world
    --q2;
    q2.print(); // Output: world
    std::cout << std::boolalpha << q2() << std::endl; // Output: false

    return 0;
}
