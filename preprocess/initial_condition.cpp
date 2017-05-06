#include "../global.hpp"
#include "initial_condition.hpp"

//constructor
Initial_Condition::Initial_Condition(Parameters pars, Variables &vars) {

	//local vars
	std::vector<double> &rho	=	vars.rho;
	std::vector<double> &T		=	vars.T;
	std::vector<double> &v		=	vars.v;
	std::vector<double> &p		=	vars.p;
	std::vector<double> &U_1	=	vars.U_1;
	std::vector<double> &U_2	=	vars.U_2;
	std::vector<double> &U_3	=	vars.U_3;

	//computation of initial conditions
//	rho	=	calc_initial_condition_rho(pars, vars);
//	T	=	calc_initial_condition_T(pars, vars);
	rho	=	calc_initial_condition_rho_2(pars, vars);
	T	=	calc_initial_condition_T_2(pars, vars);
	v	=	calc_initial_condition_v(pars, vars);
	p	=	calc_initial_condition_p(pars, vars);
	U_1	=	calc_initial_condition_U_1(pars, vars);
	U_2	=	calc_initial_condition_U_2(pars, vars);
	U_3	=	calc_initial_condition_U_3(pars, vars);
}

//initial condition for rho
std::vector<double> Initial_Condition::calc_initial_condition_rho(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node		=	pars.max_node;
	double duct_length	=	pars.duct_length;
	std::vector<double> x	=	vars.x;

	//local boundaries
	double limit_0	=	duct_length - duct_length;
	double limit_1	=	duct_length/6;			
	double limit_2	=	duct_length/2;
	double limit_3	=	duct_length*0.7;

	//processed vars
	std::vector<double> rho(max_node);

	//processing
	//for (auto i = 1; i < rho.size() - 1; i++) {
	for (auto i = 0; i < rho.size(); i++) {
		
		if (x[i] >= limit_0 && x[i] <= limit_1) {
			rho[i]	=	1.0;
		} else if (x[i] > limit_1 && x[i] <= limit_2) {
			rho[i]	=	1.0 - 0.366*(x[i] - limit_1);
		} else if (x[i] > limit_2 && x[i] <= limit_3) {
			rho[i]	=	0.634 - 0.702*(x[i] - limit_2);
		} else if (x[i] > limit_3 && x[i] <= duct_length) {
			rho[i]	=	0.5892 + 0.10228*(x[i] - limit_3);
		} else {
			std::cout << "There are something wrong in calc_initial_condition_rho!\n";
		}
	}

	return rho;
}

//initial condition for T
std::vector<double> Initial_Condition::calc_initial_condition_T(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node		=	pars.max_node;
	double duct_length	=	pars.duct_length;
	std::vector<double> x	=	vars.x;

	//local boundaries
	double limit_0	=	duct_length - duct_length;
	double limit_1	=	duct_length/6;			
	double limit_2	=	duct_length/2;
	double limit_3	=	duct_length*0.7;

	//processed vars
	std::vector<double> T(max_node);

	//processing
	//for (auto i = 1; i < T.size() - 1; i++) {
	for (auto i = 0; i < T.size(); i++) {
		
		if (x[i] >= limit_0 && x[i] <= limit_1) {
			T[i]	=	1.0;
		} else if (x[i] > limit_1 && x[i] <= limit_2) {
			T[i]	=	1.0 - 0.167*(x[i] - limit_1);
		} else if (x[i] > limit_2 && x[i] <= limit_3) {
			T[i]	=	0.833 - 0.4908*(x[i] - limit_2);
		} else if (x[i] > limit_3 && x[i] <= duct_length) {
			T[i]	=	0.93968 + 0.0622*(x[i] - limit_3);
		} else {
			std::cout << "There are something wrong in calc_initial_condition_T!\n";
		}
	}

	return T;
}

//initial condition for v
std::vector<double> Initial_Condition::calc_initial_condition_v(Parameters pars, Variables vars) {
	
	//local vars and pars
	const int max_node			=	pars.max_node;
	const double duct_length		=	pars.duct_length;
	const double U_2_constant_value	=	pars.U_2_constant_value;

	std::vector<double> rho		=	vars.rho;
	std::vector<double> area	=	vars.area;

	//processed vars
	std::vector<double> v(max_node);

	//processing
	//for (auto i = 1; i < v.size() - 1; i++) {
	for (auto i = 0; i < v.size(); i++) {

		v[i]	=	U_2_constant_value/(rho[i]*area[i]);
	}

	return v;
}

