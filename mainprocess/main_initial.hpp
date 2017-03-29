#ifndef MAIN_INITIAL_HPP
#define MAIN_INITIAL_HPP

class Main_Initial {

	std::vector<double> calc_sound_speed(Parameters pars, std::vector<double> T);
	double calc_delta_t(Parameters pars, Variables vars);

	public:
		Main_Initial(Parameters pars, Variables &vars);
};

#endif
