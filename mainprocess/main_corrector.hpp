#ifndef MAIN_CORRECTOR_HPP
#define MAIN_CORRECTOR_HPP

#include "main_predictor.hpp"

class Main_Corrector: public Main_Predictor {

	public:
		Variables bc_inflow_corrector(Parameters pars, Variables vars);

		std::vector<double> calc_F_1_corrector(Parameters pars, Variables vars);
		std::vector<double> calc_F_2_corrector(Parameters pars, Variables vars);
		std::vector<double> calc_F_3_corrector(Parameters pars, Variables vars);

		std::vector<double> calc_dU_1_dt_corrector(Parameters pars, Variables vars);
		std::vector<double> calc_dU_2_dt_corrector(Parameters pars, Variables vars);
		std::vector<double> calc_dU_3_dt_corrector(Parameters pars, Variables vars);
};

#endif
