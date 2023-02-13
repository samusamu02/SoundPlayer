#pragma once
#include <array>
#include <vector>
struct ChannelL
{
	double gain;
	double am;
	double fm;
	std::vector<double> vcf;
	std::array<int, 3> a;
	std::array<int, 3> b;
};

struct ChannelR
{
	double gain;
	double am;
	double fm;
	std::vector<double> vcf;
	std::array<int, 3> a;
	std::array<int, 3> b;
};