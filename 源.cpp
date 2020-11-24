#include<Eigen/Dense>
#include"database.h"
using namespace Eigen;

static string OLDDATATXT = "ol_data.txt";
static string NEDATATXT = "ne_data.txt";
static int OLNUMBER = 12;
static int NENUMBER = 7;

int main() {
	cout << "7参数转换：\n请输入旧坐标总个数：\n"; cin >> OLNUMBER;
	cout << "请输入新坐标的个数：\n"; cin >> NENUMBER;
	point* ol = new point[OLNUMBER];
	point* ne = new point[NENUMBER];
	point* temp = ol,*temp1=ne;
	read_table(OLDDATATXT, ol, OLNUMBER);
	read_table(NEDATATXT, ne, NENUMBER);

	int num = 0;
	num = OLNUMBER * 3;
	double* olxyz = new double[num];
	num = NENUMBER * 3;
	double* nexyz = new double[num];

	MatrixXd b(3 * NENUMBER, 7),nb(3*OLNUMBER,7), l(3 * NENUMBER, 1), v, x;
	num = 0;
	MatrixXd mol(OLNUMBER, 3), mne(NENUMBER, 3);
	temp = ol; temp1 = ne;
	for (int i = 0; i < OLNUMBER; i++,temp++) {
		mol(i, 0) = temp->x; mol(i, 1) = temp->y; mol(i, 2) = temp->z;
	}
	for (int i = 0; i < NENUMBER; i++,temp1++) {
		mne(i, 0) = temp1->x; mne(i, 1) = temp1->y; mne(i, 2) = temp1->z;
	}
	temp = ol; temp1 = ne;
	for (int i = 0; i < 3 * NENUMBER; i++) {
		if (i % 3 == 0) {
			b(i, 0) = 1; b(i, 1) = 0; b(i, 2) = 0; b(i, 3) = 0; b(i, 4) = -1 * temp->z; b(i, 5) = temp->y; b(i, 6) = temp->x;
		}
		else if (i % 3 == 1) {
			b(i, 0) = 0; b(i, 1) = 1; b(i, 2) = 0; b(i, 3) = temp->z; b(i, 4) = 0; b(i, 5) = -1 * temp->x; b(i, 6) = temp->y;
		}
		else {
			b(i, 0) = 0; b(i, 1) = 0; b(i, 2) = 1; b(i, 3) = -1 * temp->y; b(i, 4) = temp->x; b(i, 5) = 0; b(i, 6) = temp->z;
			temp++;
		}
	}
	temp = ol; temp1 = ne;
	for (int i = 0; i < 3 * NENUMBER; i++) {
		if (i % 3 == 0) {
			l(i, 0) = temp1->x - temp->x;
		}
		else if (i % 3 == 1) {
			l(i, 0) = temp1->y - temp->y;
		}
		else {
			l(i, 0) = temp1->z - temp->z;
			temp1++; temp++;
		}
	}
	cout << "b\n" << b << endl << "l\n" << l << endl;

	x = (b.transpose() * b).inverse() * b.transpose() * l;
	v = b * x - l;
	MatrixXd xigama;
	xigama = v.transpose() * v;
	double xigamad = xigama(0, 0);
	xigamad = sqrt(xigamad / (NENUMBER * 3.0 - 7));
	cout << "x\n" << x << endl << "v\n" << v<<endl <<"xigama:\n"<<xigamad<< endl;
	temp = ol;
	for (int i = 0; i < 3 * OLNUMBER; i++) {
		if (i % 3 == 0) {
			nb(i, 0) = 1; nb(i, 1) = 0; nb(i, 2) = 0; nb(i, 3) = 0; nb(i, 4) = -1 * temp->z; nb(i, 5) = temp->y; nb(i, 6) = temp->x;
		}
		else if (i % 3 == 1) {
			nb(i, 0) = 0; nb(i, 1) = 1; nb(i, 2) = 0; nb(i, 3) = temp->z; nb(i, 4) = 0; nb(i, 5) = -1 * temp->x; nb(i, 6) = temp->y;
		}
		else {
			nb(i, 0) = 0; nb(i, 1) = 0; nb(i, 2) = 1; nb(i, 3) = -1 * temp->y; nb(i, 4) = temp->x; nb(i, 5) = 0; nb(i, 6) = temp->z;
			temp++;
		}
	}
	MatrixXd nematrix;
	nematrix = nb * x+mol;
	cout << "new\n" << nematrix << endl;
	return 0;
}