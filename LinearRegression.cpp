#include <cmath>
#include <vector>
#include <numeric>
#include <iostream>
#include "LinearRegression.hpp"
#include <unistd.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

LinearRegression::LinearRegression(unsigned int iterations, double lr) : 
	_iterations(iterations), 
	_lr(lr), 
	_intercept(0.),
	_coef(0.),
	_mag(1.)
	{}

LinearRegression::LinearRegression() :
	_iterations(0.), 
	_lr(0.), 
	_intercept(0.),
	_coef(0.),
	_mag(1.)
	{}

void LinearRegression::fit(std::vector<double> const X, std::vector<double> const Y) {
	double size = X.size();
	auto  X_Normalized = NormalizeData(X);
	auto minmax = std::minmax_element(X.begin(), X.end());

	for (int iter = 0; iter < _iterations; iter++) {	
		plt::clf();	
		plt::scatter(X, Y, 5.);
		plt::plot({*minmax.first, *minmax.second},{predict(*minmax.first), predict(*minmax.second)}, "");
		plt::pause(std::numeric_limits<double>::epsilon());
		plt::draw();
		
		std::cout << iter << " iterations. Score: " << score(X, Y) << std::endl;
		
		double tmpT0 = 0.;
		double tmpT1 = 0.;
		for (auto i=0; i < size; i++) {
			double estimatePrice = _intercept + (_coef * X_Normalized[i]);
			double error = estimatePrice - Y[i];
			tmpT0 += error;
			tmpT1 += error * X_Normalized[i];
		}
		_intercept -= _lr * tmpT0 / size;
		_coef -= _lr * tmpT1 / size;
	}
	
}

std::vector<double> LinearRegression::NormalizeData(std::vector<double> const & data) {
	std::vector<double> output = data;
	double mod = 0.0;

	std::for_each(data.begin(), data.end(), [&](double data) {
		mod += std::pow(data, 2);
	});
    _mag = std::sqrt(mod);
    if (_mag == 0) {
        throw std::logic_error("The input vector is a zero vector");
    }

	std::for_each(output.begin(), output.end(), [this](double & data) {
		data /= _mag;
	});
	return output;
}

double 	LinearRegression::predict(double X, bool normalizeX) const {
	if (normalizeX == true)
		X /= _mag;// normalization reasons
	return (_coef * X + _intercept);
}

double LinearRegression::score(std::vector<double> const & X, std::vector<double> const & Y) {
	auto X_iter = X.cbegin();
	double RMSE = 0.;

		
	std::for_each(Y.cbegin(), Y.cend(), [&](double value) {
		RMSE += std::pow(value - predict(*X_iter),2);
		X_iter++;
	});
	return std::sqrt(RMSE / Y.size());
}

double	LinearRegression::coef() {return _coef / _mag;}

double	LinearRegression::intercept() {return _intercept;}

void	LinearRegression::set_intercept(double intercept) {
	_intercept = intercept;
}

void	LinearRegression::set_coef(double coef) {
	_coef = coef;
}

LinearRegression::~LinearRegression() {}
