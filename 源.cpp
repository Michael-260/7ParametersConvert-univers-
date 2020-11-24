#include<Eigen/Dense>
#include"database.h"
using namespace Eigen;

static string OLDDATATXT = "ol_data.txt";
static string NEDATATXT = "ne_data.txt";
static int OLNUMBER = 7;
static int NENUMBER = 12;

int main() {
	point* ol = new point[OLNUMBER];
	point* ne = new point[NENUMBER];
	point* temp = ol;
	read_table(OLDDATATXT, ol, OLNUMBER);
	read_table(NEDATATXT, ne, NENUMBER);

	int num = 0;
	num = OLNUMBER * 3;
	double* olxyz = new double[num];
	num = NENUMBER * 3;
	double* nexyz = new double[num];
	
	//MatrixXd b(OLNUMBER,7), l(3*OLNUMBER,1), v, x;
	MatrixXd molxyz(OLNUMBER,3), mnexyz;
	num = 0;
	for (int i = 0; i < OLNUMBER; i++, temp++) {
		molxyz(i, 0) = temp->x;
		molxyz(i, 1) = temp->y;
		molxyz(i, 2) = temp->z;
	}
	cout << "old:\n" << molxyz << endl;
}