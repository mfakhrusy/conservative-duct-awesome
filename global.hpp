#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <iostream>
#include <cmath>
#include <vector>

struct Variables {
	std::vector<double> x;		//length
	std::vector<double> area;	//area of duct
	std::vector<double> rho;	//density
	std::vector<double> v;		//velocity
	std::vector<double> T;		//temperature
	std::vector<double> p;		//pressure
	std::vector<double> mach;	//mach number
	std::vector<double> mass_flow;	//mass flow rate
	
	//u1 u2 u3
	std::vector<double> U_1;
	std::vector<double> U_2;
	std::vector<double> U_3;

	//f1 f2 f3
	std::vector<double> F_1;
	std::vector<double> F_2;
	std::vector<double> F_3;

	std::vector<double> sound_speed;		//speed of sound

	//delta x and delta t
	std::vector<double> delta_x;	//use vector in case delta_x is different each node
	double delta_t;
};

struct Parameters {
	int max_node;
	int max_iter;
	double duct_length;
	double error_max;
	double gamma;
	double gas_constant;
	double courant_number;
	double U_2_constant_value;
	double pressure_exit;
};

#endif
