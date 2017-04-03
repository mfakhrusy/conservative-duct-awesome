#include "../global.hpp"
#include "main_corrector.hpp"

//inflow boundary condition
Variables Main_Corrector::bc_inflow_corrector(Parameters pars, Variables vars) {

	//local pars
	int max_node		=	pars.max_node;
	double gamma		=	pars.gamma;
	double pressure_exit	=	pars.pressure_exit;

	//local vars
	std::vector<double> &rho	=	vars.rho;
	std::vector<double> &T		=	vars.T;
	std::vector<double> &U_1	=	vars.U_1;
	std::vector<double> &U_2	=	vars.U_2;
	std::vector<double> &U_3	=	vars.U_3;
	std::vector<double> &v		=	vars.v;
	std::vector<double> area	=	vars.area;

	//BC for rho
	rho[0]		=	1.0;

	//BC for T
	T[0]		=	1.0;

	//BC for U_1
	U_1[0]		=	rho[0]*area[0];

	//BC for U_2
	U_2[0]		=	2*U_2[1] - U_2[2];

	//BC for v
	v[0]		=	U_2[0]/U_1[0];

	//BC for U_3
	U_3[0]		=	U_1[0]*((T[0]/(gamma - 1)) + (0.5*gamma*pow(v[0],2)));

	return vars;
}

//calculate dU_1_dt_corrector
std::vector<double> Main_Corrector::calc_dU_1_dt_corrector(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;
	
	//local vars
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> F_1		=	vars.F_1;

	//processed variable
	std::vector<double> dU_1_dt_corrector(max_node);

	//process dU_1_dt_corrector
	for (auto i = 1; i < max_node - 1; i++) {
		dU_1_dt_corrector[i]	=	-1*((F_1[i] - F_1[i-1])/delta_x[i]);
	}

	return dU_1_dt_corrector;
}

//calculate dU_2_dt_corrector
std::vector<double> Main_Corrector::calc_dU_2_dt_corrector(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;
	
	//local vars
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> F_2		=	vars.F_2;
	std::vector<double> J_2		=	vars.J_2;

	//processed variable
	std::vector<double> dU_2_dt_corrector(max_node);

	//process dU_2_dt_corrector
	for (auto i = 1; i < max_node - 1; i++) {
		dU_2_dt_corrector[i]	=	-1*((F_2[i] - F_2[i-1])/delta_x[i]) + J_2[i];
	}

	return dU_2_dt_corrector;
}

//calculate dU_3_dt_corrector
std::vector<double> Main_Corrector::calc_dU_3_dt_corrector(Parameters pars, Variables vars) {

	//local pars
	int max_node	=	pars.max_node;
	
	//local vars
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> F_3		=	vars.F_3;

	//processed variable
	std::vector<double> dU_3_dt_corrector(max_node);

	//process dU_3_dt_corrector
	for (auto i = 1; i < max_node - 1; i++) {
		dU_3_dt_corrector[i]	=	-1*((F_3[i] - F_3[i-1])/delta_x[i]);
	}

	return dU_3_dt_corrector;
}
