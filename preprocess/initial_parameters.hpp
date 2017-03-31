#ifndef INITIAL_PARAMETERS_HPP
#define INITIAL_PARAMETERS_HPP
#include <fstream>

class Initial_Parameters {

	Parameters read_input();

	std::vector<double> compute_point_x(int max_node, double duct_length);
	std::vector<double> compute_profile(int max_node, std::vector<double> x, double duct_length);
	std::vector<double> compute_delta_x(int max_node, std::vector<double> x);

	double duct_profile_function(double x, double duct_length);
	public:
		Initial_Parameters(Parameters &pars, Variables &vars);
};

#endif
