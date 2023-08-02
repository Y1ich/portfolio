#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

int main()
{
    // Часть 1
    string text, substring;
    cout << "Введите текст: ";
    getline(cin, text);
    cout << "Введите подстроку: ";
    cin >> substring;

    int count = 0;
    map<string, int> words;

    vector<int> positions;
    string::size_type pos = text.find(substring);
    while (pos != std::string::npos) {
        positions.push_back(pos);
        pos = text.find(substring, pos + 1);
    }

    std::sort(positions.begin(), positions.end());

    std::cout << "Подстрока встречается " << positions.size() << " раз(а) в тексте:" << std::endl;

    // Разбиваем текст на слова
    string word;
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
        {
            if (word.length() > 0)
            {
                // Проверяем, содержит ли слово подстроку
                if (word.find(substring) != string::npos)
                {
                    // Если да, добавляем его в словарь
                    words[word] = i - word.length();
                }
                word = "";
            }
        }
        else
        {
            word += text[i];
        }
    }

    // Проверяем последнее слово
    if (word.length() > 0)
    {
        if (word.find(substring) != string::npos)
        {
            words[word] = text.length() - word.length();
        }
    }

    // Часть 2
    words.clear();

    // Разбиваем текст на слова
    word = "";
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t')
        {
            if (word.length() > 0)
            {
                // Добавляем слово в словарь
                words[word]++;
                word = "";
            }
        }
        else
        {
            word += text[i];
        }
    }

    // Проверяем последнее слово
    if (word.length() > 0)
    {
        words[word]++;
    }

    // Сортируем слова по убыванию частоты использования
    vector<pair<string, int>> sorted_words(words.begin(), words.end());
    sort(sorted_words.begin(), sorted_words.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
        });

    // Выводим результат
    for (auto it = sorted_words.begin(); it != sorted_words.end(); it++)
    {
        cout << it->first << " - " << it->second << endl;
    }

    return 0;
}
