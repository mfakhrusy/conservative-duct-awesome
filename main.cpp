#include "global.hpp"
#include "preprocess/init_parameters.hpp"
#include "preprocess/initial_condition.hpp"

int main() {

	Parameters pars;
	Variables vars;

	Init_Parameters init_pars(pars, vars); //constructor of Init_Parameters
	Initial_Condition init_cond(pars, vars);

	//local vars
	double max_node		=	pars.max_node;
	double error_max	=	pars.error_max;

	//declare error variable
	double error_value;

	//looping process
	do {
	//first -> main_initial
	
	
	} while (error_value > error_max);
}
