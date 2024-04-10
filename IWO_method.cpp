#include <iostream>
#include <vector>
#include <algorithm>
#include "some_test.h"

using namespace std;

double Grivanka (vector<double> x) {
	double sum = 0;
	double mult = 1;
	for (int i = 1; i <= x.size (); i++) {
		sum += x[i - 1] * x[i - 1];
		mult *= cos (x[i - 1] / sqrt (i));
	}
	return -(1 + sum / 400 - mult);
}

int main ()
{
	/*int low = 0;
	int high = 0;
	int mid = 0;
	for (int i = 0; i < 10000; i++) {
		int tmp = some_test::gen (0, 50);
		if (tmp < 15) {
			low++;
		}
		else if (tmp > 35) {
			high++;
		}
		else {
			mid++;
		}
	}
	cout << low << "  " << mid << "  " << high;*/
	double h = 5.05;
	for (int i = 0; i < 20; i++) {
		cout << i << endl;
		some_test test = some_test (Grivanka, 10, 20, -20, 600, 100, 6, 1, 10, 1.5, 100);
		cout << endl;
		//h -= 0.25;
	}
}
