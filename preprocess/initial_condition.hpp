#ifndef INITIAL_CONDITION_HPP
#define INITIAL_CONDITION_HPP

class Initial_Condition {


	std::vector<double> calc_initial_condition_rho(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_T(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_v(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_p(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_U_1(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_U_2(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_U_3(Parameters pars, Variables vars);
	
	std::vector<double> calc_initial_condition_rho_2(Parameters pars, Variables vars);
	std::vector<double> calc_initial_condition_T_2(Parameters pars, Variables vars);
	public:
		Initial_Condition(Parameters pars, Variables &vars);
};

#endif
