#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


//////////自定义类部分//////////
//自定义类的一个例子，可根据需求改写（示例代码）
class point {
public:
	/**********数据区域*************/
	string ID;
	double x;
	double y;
	double z;

	/*********构造函数**********/
	point(string id = "p1", double xx = 0, double yy = 0, double zz = 0) :ID(id), x(xx), y(yy), z(zz) {}//构造函数

	//重写友元函数
	friend ostream& operator<<(ostream&, point&);
	friend istream& operator>>(istream&, point&);

	/*********其它成员函数**********/


};

//重写流插入运算符（需要根据不同情况改写）
ostream& operator<<(ostream& output, point& p) {

	/*************重写流插入运算符**************/
	output << setprecision(12) << p.ID << " " <<
		setprecision(12) << p.x << " " <<
		setprecision(12) << p.y << " " <<
		setprecision(12) << p.z;

	return output;
}
//重写流提取运算符（需要根据不同情况改写）
istream& operator>>(istream& input, point& p) {

	/*************重写流提取运算符**************/
	input >> p.ID >> p.x >> p.y >> p.z;

	return input;
}
/************筛选规则***********/
bool point_judge(point& pp) {
	if (pp.ID == "p4")return true;
	else
	{
		return false;
	}
}
/**************修改规则*******************/
void point_correct_data(point& pp) {
	pp.x = pp.x + 1;
}
bool(*JUDGEFUN)(point&)=point_judge;
void(*CORRECTFUN)(point&)=point_correct_data;


//////////数据库部分//////////

//创建一个表
/*
* @param output_txtname 输出文件名
* @param t 自定义对象头指针（输出方）
* @param LINENUMBER 自定义对象数组的长度
*/
template <typename T>
void create_table(string output_txtname,T* t, int LINENUMBER) {
	fstream file;
	file.open(output_txtname, ios::out);
	if (!file) { cerr<<"打开文件错误！\n"; exit(0); }
	for (int i = 0; i < LINENUMBER; i++,t++) {
		file << *t << endl;
	}
	file.close();
}

//读取一个表
/*
* @param input_txtname 输入文件名
* @param t 自定义对象头指针（接收方）
* @param LINENUMBER 自定义对象数组的长度
*/
template<typename T>
void read_table(string input_txtname, T* t, int LINENUMBER) {
	fstream file;
	file.open(input_txtname, ios::in);
	if (!file) { cerr << "读取文件错误！\n"; exit(0); }
	for (int i = 0; i < LINENUMBER; i++, t++) {
		file >> *t;
	}
	file.close();
}

//查找表中符合要求的元素，并返回结果集的头指针
/*
* @param input_txtname 输入文件名
* @param p 自定义筛选函数指针
* @param LINENUMBER 处理数据的个数
* @param size 返回结果的数据个数，存储在size中
*/
template<typename T>
T* find_data(string input_txtname, bool(*p)(T&),int LINENUMBER,int&size) {
	fstream file;
	file.open(input_txtname, ios::in);
	if (!file) { cerr << "读取文件错误！\n"; exit(0); }
	int count = 0; T t;
	//遍历两遍
	for (int i = 0; i < LINENUMBER; i++) {
		file >> t;
		if (p(t)) {
			count++;
		}
	}
	if (count == 0) {
		size = 0;
		throw "未找到！\n";
		return NULL;
	};
	T* result = new T[count],*tem=result;
	file.seekg(ios::beg);
	for (int i = 0; i < LINENUMBER; i++) {
		file >> t;
		if (p(t)) {
			*tem = t;
			tem++;
		}
	}
	file.close();
	size = count;
	return result;
}

//改写目标表中符合筛选条件的数据
/*
* @param input_txtname 输入文件名
* @param p 自定义筛选函数(指针)
* @param c 自定义改写规则函数(指针)
* @param LINENUMBER 处理数据的个数
*/
template<typename T>
void correct(string input_txtname, bool(*p)(T&),void(*c)(T&),int LINENUMBER) {
	fstream file;
	file.open(input_txtname, ios::in);
	if (!file) { cerr << "读取文件错误！\n"; exit(0); }
	T *t=new T[LINENUMBER],*h=t;
	for (int i = 0; i < LINENUMBER; i++,h++) {
		file >> *h; 
		if (p(*h)) {
			c(*h);
		}
	}
	file.close();
	
	file.open(input_txtname, ios::out);
	if (!file) { cerr << "打开文件错误！\n"; exit(0); }
	h = t;
	for (int i = 0; i < LINENUMBER; i++, h++) {
		file << *h << endl;
	}
	delete[]t;
	file.close();
}