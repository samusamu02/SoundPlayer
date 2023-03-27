#pragma once
#include <vector>
struct ChannelL
{
	double pmin;		
	double pmax;		
	double q;			
	double offset0;		
	double offset1;		
	double ta;			
	double tb;			

	std::vector<double> x;		
	std::vector<double> y;		
	std::vector<double> r;		
};

struct ChannelR
{
	double pmin;		
	double pmax;			
	double q;			
	double offset0;		
	double offset1;		
	double ta;				
	double tb;			

	std::vector<double> x;		
	std::vector<double> y;		
	std::vector<double> r;		
};