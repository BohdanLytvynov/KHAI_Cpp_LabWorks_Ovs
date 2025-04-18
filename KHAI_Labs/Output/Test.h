#ifndef TEST_H
#define TEST_H
struct Example
{
	Example();

	Example(long int* field1, double* field2, double field3);

	~Example();

	long int*  get_field1();
	double*  get_field2();
	double  get_field3();

	void set_field1(long int* field1);
	void set_field2(double* field2);
	void set_field3(double field3);

private:
	long int* m_field1;
	double* m_field2;
	double m_field3;
};
#endif