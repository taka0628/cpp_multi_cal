
#include "cal_class.h"
#include "data.h"
#include "Result.h"

/*�S�Ă̐����ϐ��̑g�ݍ��킹����œK�Ȑ����ϐ������߂�*/


using namespace std;

int get_double_csvdata(FILE* fp, const Cal& data, double temp_data[])
{
	char readline[sizeof(double) * 1024] = { 0 };
	if (fgets(readline, sizeof(readline), fp) == NULL) {
		return 0;
	}
	char* tp = NULL;
	tp = strtok(readline, ",");
	for (int i = 0; i < data.get_dim() && tp != NULL; i++) {
		if (sizeof(strtod(tp, NULL)) <= sizeof(temp_data[0])) {
			//cout << "sizeof(baffer): " << sizeof(baffer) << "\nsizeof(double): " << sizeof(temp_data[0]) << "\n";
			temp_data[i] = strtod(tp, NULL);
		}
		else {
			cerr << "���͒l��bouble�̑傫���𒴂��Ă��܂�\n";
			return 0;
		}
		tp = strtok(NULL, ",");
	}
	return 1;
}

int main() {
	FILE* fp;
	if ((fp = fopen("Book3.csv", "r")) == NULL) {
		//puts("�t�@�C���ǂݍ��݃G���[");
		cout << "�t�@�C���ǂݍ��݃G���[\n" << __func__;
		return 0;
	}

	Cal data;
	data.input_data_dim(fp);
	data.input_data_elem(fp);
	data.create_mem();


	/*�f�[�^�̓ǂݍ���*/
	int aa = data.get_dim();
	double* temp_data = new double[data.get_dim()];
	for (int i = 0; i < data.get_dim(); i++) {
		temp_data[i] = 0;
	}
	for (int now_elem = 0; now_elem < data.get_elem(); now_elem++) {
		if (get_double_csvdata(fp, data, temp_data) == false) {
			return 0;
		}
		data.input_data(temp_data, now_elem);
	}
	fclose(fp);

	/*�v�Z*/
	data.cal_ave();
	data.cal_var();
	data.cal_cov();

	data.print_data();

	int loop_cnt = 0;
	int temp = 0;
	for (int i = 2; i <= data.get_dim() - 1; i++) {
		temp = data.nCr(i, data.get_dim() - 1);
		if (temp <= 0) {
			puts("loop_count error");
			return 0;
		}
		else {
			loop_cnt += temp;
		}
	}
	total_result result;
	while (loop_cnt--) {
		data.cal_next_inver_data();
		data.cal_inver();
		
		dis_result dis_result(data);
		dis_result.cal_prediction_y(data);
		dis_result.cal_R();
		dis_result.cal_adjustR(data);
		dis_result.cal_diff_R_verR();

		dis_result.print_R();

		result.input_score(dis_result);
	}
	result.print_total_result();
}