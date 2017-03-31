#include "global.hpp"
#include "preprocess/initial_parameters.hpp"
#include "preprocess/initial_condition.hpp"
#include "mainprocess/main_initial.hpp"
#include "mainprocess/main_predictor.hpp"

int main() {

	//define data structures
	Parameters pars;
	Variables vars;

	//define classes of preprocess
	Initial_Parameters init_pars(pars, vars); //constructor of Initial_Parameters
	Initial_Condition init_cond(pars, vars); //constructor of Initial_Condition

	//define classes of mainprocess
	Main_Initial main_init;
	Main_Predictor main_predictor;

	//local pars
	double max_node		=	pars.max_node;
	double error_max	=	pars.error_max;

	//local vars
	std::vector<double> &x			=	vars.x;		//length
	std::vector<double> &area		=	vars.area;	//area of duct
	std::vector<double> &rho		=	vars.rho;	//density
	std::vector<double> &v			=	vars.v;		//velocity
	std::vector<double> &T			=	vars.T;		//temperature
	std::vector<double> &p			=	vars.p;		//pressure
	std::vector<double> &mach		=	vars.mach;	//mach number
	std::vector<double> &mass_flow		=	vars.mass_flow;	//mass flow rate
	//u1 u2 u3
	std::vector<double> &U_1		=	vars.U_1;
	std::vector<double> &U_2		=	vars.U_2;
	std::vector<double> &U_3		=	vars.U_3;
	//f1 f2 f3
	std::vector<double> &F_1		=	vars.F_1;
	std::vector<double> &F_2		=	vars.F_2;
	std::vector<double> &F_3		=	vars.F_3;
	//sound speed
	std::vector<double> &sound_speed	=	vars.sound_speed;		//speed of sound
	//delta x and delta t
	std::vector<double> &delta_x		=	vars.delta_x;		//use vector in case delta_x is different each node
	double &delta_t				=	vars.delta_t;
	
	//declare error variable
	double error_value;

	//looping process
	do {
	
	//define variables of predictors and correctors
	Variables vars_predictor;
	Variables vars_corrector;

	//---------- first -> main_initial ----------//
	//calculate sound speed
	sound_speed	=	main_init.calc_sound_speed(pars, T);
	//calculate delta_t
	delta_t		=	main_init.calc_delta_t(pars, vars);
	std::cout << delta_t << std::endl;
	
	//---------- second -> main_predictor ----------//
	
	//copy vars into vars_predictor
	vars_predictor	=	vars;

	//bc outflow
	vars_predictor		=	main_predictor.bc_outflow_predictor(pars, vars_predictor);
	
	//F_1 F_2 F_3
	vars_predictor.F_1	=	main_predictor.calc_F_1(pars, vars_predictor);
	vars_predictor.F_2	=	main_predictor.calc_F_2(pars, vars_predictor);
	vars_predictor.F_3	=	main_predictor.calc_F_3(pars, vars_predictor);

	//time derivative
	vars_predictor.dU_1_dt	=	main_predictor.calc_dU_1_dt(pars, vars_predictor);
	vars_predictor.dU_2_dt	=	main_predictor.calc_dU_2_dt(pars, vars_predictor);
	vars_predictor.dU_3_dt	=	main_predictor.calc_dU_3_dt(pars, vars_predictor);

	//U_1 U_2 U_3
	vars_predictor.U_1	=	main_predictor.calc_new_U_1(pars, vars_predictor);
	vars_predictor.U_2	=	main_predictor.calc_new_U_2(pars, vars_predictor);
	vars_predictor.U_3	=	main_predictor.calc_new_U_3(pars, vars_predictor);
	

	
	} while (error_value > error_max);
}
