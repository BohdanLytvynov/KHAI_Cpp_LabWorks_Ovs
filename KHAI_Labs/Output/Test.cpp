#include "Test.h"

Example::Example()
{
}

Example::Example(long int* field1, double* field2, double field3)
{
	this->m_field1 = field1;
	this->m_field2 = field2;
	this->m_field3 = field3;

}

Example::~Example()
{
	delete[] m_field1;
	delete m_field2;

}
long int*  Example::field1()
{return this->m_field1;

}

double*  Example::field2()
{return this->m_field2;

}

double  Example::field3()
{return this->m_field3;

}
