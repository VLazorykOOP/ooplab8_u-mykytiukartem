#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

template<typename T>
class Matrix {
private:
    int rows, cols;
    T** data;

    void allocate() {
        data = new T*[rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols]{};
    }

    void deallocate() {
        if (data) {
            for (int i = 0; i < rows; ++i)
                delete[] data[i];
            delete[] data;
        }
    }

public:
    // Конструктор за замовчуванням
    Matrix() : rows(0), cols(0), data(nullptr) {}

    // Конструктор з параметрами
    Matrix(int r, int c) : rows(r), cols(c) {
        allocate();
    }

    // Конструктор копіювання
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        allocate();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
    }

    // Деструктор
    ~Matrix() {
        deallocate();
    }

    // Оператор присвоєння =
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            deallocate();
            rows = other.rows;
            cols = other.cols;
            allocate();
            for (int i = 0; i < rows; ++i)
                for (int j = 0; j < cols; ++j)
                    data[i][j] = other.data[i][j];
        }
        return *this;
    }

    // Оператор доступу до рядка []
    T* operator[](int index) {
        return data[index];
    }

    // Оператор додавання +
    Matrix operator+(const Matrix& other) const {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    // Оператор +=
    Matrix& operator+=(const Matrix& other) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] += other.data[i][j];
        return *this;
    }

    // Введення з клавіатури
    void inputFromConsole() {
        std::cout << "Введіть елементи матриці (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                std::cin >> data[i][j];
    }

    // Зчитування з файлу
    bool inputFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin) return false;

        fin >> rows >> cols;
        allocate();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                fin >> data[i][j];

        fin.close();
        return true;
    }

    // Генерація випадкових значень
    void randomFill(int min = 0, int max = 100) {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = static_cast<T>(min + rand() % (max - min + 1));
    }

    // Виведення
    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                std::cout << data[i][j] << " ";
            std::cout << "\n";
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

// === Головна функція ===
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    int rows = 2, cols = 3;

    // Матриці типу int
    Matrix<int> A(rows, cols), B(rows, cols);
    A.randomFill(0, 9);
    B.randomFill(0, 9);

    std::cout << "Матриця A:\n"; A.print();
    std::cout << "\nМатриця B:\n"; B.print();

    Matrix<int> C = A + B;
    std::cout << "\nA + B:\n"; C.print();

    A += B;
    std::cout << "\nA після A += B:\n"; A.print();

    // Матриця float з клавіатури
    Matrix<float> F(2, 2);
    F.inputFromConsole();
    std::cout << "\nМатриця F:\n"; F.print();

    // Зчитування з файлу
    Matrix<double> D;
    if (D.inputFromFile("matrix.txt")) {
        std::cout << "\nМатриця з файлу:\n"; D.print();
    } else {
        std::cerr << "\nНе вдалося відкрити файл matrix.txt\n";
    }

    return 0;
}
