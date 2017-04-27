#include "../global.hpp"
#include "main_final.hpp"

//calculate dU_dt_average (time derivative average)
std::vector<double> Main_Final::calc_dU_dt_average(Parameters pars, std::vector<double> dU_dt_predictor, std::vector<double> dU_dt_corrector) {

	//local pars
	const int max_node	=	pars.max_node;

	//processed variable
	std::vector<double> dU_dt_average(max_node);

	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		dU_dt_average[i]	=	0.5*(dU_dt_predictor[i] + dU_dt_corrector[i]);
	}

	return dU_dt_average;
}

//calculate new v
std::vector<double> Main_Final::calc_new_v(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	std::vector<double> U_1	=	vars.U_1;
	std::vector<double> U_2	=	vars.U_2;

	//processed variable
	std::vector<double> v(max_node);

	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		
		v[i]	=	U_2[i]/U_1[i];
	}

	return v;
}

//error calculation
double Main_Final::calc_error(std::vector<double> old_F, std::vector<double> new_F) {

	//get the size
	const int max_node	=	old_F.size();

	//processed variable
	double error_var = 0;

	for (auto i = 0; i < max_node; i++) {
	
		if (old_F[i] != 0) {
			error_var = error_var + std::abs(old_F[i] - new_F[i])/old_F[i];
		} else {
			error_var = error_var;
		}

	}
	
	return error_var;
}

//mach calculation
std::vector<double> Main_Final::calc_mach(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	std::vector<double> v		=	vars.v;
	std::vector<double> sound_speed	=	vars.sound_speed;

	//processed variable
	std::vector<double> mach(max_node);

	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
		
		mach[i]	=	v[i]/sound_speed[i];
	}

	return mach;
}

//pressure calculation
std::vector<double> Main_Final::calc_pressure(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;
	const double gamma	=	pars.gamma;

	//local vars
	std::vector<double> T		=	vars.T;

	//processed variable
	std::vector<double> pressure(max_node);

	double temp	=	gamma/(gamma - 1);
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
	
		pressure[i]	=	pow(T[i], temp);
//		if(std::isnan(pressure[i])) {
//			std::cout << i << " " << pressure[i] << " " << temp << " " << T[i] << " " << pow(T[i],1.1) << std::endl;
//		}
	}

	return pressure;
}


//mass flow calculation
std::vector<double> Main_Final::calc_mass_flow(Parameters pars, Variables vars) {

	//local pars
	const int max_node	=	pars.max_node;

	//local vars
	std::vector<double> v		=	vars.v;
	std::vector<double> rho		=	vars.rho;
	std::vector<double> area	=	vars.area;

	//processed variable
	std::vector<double> mass_flow(max_node);

	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
	
		mass_flow[i]	=	v[i]*rho[i]*area[i];
	}

	return mass_flow;
}

//smoothing function
std::vector<double> Main_Final::calc_S_1_final(Parameters pars, Variables vars, std::vector<double> old_p) {

	//local pars
	const int max_node		=	pars.max_node;
	const double smoothing_constant	=	pars.smoothing_constant;

	//local vars
	std::vector<double> p	=	vars.p;
	std::vector<double> U_1	=	vars.U_1;

	//processed variable
	std::vector<double> S_1(max_node);

	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	std::abs(p[i+1] - 2*p[i] + p[i-1])*smoothing_constant;
		double temp_2	=	old_p[i+1] + 2*old_p[i] + old_p[i-1];
		double temp_3	=	U_1[i+1] - 2*U_1[i] + U_1[i-1];	
		
		//S_1[i]		=	(temp_1/temp_2)*temp_3;
		S_1[i]		=	0;
	}

	return S_1;
}

//smoothing function
std::vector<double> Main_Final::calc_S_2_final(Parameters pars, Variables vars, std::vector<double> old_p) {

	//local pars
	const int max_node		=	pars.max_node;
	const double smoothing_constant	=	pars.smoothing_constant;

	//local vars
	std::vector<double> p	=	vars.p;
	std::vector<double> U_2	=	vars.U_2;

	//processed variable
	std::vector<double> S_2(max_node);

	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	std::abs(p[i+1] - 2*p[i] + p[i-1])*smoothing_constant;
		double temp_2	=	old_p[i+1] + 2*old_p[i] + old_p[i-1];
		double temp_3	=	U_2[i+1] - 2*U_2[i] + U_2[i-1];	
		
		//S_2[i]		=	(temp_1/temp_2)*temp_3;
		S_2[i]		=	0;
//		if (std::isnan(S_2[i])) {
//			std::cout << i << " " << p[i-1] << " " << p[i] << " " << p[i+1] << std::endl;
//		}
	}

	return S_2;
}

//smoothing function
std::vector<double> Main_Final::calc_S_3_final(Parameters pars, Variables vars, std::vector<double> old_p) {

	//local pars
	const int max_node		=	pars.max_node;
	const double smoothing_constant	=	pars.smoothing_constant;

	//local vars
	std::vector<double> p	=	vars.p;
	std::vector<double> U_3	=	vars.U_3;

	//processed variable
	std::vector<double> S_3(max_node);

	for (auto i = 1; i < max_node - 1; i++) {
	//for (auto i = 0; i < max_node; i++) {
		
		double temp_1	=	std::abs(p[i+1] - 2*p[i] + p[i-1])*smoothing_constant;
		double temp_2	=	old_p[i+1] + 2*old_p[i] + old_p[i-1];
		double temp_3	=	U_3[i+1] - 2*U_3[i] + U_3[i-1];	
		
		//S_3[i]		=	(temp_1/temp_2)*temp_3;
		S_3[i]		=	0;
	}

	return S_3;
}

