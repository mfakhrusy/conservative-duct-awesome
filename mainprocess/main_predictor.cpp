#include "../global.hpp"
#include "main_predictor.hpp"

//outflow boundary condition
Variables Main_Predictor::bc_outflow_predictor(Parameters pars, Variables vars) {

	//local pars
	int max_node		=	pars.max_node;
	double gamma		=	pars.gamma;
	double pressure_exit	=	pars.pressure_exit;

	//local vars
	std::vector<double> &U_1	=	vars.U_1;
	std::vector<double> &U_2	=	vars.U_2;
	std::vector<double> &U_3	=	vars.U_3;
	std::vector<double> &v		=	vars.v;
	std::vector<double> area	=	vars.area;

	//BC for U_1
	U_1[max_node - 1]	=	2*U_1[max_node - 2] - U_1[max_node - 3];

	//BC for U_2
	U_2[max_node - 1]	=	2*U_2[max_node - 2] - U_2[max_node - 3];

	//BC for v
	v[max_node - 1]		=	U_2[max_node - 1]/U_1[max_node - 1];

	//BC for U_3
	U_3[max_node - 1]	=	(pressure_exit*area[max_node - 1])/(gamma - 1) + 0.5*gamma*U_2[max_node - 1]*v[max_node - 1];

	return vars;
}

//calculate F_1
std::vector<double> Main_Predictor::calc_F_1_predictor(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;

	//local vars
	std::vector<double> U_2		=	vars.U_2;

	//processed variable
	std::vector<double> F_1(max_node);

	//process F_1
	for (auto i = 0; i < max_node; i++) {
		
		F_1[i]	=	U_2[i];
	}

	return F_1;
}

//calculate F_2
std::vector<double> Main_Predictor::calc_F_2_predictor(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> U_2		=	vars.U_2;
	std::vector<double> U_3		=	vars.U_3;

	//processed variable
	std::vector<double> F_2(max_node);

	//process F_2
	for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	pow(U_2[i],2)/U_1[i];
		double temp_2	=	U_3[i] - 0.5*gamma*temp_1;

		F_2[i]		=	temp_1 + ((gamma - 1)/(gamma))*temp_2;
	}

	return F_2;
}

//calculate F_3
std::vector<double> Main_Predictor::calc_F_3_predictor(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> U_2		=	vars.U_2;
	std::vector<double> U_3		=	vars.U_3;

	//processed variable
	std::vector<double> F_3(max_node);

	//process F_3
	for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	U_2[i]*U_3[i]/U_1[i];
		double temp_2	=	pow(U_2[i],3)/pow(U_1[i],2);

		F_3[i]		=	gamma*temp_1 - 0.5*gamma*(gamma - 1)*temp_2;
	}

	return F_3;
}

//calculate J_2
std::vector<double> Main_Predictor::calc_J_2_predictor(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> area	=	vars.area;
	std::vector<double> x		=	vars.x;
	std::vector<double> rho		=	vars.rho;
	std::vector<double> T		=	vars.T;
	//processed variable
	std::vector<double> J_2(max_node);

	//process J_2
	for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	(area[i+1] - area[i])/(x[i+1] - x[i]);
		J_2[i]		=	(1/gamma)*rho[i]*T[i]*temp_1;
	}

	return J_2;
}

