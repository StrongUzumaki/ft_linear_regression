#pragma once
#include "csv.h"
#include <cmath>
#include <vector>
#include <iostream>

class LinearRegression {
	
	public:
				LinearRegression();
				LinearRegression(unsigned int iterations, double lr);
				LinearRegression(LinearRegression const & src) = delete;
				LinearRegression & operator=(LinearRegression const & src) = delete;
				~LinearRegression();
		void 	fit(std::vector<double> const X, std::vector<double> const Y);
		double 	predict(double X, bool normalizeX=true) const;
		double	coef();
		double	intercept();
		double	score(std::vector<double> const & X, std::vector<double> const & Y);
		void	set_intercept(double intercept);
		void	set_coef(double coef);
	private:
	std::vector<double> 		NormalizeData(std::vector<double> const & data);
		double		_lr;
		unsigned	_iterations;
		double		_intercept {0.};	
		double		_coef {0.};
		double		_mag;
};

