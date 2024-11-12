#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <algorithm>
#include <windows.h>

using namespace std;

// Структура для зберігання даних про товар
struct Price {
    string product_name;
    string store_name;
    double price;
};

// Функції для роботи з масивом структур
void Create(Price* products, const int N);
void Print(const Price* products, const int N);
void Sort(Price* products, const int N);
void Search(const Price* products, const int N, const string& store_name);
void SaveToFile(const Price* products, const int N, const string& filename);
void LoadFromFile(Price*& products, int& N, const string& filename);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "Введіть кількість товарів: ";
    cin >> N;

    Price* products = new Price[N];
    int MenuItem;
    string filename;

    while (true) {
        cout << endl << endl;
        cout << "Оберіть дію:" << endl;
        cout << "1 - Ввести інформацію про товари" << endl;
        cout << "2 - Вивести інформацію про товари" << endl;
        cout << "3 - Впорядкувати товари за алфавітним порядком назв" << endl;
        cout << "4 - Пошук товарів за назвою магазину" << endl;
        cout << "5 - Записати товари у файл" << endl;
        cout << "6 - Зчитати товари з файлу" << endl;
        cout << "0 - Завершити роботу програми" << endl;
        cout << "Введіть: ";
        cin >> MenuItem;
        cout << endl;

        switch (MenuItem) {
        case 1:
            Create(products, N);
            break;
        case 2:
            Print(products, N);
            break;
        case 3:
            Sort(products, N);
            Print(products, N);
            break;
        case 4: {
            string store;
            cout << "Введіть назву магазину для пошуку: ";
            cin.ignore();
            getline(cin, store);
            Search(products, N, store);
            break;
        }
        case 5:
            cout << "Введіть ім'я файлу для запису: ";
            cin >> filename;
            SaveToFile(products, N, filename);
            break;
        case 6:
            cout << "Введіть ім'я файлу для зчитування: ";
            cin >> filename;
            LoadFromFile(products, N, filename);
            break;
        case 0:
            delete[] products;
            return 0;
        default:
            cout << "Невірний вибір, спробуйте ще раз." << endl;
        }
    }
}

void Create(Price* products, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Товар №" << i + 1 << endl;
        cin.ignore();
        cout << "Назва товару: ";
        getline(cin, products[i].product_name);
        cout << "Назва магазину: ";
        getline(cin, products[i].store_name);
        cout << "Вартість товару: ";
        cin >> products[i].price;
        cout << endl;
    }
}

void Print(const Price* products, const int N) {
    cout << "=================================================================" << endl;
    cout << "|  №  |   Назва товару   |   Назва магазину |  Вартість товару  |" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "|" << setw(4) << right << i + 1 << " ";
        cout << "|" << setw(18) << left << products[i].product_name;
        cout << "|" << setw(18) << left << products[i].store_name;
        cout << "|" << setw(18) << right << products[i].price << " |" << endl;
    }
    cout << "=================================================================" << endl << endl;
}

// Компаратор для сортування за алфавітним порядком назв товарів (незалежно від регістру)
bool CompareIgnoreCase(const Price& a, const Price& b) {
    string lower_a = a.product_name;
    string lower_b = b.product_name;
    transform(lower_a.begin(), lower_a.end(), lower_a.begin(), ::tolower);
    transform(lower_b.begin(), lower_b.end(), lower_b.begin(), ::tolower);
    return lower_a < lower_b;
}

void Sort(Price* products, const int N) {
    sort(products, products + N, CompareIgnoreCase);
}

void Search(const Price* products, const int N, const string& store_name) {
    bool found = false;
    for (int i = 0; i < N; i++) {
        if (products[i].store_name == store_name) {
            if (!found) {
                cout << "=================================================================" << endl;
                cout << "|  №  |   Назва товару   |   Назва магазину |  Вартість товару  |" << endl;
                cout << "-----------------------------------------------------------------" << endl;
                found = true;
            }
            cout << "|" << setw(4) << right << i + 1 << " ";
            cout << "|" << setw(18) << left << products[i].product_name;
            cout << "|" << setw(18) << left << products[i].store_name;
            cout << "|" << setw(18) << right << products[i].price << " |" << endl;
        }
    }
    if (!found) {
        cout << "Магазин з такою назвою не знайдено." << endl;
    }
    cout << "=================================================================" << endl << endl;
}

void SaveToFile(const Price* products, const int N, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Помилка відкриття файлу для запису." << endl;
        return;
    }
    file << N << endl;
    for (int i = 0; i < N; i++) {
        file << products[i].product_name << endl;
        file << products[i].store_name << endl;
        file << products[i].price << endl;
    }
    file.close();
    cout << "Дані успішно записані у файл." << endl;
}

void LoadFromFile(Price*& products, int& N, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Помилка відкриття файлу для читання." << endl;
        return;
    }
    file >> N;
    file.ignore();
    delete[] products;
    products = new Price[N];
    for (int i = 0; i < N; i++) {
        getline(file, products[i].product_name);
        getline(file, products[i].store_name);
        file >> products[i].price;
        file.ignore();
    }
    file.close();
    cout << "Дані успішно завантажені з файлу." << endl;
}
