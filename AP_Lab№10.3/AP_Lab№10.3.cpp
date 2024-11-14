#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

using namespace std;

// Структура для зберігання інформації про товар
struct Product {
    string name;
    string store;
    double price;
    int quantity;
    string unit;
};

// Функції для роботи з даними
void addProduct(vector<Product>& products);
void removeProduct(vector<Product>& products);
void editProduct(vector<Product>& products);
void sortByName(vector<Product>& products);
void sortByStore(vector<Product>& products);
void findProductByName(const vector<Product>& products);
void findProductsByStore(const vector<Product>& products);
void saveToFile(const vector<Product>& products);
void loadFromFile(vector<Product>& products);
void printProducts(const vector<Product>& products);
void printProduct(const Product& product);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Product> products;
    int choice;

    do {
        cout << "\nМеню програми:\n";
        cout << "1. Додати товар\n";
        cout << "2. Видалити товар\n";
        cout << "3. Редагувати товар\n";
        cout << "4. Сортувати за назвою\n";
        cout << "5. Сортувати за магазином\n";
        cout << "6. Знайти товар за назвою\n";
        cout << "7. Знайти товари за магазином\n";
        cout << "8. Зберегти у файл\n";
        cout << "9. Завантажити з файлу\n";
        cout << "10. Показати всі товари\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: addProduct(products); break;
        case 2: removeProduct(products); break;
        case 3: editProduct(products); break;
        case 4: sortByName(products); break;
        case 5: sortByStore(products); break;
        case 6: findProductByName(products); break;
        case 7: findProductsByStore(products); break;
        case 8: saveToFile(products); break;
        case 9: loadFromFile(products); break;
        case 10: printProducts(products); break;
        case 0: cout << "Дякуємо за використання програми!\n"; break;
        default: cout << "Невірний вибір! Спробуйте ще раз.\n";
        }
    } while (choice != 0);

    return 0;
}

void addProduct(vector<Product>& products) {
    Product p;
    cout << "Введіть назву товару: ";
    getline(cin, p.name);
    cout << "Введіть назву магазину: ";
    getline(cin, p.store);
    cout << "Введіть ціну товару: ";
    cin >> p.price;
    cout << "Введіть кількість: ";
    cin >> p.quantity;
    cin.ignore();
    cout << "Введіть одиницю виміру: ";
    getline(cin, p.unit);
    products.push_back(p);
}

void removeProduct(vector<Product>& products) {
    if (products.empty()) {
        cout << "Список товарів порожній!\n";
        return;
    }

    cout << "Введіть індекс товару для видалення (1-" << products.size() << "): ";
    int index;
    cin >> index;

    if (index > 0 && index <= static_cast<int>(products.size())) {
        products.erase(products.begin() + index - 1);
        cout << "Товар видалено.\n";
    }
    else {
        cout << "Невірний індекс!\n";
    }
}

void editProduct(vector<Product>& products) {
    if (products.empty()) {
        cout << "Список товарів порожній!\n";
        return;
    }

    cout << "Введіть індекс товару для редагування (1-" << products.size() << "): ";
    int index;
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= static_cast<int>(products.size())) {
        Product& p = products[index - 1];
        cout << "Введіть нову назву товару (або Enter для пропуску): ";
        string input;
        getline(cin, input);
        if (!input.empty()) p.name = input;

        cout << "Введіть нову назву магазину (або Enter для пропуску): ";
        getline(cin, input);
        if (!input.empty()) p.store = input;

        cout << "Введіть нову ціну (або 0 для пропуску): ";
        double price;
        cin >> price;
        if (price != 0) p.price = price;

        cout << "Введіть нову кількість (або 0 для пропуску): ";
        int quantity;
        cin >> quantity;
        if (quantity != 0) p.quantity = quantity;

        cin.ignore();
        cout << "Введіть нову одиницю виміру (або Enter для пропуску): ";
        getline(cin, input);
        if (!input.empty()) p.unit = input;

        cout << "Товар відредаговано.\n";
    }
    else {
        cout << "Невірний індекс!\n";
    }
}

void sortByName(vector<Product>& products) {
    sort(products.begin(), products.end(),
        [](const Product& a, const Product& b) { return a.name < b.name; });
    cout << "Список відсортовано за назвою.\n";
}

void sortByStore(vector<Product>& products) {
    sort(products.begin(), products.end(),
        [](const Product& a, const Product& b) { return a.store < b.store; });
    cout << "Список відсортовано за магазином.\n";
}

void findProductByName(const vector<Product>& products) {
    cout << "Введіть назву товару: ";
    string name;
    getline(cin, name);

    bool found = false;
    for (const auto& p : products) {
        if (p.name == name) {
            printProduct(p);
            found = true;
        }
    }

    if (!found) {
        cout << "Товар не знайдено.\n";
    }
}

void findProductsByStore(const vector<Product>& products) {
    cout << "Введіть назву магазину: ";
    string store;
    getline(cin, store);

    bool found = false;
    for (const auto& p : products) {
        if (p.store == store) {
            printProduct(p);
            found = true;
        }
    }

    if (!found) {
        cout << "Товари не знайдено.\n";
    }
}

void saveToFile(const vector<Product>& products) {
    string filename;
    cout << "Введіть ім'я файлу: ";
    getline(cin, filename);

    ofstream file(filename);
    if (!file) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    for (const auto& p : products) {
        file << p.name << endl
            << p.store << endl
            << p.price << endl
            << p.quantity << endl
            << p.unit << endl;
    }

    cout << "Дані збережено у файл.\n";
}

void loadFromFile(vector<Product>& products) {
    string filename;
    cout << "Введіть ім'я файлу: ";
    getline(cin, filename);

    ifstream file(filename);
    if (!file) {
        cout << "Помилка відкриття файлу!\n";
        return;
    }

    products.clear();
    Product p;
    while (getline(file, p.name)) {
        getline(file, p.store);
        file >> p.price;
        file >> p.quantity;
        file.ignore();
        getline(file, p.unit);
        products.push_back(p);
    }

    cout << "Дані завантажено з файлу.\n";
}

void printProduct(const Product& p) {
    cout << "Назва: " << p.name << endl
        << "Магазин: " << p.store << endl
        << "Ціна: " << fixed << setprecision(2) << p.price << " грн" << endl
        << "Кількість: " << p.quantity << " " << p.unit << endl
        << "------------------------" << endl;
}

void printProducts(const vector<Product>& products) {
    if (products.empty()) {
        cout << "Список товарів порожній!\n";
        return;
    }

    cout << "\nСписок товарів:\n";
    cout << "------------------------\n";
    for (size_t i = 0; i < products.size(); ++i) {
        cout << "Товар #" << (i + 1) << endl;
        printProduct(products[i]);
    }
}