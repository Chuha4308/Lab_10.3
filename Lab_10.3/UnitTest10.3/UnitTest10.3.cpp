#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.3/Lab_10.3.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(SortTest)
        {
            const int N = 3;
            Price products[N] = {
              {"Orange", "Market A", 2.5},
              {"apple", "Market B", 1.0},
              {"Banana", "Market C", 1.5}
            };

            // ������ ������� ����������
            Sort(products, N);

            // �������� ����� ������ � ������� ����������
            string expected_product_names[N] = { "apple", "Banana", "Orange" };

            // �������� ���������� ����������
            for (int i = 0; i < N; i++)
            {
                Assert::AreEqual(expected_product_names[i], products[i].product_name, L"����� ������ �� ������� � ���������� ���� ����������", LINE_INFO());
            }
        }
    };
}
