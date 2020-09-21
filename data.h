#pragma once

#ifndef ___DATA_CLASS
#define ___DATA_CLASS

#include <cstdlib>
#include <cstdio>
#include <new>
#include <iostream>
#include <vector>

/*�ꎟ���z��ƁA���̗v�f�����L������N���X*/
class Array_1
{
	int array_size;//�m�ۂ����z��̗v�f��
	double max;
	double min;

public:
	Array_1();
	virtual ~Array_1();
	void create_array(int size);//�z����m�ہA0�ɏ����������
	int get_array_size() const;//�z��̗v�f����Ԃ�
	void cal_max_min();

	double get_max()const;
	double get_min()const;

	double* array;//�z��{��
};

/*�񎟌��z��ƁA�e�������L�^����N���X*/
class Array_2
{
public:
	Array_2();
	virtual ~Array_2();
	void create_array(int m, int n);
	int get_array_m() const;//m
	int get_array_n() const;//n

	double** array;

private:
	int m;//�s
	int n;//��
};

/*��A�W�������߂�܂łɕK�v�Ȑ��l��ێ�����N���X*/
class mydata_class : public Array_1, public Array_2
{
public:
	Array_2 data_list;//�f�[�^�{��
	int data_elem_size;//�f�[�^�̗v�f��
	int data_dim_size;//�f�[�^�̎�ސ�
	Array_1 ave;//����
	Array_1 var;//���U
	Array_2 cov_xx;//�����ϐ����m�̋����U
	Array_1 cov_xy;//�����ϐ��ƖړI�ϐ��̋����U
	Array_1 inver_use_data;//�t�s��̌v�Z�Ŏg�p����data_list�̔z��ԍ�
	int inver_dim;//�t�s��̎���
	Array_1 multiple_regression_coefficient;//��A�W��

	mydata_class();
	//data_class(int data_elem, int data_dim);
	virtual ~mydata_class();

	void print_data() const;
	double get_ave(int dim) const;//���ϒl��Ԃ�
	double get_ver(int dim) const;//���U��Ԃ�
	int get_dim() const;//�ǂݍ��񂾃f�[�^�̎�ނ̐���Ԃ�
	int get_elem() const;//�ǂݍ��񂾃f�[�^�̗v�f����Ԃ�
	double get_data_list(int m, int n) const;//�C�ӂ̏ꏊ�̃f�[�^��Ԃ�
	double** get_data_list() const;//�C�ӂ̏ꏊ�̃f�[�^��Ԃ�

	int input_data_elem(FILE* fp);//�t�@�C������v�f�����擾
	int input_data_dim(FILE* fp);//�t�@�C������f�[�^�̎�ސ����擾
	template<int dim, int elem> void input_data_test(double data[dim][elem]);
	void input_data(double data[], int write_elem);//�t�@�C������f�[�^���擾
	void create_mem();//�t�@�C�������荞�񂾃f�[�^�����ƂɃ��������m��
};


#endif // !___DATA_CLASS