//initial condition for pressure
std::vector<double> Initial_Condition::calc_initial_condition_p(Parameters pars, Variables vars) {

	//local vars and pars
	const int max_node	=	pars.max_node;
	const double gamma	=	pars.gamma;

	std::vector<double> T	=	vars.T;

	//processed variable
	std::vector<double> pressure(max_node);

	const double temp	=	gamma/(gamma - 1);
	//for (auto i = 1; i < max_node - 1; i++) {
	for (auto i = 0; i < max_node; i++) {
	
		pressure[i]	=	pow(T[i], temp);
	}

	return pressure;

}
//initial condition for U_1
std::vector<double> Initial_Condition::calc_initial_condition_U_1(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node			=	pars.max_node;
	double duct_length		=	pars.duct_length;

	std::vector<double> rho		=	vars.rho;
	std::vector<double> area	=	vars.area;

	//processed vars
	std::vector<double> U_1(max_node);

	//processing
	//for (auto i = 1; i < U_1.size() - 1; i++) {
	for (auto i = 0; i < U_1.size(); i++) {
		U_1[i]	=	rho[i]*area[i];
	}

	return U_1;
}

//initial condition for U_2
std::vector<double> Initial_Condition::calc_initial_condition_U_2(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node			=	pars.max_node;
	double duct_length		=	pars.duct_length;

	std::vector<double> rho		=	vars.rho;
	std::vector<double> area	=	vars.area;
	std::vector<double> v		=	vars.v;
	
	//processed vars
	std::vector<double> U_2(max_node);

	//processing
	//for (auto i = 1; i < U_2.size() - 1; i++) {
	for (auto i = 0; i < U_2.size(); i++) {
		U_2[i]	=	rho[i]*area[i]*v[i];
	}

	return U_2;
}

//initial condition for U_3
std::vector<double> Initial_Condition::calc_initial_condition_U_3(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node			=	pars.max_node;
	double duct_length		=	pars.duct_length;
	double gamma			=	pars.gamma;

	std::vector<double> rho		=	vars.rho;
	std::vector<double> area	=	vars.area;
	std::vector<double> v		=	vars.v;
	std::vector<double> T		=	vars.T;

	//processed vars
	std::vector<double> U_3(max_node);

	//processing
	for (auto i = 0; i < U_3.size(); i++) {
		double temp_1	=	T[i]/(gamma - 1);
		double temp_2	=	0.5*gamma*pow(v[i],2);
		U_3[i]		=	rho[i]*area[i]*(temp_1 + temp_2);
	}

	return U_3;
}

//FOR CHECKING PURPOSE

//initial condition for rho_v2
std::vector<double> Initial_Condition::calc_initial_condition_rho_2(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node		=	pars.max_node;
	double duct_length	=	pars.duct_length;
	std::vector<double> x	=	vars.x;

	//local boundaries
	double limit_0	=	duct_length - duct_length;
	double limit_1	=	duct_length/6;			
	double limit_2	=	duct_length/2;
	double limit_3	=	duct_length*0.7;

	//processed vars
	std::vector<double> rho(max_node);

	//processing
	//for (auto i = 1; i < rho.size() - 1; i++) {
	for (auto i = 0; i < rho.size(); i++) {
		
		if (x[i] >= limit_0 && x[i] <= limit_1) {
			rho[i]	=	1.0;
		} else if (x[i] > limit_1 && x[i] <= limit_2) {
			rho[i]	=	1.0 - 0.366*(x[i] - limit_1);
		} else if (x[i] > limit_2 && x[i] <= duct_length) {
			rho[i]	=	0.634 - 0.3879*(x[i] - limit_2);
		} else {
			std::cout << "There are something wrong in calc_initial_condition_rho!\n";
		}
	}

	return rho;
}

//initial condition for T_v2
std::vector<double> Initial_Condition::calc_initial_condition_T_2(Parameters pars, Variables vars) {
	
	//local vars and pars
	int max_node		=	pars.max_node;
	double duct_length	=	pars.duct_length;
	std::vector<double> x	=	vars.x;

	//local boundaries
	double limit_0	=	duct_length - duct_length;
	double limit_1	=	duct_length/6;			
	double limit_2	=	duct_length/2;

	//processed vars
	std::vector<double> T(max_node);

	//processing
	//for (auto i = 1; i < T.size() - 1; i++) {
	for (auto i = 0; i < T.size(); i++) {
		
		if (x[i] >= limit_0 && x[i] <= limit_1) {
			T[i]	=	1.0;
		} else if (x[i] > limit_1 && x[i] <= limit_2) {
			T[i]	=	1.0 - 0.167*(x[i] - limit_1);
		} else if (x[i] > limit_2 && x[i] <= duct_length) {
			T[i]	=	0.833 - 0.3507*(x[i] - limit_2);
		} else {
			std::cout << "There are something wrong in calc_initial_condition_T!\n";
		}
	}

	return T;
}


