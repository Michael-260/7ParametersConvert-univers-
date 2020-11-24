#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;


//////////�Զ����ಿ��//////////
//�Զ������һ�����ӣ��ɸ��������д��ʾ�����룩
class point {
public:
	/**********��������*************/
	string ID;
	double x;
	double y;
	double z;

	/*********���캯��**********/
	point(string id = "p1", double xx = 0, double yy = 0, double zz = 0) :ID(id), x(xx), y(yy), z(zz) {}//���캯��

	//��д��Ԫ����
	friend ostream& operator<<(ostream&, point&);
	friend istream& operator>>(istream&, point&);

	/*********������Ա����**********/


};

//��д���������������Ҫ���ݲ�ͬ�����д��
ostream& operator<<(ostream& output, point& p) {

	/*************��д�����������**************/
	output << setprecision(12) << p.ID << " " <<
		setprecision(12) << p.x << " " <<
		setprecision(12) << p.y << " " <<
		setprecision(12) << p.z;

	return output;
}
//��д����ȡ���������Ҫ���ݲ�ͬ�����д��
istream& operator>>(istream& input, point& p) {

	/*************��д����ȡ�����**************/
	input >> p.ID >> p.x >> p.y >> p.z;

	return input;
}
/************ɸѡ����***********/
bool point_judge(point& pp) {
	if (pp.ID == "p4")return true;
	else
	{
		return false;
	}
}
/**************�޸Ĺ���*******************/
void point_correct_data(point& pp) {
	pp.x = pp.x + 1;
}
bool(*JUDGEFUN)(point&)=point_judge;
void(*CORRECTFUN)(point&)=point_correct_data;


//////////���ݿⲿ��//////////

//����һ����
/*
* @param output_txtname ����ļ���
* @param t �Զ������ͷָ�루�������
* @param LINENUMBER �Զ����������ĳ���
*/
template <typename T>
void create_table(string output_txtname,T* t, int LINENUMBER) {
	fstream file;
	file.open(output_txtname, ios::out);
	if (!file) { cerr<<"���ļ�����\n"; exit(0); }
	for (int i = 0; i < LINENUMBER; i++,t++) {
		file << *t << endl;
	}
	file.close();
}

//��ȡһ����
/*
* @param input_txtname �����ļ���
* @param t �Զ������ͷָ�루���շ���
* @param LINENUMBER �Զ����������ĳ���
*/
template<typename T>
void read_table(string input_txtname, T* t, int LINENUMBER) {
	fstream file;
	file.open(input_txtname, ios::in);
	if (!file) { cerr << "��ȡ�ļ�����\n"; exit(0); }
	for (int i = 0; i < LINENUMBER; i++, t++) {
		file >> *t;
	}
	file.close();
}

//���ұ��з���Ҫ���Ԫ�أ������ؽ������ͷָ��
/*
* @param input_txtname �����ļ���
* @param p �Զ���ɸѡ����ָ��
* @param LINENUMBER �������ݵĸ���
* @param size ���ؽ�������ݸ������洢��size��
*/
template<typename T>
T* find_data(string input_txtname, bool(*p)(T&),int LINENUMBER,int&size) {
	fstream file;
	file.open(input_txtname, ios::in);
	if (!file) { cerr << "��ȡ�ļ�����\n"; exit(0); }
	int count = 0; T t;
	//��������
	for (int i = 0; i < LINENUMBER; i++) {
		file >> t;
		if (p(t)) {
			count++;
		}
	}
	if (count == 0) {
		size = 0;
		throw "δ�ҵ���\n";
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

//��дĿ����з���ɸѡ����������
/*
* @param input_txtname �����ļ���
* @param p �Զ���ɸѡ����(ָ��)
* @param c �Զ����д������(ָ��)
* @param LINENUMBER �������ݵĸ���
*/
template<typename T>
void correct(string input_txtname, bool(*p)(T&),void(*c)(T&),int LINENUMBER) {
	fstream file;
	file.open(input_txtname, ios::in);
	if (!file) { cerr << "��ȡ�ļ�����\n"; exit(0); }
	T *t=new T[LINENUMBER],*h=t;
	for (int i = 0; i < LINENUMBER; i++,h++) {
		file >> *h; 
		if (p(*h)) {
			c(*h);
		}
	}
	file.close();
	
	file.open(input_txtname, ios::out);
	if (!file) { cerr << "���ļ�����\n"; exit(0); }
	h = t;
	for (int i = 0; i < LINENUMBER; i++, h++) {
		file << *h << endl;
	}
	delete[]t;
	file.close();
}