#include "cal_class.h"

using namespace std;

Cal::Cal() {

}

Cal::~Cal() {

}

void Cal::cal_ave(mydata_class& data) {
	double sum = 0;
	if (data.get_data_list() == nullptr) {
		exit;
	}
	for (int dim = 0; dim < data.data_list.get_array_m(); dim++) {
		sum = 0;
		for (int elem = 0; elem < data.data_list.get_array_n(); elem++) {
			//sum += data_list.array[dim][elem];
			sum += data.get_data_list(dim, elem);
		}
		data.ave.array[dim] = sum / static_cast<double>(data.get_elem());
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

void Cal::cal_var(mydata_class& data) {
	if (data.data_list.array == nullptr || data.var.array == nullptr || data.ave.array == nullptr) {
		exit;
	}
	double temp_var = 0;

	for (int dim = 0; dim < data.data_dim_size; dim++) {
		for (int elem = 0; elem < data.data_elem_size; elem++) {
			temp_var += Cal::power((data.data_list.array[dim][elem] - data.ave.array[dim]), 2);
		}
		if (temp_var == 0) {
			cerr << "[ERROR]\nget_var" << endl;
			return;
		}
		else {
			data.var.array[dim] = temp_var / (data.data_elem_size - 1);
		}
		temp_var = 0;
	}

}

void Cal::cal_cov(mydata_class& data) {

	/*cov_xx*/
	int cov_cnt = 0;
	int temp = data.data_dim_size - 2;
	while (temp) {
		cov_cnt += temp;
		temp--;
	}

	int cov_idx = 0;
	int x_1 = 0, x_2 = 1;
	for (int i = 0; i < data.data_dim_size - 2 && cov_cnt >= 0; i++) {
		while (cov_cnt--) {
			double temp = 0;
			for (int elem = 0; elem < data.data_elem_size; elem++) {
				temp += (data.data_list.array[x_1][elem] - data.ave.array[x_1]) * (data.data_list.array[x_2][elem] - data.ave.array[x_2]);
			}
			data.cov_xx.array[x_1][x_2] = temp / (data.data_elem_size - 1);

			if (x_2 <= data.data_dim_size - 3) {
				x_2++;
			}
			else {
				x_1 = i + 1;
				x_2 = x_1 + 1;
			}
		}
	}

	/*cov_xy*/
	for (int i = 0; i < data.data_dim_size - 1; i++) {
		double temp = 0;
		x_1 = i;
		for (int elem = 0; elem < data.data_elem_size; elem++) {
			temp += (data.data_list.array[x_1][elem] - data.ave.array[x_1]) * (data.data_list.array[data.data_dim_size - 1][elem] - data.ave.array[data.data_dim_size - 1]);
		}
		data.cov_xy.array[x_1] = temp / (data.data_elem_size - 1);
	}
}

void vec_diff(Array_1& a, Array_2& b, int b_dim, int dim) {
	
	for (int i = 0; i < dim; i++) {
		b.array[b_dim][i] -= a.array[i];
	}
}


void Cal::cal_inver(mydata_class& data) {
	Array_1 use_var;
	use_var.create_array(get_inver_dim());
	Array_2 use_cov;
	use_cov.create_array(get_inver_dim(), get_inver_dim());
	int cov_point = 0;

	/*下準備*/
	/*使用するデータをコピー*/
	for (int i = 0; i < get_inver_dim(); i++) {
		use_var.array[i] = data.var.array[get_inver_use_data(i)];
	}
	/*int use_cov_dim = 0;
	for (int i = 0; i < get_inver_dim() - 1; i++) {
		cov_point = i + 1;
		while (cov_point < get_inver_dim()) {
			use_cov.array[use_cov_dim][cov_point - 1 - i] = cov_xx.array[get_inver_use_data(i)][get_inver_use_data(cov_point) - 1 - get_inver_use_data(i)];
			cov_point++;
		}
		use_cov_dim++;
	}*/

	for (int m = 0; m < get_inver_dim(); m++) {
		for (int n = m + 1; n < get_inver_dim(); n++) {
			use_cov.array[m][n] = data.cov_xx.array[get_inver_use_data(m)][get_inver_use_data(n)];
		}
	}

	Array_2 m;
	m.create_array(get_inver_dim(), get_inver_dim());
	for (int i = 0; i < get_inver_dim(); i++) {
		for (int j = 0; j < get_inver_dim(); j++) {
			if (i == j) {
				m.array[i][j] = use_var.array[i];
			}
			else {
				if (i < j) {
					m.array[i][j] = use_cov.array[i][j];
					m.array[j][i] = use_cov.array[i][j];
				}
			}
		}
	}

	Array_1 a;
	a.create_array(get_inver_dim());
	for (int i = 0; i < get_inver_dim(); i++) {
		a.array[i] = data.cov_xy.array[get_inver_use_data(i)];
	}

	cout << "連立方程式を計算" << endl;
	cout << "use_dim: ";
	for (int i = 0; i < get_inver_dim(); i++) {
		cout << get_inver_use_data(i) << ", ";
	}
	cout << endl;

	for (int i = 0; i < get_inver_dim(); i++) {
		for (int j = 0; j < get_inver_dim(); j++) {
			printf("%.4f ", m.array[i][j]);
			if (j == get_inver_dim() - 1) {
				printf("\n");
			}
		}
	}
	cout << endl;

	for (int i = 0; i < get_inver_dim(); i++) {
		for (int j = i + 1; j < get_inver_dim(); j++) {
			double coef = m.array[j][i] / m.array[i][i];
			Array_1 del;
			del.create_array(get_inver_dim());

			for (int k = 0; k < get_inver_dim(); k++) {
				del.array[k] = m.array[i][k] * coef;
			}
			vec_diff(del, m, j, get_inver_dim());
			a.array[j] -= a.array[i] * coef;
		}
	}

	for (int i = get_inver_dim() - 1; i >= 0; i--) {
		double x = 1. / m.array[i][i];
		m.array[i][i] *= x;
		a.array[i] *= x;

		for (int j = 0; j < i; j++) {
			a.array[j] -= a.array[i] * m.array[j][i];
			m.array[j][i] = 0;
		}
	}

	for (int i = 0; i < get_inver_dim(); i++) {
		for (int j = 0; j < get_inver_dim(); j++) {
			printf("%.3f ", m.array[i][j]);
			if (j == get_inver_dim() - 1) {
				printf("\n");
			}
		}
	}

	for (int i = 0; i < get_inver_dim(); i++) {
		printf("a%d: %.5lf ", i, a.array[i]);
		result.array[i] = a.array[i];
	}
	cout << endl;

	//#endif
}

int Cal::nCr(int n, int r) const {
	int up_num = 1;
	int under_num = 1;
	for (int i = 0; i < n; i++) {
		up_num *= r - i;
	}
	for (int i = n; i > 1; i--) {
		under_num *= i;
	}
	if (under_num > 0) {
		return up_num / under_num;
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		return 0;
	}
}

void Cal::input_data_from_Inver(mydata_class& data) {
	data.inver_dim = get_inver_dim();
	for (int i = 0; i < get_inver_dim(); i++) {
		data.multiple_regression_coefficient.array[i] = get_inver_result(i);
		data.inver_use_data.array[i] = get_inver_use_data(i);
	}
}

/*Inver*/

Inver::Inver()
{
	inver_dim = 2;
	inver_use_data.array = nullptr;
}

Inver::Inver(int dim) 
{
	inver_dim = 2;
}

Inver::~Inver()
{
	
}

void Inver::cal_next_inver_data(const mydata_class& data) {
	bool isDimPlus = false;
	if (inver_use_data.array == nullptr && data.get_dim() > 0) {
		inver_use_data.create_array(data.get_dim() - 1);
		inver_dim = 2;//初期状態, 最初は二次元の行列計算
	}
	if (result.array == nullptr) {
		result.create_array(data.get_dim() - 1);
	}

	if (data.get_dim() <= 0) {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}


	for (int i = inver_dim - 1; i >= 0; i--) {
		if (i == inver_dim - 1 && inver_use_data.array[i] < data.get_dim() - 2) {//データの最大配列を参照&&格納さてている値がデータの次元以下の時
			inver_use_data.array[i]++;//値に1を加算
			break;
		}
		if (i > 0) {
			if (inver_use_data.array[i] + 1 < inver_use_data.array[i + 1]) {
				inver_use_data.array[i]++;
				break;
			}
			else {
				continue;
			}
		}
		else if (i == 0) {
			if (inver_use_data.array[i] + 1 < inver_use_data.array[i + 1]) {
				for (int j = 0; j < inver_dim; j++) {
					if (j == 0) {
						inver_use_data.array[j] = inver_use_data.array[0] + 1;
					}
					else {
						inver_use_data.array[j] = inver_use_data.array[j - 1] + 1;
					}
				}
				break;
			}
			else {
				if (inver_dim < data.get_dim() - 1) {//現在のペアを全て解析したとき
					inver_dim++;//ペアを増やす
					for (int j = 0; j < inver_dim; j++) {//新たなペアで再配置
						inver_use_data.array[j] = j;
					}
					break;
				}
			}
		}
	}
}



int Inver::get_inver_dim() const {
	return inver_dim;
}

int Inver::get_inver_use_data(int elem) const {
	if (elem < inver_dim && elem >= 0) {
		return inver_use_data.array[elem];
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}
}

double Inver::get_inver_result(int elem) const {
	if (elem >= 0 && elem <= result.get_array_size()) {
		return result.array[elem];
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}
}
