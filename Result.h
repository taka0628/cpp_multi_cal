#pragma once
#ifndef ___Result
#define ___Result

#include "data.h"
#include "cal_class.h"


/*ŒÂ•Ê‚Ìd‰ñ‹A•ªÍ‚ÌŒ‹‰Ê‚ğ•Û*/
class dis_result : public Array_1
{
public:
	dis_result();
	dis_result(const mydata_class& data);
	~dis_result();

	void cal_prediction_y(const mydata_class& data);
	void cal_R();
	void cal_adjustR(const mydata_class& data);
	void cal_diff_R_verR();
	void print_R() const;

	double get_R() const;
	double get_adjust_R() const;
	double get_diff_R() const;
	int get_use_dim_size() const;
	int get_use_dim(int elem) const;
	double get_expression(int elem) const;

	Array_1 prediction_y;
	Array_1 expression;
	Array_1 use_data;
	double prediction_ave;
	double prediction_var;
	double var_y;
	double R;
	double adjust_R;
	double diff_R_adjR;
};



/*d‘ŠŠÖŒW”‚Ì‚‚¢•ªÍŒ‹‰Ê‚ğ•Û*/
class total_result
{
public:
	total_result();
	~total_result();

	void input_score(const dis_result& result);
	void print_total_result() const;
	void copy_result(dis_result& result, const dis_result& temp);

private:
	dis_result max_R;
	dis_result max_adjR;
	dis_result min_diff_R;
};



#endif // !___Result


