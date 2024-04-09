#include <iostream>
#include <vector>

using namespace std;

int main ()
{
	std::cout << "Hello World!\n";
}
//import random
//import numpy as np
//
//def sort (x, f) :
//    k = 1
//    while k > 0:
//k = 0
//for i in range (len (f) - 1) :
//    if f[i] > f[i + 1]:
//temp = f[i]
//f[i] = f[i + 1]
//f[i + 1] = temp
//temp = x[i]
//x[i] = x[i + 1]
//x[i + 1] = temp
//k += 1
//
//
//def IWO (func, s0, smax, nmin, nmax, sigma_b, sigma_e, Xmin, Xmax, m, tmax, teoretic_x) :
//    X = []
//    for i in range (s0) : # Блок инициализации
//        xi = []
//        for j in range (len (Xmin)) :
//            xi.append (Xmin[j] + random.random () * (Xmax[j] - Xmin[j]))
//            X.append (xi)
//            f = []
//            for xi in X :
//f.append (func (xi))
//t = 0
//while t <= tmax :
//    n = []  # Блок генерации семян
//    fbest = min (f)
//    fworst = max (f)
//    for fi in f :
//n.append (round (fi * (nmax - nmin) / (fbest - fworst) + (fbest * nmin - fworst * nmax) / (fbest - fworst)))
//Xnew = []
//sigma = (((tmax - t) / tmax) * *m) * (sigma_b - sigma_e) + sigma_e
//for k in range (len (X)) :
//    for i in range (n[k]) :
//        xj = []
//        for j in range (len (X[k])) :
//            xj.append (X[k][j] + np.random.normal (0, sigma))
//            xj = np.clip (xj, Xmin, Xmax)
//            Xnew.append (xj)
//            X = X + Xnew
//
//            f = []  # Блок конкурентного исключения
//            for xi in X :
//f.append (func (xi))
//sort (X, f)
//if len (X) > smax:
//X = X[:smax]
//f = f[:smax]
//t += 1
//if np.linalg.norm (np.array (X[0]) - np.array (teoretic_x)) < 1e-2 * len (teoretic_x) :
//    return[X[0], True, t]
//    # print ("Поколение {}: {} {} {}".format (t, max (f), min (f), np.mean (f)))
//
//    return[X[0], False, tmax]

struct Single_Weed {
	vector<double> coord = { 0 };
	double f = numeric_limits<double>::max ();
	int seeds;
};

class IWO_method {
public:
	IWO_method (double(*funk)(vector<double>),
		const int    coordinates_number,
		const double max_coordinate,
		const double min_coordinate,
		const int    seeds_count,
		const int    weeds_count,
		const int    max_seeds_count,
		const int    min_seeds_count,
		const double dispersion_max,
		const double dispersion_min,
		const int    iteration_max);
private:
	vector<Single_Weed> weeds; //weeds
	vector<Single_Weed> weeds_tmp; //temp weeds
	vector<Single_Weed> seeds; //seeds
	vector<double> best_coordinates; //best coordinates
	double best_f = numeric_limits<double>::max ();           //fitness of the best coordinates
	
	double current_best_f = numeric_limits<double>::max ();
	double current_worst_f = numeric_limits<double>::min ();
	double range_max = 0; //maximum search range
	double range_min = 0; //manimum search range
	int    coordinates = 0;       //Coordinates number
	int    number_seeds = 0;       //Number of seeds
	int    number_weeds = 0;       //Number of weeds
	int    total_weeds = 0;     //Total number of weeds
	int    max_number_seeds = 0;    //Maximum number of seeds
	int    min_number_seeds = 0;    //Minimum number of seeds
	double max_dispersion = 0;     //Maximum dispersion
	double min_dispersion = 0;     //Minimum dispersion
	int    max_iteration = 0;      //Maximum iterations
	int	   current_iter = 0;

	bool Work (double(*funk)(vector<double>));
	void Reproduction (double(*funk)(vector<double>));
	void Selection ();

	//Implementation----------------------------
	IWO_method (double(*funk)(vector<double>),
		const int    coordinates_number,
		const double max_coordinate,
		const double min_coordinate,
		const int    seeds_count,
		const int    weeds_count,
		const int    max_seeds_count,
		const int    min_seeds_count,
		const double dispersion_max,
		const double dispersion_min,
		const int    iteration_max) {

		coordinates = coordinates_number;
		range_max = max_coordinate;
		range_min = min_coordinate;
		number_seeds = seeds_count;
		number_weeds = weeds_count;
		max_number_seeds = max_seeds_count;
		min_number_seeds = min_seeds_count;
		max_dispersion = dispersion_max;
		min_dispersion = dispersion_min;
		max_iteration = iteration_max;

		if (min_number_seeds < 1) min_number_seeds = 1;
		if (number_weeds * min_number_seeds > number_seeds) number_weeds = number_seeds / min_number_seeds;

		total_weeds = number_weeds + number_seeds;

		best_coordinates.resize(coordinates);

		weeds.resize (total_weeds);
		weeds_tmp.resize (total_weeds);
		seeds.resize (number_seeds);

		for (int i = 0; i < number_weeds; i++)
		{
			weeds[i].coord.resize (coordinates);
			weeds_tmp[i].coord.resize (coordinates);
			for (int j = 0; j < coordinates; j++) {
				weeds[i].coord[j] = RandDouble (range_max, range_min);
			}
			weeds[i].f = funk (weeds[i].coord);
			if (weeds[i].f < current_best_f) {
				current_best_f = weeds[i].f;
			}
			if (weeds[i].f > current_worst_f) {
				current_worst_f = weeds[i].f;
			}
			weeds[i].seeds = 0;
		}
		for (int i = 0; i < number_seeds; i++)
		{
			seeds[i].coord.resize (coordinates);
			seeds[i].seeds = 0;
		}
		Work (funk);
	}

	bool Work (double(*funk)(vector<double>)) {
		while (current_iter < max_iteration) {
			Reproduction (funk);
			Selection ();
		}
	}

	void Reproduction (double(*funk)(vector<double>)) {
		int current_number_seeds = 0;

		//начальное распределение количества семян
		for (int i = 0; i < number_weeds; i++) {
			weeds[i].seeds = round((max_number_seeds * (current_best_f - weeds[i].f) + min_number_seeds * (weeds[i].f - current_worst_f))
				/ (current_best_f - current_worst_f));
			current_number_seeds += weeds[i].seeds;
		}

		//добивание количества семян до общего максимума
		int tmp_iter = 0;
		while (current_number_seeds < number_seeds) {
			if (weeds[tmp_iter].seeds < number_seeds) {
				weeds[tmp_iter].seeds++;
				current_number_seeds++;
			}
			tmp_iter++;
			if (tmp_iter == number_weeds) {
				tmp_iter = 0;
			}
		}

		double dispertion = pow ((max_iteration - current_iter) / max_iteration, 2) * (max_dispersion - min_dispersion) + min_dispersion;
		
		//выращивание семян
		int current_seed = number_seeds;
		for (int i = 0; i < number_weeds; i++) {
			for (int j = 1; j <= weeds[i].seeds; j++) {
				for (int k = 0; k < coordinates; k++) {
					weeds[current_seed].coord[k] = RandDouble (weeds[i].coord[k] + dispertion, weeds[i].coord[k] - dispertion);
				}
				weeds[current_seed].f = funk (weeds[current_seed].coord);
				weeds[current_seed].seeds = 0;
				current_seed++;
			}
		}
		

		
	}
	
	void Selection () {

	}
};

double RandDouble (double max, double min) {
	return min + (max - min) * (rand () % RAND_MAX) / RAND_MAX;
}