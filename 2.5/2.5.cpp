#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Сортування шаблон
template <typename T>
void sortArray(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Спеціалізація для char*
template <>
void sortArray<char*>(char* arr[], int size) {
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (strcmp(arr[j], arr[j + 1]) > 0)
                swap(arr[j], arr[j + 1]);
}

// Бінарний пошук шаблон
template <typename T>
int binarySearch(T arr[], int size, T key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Спеціалізація для char*
template <>
int binarySearch<char*>(char* arr[], int size, char* key) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(arr[mid], key);
        if (cmp == 0) return mid;
        else if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// Введення з клавіатури
template <typename T>
void inputFromKeyboard(T arr[], int size) {
    cout << "Введіть " << size << " елементів:\n";
    for (int i = 0; i < size; ++i)
        cin >> arr[i];
}

// Зчитування з файлу
template <typename T>
void inputFromFile(T arr[], int size, const char* filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Не вдалося відкрити файл!\n";
        return;
    }
    for (int i = 0; i < size && file; ++i)
        file >> arr[i];
    file.close();
}

//  Генерація випадкових чисел
template <typename T>
void randomInput(T arr[], int size, T minVal, T maxVal) {
    for (int i = 0; i < size; ++i)
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
}

int main() {
    srand(time(0));
    const int SIZE = 5;

    // Приклад з int
    int intArr[SIZE];
    cout << "\n Ввід int з клавіатури:\n";
    inputFromKeyboard(intArr, SIZE);
    sortArray(intArr, SIZE);
    int intKey;
    cout << " Введіть ключ для пошуку: ";
    cin >> intKey;
    int idxInt = binarySearch(intArr, SIZE, intKey);
    if (idxInt != -1)
        cout << "Знайдено на позиції: " << idxInt << "\n";
    else
        cout << "Ключ не знайдено.\n";

    // Приклад з char*
    cout << "\n Приклад з char*:\n";
    char s1[] = "apple", s2[] = "banana", s3[] = "grape", s4[] = "kiwi", s5[] = "orange";
    char* strArr[SIZE] = { s1, s2, s3, s4, s5 };
    sortArray(strArr, SIZE);

    char keyStr[20];
    cout << " Введіть слово для пошуку: ";
    cin >> keyStr;
    int idxStr = binarySearch(strArr, SIZE, keyStr);
    if (idxStr != -1)
        cout << "Слово знайдено на позиції: " << idxStr << "\n";
    else
        cout << "Слово не знайдено.\n";

    // Зчитування з файлу
    cout << "\n Зчитування int з файлу (input.txt):\n";
    int fileArr[SIZE];
    inputFromFile(fileArr, SIZE, "input.txt");
    sortArray(fileArr, SIZE);
    cout << " Введіть ключ для пошуку: ";
    cin >> intKey;
    idxInt = binarySearch(fileArr, SIZE, intKey);
    if (idxInt != -1)
        cout << "Знайдено на позиції: " << idxInt << "\n";
    else
        cout << "Ключ не знайдено.\n";

    // Випадкові числа
    cout << "\n Випадкові значення:\n";
    int rndArr[SIZE];
    randomInput(rndArr, SIZE, 1, 20);
    sortArray(rndArr, SIZE);
    cout << "Масив після сортування: ";
    for (int i = 0; i < SIZE; ++i)
        cout << rndArr[i] << " ";
    cout << "\n Введіть ключ для пошуку: ";
    cin >> intKey;
    idxInt = binarySearch(rndArr, SIZE, intKey);
    if (idxInt != -1)
        cout << "Знайдено на позиції: " << idxInt << "\n";
    else
        cout << "Ключ не знайдено.\n";

    return 0;
}
