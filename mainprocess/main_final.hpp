#ifndef MAIN_FINAL_HPP
#define MAIN_FINAL_HPP

#include "main_predictor.hpp"

class Main_Final : public Main_Predictor {

	public:
		std::vector<double> calc_dU_dt_average(Parameters pars, std::vector<double> dU_dt_predictor, std::vector<double> dU_dt_corrector);
		std::vector<double> calc_new_v(Parameters pars, Variables vars);

		//error calculations
		double calc_error(std::vector<double> old_F, std::vector<double> new_F);
};

#endif
