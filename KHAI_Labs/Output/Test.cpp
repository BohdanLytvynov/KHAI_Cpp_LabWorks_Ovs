#include "Test.h"

Example::Example()
{
	this->m_k = nullptr;
	this->m_m = nullptr;
	this->m_field1 = nullptr;
	this->m_field2 = nullptr;

}

Example::Example(int* k, size_t k_count, int* m, size_t m_count, int l, int sum, long int* field1, size_t field1_count, double* field2, size_t field2_count, double field3)
{
	this->m_k_count = k_count;
	InitArray(this->m_k, this->m_k_count);
	Copy(k, this->m_k_count, this->m_k, this->m_k_count);

	this->m_m_count = m_count;
	InitArray(this->m_m, this->m_m_count);
	Copy(m, this->m_m_count, this->m_m, this->m_m_count);

	this->m_l = l;
	this->m_sum = sum;
	this->m_field1_count = field1_count;
	InitArray(this->m_field1, this->m_field1_count);
	Copy(field1, this->m_field1_count, this->m_field1, this->m_field1_count);

	this->m_field2_count = field2_count;
	InitArray(this->m_field2, this->m_field2_count);
	Copy(field2, this->m_field2_count, this->m_field2, this->m_field2_count);

	this->m_field3 = field3;
}

Example::~Example()
{
	delete[] m_k;
	delete[] m_m;
	delete[] m_field1;
	delete[] m_field2;

}
int* Example::get_k()
{
	return this->m_k;
}

int* Example::get_m()
{
	return this->m_m;
}

int Example::get_l()
{
	return this->m_l;
}

int Example::get_sum()
{
	return this->m_sum;
}

long int* Example::get_field1()
{
	return this->m_field1;
}

double* Example::get_field2()
{
	return this->m_field2;
}

double Example::get_field3()
{
	return this->m_field3;
}

void Example::set_k(int* k, size_t k_count)
{
	if(this->m_k != nullptr) delete[] this->m_k;

	this->m_k_count = k_count;
	InitArray(this->m_k, k_count);
	Copy(k, k_count, this->m_k, k_count);
}

void Example::set_m(int* m, size_t m_count)
{
	if(this->m_m != nullptr) delete[] this->m_m;

	this->m_m_count = m_count;
	InitArray(this->m_m, m_count);
	Copy(m, m_count, this->m_m, m_count);
}

void Example::set_l(int l)
{
	this->m_l = l;
}

void Example::set_sum(int sum)
{
	this->m_sum = sum;
}

void Example::set_field1(long int* field1, size_t field1_count)
{
	if(this->m_field1 != nullptr) delete[] this->m_field1;

	this->m_field1_count = field1_count;
	InitArray(this->m_field1, field1_count);
	Copy(field1, field1_count, this->m_field1, field1_count);
}

void Example::set_field2(double* field2, size_t field2_count)
{
	if(this->m_field2 != nullptr) delete[] this->m_field2;

	this->m_field2_count = field2_count;
	InitArray(this->m_field2, field2_count);
	Copy(field2, field2_count, this->m_field2, field2_count);
}

void Example::set_field3(double field3)
{
	this->m_field3 = field3;
}

size_t Example::get_k_count()
{
	 return this->m_k_count;
}
size_t Example::get_m_count()
{
	 return this->m_m_count;
}
size_t Example::get_field1_count()
{
	 return this->m_l_count;
}
size_t Example::get_field2_count()
{
	 return this->m_sum_count;
}
#include "Test.h"

Example::Example()
{
	this->m_k = nullptr;
	this->m_m = nullptr;
	this->m_field1 = nullptr;
	this->m_field2 = nullptr;

}

Example::Example(int* k, size_t k_count, int* m, size_t m_count, int l, int sum, long int* field1, size_t field1_count, double* field2, size_t field2_count, double field3)
{
	this->m_k_count = k_count;
	InitArray(this->m_k, this->m_k_count);
	Copy(k, this->m_k_count, this->m_k, this->m_k_count);

	this->m_m_count = m_count;
	InitArray(this->m_m, this->m_m_count);
	Copy(m, this->m_m_count, this->m_m, this->m_m_count);

	this->m_l = l;
	this->m_sum = sum;
	this->m_field1_count = field1_count;
	InitArray(this->m_field1, this->m_field1_count);
	Copy(field1, this->m_field1_count, this->m_field1, this->m_field1_count);

	this->m_field2_count = field2_count;
	InitArray(this->m_field2, this->m_field2_count);
	Copy(field2, this->m_field2_count, this->m_field2, this->m_field2_count);

	this->m_field3 = field3;
}

Example::~Example()
{
	delete[] m_k;
	delete[] m_m;
	delete[] m_field1;
	delete[] m_field2;

}
int* Example::get_k()
{
	return this->m_k;
}

int* Example::get_m()
{
	return this->m_m;
}

int Example::get_l()
{
	return this->m_l;
}

int Example::get_sum()
{
	return this->m_sum;
}

long int* Example::get_field1()
{
	return this->m_field1;
}

double* Example::get_field2()
{
	return this->m_field2;
}

double Example::get_field3()
{
	return this->m_field3;
}

void Example::set_k(int* k, size_t k_count)
{
	if(this->m_k != nullptr) delete[] this->m_k;

	this->m_k_count = k_count;
	InitArray(this->m_k, k_count);
	Copy(k, k_count, this->m_k, k_count);
}

void Example::set_m(int* m, size_t m_count)
{
	if(this->m_m != nullptr) delete[] this->m_m;

	this->m_m_count = m_count;
	InitArray(this->m_m, m_count);
	Copy(m, m_count, this->m_m, m_count);
}

void Example::set_l(int l)
{
	this->m_l = l;
}

void Example::set_sum(int sum)
{
	this->m_sum = sum;
}

void Example::set_field1(long int* field1, size_t field1_count)
{
	if(this->m_field1 != nullptr) delete[] this->m_field1;

	this->m_field1_count = field1_count;
	InitArray(this->m_field1, field1_count);
	Copy(field1, field1_count, this->m_field1, field1_count);
}

void Example::set_field2(double* field2, size_t field2_count)
{
	if(this->m_field2 != nullptr) delete[] this->m_field2;

	this->m_field2_count = field2_count;
	InitArray(this->m_field2, field2_count);
	Copy(field2, field2_count, this->m_field2, field2_count);
}

void Example::set_field3(double field3)
{
	this->m_field3 = field3;
}

size_t Example::get_k_count()
{
	 return this->m_k_count;
}
size_t Example::get_m_count()
{
	 return this->m_m_count;
}
size_t Example::get_field1_count()
{
	 return this->m_l_count;
}
size_t Example::get_field2_count()
{
	 return this->m_sum_count;
}
