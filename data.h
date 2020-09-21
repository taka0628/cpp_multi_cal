#pragma once

#ifndef ___DATA_CLASS
#define ___DATA_CLASS

#include <cstdlib>
#include <cstdio>
#include <new>
#include <iostream>
#include <vector>

/*一次元配列と、その要素数を記憶するクラス*/
class Array_1
{
	int array_size;//確保した配列の要素数
	double max;
	double min;

public:
	Array_1();
	virtual ~Array_1();
	void create_array(int size);//配列を確保、0に初期化される
	int get_array_size() const;//配列の要素数を返す
	void cal_max_min();

	double get_max()const;
	double get_min()const;

	double* array;//配列本体
};

/*二次元配列と、各次元を記録するクラス*/
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
	int m;//行
	int n;//列
};

/*回帰係数を求めるまでに必要な数値を保持するクラス*/
class mydata_class : public Array_1, public Array_2
{
public:
	Array_2 data_list;//データ本体
	int data_elem_size;//データの要素数
	int data_dim_size;//データの種類数
	Array_1 ave;//平均
	Array_1 var;//分散
	Array_2 cov_xx;//説明変数同士の共分散
	Array_1 cov_xy;//説明変数と目的変数の共分散
	Array_1 inver_use_data;//逆行列の計算で使用するdata_listの配列番号
	int inver_dim;//逆行列の次元
	Array_1 multiple_regression_coefficient;//回帰係数

	mydata_class();
	//data_class(int data_elem, int data_dim);
	virtual ~mydata_class();

	void print_data() const;
	double get_ave(int dim) const;//平均値を返す
	double get_ver(int dim) const;//分散を返す
	int get_dim() const;//読み込んだデータの種類の数を返す
	int get_elem() const;//読み込んだデータの要素数を返す
	double get_data_list(int m, int n) const;//任意の場所のデータを返す
	double** get_data_list() const;//任意の場所のデータを返す

	int input_data_elem(FILE* fp);//ファイルから要素数を取得
	int input_data_dim(FILE* fp);//ファイルからデータの種類数を取得
	template<int dim, int elem> void input_data_test(double data[dim][elem]);
	void input_data(double data[], int write_elem);//ファイルからデータを取得
	void create_mem();//ファイルから取り込んだデータをもとにメモリを確保
};


#endif // !___DATA_CLASS



