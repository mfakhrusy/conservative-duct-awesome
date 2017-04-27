#include "../global.hpp"
#include "main_predictor.hpp"

//outflow boundary condition
Variables Main_Predictor::bc_outflow_predictor(Parameters pars, Variables vars) {

	//local pars
	const int max_node		=	pars.max_node;
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
	const int max_node	=	pars.max_node;

	//local vars
	std::vector<double> U_2		=	vars.U_2;

	//processed variable
	std::vector<double> F_1(max_node);

	//process F_1
	for (auto i = 1; i < max_node; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		F_1[i]	=	U_2[i];
	}

	return F_1;
}

//calculate F_2
std::vector<double> Main_Predictor::calc_F_2_predictor(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> U_2		=	vars.U_2;
	std::vector<double> U_3		=	vars.U_3;

	//processed variable
	std::vector<double> F_2(max_node);

	//process F_2
	for (auto i = 1; i < max_node; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	pow(U_2[i],2)/U_1[i];
		double temp_2	=	U_3[i] - 0.5*gamma*temp_1;

		F_2[i]		=	temp_1 + ((gamma - 1)/(gamma))*temp_2;
	}

	return F_2;
}

//calculate F_3
std::vector<double> Main_Predictor::calc_F_3_predictor(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> U_2		=	vars.U_2;
	std::vector<double> U_3		=	vars.U_3;

	//processed variable
	std::vector<double> F_3(max_node);

	//process F_3
	for (auto i = 1; i < max_node; i++) {
//	for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	U_2[i]*U_3[i]/U_1[i];
		double temp_2	=	pow(U_2[i],3)/pow(U_1[i],2);

		F_3[i]		=	gamma*temp_1 - 0.5*gamma*(gamma - 1)*temp_2;
	}

	return F_3;
}

//calculate J_2
std::vector<double> Main_Predictor::calc_J_2(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> area	=	vars.area;
	std::vector<double> x		=	vars.x;
	std::vector<double> rho		=	vars.rho;
	std::vector<double> T		=	vars.T;
	//processed variable
	std::vector<double> J_2(max_node);

	//process J_2
	for (auto i = 1; i < max_node - 1; i++) {
//	for (auto i = 0; i < max_node - 1; i++) {
		
		double temp_1	=	(area[i+1] - area[i])/(x[i+1] - x[i]);
		J_2[i]		=	(1/gamma)*rho[i]*T[i]*temp_1;
	}

	return J_2;
}

//calculate dU_1_dt_predictor
std::vector<double> Main_Predictor::calc_dU_1_dt_predictor(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	
	//local vars
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> F_1		=	vars.F_1;

	//processed variable
	std::vector<double> dU_1_dt_predictor(max_node);

	//process dU_1_dt_predictor
	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node - 1; i++) {
		dU_1_dt_predictor[i]	=	-1*((F_1[i+1] - F_1[i])/delta_x[i]);
	}

	return dU_1_dt_predictor;
}

//calculate dU_2_dt_predictor
std::vector<double> Main_Predictor::calc_dU_2_dt_predictor(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	
	//local vars
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> F_2		=	vars.F_2;
	std::vector<double> J_2		=	vars.J_2;

	//processed variable
	std::vector<double> dU_2_dt_predictor(max_node);

	//process dU_2_dt_predictor
	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node - 1; i++) {
		dU_2_dt_predictor[i]	=	-1*((F_2[i+1] - F_2[i])/delta_x[i]) + J_2[i];
	}

	return dU_2_dt_predictor;
}

//calculate dU_3_dt_predictor
std::vector<double> Main_Predictor::calc_dU_3_dt_predictor(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	
	//local vars
	std::vector<double> delta_x	=	vars.delta_x;
	std::vector<double> F_3		=	vars.F_3;

	//processed variable
	std::vector<double> dU_3_dt_predictor(max_node);

	//process dU_3_dt_predictor
	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node - 1; i++) {
		dU_3_dt_predictor[i]	=	-1*((F_3[i+1] - F_3[i])/delta_x[i]);
	}

	return dU_3_dt_predictor;
}

//calculate U_1 at n+1
std::vector<double> Main_Predictor::calc_new_U_1(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	const double delta_t		=	vars.delta_t;
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> dU_1_dt	=	vars.dU_1_dt;
	std::vector<double> S_1		=	vars.S_1;

	//processed variable
	std::vector<double> new_U_1(max_node);

	//process U_1
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		new_U_1[i]	=	U_1[i] + dU_1_dt[i]*delta_t + S_1[i];
	}

	return new_U_1;

}

