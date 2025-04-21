#ifndef TEST_H
#define TEST_H
struct Example
{
	Example();

	Example(int* k, size_t k_count, int* m, size_t m_count, int l, int sum, long int* field1, size_t field1_count, double* field2, size_t field2_count, double field3);

	~Example();

//Getters for Counts
	size_t get_k_count();
	size_t get_m_count();
	size_t get_field1_count();
	size_t get_field2_count();

//Getters for Fields
	int* get_k();
	int* get_m();
	int get_l();
	int get_sum();
	long int* get_field1();
	double* get_field2();
	double get_field3();

//Setters
	void set_k(int* k, size_t k_count);
	void set_m(int* m, size_t m_count);
	void set_l(int l);
	void set_sum(int sum);
	void set_field1(long int* field1, size_t field1_count);
	void set_field2(double* field2, size_t field2_count);
	void set_field3(double field3);

private:
	int* m_k;
	int* m_m;
	int m_l;
	int m_sum;
	long int* m_field1;
	double* m_field2;
	double m_field3;

	size_t m_k_count;
	size_t m_m_count;
	size_t m_field1_count;
	size_t m_field2_count;

	template<class T>
	void InitArray(T*& array, size_t count)
	{
		array = new T[count];
	}

	template<class T>
	void Copy(const T* src, size_t src_count,  T*& dest, size_t dest_count)
	{
		if (src_count != dest_count)
			return;
		for (size_t i = 0; i < src_count; i++)
		{
			dest[i] = src[i];
		}
	}
};
#endif