
#include "cal_class.h"
#include "data.h"

//#include "data_class.h"

#define ELEM_SIZE 6
#define DIM_MAX 100
#define N 2
#define INVER


using namespace std;

int get_double_csvdata(FILE* fp, mydata_class data, double temp_data[])
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
			cerr << "入力値がboubleの大きさを超えています\n";
			return 0;
		}
		tp = strtok(NULL, ",");
	}
	return 1;
}

int main() {
	FILE* fp;
	if ((fp = fopen("Book3.csv", "r")) == NULL) {
		//puts("ファイル読み込みエラー");
		cout << "ファイル読み込みエラー\n" << __func__;
		return 0;
	}

	Cal data;
	data.input_data_dim(fp);
	data.input_data_elem(fp);
	data.create_mem();


	/*データの読み込み*/
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

	/*計算*/
	data.cal_ave();
	data.cal_var();
	data.cal_cov();

	
	data.print_data();
}