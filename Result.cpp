#include "Result.h"
//#include <>

using namespace std;

double power(double x, int times){
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

dis_result::dis_result() {
	R = 0;
	adjust_R = 0;
	diff_R_adjR = UINT16_MAX;
	prediction_ave = 0;
	prediction_var = 0;
	
}

dis_result::dis_result(const mydata_class& data) {
	R = 0;
	adjust_R = 0;
	diff_R_adjR = 0;
	prediction_ave = 0;
	prediction_var = 0;
	var_y = data.get_ver(data.get_dim() - 1);

	if (prediction_y.array == nullptr) {
		prediction_y.create_array(data.get_elem());
	}
	if (expression.array == nullptr) {
		expression.create_array(data.get_dim());
	}
	if (use_data.array == nullptr) {
		use_data.create_array(data.inver_dim);
		for (int i = 0; i < use_data.get_array_size(); i++) {
			use_data.array[i] = data.inver_use_data.array[i];
		}
	}
}

dis_result::~dis_result() {

}

/*à–¾•Ï”‚ð—\‘ª*/
void dis_result::cal_prediction_y(const mydata_class& data) {
	double a0 = data.get_ave(data.get_dim() - 1);
	for (int i = 0; i < data.data_dim_size; i++) {
		a0 -= data.multiple_regression_coefficient.array[i] * data.get_ave(data.inver_use_data.array[i]);
	}
	printf("Y = %.4lf", a0);

	expression.array[0] = a0;
	for (int i = 0; i < data.inver_dim; i++) {
		printf(" + %.4fx_%d", data.multiple_regression_coefficient.array[i], i + 1);
		expression.array[i + 1] = data.multiple_regression_coefficient.array[i];
	}
	cout << endl;

	/*d‰ñ‹AŒW”‚©‚çà–¾•Ï”‚ð—\‘ª*/
	for (int i = 0; i < data.get_elem(); i++) {
		prediction_y.array[i] += a0;
		for (int j = 0; j < data.inver_dim; j++) {
			prediction_y.array[i] += data.multiple_regression_coefficient.array[j] * data.get_data_list(data.inver_use_data.array[j], i);
		}
	}
}

void dis_result::cal_R() {
	for (int i = 0; i < prediction_y.get_array_size(); i++) {
		prediction_ave += prediction_y.array[i];
	}
	prediction_ave = prediction_ave / prediction_y.get_array_size();

	for (int i = 0; i < prediction_y.get_array_size(); i++) {
		prediction_var += (prediction_y.array[i] - prediction_ave) * (prediction_y.array[i] - prediction_ave);
	}
	prediction_var = prediction_var / (static_cast<double>(prediction_y.get_array_size()) - 1);
	R = prediction_var / var_y;
}

void dis_result::cal_adjustR(const mydata_class& data) {
	double Scal = 0, Sy = 0;
	for (int i = 0; i < prediction_y.get_array_size(); i++) {
		Scal += power(data.get_data_list(data.get_dim() - 1, i) - prediction_y.array[i], 2);
		//Sy += (*VAL(data, data_dim - 1, i) - ave.y) * (*VAL(data, data_dim - 1, i) - ave.y);
		Sy += power(data.get_data_list(data.get_dim() - 1, i) - data.get_ave(data.get_dim() - 1), 2);
	}
	Scal = Scal / (data.get_elem() - data.inver_dim);
	Sy = Sy / (data.get_elem() - 1);
	adjust_R = 1 - (Scal / Sy);
}

void dis_result::cal_diff_R_verR() {
	diff_R_adjR = R - adjust_R;
}

double dis_result::get_R() const{
	return R;
}

double dis_result::get_adjust_R() const {
	return adjust_R;
}

double dis_result::get_diff_R() const {
	return diff_R_adjR;
}

void dis_result::print_R() const {
	printf("R^2: %.4lf\nR~^2: %.4lf\n·: %.4lf\n", R, adjust_R, diff_R_adjR);
}

int dis_result::get_use_dim_size() const {
	return use_data.get_array_size();
}

double dis_result::get_expression(int elem) const {
	if (elem >= 0 && elem <= expression.get_array_size()) {
		return expression.array[elem];
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}
}

int dis_result::get_use_dim(int elem) const {
	if (elem >= 0 && elem <= use_data.get_array_size()) {
		return use_data.array[elem];
	}
	else {
		cerr << "[ERROR]\n" << __func__ << endl;
		exit;
	}
}


total_result::total_result() {

}


total_result::~total_result() {

}


void total_result::copy_result(dis_result& result, const dis_result& temp) {
	result.R = temp.R;
	result.adjust_R = temp.adjust_R;
	result.diff_R_adjR = temp.diff_R_adjR;
	result.expression.create_array(temp.get_use_dim_size() + 1);
	for (int i = 0; i < temp.get_use_dim_size() + 1; i++) {
		result.expression.array[i] = temp.expression.array[i];
	}
	result.use_data.create_array(temp.get_use_dim_size());
	for (int i = 0; i < temp.get_use_dim_size(); i++) {
		result.use_data.array[i] = temp.use_data.array[i];
	}

}

void total_result::input_score(const dis_result& result) {
	if (max_R.get_R() < result.get_R()) {
		copy_result(max_R, result);
	}
	if (max_adjR.get_adjust_R() < result.get_adjust_R()) {
		copy_result(max_adjR, result);
	}
	if (min_diff_R.get_diff_R() > result.get_diff_R()) {
		copy_result(min_diff_R, result);
	}
}

void print_result_tepm(const dis_result& result) {
	printf("dim: ");
	for (int i = 0; i < result.get_use_dim_size(); i++) {
		printf("x_%d ", result.get_use_dim(i));
	}
	printf("\tR: %.4lf, verR: %.4lf, diff: %.4lf\n", result.get_R(), result.get_adjust_R(), result.get_diff_R());
	printf("Y = ");
	for (int i = 1; i <= result.get_use_dim_size(); i++) {
		printf("+ %.4lfx_%d ", result.get_expression(i), i);
	}
	printf("+ %.4lf\n\n", result.get_expression(0));
}


void total_result::print_total_result() const {
	printf("[max_R]\n");
	print_result_tepm(max_R);
	printf("[max_verR]\n");
	print_result_tepm(max_adjR);
	printf("[min_diff]\n");
	print_result_tepm(min_diff_R);
}
