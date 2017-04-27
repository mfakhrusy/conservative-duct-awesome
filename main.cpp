#include "global.hpp"
#include "preprocess/initial_parameters.hpp"
#include "preprocess/initial_condition.hpp"
#include "mainprocess/main_initial.hpp"
#include "mainprocess/main_predictor.hpp"
#include "mainprocess/main_corrector.hpp"
#include "mainprocess/main_final.hpp"
#include "misc/post_output.hpp"
#include <fstream>

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
	Main_Corrector main_corrector;
	Main_Final main_final;

	//misc
	Post_Output post_output;

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
	//du1_dt du2_dt du3_dt
	std::vector<double> &dU_1_dt		=	vars.dU_1_dt;
	std::vector<double> &dU_2_dt		=	vars.dU_2_dt;
	std::vector<double> &dU_3_dt		=	vars.dU_3_dt;
	//f1 f2 f3
	std::vector<double> &F_1		=	vars.F_1;
	std::vector<double> &F_2		=	vars.F_2;
	std::vector<double> &F_3		=	vars.F_3;
	//s1 s2 s3
	std::vector<double> &S_1		=	vars.S_1;
	std::vector<double> &S_2		=	vars.S_2;
	std::vector<double> &S_3		=	vars.S_3;
	//sound speed
	std::vector<double> &sound_speed	=	vars.sound_speed;		//speed of sound
	//delta x and delta t
	std::vector<double> &delta_x		=	vars.delta_x;		//use vector in case delta_x is different each node
	double &delta_t				=	vars.delta_t;
	
	//preserve old pressure
	std::vector<double> old_p		=	p;
		
	//declare error variable
	double error_rho;
	double error_v;
	double error_T;

	int count = 0;

	std::ofstream errors("output/errors.dat");
	errors << "iteration error_rho error_v error_T" << std::endl;

	//resize some variables
	p.resize(max_node);

	//looping process
	do {
		count++;
		std::cout << "Iteration-" << count << std::endl;
	
		//---------- first -> main_initial ----------//
		//calculate sound speed
		sound_speed	=	main_init.calc_sound_speed(pars, T);
		//calculate delta_t
		delta_t		=	main_init.calc_delta_t(pars, vars);
		
		//---------- second -> main_predictor ----------//
		
		std::cout << "(Computing) Predictor Step . . ." << std::endl;
		//copy vars into vars_predictor
		Variables vars_predictor;
		vars_predictor		=	vars;
		
		//bc outflow
		vars_predictor		=	main_predictor.bc_outflow_predictor(pars, vars_predictor);
		
		//F_1 F_2 F_3 J_2
		vars_predictor.F_1	=	main_predictor.calc_F_1_predictor(pars, vars_predictor);
		vars_predictor.F_2	=	main_predictor.calc_F_2_predictor(pars, vars_predictor);
		vars_predictor.F_3	=	main_predictor.calc_F_3_predictor(pars, vars_predictor);
		vars_predictor.J_2	=	main_predictor.calc_J_2(pars, vars_predictor);
		
		//time derivative
		vars_predictor.dU_1_dt	=	main_predictor.calc_dU_1_dt_predictor(pars, vars_predictor);
		vars_predictor.dU_2_dt	=	main_predictor.calc_dU_2_dt_predictor(pars, vars_predictor);
		vars_predictor.dU_3_dt	=	main_predictor.calc_dU_3_dt_predictor(pars, vars_predictor);
	
		//smoothing constant
		vars_predictor.S_1	=	main_predictor.calc_S_1(pars, vars_predictor);
		vars_predictor.S_2	=	main_predictor.calc_S_2(pars, vars_predictor);
		vars_predictor.S_3	=	main_predictor.calc_S_3(pars, vars_predictor);

		//U_1 U_2 U_3
		vars_predictor.U_1	=	main_predictor.calc_new_U_1(pars, vars_predictor);
		vars_predictor.U_2	=	main_predictor.calc_new_U_2(pars, vars_predictor);
		vars_predictor.U_3	=	main_predictor.calc_new_U_3(pars, vars_predictor);
	
		//T and rho
		vars_predictor.rho	=	main_predictor.calc_new_rho(pars, vars_predictor);
		vars_predictor.T	=	main_predictor.calc_new_T(pars, vars_predictor);


		//---------- third -> main_corrector ----------//
		
		std::cout << "(Computing) Corrector Step . . ." << std::endl;
		//copy vars_predictor into vars_corrector
		Variables vars_corrector;
		vars_corrector		=	vars_predictor;
	
		//bc inflow
		vars_corrector		=	main_corrector.bc_inflow_corrector(pars, vars_corrector);
	
		//F_1 F_2 F_3 J_2
		vars_corrector.F_1	=	main_corrector.calc_F_1_corrector(pars, vars_corrector);
		vars_corrector.F_2	=	main_corrector.calc_F_2_corrector(pars, vars_corrector);
		vars_corrector.F_3	=	main_corrector.calc_F_3_corrector(pars, vars_corrector);
		vars_corrector.J_2	=	main_corrector.calc_J_2(pars, vars_corrector);
	
		//time derivative
		vars_corrector.dU_1_dt	=	main_corrector.calc_dU_1_dt_corrector(pars, vars_corrector);
		vars_corrector.dU_2_dt	=	main_corrector.calc_dU_2_dt_corrector(pars, vars_corrector);
		vars_corrector.dU_3_dt	=	main_corrector.calc_dU_3_dt_corrector(pars, vars_corrector);
		
		//---------- fourth -> main_final ----------//
		
		std::cout << "(Computing) Final Step . . ." << std::endl;

		//T and rho and v
		//copy T rho v to new var
		std::vector<double> old_rho	=	rho;
		std::vector<double> old_v	=	v;
		std::vector<double> old_T	=	T;

		//calculate average time derivative in vars object
		dU_1_dt		=	main_final.calc_dU_dt_average(pars, vars_predictor.dU_1_dt, vars_corrector.dU_1_dt);
		dU_2_dt		=	main_final.calc_dU_dt_average(pars, vars_predictor.dU_2_dt, vars_corrector.dU_2_dt);
		dU_3_dt		=	main_final.calc_dU_dt_average(pars, vars_predictor.dU_3_dt, vars_corrector.dU_3_dt);
	
		//calculate smoothing for final step
		S_1	=	main_final.calc_S_1_final(pars, vars, old_p);
		S_2	=	main_final.calc_S_2_final(pars, vars, old_p);
		S_3	=	main_final.calc_S_3_final(pars, vars, old_p);

		//calculate new U_1, U_2, and U_3
		U_1	=	main_final.calc_new_U_1(pars, vars);
		U_2	=	main_final.calc_new_U_2(pars, vars);
		U_3	=	main_final.calc_new_U_3(pars, vars);
	
		//preserve old pressure
		old_p		=	p;

		//calculations
		rho		=	main_final.calc_new_rho(pars, vars);
		v		=	main_final.calc_new_v(pars, vars);
		T		=	main_final.calc_new_T(pars, vars);
		p		=	main_final.calc_pressure(pars, vars);
		mach		=	main_final.calc_mach(pars, vars);
		mass_flow	=	main_final.calc_mass_flow(pars, vars);
		
		//CHECK PREDICTED VALUE
		//TO MAKE THESE FILES TO APPEAR, ONE NEED TO MAKE new directory "output_dump/"
		
		post_output.print_vector(vars_predictor.F_1, "F_1_predictor");
		post_output.print_vector(vars_predictor.F_2, "F_2_predictor");
		post_output.print_vector(vars_predictor.F_3, "F_3_predictor");
		post_output.print_vector(vars_predictor.J_2, "J_2_predictor");
	
		post_output.print_vector(vars_predictor.dU_1_dt, "dU_1_dt_predictor");
		post_output.print_vector(vars_predictor.dU_2_dt, "dU_2_dt_predictor");
		post_output.print_vector(vars_predictor.dU_3_dt, "dU_3_dt_predictor");
	
		post_output.print_vector(vars_predictor.U_1, "U_1_predictor");
		post_output.print_vector(vars_predictor.U_2, "U_2_predictor");
		post_output.print_vector(vars_predictor.U_3, "U_3_predictor");
	
		post_output.print_vector(vars_predictor.rho, "rho_predictor");
		post_output.print_vector(vars_predictor.v, "v_predictor");
		
		//CHECK SMOOTHED PREDICTED VALUE
		post_output.print_vector(vars_predictor.S_1, "S_1_predictor");
		post_output.print_vector(vars_predictor.S_2, "S_2_predictor");
		post_output.print_vector(vars_predictor.S_3, "S_3_predictor");

		//CHECK CORRECTOR VALUE
	
		post_output.print_vector(vars_corrector.F_1, "F_1_corrector");
		post_output.print_vector(vars_corrector.F_2, "F_2_corrector");
		post_output.print_vector(vars_corrector.F_3, "F_3_corrector");
		post_output.print_vector(vars_corrector.J_2, "J_2_corrector");
	
		post_output.print_vector(vars_corrector.dU_1_dt, "dU_1_dt_corrector");
		post_output.print_vector(vars_corrector.dU_2_dt, "dU_2_dt_corrector");
		post_output.print_vector(vars_corrector.dU_3_dt, "dU_3_dt_corrector");
	
		post_output.print_vector(U_1, "U_1_corrector");
		post_output.print_vector(U_2, "U_2_corrector");
		post_output.print_vector(U_3, "U_3_corrector");
	
		//CHECK NEW VALUE
		
		post_output.print_vector(rho, "rho");
		post_output.print_vector(v, "v");
		post_output.print_vector(T, "T");

		//CHECK SMOOTHING VALUE
		post_output.print_vector(S_1, "S_1");
		post_output.print_vector(S_2, "S_2");
		post_output.print_vector(S_3, "S_3");

		//PRINT RESULT
		post_output.print_result(max_node, vars);
	
		//calculate errors
		//continuity -> rho
		error_rho	=	main_final.calc_error(old_rho, rho);
		error_v		=	main_final.calc_error(old_v, v);
		error_T		=	main_final.calc_error(old_T, T);
	
		//print errors on external file
	
		errors << count << " " << error_rho << " " << error_v << " " << error_T << std::endl;

		std::cout << count << " " << error_rho << " " << error_v << " " << error_T << std::endl;
		//if (count >= 4000) {
		if (count >= 50000) {
			std::cout << "Computation too long, program exit" << std::endl;
			break;	
		}

	} while (error_rho > error_max || error_v > error_max || error_T > error_max);

	std::cout << "Computation Finished! " << std::endl;
	errors.close();
}
