#include "data.h"

using namespace std;

/*Array_1*/

Array_1::Array_1()
{
	array = nullptr;
	array_size = 0;
	max = 0;
	min = UINT32_MAX;
}

Array_1::~Array_1()
{
	if (array != nullptr) {
		delete[] array;
	}
}

void Array_1::create_array(int size) {
	if (size > 0) {
		array = new double[size];
		array_size = size;
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}

	for (int i = 0; i < array_size; i++) {
		array[i] = 0;
	}
}

int Array_1::get_array_size() const {
	return array_size;
}

void Array_1::cal_max_min() {
	if (array == nullptr) {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}

	double temp_max = 0, temp_min = UINT32_MAX;
	for (int i = 0; i < get_array_size(); i++) {
		if (temp_max < array[i]) {
			temp_max = array[i];
		}
		if (temp_min > array[i]) {
			temp_min = array[i];
		}
	}
	max = temp_max;
	min = temp_min;
}

double Array_1::get_max() const {
	return max;
}

double Array_1::get_min() const {
	return min;
}


/*Array_2*/

Array_2::Array_2()
{
	array = nullptr;
	m = n = 0;
}

Array_2::~Array_2()
{
	if (m >= 0 && n > 0) {
		for (int i = 0; i < m; i++) {
			delete[] array[i];
		}
		delete[] array;
	}
}

void Array_2::create_array(int m, int n) {
	if (m >= 0, n > 0) {
		array = new double* [m];
		for (int i = 0; i < m; i++) {
			array[i] = new double[n];
			for (int elem = 0; elem < n; elem++) {
				array[i][elem] = 0;
			}
		}
		this->m = m;
		this->n = n;
	}
	else {
		cerr << "[ERROE]\n" << __func__ << endl;
	}
}

int Array_2::get_array_m() const { //m
	return m;
}

int Array_2::get_array_n() const { //n
	return n;
}