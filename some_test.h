#include <iostream>
#include <vector>
#include <algorithm>
#pragma once

using namespace std;

class some_test
{
	struct Single_Weed {
		vector<double> coord = { 0 };
		double f = numeric_limits<double>::max ();
		int seeds = 0;
	};

	
	public:
		some_test (double(*funk)(vector<double>),
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
			srand (time (0));
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

			best_coordinates.resize (coordinates);

			weeds.resize (total_weeds);

			for (int i = 0; i < number_weeds; i++)
			{
				weeds[i].coord.resize (coordinates);
				for (int j = 0; j < coordinates; j++) {
					weeds[i].coord[j] = RandDouble (teor_x + max_dispersion, teor_x - max_dispersion);
				}
				weeds[i].f = funk (weeds[i].coord);
				if (weeds[i].f < current_best_f) {
					current_best_f = weeds[i].f;
				}
				if (weeds[i].f > current_worst_f) {
					current_worst_f = weeds[i].f;
				}
			}
			for (int i = number_weeds; i < total_weeds; i++) {
				weeds[i].coord.resize (coordinates);
			}

			int current_number_seeds = 0;

			//начальное распределение количества семян
			for (int i = 0; i < number_weeds; i++) {
				weeds[i].seeds = max_number_seeds;
			}
			Selection ();
			Work (funk);
		}
	private:
		vector<Single_Weed> weeds; //weeds
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
		double teor_x = 1;  //WARNING-------------WARNING-----------WARNING-----------

		void Work (double(*funk)(vector<double>)) {
			while (current_iter < max_iteration) {
				Reproduction (funk);
				Selection ();
				current_iter++;
			}
			for (int i = 0; i < coordinates; i++) {
				cout << best_coordinates[i] << "  ";
			}
			cout << endl << best_f << endl;
		}
		void Reproduction (double(*funk)(vector<double>)) {
			int current_number_seeds = 0;

			//начальное распределение количества семян
			for (int i = 0; i < number_weeds; i++) {
				weeds[i].seeds = round ((max_number_seeds * (current_best_f - weeds[i].f) + min_number_seeds * (weeds[i].f - current_worst_f))
					/ (current_best_f - current_worst_f));
				current_number_seeds += weeds[i].seeds;

			}

			double dispertion = pow ((max_iteration - current_iter) / max_iteration, 2) * (max_dispersion - min_dispersion) + min_dispersion;

			//выращивание семян
			int current_seed = number_weeds;
			for (int i = 0; i < number_weeds; i++) {
				for (int j = 0; j < weeds[i].seeds; j++) {
					for (int k = 0; k < coordinates; k++) {
						double tmp = RandDouble (weeds[i].coord[k] + dispertion, weeds[i].coord[k] - dispertion);
						if (tmp > range_max) {
							tmp = range_max;
						}
						else if (tmp < range_min) {
							tmp = range_min;
						}
						weeds[current_seed].coord[k] = tmp;

					}

					weeds[current_seed].f = funk (weeds[current_seed].coord);
					current_seed++;
				}
			}
		}
		void Selection () {
			sort (weeds.begin (), weeds.end (),
				[](Single_Weed a, Single_Weed b) {
					return a.f < b.f;
				});
			current_best_f = weeds[0].f;
			current_worst_f = weeds[number_weeds - 1].f;
			//cout << "Итерация" << current_best_f << endl;
			if (current_best_f < best_f) {
				best_f = current_best_f;
				best_coordinates = weeds[0].coord;
			}
		};

	double RandDouble (double mx, double mn) {
		return mn + (mx - mn) * (rand () % RAND_MAX) / RAND_MAX;
	}

	public: static double gen (double mn, double mx) { // не используйте min max это функции из cmath
		double dx = mx - mn;
		double accur = 1e6;
		int fmx = dx * accur;
		double t = rand () % fmx;
		t /= accur;
		return mn + t;
	}
};


