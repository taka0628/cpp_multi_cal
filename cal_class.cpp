#include "cal_class.h"

using namespace std;

Cal::Cal() :mydata_class() {};

void Cal::cal_ave() {
	double sum = 0;
	if (data_list.array == nullptr) {
		exit;
	}
	for (int dim = 0; dim < data_list.get_array_row_size(); dim++) {
		sum = 0;
		for (int elem = 0; elem < data_list.get_array_column(); elem++) {
			sum += data_list.array[dim][elem];
		}
		ave.array[dim] = sum / static_cast<double>(data_elem_size);
	}
}

double Cal::power(double x, int times) const {
	if (times >= 0) {
		double temp = x;
		for (int i = 0; i < times - 1; i++) {
			x = x * temp;
		}
		return x;
	}
	else {
		cerr << "[ERROR]\npower" << endl;
		exit;
	}
}


void Cal::cal_var() {
	if (data_list.array == nullptr || var.array == nullptr || ave.array == nullptr) {
		exit;
	}
	double temp_var = 0;

	for (int dim = 0; dim < data_dim_size; dim++) {
		for (int elem = 0; elem < data_elem_size; elem++) {
			temp_var += Cal::power((data_list.array[dim][elem] - ave.array[dim]), 2);
		}
		if (temp_var == 0) {
			cerr << "[ERROR]\nget_var" << endl;
			return;
		}
		else {
			var.array[dim] = temp_var / (data_elem_size - 1);
		}
		temp_var = 0;
	}

}

void Cal::cal_cov() {

	/*cov_xx*/
	int cov_cnt = 0;
	int temp = data_dim_size - 2;
	while (temp) {
		cov_cnt += temp;
		temp--;
	}


	int cov_idx = 0;
	int x_1 = 0, x_2 = 1;
	for (int i = 0; i < data_dim_size - 2 && cov_cnt >= 0; i++) {
		while (cov_cnt--) {
			double temp = 0;
			for (int elem = 0; elem < data_elem_size; elem++) {
				temp += (data_list.array[x_1][elem] - ave.array[x_1]) * (data_list.array[x_2][elem] - ave.array[x_2]);
			}
			cov_xx.array[x_1][x_2] = temp / (data_elem_size - 1);

			if (x_2 <= data_dim_size - 3) {
				x_2++;
			}
			else {
				x_1 = i + 1;
				x_2 = x_1 + 1;
			}
		}
	}

	/*cov_xy*/

	for (int i = 0; i < data_dim_size - 1; i++) {
		double temp = 0;
		x_1 = i;
		for (int elem = 0; elem < data_elem_size; elem++) {
			temp += (data_list.array[x_1][elem] - ave.array[x_1]) * (data_list.array[data_dim_size - 1][elem] - ave.array[data_dim_size - 1]);
		}
		cov_xy.array[x_1] = temp / (data_elem_size - 1);
	}
}