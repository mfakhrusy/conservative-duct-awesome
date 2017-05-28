#include "../global.hpp"
#include "main_initial.hpp"

//calculation of sound speed
std::vector<double> Main_Initial::calc_sound_speed(Parameters pars, std::vector<double> T) {

	//declare local pars
	const int max_node	=	pars.max_node;
	double gas_constant	=	pars.gas_constant;
	double gamma		=	pars.gamma;

	//declare processed variables
	std::vector<double> sound_speed(max_node);

	for (auto i = 0; i < max_node; i++) {
		
	//for nondimensional:
		sound_speed[i] = sqrt(T[i]);
	}

	return sound_speed;
}

//calculation of delta_t
double Main_Initial::calc_delta_t(Parameters pars, Variables vars) {

	//declare local vars
	const int max_node			=	pars.max_node;
	double courant_number		=	pars.courant_number;
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> sound_speed	=	vars.sound_speed;
	std::vector<double> v		=	vars.v;

	//declare processed variables
	double delta_t = 1;
	double temp_delta_t = 1;

	//looping start
	for (auto i = 0; i < delta_x.size(); i++) {
		temp_delta_t		=	courant_number*(delta_x[i]/(sound_speed[i] + v[i]));

		if (temp_delta_t < delta_t) {
			delta_t = temp_delta_t;
		}
	}

	return delta_t;
}
