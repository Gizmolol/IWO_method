#include <iostream>
#include <vector>

using namespace std;

int main ()
{
	std::cout << "Hello World!\n";
}

//----------STRUCTURES-----------

struct S_Weed
{
	vector<double> coordinates;
	double f;
	int seeds;    //number of seeds
};


struct S_WeedFitness
{
	double start;
	double end;
};
//-------------------------------

class C_AO_IWO
{
public:
	vector<double> range_max; //maximum search range
	vector<double> range_min; //manimum search range
	vector<double> range_step; //step search
	vector<S_Weed> weeds; //weeds
	vector<S_Weed> weeds_tmp; //temp weeds
	vector<S_Weed> seeds; //seeds
	vector<double> best_coordinates; //best coordinates
	double best_f;           //fitness of the best coordinates

	void Init (const int    coordinates_number,      //Number of coordinates
		const int    seeds_count,      //Number of seeds
		const int    weeds_count,      //Number of weeds
		const int    max_seeds_count,   //Maximum number of seeds per weed
		const int    min_seeds_count,   //Minimum number of seeds per weed
		const double dispersion_max,    //Maximum dispersion
		const double dispersion_min,    //Minimum dispersion
		const int    iteration_max);    //Maximum iterations

	void Sowing (int iter);
	void Germination ();

private: 
	void   Sorting ();
	double Limits_correction (double in, double in_min, double in_max, double step);
	double Random_number (double min, double max);
	double Scale (double in, double in_min, double in_max, double out_min, double out_max, bool revers);

	vector<double> vec;
	vector<int> ind;
	vector<double> val;
	vector<S_WeedFitness> weeds_fitness;
	bool   sowing;            //Sowing
	int    coordinates;       //Coordinates number
	int    number_seeds;       //Number of seeds
	int    number_weeds;       //Number of weeds
	int    total_weeds;     //Total number of weeds
	int    max_number_seeds;    //Maximum number of seeds
	int    min_number_seeds;    //Minimum number of seeds
	double max_dispersion;     //Maximum dispersion
	double min_dispersion;     //Minimum dispersion
	int    max_iteration;      //Maximum iterations
};


void C_AO_IWO::Init (const int    coordinates_number,      //Number of coordinates
	const int    seeds_count,      //Number of seeds
	const int    weeds_count,      //Number of weeds
	const int    max_seeds_count,   //Maximum number of seeds per weed
	const int    min_seeds_count,   //Minimum number of seeds per weed
	const double dispersion_max,    //Maximum dispersion
	const double dispersion_min,    //Minimum dispersion
	const int    iteration_max)     //Maximum iterations
{
	srand(time(0));
	best_f = -numeric_limits<double>::max ();

	coordinates = coordinates_number;
	number_seeds = seeds_count;
	number_weeds = weeds_count;
	max_number_seeds = max_seeds_count;
	min_number_seeds = min_seeds_count;
	max_dispersion = dispersion_max;
	min_dispersion = dispersion_min;
	max_iteration = iteration_max;


	if (min_number_seeds < 1) min_number_seeds = 1;
	if (number_weeds * min_number_seeds > number_seeds) number_weeds = number_seeds / min_number_seeds;
	else number_weeds = weeds_count;

	total_weeds = number_weeds + number_seeds;

	range_max.resize(coordinates);
	range_min.resize (coordinates);
	range_step.resize (coordinates);
	vec.resize (coordinates);
	best_coordinates.resize (coordinates);

	weeds.resize(total_weeds);
	weeds_tmp.resize(total_weeds);
	seeds.resize(number_seeds);

	for (int i = 0; i < number_weeds; i++)
	{
		weeds[i].coordinates.resize(coordinates);
		weeds_tmp[i].coordinates.resize(coordinates);
		weeds[i].f = -numeric_limits<double>::max ();
		weeds[i].seeds = 0;
	}
	for (int i = 0; i < number_seeds; i++)
	{
		seeds[i].coordinates.resize(coordinates);
		seeds[i].seeds = 0;
	}

	ind.resize(total_weeds);
	val.resize(total_weeds);

	weeds_fitness.resize(number_weeds);


	//the first sowing of seeds
	
	best_f = -numeric_limits<double>::max ();

	for (int s = 0; s < number_seeds; s++)
	{
		for (int c = 0; c < coordinates; c++)
		{
			seeds[s].coordinates[c] = Random_number (range_min[c], range_max[c]);
			seeds[s].coordinates[c] = Limits_correction (seeds[s].coordinates[c], range_min[c], range_max[c], range_step[c]);

			vec[c] = range_max[c] - range_min[c];
		}

		seeds[s].f = -numeric_limits<double>::max ();
		seeds[s].seeds = 0;
	}
	return;
	
}