//calculate U_2 at n+1
std::vector<double> Main_Predictor::calc_new_U_2(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	const double delta_t		=	vars.delta_t;
	std::vector<double> U_2		=	vars.U_2;
	std::vector<double> dU_2_dt	=	vars.dU_2_dt;
	std::vector<double> S_2		=	vars.S_2;

	//processed variable
	std::vector<double> new_U_2(max_node);

	//process U_2
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		new_U_2[i]	=	U_2[i] + dU_2_dt[i]*delta_t + S_2[i];
	}

	return new_U_2;

}

//calculate U_3 at n+1
std::vector<double> Main_Predictor::calc_new_U_3(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	const double delta_t			=	vars.delta_t;
	std::vector<double> U_3		=	vars.U_3;
	std::vector<double> dU_3_dt	=	vars.dU_3_dt;
	std::vector<double> S_3		=	vars.S_3;

	//processed variable
	std::vector<double> new_U_3(max_node);

	//process U_3
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		new_U_3[i]	=	U_3[i] + dU_3_dt[i]*delta_t + S_3[i];
	}

	return new_U_3;

}

//calculate new rho
std::vector<double> Main_Predictor::calc_new_rho(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> area	=	vars.area;

	//processed variable
	std::vector<double> new_rho(max_node);

	//process rho
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		new_rho[i]	=	U_1[i]/area[i];
	}

	return new_rho;

}

//calculate new rho
std::vector<double> Main_Predictor::calc_new_T(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	double gamma	=	pars.gamma;

	//local vars
	std::vector<double> U_1		=	vars.U_1;
	std::vector<double> U_2		=	vars.U_2;
	std::vector<double> U_3		=	vars.U_3;

	//processed variable
	std::vector<double> new_T(max_node);

	//process T
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	U_3[i]/U_1[i];
		double temp_2	=	pow((U_2[i]/U_1[i]),2);
		
		new_T[i]	=	(gamma - 1)*(temp_1 - 0.5*gamma*temp_2);
	}

	return new_T;

}

//smoothing function
std::vector<double> Main_Predictor::calc_S_1(Parameters pars, Variables vars) {

	//local pars
	const int max_node		=	pars.max_node;
	const double smoothing_constant	=	pars.smoothing_constant;

	//local vars
	std::vector<double> p	=	vars.p;
	std::vector<double> U_1	=	vars.U_1;

	//processed variable
	std::vector<double> S_1(max_node);

	for (auto i = 1; i < max_node-1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	std::abs(p[i+1] - 2*p[i] + p[i-1])*smoothing_constant;
		double temp_2	=	p[i+1] + 2*p[i] + p[i-1];
		double temp_3	=	U_1[i+1] - 2*U_1[i] + U_1[i-1];	
		
//		S_1[i]		=	(temp_1/temp_2)*temp_3;
		S_1[i]		=	0;
	}

	return S_1;
}

//smoothing function
std::vector<double> Main_Predictor::calc_S_2(Parameters pars, Variables vars) {

	//local pars
	const int max_node		=	pars.max_node;
	const double smoothing_constant	=	pars.smoothing_constant;

	//local vars
	std::vector<double> p	=	vars.p;
	std::vector<double> U_2	=	vars.U_2;

	//processed variable
	std::vector<double> S_2(max_node);

	for (auto i = 1; i < max_node-1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	std::abs(p[i+1] - 2*p[i] + p[i-1])*smoothing_constant;
		double temp_2	=	p[i+1] + 2*p[i] + p[i-1];
		double temp_3	=	U_2[i+1] - 2*U_2[i] + U_2[i-1];	
		
//		S_2[i]		=	(temp_1/temp_2)*temp_3;
		S_2[i]		=	0;
	}

	return S_2;
}

//smoothing function
std::vector<double> Main_Predictor::calc_S_3(Parameters pars, Variables vars) {

	//local pars
	const int max_node		=	pars.max_node;
	const double smoothing_constant	=	pars.smoothing_constant;

	//local vars
	std::vector<double> p	=	vars.p;
	std::vector<double> U_3	=	vars.U_3;

	//processed variable
	std::vector<double> S_3(max_node);

	for (auto i = 1; i < max_node-1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	std::abs(p[i+1] - 2*p[i] + p[i-1])*smoothing_constant;
		double temp_2	=	p[i+1] + 2*p[i] + p[i-1];
		double temp_3	=	U_3[i+1] - 2*U_3[i] + U_3[i-1];	
		
//		S_3[i]		=	(temp_1/temp_2)*temp_3;
		S_3[i]		=	0;
	}

	return S_3;
}
