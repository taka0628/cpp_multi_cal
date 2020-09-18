#pragma once
#ifndef ___CAL_CLASS
#define ___CAL_CLASS

#include "data.h"
#include <cstdint>

/*�t�s����v�Z���邽�߂ɕK�v�Ȑ��l���v�Z����N���X*/
class Inver
{
public:
	Inver();
	Inver(int dim);
	~Inver();
	void cal_next_inver_data(const mydata_class& data);//���̋t�s��̌v�Z�Ɏg�p��������ϐ��ƍs��̎��������߂�
	void input_result(double data);

	int get_inver_use_data(int elem) const;//�t�s��̌v�Z�Ɏg�p��������ϐ���Ԃ�
	int get_inver_dim() const;//�t�s��̎�����Ԃ�
	double get_inver_result(int elem) const;//��A�W����Ԃ�


private:
	Array_1 inver_use_data;//�t�s��̌v�Z�Ŏg�p����data_list�̔z��ԍ�
	int inver_dim;//�t�s��̎���
protected:
	Array_1 result;//��A�W��
};

class Cal : public Inver
{

public:
	Cal();
	~Cal();
	void cal_ave(mydata_class& data);//���ς��v�Z
	void cal_var(mydata_class& data);//���U���v�Z
	void cal_cov(mydata_class& data);//�����U���v�Z
	void cal_inver(mydata_class& data);//��A�W�����v�Z

	void input_data_from_Inver(mydata_class& data);

	int nCr(int n, int r) const;//nCr�̏ꍇ�̐����v�Z
	double power(double x, int times) const;//�ݏ�, x^times
};



#endif // !___CAL_CLASS

