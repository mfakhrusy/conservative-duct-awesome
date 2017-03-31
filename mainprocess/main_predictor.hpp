#ifndef MAIN_PREDICTOR_HPP
#define MAIN_PREDICTOR_HPP

class Main_Predictor {

	public:
		Variables bc_outflow_predictor(Parameters pars, Variables vars);
		
		std::vector<double> calc_F_1_predictor(Parameters pars, Variables vars);
		std::vector<double> calc_F_2_predictor(Parameters pars, Variables vars);
		std::vector<double> calc_F_3_predictor(Parameters pars, Variables vars);
		std::vector<double> calc_J_2_predictor(Parameters pars, Variables vars);

};

#endif
