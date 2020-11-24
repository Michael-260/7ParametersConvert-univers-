#include<Eigen/Dense>
#include"database.h"
using namespace Eigen;

static string OLDDATATXT = "ol_data.txt";
static string NEDATATXT = "ne_data.txt";
static int OLNUMBER = 12;
static int NENUMBER = 7;

int main() {
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

	MatrixXd b(3 * NENUMBER, 7), l(3 * NENUMBER, 1), v, x;
	num = 0;
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
	return 0;
}