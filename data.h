#pragma once

#ifndef ___DATA_CLASS
#define ___DATA_CLASS

#include <cstdlib>
#include <cstdio>
#include <new>
#include <iostream>

class Array_1
{
	int array_size;

public:
	Array_1();
	double* array;
	virtual ~Array_1();
	void create_array(int size);
	int get_array_size() const;

};


class Array_2
{
public:
	Array_2();
	virtual ~Array_2();
	void create_array(int m, int n);
	int get_array_row_size() const;
	int get_array_column() const;

	double** array;

private:
	int m;
	int n;
};



class mydata_class : public virtual Array_1, Array_2
{
protected:
	Array_2 data_list;
	int data_elem_size;
	int data_dim_size;
	Array_1 ave;
	Array_1 var;
	Array_2 cov_xx;
	Array_1 cov_xy;

public:
	mydata_class();
	//data_class(int data_elem, int data_dim);
	virtual ~mydata_class();

	void print_data() const;
	double get_ave(int dim) const;
	double get_ver(int dim) const;
	int get_dim() const;
	int get_elem() const;
	int input_data_elem(FILE* fp);
	int input_data_dim(FILE* fp);
	template<int dim, int elem> void input_data_test(double data[dim][elem]);
	void input_data(double data[], int write_elem);
	void create_mem();
	void delete_mem();



};

#endif // !___DATA_CLASS



