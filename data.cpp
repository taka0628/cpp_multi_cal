#include "data.h"

using namespace std;


mydata_class::mydata_class()
	//: data_list(), ave(), var(), cov_xx(), cov_xy()
{
	data_dim_size = 0;
	data_elem_size = 0;
}

void mydata_class::create_mem() {
	if (data_dim_size > 0 && data_elem_size > 0) {
		try
		{
			data_list.create_array(data_dim_size, data_elem_size);
			ave.create_array(data_dim_size);
			var.create_array(data_dim_size);
			cov_xx.create_array(data_dim_size - 1, data_elem_size);
			cov_xy.create_array(data_dim_size - 1);

			/*data_list.array = new double* [data_dim_size];
			for (int i = 0; i < data_dim_size; i++) {
				data_list[i] = new double[data_elem_size];
			}
			ave = new double[data_dim_size];
			var = new double[data_dim_size];
			for (int i = 0; i < data_dim_size; i++) {
				ave[i] = var[i] = 0;
			}

			cov_xy = new double[data_dim_size - 1];
			for (int i = 0; i < data_dim_size - 1; i++) {
				cov_xy[i] = 0;
			}

			cov_xx = new double* [data_dim_size - 2];
			int temp = data_dim_size - 1;
			for (int i = 0; i < data_dim_size - 2; i++) {
				cov_xx[i] = new double[temp];
				for (int j = 0; j < temp; j++) {
					cov_xx[i][j] = 0;
				}
			}*/
		}
		catch (bad_alloc& error)
		{
			//printf("”z—ñ‚Ì¶¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½\n", error.what);
			cout << "”z—ñ‚Ì¶¬‚ÉŽ¸”s‚µ‚Ü‚µ‚½\n" << error.what();
			exit(0);
		}
	}
	else {
		cerr << "[ERROR]\nelem‚Ædim‚ª“ü—Í‚³‚ê‚Ä‚¢‚Ü‚¹‚ñ" << endl;
	}
	exit;
}

mydata_class::~mydata_class() {
	/*for (int i = 0; i < data_dim_size; i++) {
		if (data_list[i] != nullptr) {
			delete[](data_list[i]);
		}
		else {
			cerr << "delete_mem error\n" << endl;
			exit;
		}
	}
	delete[] data_list;
	delete[](ave);
	delete[](var);
	delete[](cov_xy);
	for (int i = 0; i < data_dim_size - 2; i++) {
		delete[] cov_xx[i];
	}
	delete[] cov_xx;*/


	cout << "³í‚Éƒƒ‚ƒŠ‚ª‰ð•ú‚³‚ê‚Ü‚µ‚½" << endl;
}

void mydata_class::input_data(double data[], int write_elem) {
	for (int i = 0; i < data_list.get_array_row_size(); i++) {
		data_list.array[i][write_elem] = data[i];
	}
}


template<int dim, int elem> void mydata_class::input_data_test(double input_data[dim][elem]) {
	if (data_dim_size == dim && data_elem_size == elem) {

		for (int loop_dim = 0; loop_dim < dim; loop_dim++) {
			for (int loop_elem = 0; loop_elem < elem; loop_elem++) {
				data_list[loop_dim][loop_elem] = input_data[loop_dim][loop_elem];
			}
		}
	}
	else {
		cout << "[data_class::input_data]\n”z—ñ‚Ì—v‘f”‚ªˆá‚¢‚Ü‚·\n";
	}
}

int mydata_class::input_data_elem(FILE* fp) {
	int data_elem = 0;
	char readline[sizeof(double) * 1024] = { 0 };
	while (1) {
		if (fgets(readline, sizeof(readline), fp) != NULL) {
			data_elem++;
		}
		else {
			break;
		}
	}
	fseek(fp, 0L, SEEK_SET);
	data_elem_size = data_elem;
	return data_elem_size;
}

int mydata_class::input_data_dim(FILE* fp) {
	char readline[sizeof(double) * 1024] = { 0 };
	int  dim = 0;
	char* tp = NULL;

	if (fgets(readline, sizeof(readline), fp) == NULL) {
		return 0;
	}

	tp = strtok(readline, ",");
	for (int i = 0; i < UINT16_MAX && tp != NULL; i++) {
		tp = strtok(NULL, ",");
		dim++;
	}
	data_dim_size = dim;
	return dim;
}

void mydata_class::print_data() const {
	if (data_list.array != nullptr) {
#ifdef ___print 0
		for (int dim = 0; dim < data_dim_size; dim++) {
			for (int elem = 0; elem < data_elem_size; elem++) {
				printf("%.4f ", data_list[dim][elem]);
			}
			cout << endl;
		}
#else
		for (int elem = 0; elem < data_list.get_array_column(); elem++) {
			for (int dim = 0; dim < data_list.get_array_row_size(); dim++) {
				printf("%8.3f ", data_list.array[dim][elem]);
			}
			cout << endl;
		}
#endif
	}
	else {
		cerr << "data_list‚ª—L‚è‚Ü‚¹‚ñ" << endl;
		return;
	}


	cout << '\n';
	if (ave.array != nullptr) {
		for (int dim = 0; dim < ave.get_array_size(); dim++) {
			printf("ave[%d]: %.4f\n", dim, ave.array[dim]);
		}
	}

	if (var.array != nullptr) {
		cout << '\n';
		for (int dim = 0; dim < var.get_array_size(); dim++) {
			printf("var[%d]: %.4f\n", dim, var.array[dim]);
		}
	}

	if (cov_xx.array != nullptr) {
		int cov_point = 0;
		int x_2 = 0;
		cout << '\n';
		for (int dim = 0; dim < cov_xx.get_array_row_size() - 1; dim++) {
			while (x_2 < cov_xx.get_array_row_size())
			{
				printf("cov_x%d_x%d: %.3lf ", dim + 1, x_2 + 1, cov_xx.array[dim][x_2]);
				x_2++;
			}
			cout << '\n';
			x_2 = 0;
		}
		cout << '\n';
	}


	if (cov_xy.array != nullptr) {
		for (int i = 0; i < cov_xy.get_array_size(); i++) {
			printf("cov_xy[%d]: %.4f\n", i, cov_xy.array[i]);
		}
	}
	cout << '\n';
}

int mydata_class::get_dim()const {
	return data_dim_size;
}

int mydata_class::get_elem()const {
	return data_elem_size;
}

double mydata_class::get_ave(int dim)const {
	return ave.array[dim];
}

double mydata_class::get_ver(int dim)const {
	return var.array[dim];
}

double mydata_class::get_data_list(int m, int n) const{
	if (m >= 0 && n >= 0 && m <= data_list.get_array_row_size() && n <= data_list.get_array_column()) {
		return data_list.array[m][n];
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}
}