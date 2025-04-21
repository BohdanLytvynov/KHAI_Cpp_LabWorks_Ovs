#include <iostream>
#include "Testing/Test.h"
#include <crtdbg.h>
#include <string>

template<class T>
void Print(const T value)
{
	std::cout << value << std::endl;
}

template<class T>
void PrintArray(const T* value, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		std::cout << value[i] << ", ";
	}
	std::cout << std::endl;
}

template<class T>
void InitArray(T* array, size_t start, size_t end, T value)
{
	for (size_t i = start; i < end; i++)
	{
		array[i] = value;
	}
}

int main()
{
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(flag);
	
	std::cout << "Initializing!\n";

	size_t k_count = 10;
	int* k = new int[k_count];
	InitArray(k, 0, k_count, 10);

	size_t m_count = 9;
	int* m = new int[m_count];
	InitArray(m, 0, m_count, 9);

	int l = 8;

	int sum = 7;

	size_t field1_count = 6;
	long int* field1 = new long int[field1_count];
	InitArray<long int>(field1, 0, field1_count, 6);

	size_t field2_count = 5;
	double* field2 = new double[field2_count];
	InitArray<double>(field2, 0, field2_count, 5);

	double field3 = 4;

	Example e(k, k_count, m, m_count, l, sum, field1, field1_count, field2, field2_count, field3);

	int test[5] = { 1,2,3,4,5 };

	e.set_k(test, sizeof(test)/sizeof(int));

	PrintArray(e.get_k(), e.get_k_count());

	//std::cout << "Test Getters!\n";
	////Test Getters
	//PrintArray(e.get_k(), e.get_k_count());
	//PrintArray(e.get_m(), e.get_m_count());
	//Print(e.get_l());
	//PrintArray(e.get_k(), e.get_k_count());
	//Print(e.get_sum());
	//PrintArray(e.get_field1(), e.get_field1_count());
	//PrintArray(e.get_field2(), e.get_field2_count());
	//Print(e.get_field3());

	//delete[] k;

	//delete[] m;

	//delete[] field1;

	//delete[] field2;

	//k_count = 1;
	//k = new int[k_count];
	//InitArray(k, 0, k_count, 1);

	//m_count = 2;
	//m = new int[m_count];
	//InitArray(m, 0, m_count, 2);

	//l = 3;

	//sum = 4;

	//field1_count = 5;
	//field1 = new long int[field1_count];
	//InitArray<long int>(field1, 0, field1_count, 5);

	//field2_count = 6;
	//field2 = new double[field2_count];
	//InitArray<double>(field2, 0, field2_count, 6);

	//field3 = 7;
	//std::cout << "Test Setters!\n";
	////Test Setters

	//e.set_k(k, k_count);
	//e.set_m(m, m_count);
	//e.set_l(l);
	//e.set_sum(sum);
	//e.set_field1(field1, field1_count);
	//e.set_field2(field2, field2_count);
	//e.set_field3(field3);

	////Test Setters
	//PrintArray(e.get_k(), e.get_k_count());
	//PrintArray(e.get_m(), e.get_m_count());
	//Print(e.get_l());
	//PrintArray(e.get_k(), e.get_k_count());
	//Print(e.get_sum());
	//PrintArray(e.get_field1(), e.get_field1_count());
	//PrintArray(e.get_field2(), e.get_field2_count());
	//Print(e.get_field3());

	delete[] k;

	delete[] m;

	delete[] field1;

	delete[] field2;

	return 0;

	std::getchar();
}




