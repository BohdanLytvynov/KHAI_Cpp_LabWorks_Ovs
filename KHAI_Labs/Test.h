#pragma once

struct Example
{

private:
	long int* field1;//@Destr(block)

	double* field2;//@Destr(single)

	double field3;
};
