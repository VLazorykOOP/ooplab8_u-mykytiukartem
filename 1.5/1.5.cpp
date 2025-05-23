#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Функція-шаблон для знаходження мінімального елемента та кількості його повторень
template<typename T>
void findMinAndCount(T arr[], int size, T& minVal, int& count) {
    minVal = arr[0];
    count = 1;
    for (int i = 1; i < size; ++i) {
        if (arr[i] < minVal) {
            minVal = arr[i];
            count = 1;
        } else if (arr[i] == minVal) {
            count++;
        }
    }
}

// Спеціалізація шаблону для char*
template<>
void findMinAndCount<char*>(char* arr[], int size, char*& minVal, int& count) {
    minVal = arr[0];
    count = 1;
    for (int i = 1; i < size; ++i) {
        if (strcmp(arr[i], minVal) < 0) {
            minVal = arr[i];
            count = 1;
        } else if (strcmp(arr[i], minVal) == 0) {
            count++;
        }
    }
}

// Допоміжна функція для заповнення масиву випадковими числами
void generateRandomArray(int arr[], int size, int minVal = 0, int maxVal = 100) {
    for (int i = 0; i < size; ++i) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

int main() {
    srand(time(0)); // ініціалізація генератора випадкових чисел
    const int SIZE = 10;
    
    // 1. Введення з клавіатури
    cout << "=== Введення з клавіатури ===\n";
    int arr1[SIZE];
    cout << "Введіть " << SIZE << " цілих чисел:\n";
    for (int i = 0; i < SIZE; ++i)
        cin >> arr1[i];
    int min1, count1;
    findMinAndCount(arr1, SIZE, min1, count1);
    cout << "Мінімум: " << min1 << ", Кількість повторень: " << count1 << "\n\n";

    // 2. Зчитування з файлу
    cout << "=== Зчитування з файлу ===\n";
    ofstream fout("input.txt");
    for (int i = 0; i < SIZE; ++i)
        fout << (rand() % 50) << " ";
    fout.close();

    ifstream fin("input.txt");
    int arr2[SIZE];
    for (int i = 0; i < SIZE; ++i)
        fin >> arr2[i];
    fin.close();
    int min2, count2;
    findMinAndCount(arr2, SIZE, min2, count2);
    cout << "Мінімум з файлу: " << min2 << ", Кількість: " << count2 << "\n\n";

    // 3. Випадкові числа
    cout << "=== Випадкові значення ===\n";
    int arr3[SIZE];
    generateRandomArray(arr3, SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr3[i] << " ";
    cout << "\n";
    int min3, count3;
    findMinAndCount(arr3, SIZE, min3, count3);
    cout << "Мінімум: " << min3 << ", Кількість: " << count3 << "\n\n";

    // 4. Приклад з char*
    cout << "=== Масив рядків (char*) ===\n";
    char* strArr[5] = { (char*)"apple", (char*)"banana", (char*)"apple", (char*)"pear", (char*)"apple" };
    char* minStr;
    int strCount;
    findMinAndCount(strArr, 5, minStr, strCount);
    cout << "Мінімальний рядок: " << minStr << ", Кількість: " << strCount << "\n";

    return 0;
}
