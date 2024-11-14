#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct Product {
    std::string name;
    std::string store;
    double price;
    int quantity;
    std::string unit;
};

namespace StoreManagementTests
{
    TEST_CLASS(ProductManagementTests)
    {
    public:
        TEST_METHOD(TestSortByName)
        {
            std::vector<Product> products = {
                {"Яблука", "АТБ", 25.50, 100, "кг"},
                {"Банани", "Сільпо", 45.00, 50, "кг"},
                {"Груші", "АТБ", 35.75, 75, "кг"}
            };

            sort(products.begin(), products.end(),
                [](const Product& a, const Product& b) { return a.name < b.name; });

            Assert::AreEqual(std::string("Банани"), products[0].name);
            Assert::AreEqual(std::string("Груші"), products[1].name);
            Assert::AreEqual(std::string("Яблука"), products[2].name);
        }

        TEST_METHOD(TestSortByStore)
        {
            std::vector<Product> products = {
                {"Яблука", "АТБ", 25.50, 100, "кг"},
                {"Банани", "Сільпо", 45.00, 50, "кг"},
                {"Груші", "АТБ", 35.75, 75, "кг"}
            };

            sort(products.begin(), products.end(),
                [](const Product& a, const Product& b) { return a.store < b.store; });

            Assert::AreEqual(std::string("АТБ"), products[0].store);
            Assert::AreEqual(std::string("АТБ"), products[1].store);
            Assert::AreEqual(std::string("Сільпо"), products[2].store);
        }

        TEST_METHOD(TestProductManipulation)
        {
            std::vector<Product> products;

            Product newProduct = { "Тест", "Магазин", 10.0, 1, "шт" };
            products.push_back(newProduct);
            Assert::AreEqual(size_t(1), products.size());

            products.erase(products.begin());
            Assert::AreEqual(size_t(0), products.size());
        }
    };
}