double C_AO_IWO::Random_number (double min, double max) {
	return min + (max - min) * (rand() % RAND_MAX) / RAND_MAX;
}

double C_AO_IWO::Limits_correction (double in, double in_min, double in_max, double step)
{
	if (in <= in_min)
		return (in_min);
	if (in >= in_max)
		return (in_max);
	if (step == 0.0) 
		return (in);
	else 
		return (in_min + step * round((in - in_min) / step));
}

//guaranteed sowing of seeds by each weed-------------------------------------
int    pos = 0;
double r = 0.0;
double dispersion = ((max_iteration - iter) / (double)max_iteration) * (max_dispersion - min_dispersion) + min_dispersion;

for (int w = 0; w < number_weeds; w++)
{
	weeds[w].s = 0;

	for (int s = 0; s < min_number_seeds; s++)
	{
		for (int c = 0; c < coordinates; c++)
		{
			r = Random_number (-1.0, 1.0);
			r = r * r * r;

			seeds[pos].c[c] = weeds[w].c[c] + r * vec[c] * dispersion;
			seeds[pos].c[c] = Limits_correction (seeds[pos].c[c], range_min[c], range_max[c], range_step[c]);
		}

		pos++;
		weeds[w].s++;
	}
}

//============================================================================
//sowing seeds in proportion to the fitness of weeds--------------------------

//the distribution of the probability field is proportional to the fitness of weeds
weeds_fitness[0].start = weeds[0].f;
weeds_fitness[0].end = weeds_fitness[0].start + (weeds[0].f - weeds[number_weeds - 1].f);

for (int f = 1; f < number_weeds; f++)
{
	if (f != number_weeds - 1)
	{
		weeds_fitness[f].start = weeds_fitness[f - 1].end;
		weeds_fitness[f].end = weeds_fitness[f].start + (weeds[f].f - weeds[number_weeds - 1].f);
	}
	else
	{
		weeds_fitness[f].start = weeds_fitness[f - 1].end;
		weeds_fitness[f].end = weeds_fitness[f].start + (weeds[f - 1].f - weeds[f].f) * 0.1;
	}
}

bool seedingLimit = false;
int  weedsPos = 0;

for (int s = pos; s < number_seeds; s++)
{
	r = Random_number (weeds_fitness[0].start, weeds_fitness[number_weeds - 1].end);

	for (int f = 0; f < number_weeds; f++)
	{
		if (weeds_fitness[f].start <= r && r < weeds_fitness[f].end)
		{
			weedsPos = f;
			break;
		}
	}

	if (weeds[weedsPos].s >= max_number_seeds)
	{
		seedingLimit = false;
		while (!seedingLimit)
		{
			weedsPos++;
			if (weedsPos >= number_weeds)
			{
				weedsPos = 0;
				seedingLimit = true;
			}
			else
			{
				if (weeds[weedsPos].s < max_number_seeds)
				{
					seedingLimit = true;
				}
			}
		}
	}

	for (int c = 0; c < coordinates; c++)
	{
		r = Random_number (-1.0, 1.0);
		r = r * r * r;

		seeds[s].c[c] = weeds[weedsPos].c[c] + r * vec[c] * dispersion;
		seeds[s].c[c] = Limits_correction (seeds[s].c[c], range_min[c], range_max[c], range_step[c]);
	}

	seeds[s].s = 0;
	weeds[weedsPos].s++;
}

//——————————————————————————————————————————————————————————————————————————————
void C_AO_IWO::Germination ()
{
	for (int s = 0; s < number_seeds; s++)
	{
		weeds[number_weeds + s] = seeds[s];
	}

	Sorting ();

	if (weeds[0].f > best_f) best_f = weeds[0].f;
}