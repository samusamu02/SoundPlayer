#pragma once

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

	double* x;
	double* y;
	double* r;
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

	double* x;
	double* y;
	double* r;
};
