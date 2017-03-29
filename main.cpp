#include "global.hpp"
#include "preprocessing/init_parameters.hpp"
#include "preprocessing/initial_condition.hpp"

int main() {

	Parameters pars;
	Variables vars;

	Init_Parameters init_pars(pars, vars); //constructor of Init_Parameters
	Initial_Condition init_cond(pars, vars);



}
