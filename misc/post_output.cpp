#include "../global.hpp"
#include "post_output.hpp"
#include <fstream>

void Post_Output::print_vector(std::vector<double> var, std::string var_name) {

	//node
	int max_node = var.size();

	std::ofstream output_file("output_dump/" + var_name + ".log");
	for (auto i = 0; i < max_node; i++) {

		output_file << i << " " << var[i] << std::endl;
	}

	output_file.close();
}

void Post_Output::print_result(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	const double C_x	=	pars.smoothing_constant;
	const double P_e	=	pars.pressure_exit;

	//local vars
	std::vector<double> x			=	vars.x;
	std::vector<double> area		=	vars.area;
	std::vector<double> rho			=	vars.rho;
	std::vector<double> v			=	vars.v;
	std::vector<double> T			=	vars.T;
	std::vector<double> p			=	vars.p;
	std::vector<double> mach		=	vars.mach;
	std::vector<double> mass_flow	=	vars.mass_flow;

	//change C_x and P_e into string
	auto C_x_str	=	std::to_string(C_x);
	auto P_e_str	=	std::to_string(P_e);
	//delete trailing zeros
	C_x_str.erase(C_x_str.find_last_not_of('0') + 1, std::string::npos);
	P_e_str.erase(P_e_str.find_last_not_of('0') + 1, std::string::npos);

	std::ofstream output_file("output/output_Cx" + C_x_str + "_Pe" + P_e_str + ".csv");
	output_file << "n,x,area,density,velocity,temperature,pressure,mach,mass_flow" << std::endl;
	for (auto i = 0; i < max_node; i++) {
		
		output_file << i << ",";
		output_file << x[i] << ",";
		output_file << area[i] << ",";
		output_file << rho[i] << ",";
		output_file << v[i] << ",";
		output_file << T[i] << ",";
		output_file << p[i] << ",";
		output_file << mach[i] << ",";
		output_file << mass_flow[i];
		output_file << std::endl;
	}

	output_file.close();
}
