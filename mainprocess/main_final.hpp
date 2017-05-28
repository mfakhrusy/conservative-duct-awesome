#ifndef MAIN_FINAL_HPP
#define MAIN_FINAL_HPP

#include "main_predictor.hpp"

class Main_Final : public Main_Predictor {

	public:
		std::vector<double> calc_dU_dt_average(Parameters pars, std::vector<double> dU_dt_predictor, std::vector<double> dU_dt_corrector);
		std::vector<double> calc_new_v(Parameters pars, Variables vars);
		std::vector<double> calc_mach(Parameters pars, Variables vars);
		std::vector<double> calc_mass_flow(Parameters pars, Variables vars);
		std::vector<double> calc_pressure(Parameters pars, Variables vars);
		std::vector<double> calc_pressure_v2(Parameters pars, Variables vars);

		//smoothing final calculation
		std::vector<double> calc_S_1_final(Parameters pars, Variables vars, std::vector<double> old_p);
		std::vector<double> calc_S_2_final(Parameters pars, Variables vars, std::vector<double> old_p);
		std::vector<double> calc_S_3_final(Parameters pars, Variables vars, std::vector<double> old_p);

		//error calculations
		double calc_error(std::vector<double> old_F, std::vector<double> new_F);
		double calc_error_rms(std::vector<double> old_F, std::vector<double> new_F);
};

#endif
