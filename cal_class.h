#pragma once
#ifndef ___CAL_CLASS
#define ___CAL_CLASS

#include "data.h"
#include <cstdint>

/*逆行列を計算するために必要な数値を計算するクラス*/
class Inver
{
public:
	Inver();
	Inver(int dim);
	~Inver();
	void cal_next_inver_data(const mydata_class& data);//次の逆行列の計算に使用する説明変数と行列の次元を求める
	void input_result(double data);

	int get_inver_use_data(int elem) const;//逆行列の計算に使用する説明変数を返す
	int get_inver_dim() const;//逆行列の次元を返す
	double get_inver_result(int elem) const;//回帰係数を返す


private:
	Array_1 inver_use_data;//逆行列の計算で使用するdata_listの配列番号
	int inver_dim;//逆行列の次元
protected:
	Array_1 result;//回帰係数
};

class Cal : public Inver
{

public:
	Cal();
	~Cal();
	void cal_ave(mydata_class& data);//平均を計算
	void cal_var(mydata_class& data);//分散を計算
	void cal_cov(mydata_class& data);//共分散を計算
	void cal_inver(mydata_class& data);//回帰係数を計算

	void input_data_from_Inver(mydata_class& data);

	int nCr(int n, int r) const;//nCrの場合の数を計算
	double power(double x, int times) const;//累乗, x^times
};



#endif // !___CAL_CLASS

