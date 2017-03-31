#ifndef MAIN_PREDICTOR_HPP
#define MAIN_PREDICTOR_HPP

class Main_Predictor {

	public:
		Variables bc_outflow_predictor(Parameters pars, Variables vars);
		
		std::vector<double> calc_F_1(Parameters pars, Variables vars);
		std::vector<double> calc_F_2(Parameters pars, Variables vars);
		std::vector<double> calc_F_3(Parameters pars, Variables vars);
		std::vector<double> calc_J_2(Parameters pars, Variables vars);

		std::vector<double> calc_dU_1_dt(Parameters pars, Variables vars);
		std::vector<double> calc_dU_2_dt(Parameters pars, Variables vars);
		std::vector<double> calc_dU_3_dt(Parameters pars, Variables vars);

		std::vector<double> calc_new_U_1(Parameters pars, Variables vars);
		std::vector<double> calc_new_U_2(Parameters pars, Variables vars);
		std::vector<double> calc_new_U_3(Parameters pars, Variables vars);

		std::vector<double> calc_new_rho(Parameters pars, Variables vars);
		std::vector<double> calc_new_T(Parameters pars, Variables vars);

};

#endif
