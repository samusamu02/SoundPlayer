#pragma once
#include <vector>
struct ChannelL
{
	int pmin;
	int pmax;
	int p;
	int q;
	int offset0;
	int offset1;
	int ta;
	int tb;

	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> r;
};

struct ChannelR
{
	int pmin;
	int pmax;
	int p;
	int q;
	int offset0;
	int offset1;
	int ta;
	int tb;

	std::vector<double> x;
	std::vector<double> y;
	std::vector<double> r;
};