#include <iostream>
#include <vector>
#include <algorithm>
#include "Method.h"

using namespace std;

int work_time = 0;
int call_counter = 0;
int iteration_real = 0;
double average_best = 0;
double N = 10;

double Grivanka (vector<double> x) {
	double sum = 0;
	double mult = 1;
	for (int i = 1; i <= x.size (); i++) {
		sum += x[i - 1] * x[i - 1];
		mult *= cos (x[i - 1] / sqrt (i));
	}
	call_counter++;
	return 1 + sum / 400 - mult;
}

void tests (int size1, double maximal1, double minimal1, int max_first_seeds1, int max_weeds1, int max_seed1, int min_seed1, double max_disp1, double min_disp1, int max_iter1) {
	for (int i = 0; i < N; i++) {
		Method test = Method (Grivanka, size1, maximal1, minimal1, max_first_seeds1, max_weeds1, max_seed1, min_seed1, max_disp1, min_disp1, max_iter1);
	}
	cout << size1 << " " << maximal1 << " " << minimal1 << " " << max_first_seeds1 << " " << max_weeds1 << " " << max_seed1 << " " << min_seed1 << " " << max_disp1 << " " << min_disp1 << " " << max_iter1 << endl;
	cout << work_time / N << "  " << call_counter / N << "  " << iteration_real / N << "  " << average_best / N;
	work_time = 0;
	call_counter = 0;
	iteration_real = 0;
	average_best = 0;
	cout << endl << endl;
}

int main ()
{
	int f_size = 5;
	double maximal = 20;
	double minimal = -20;
	int max_first_seeds = 500;
	int max_weeds = 100;
	int max_seed = 5;
	int min_seed = 1;
	double max_disp = 10;
	double min_disp = 0.1;
	int max_iter = 100;
	//идеальный случай
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	 
	//размер целевой функции
	tests (1, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (3, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (10, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (20, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (30, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);

	//границы
	tests (f_size, 5, -5, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, 10, -10, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, 15, -15, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, 30, -30, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, 50, -50, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);

	//кол-во начальной популяции
	tests (f_size, maximal, minimal, 300, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, 600, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, 800, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, 1000, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, 1500, max_weeds, max_seed, min_seed, max_disp, min_disp, max_iter);

	//кол-во растений
	tests (f_size, maximal, minimal, max_first_seeds, 1, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, 10, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, 50, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, 200, max_seed, min_seed, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, 500, max_seed, min_seed, max_disp, min_disp, max_iter);

	//соотношение семян у одного растения
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, 1, 1, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, 2, 1, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, 6, 1, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, 10, 1, max_disp, min_disp, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, 15, 1, max_disp, min_disp, max_iter);

	//Соотношение дисперсий при минимальной дисперсии 0.1
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 0.3, 0.1, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 1, 0.1, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 3, 0.1, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 7, 0.1, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 10, 0.1, max_iter);

	//Соотношение дисперсий при максимальной дисперсии 10
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 10, 3.33, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 10, 1, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 10, 0.33, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 10, 0.142, max_iter);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, 10, 0.01, max_iter);

	//количество итераций........
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, 1);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, 10);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, 500);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, 700);
	tests (f_size, maximal, minimal, max_first_seeds, max_weeds, max_seed, min_seed, max_disp, min_disp, 1000);
}
