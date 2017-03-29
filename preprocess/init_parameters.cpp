#include "../global.hpp"
#include "init_parameters.hpp"

//constructor
Init_Parameters::Init_Parameters(Parameters &pars, Variables &vars) {

	//local vars
	std::vector<double> &x		=	vars.x;
	std::vector<double> &area	=	vars.area;
	std::vector<double> &delta_x	=	vars.delta_x;

	//local pars
	int &max_node			=	pars.max_node;
	double &duct_length		=	pars.duct_length;

	//read input
	pars	=	read_input();

	//calculate things
	x	=	compute_point_x(max_node, duct_length);
	area	=	compute_profile(max_node, x, duct_length);
	delta_x	=	compute_delta_x(max_node, x);

}

//read input
Parameters Init_Parameters::read_input() {
	
	std::ifstream infile("input/input.dat");
	double value;
	std::string value_title;

	Parameters pars;
	int count = 0;
	while (infile >> value >> value_title) {
		
		count = count + 1;

		switch(count) {
			
			case 1:
				pars.max_node = static_cast<int>(value);
				break;
			case 2:
				pars.max_iter = static_cast<int>(value);
				break;
			case 3:
				pars.error_max = value;
				break;
			case 4:
				pars.duct_length = value;
				break;
			case 5:
				pars.gamma = value;
				break;
			case 6:
				pars.gas_constant = value;
				break;
			case 7:
				pars.courant_number = value;
				break;
			case 8:
				pars.U_2_constant_value = value;
				break;
			default:
				std::cout << "Something wrong here!\n";
		}
	}

	return pars;
}

//compute the x
std::vector<double> Init_Parameters::compute_point_x(int max_node, double duct_length) {
	
	std::vector<double> x(max_node);

	for (auto i = 0; i < max_node; i++) {
		
		x[i] = (static_cast<double>(i)/(static_cast<double>(max_node - 1)))*duct_length;
	
	}

	return x;
}

//compute duct profile (the function is given on another method)
std::vector<double> Init_Parameters::compute_profile(int max_node, std::vector<double> x, double duct_length) {

	std::vector<double> area(max_node);

	for(auto i = 0; i < max_node; i++) {
		
		area[i] = duct_profile_function(x[i], duct_length); 
	}

	return area;

}

//compute delta_x each point
std::vector<double> Init_Parameters::compute_delta_x(int max_node, std::vector<double> x) {

	std::vector<double> delta_x(max_node - 1); //the max index is max_node - 1 because obvious reason

	for (auto i = 0; i < delta_x.size(); i++) {
		
		delta_x[i] = x[i + 1] - x[i];
	}

	return delta_x;
}

//duct profile function
double Init_Parameters::duct_profile_function(double x, double duct_length) {
	
	return 1 + 2.2*pow((x - (0.5*duct_length)),2);
}
