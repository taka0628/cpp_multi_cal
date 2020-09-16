#pragma once
#ifndef ___CAL_CLASS
#define ___CAL_CLASS

#include "data.h"
#include <cstdint>

class Cal : public mydata_class
{

public:
	Cal() :mydata_class(){};
	void cal_ave();
	void cal_var();
	double power(double x, int times) const;
	void cal_cov();
};


#endif // !___CAL_CLASS

