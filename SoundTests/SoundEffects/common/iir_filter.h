#define _USE_MATH_DEFINES
#include <cmath>

inline void IIR_LPF(double fc, double Q, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = 4.0 * M_PI * M_PI * fc * fc / a[0];
  d[1] = 8.0 * M_PI * M_PI * fc * fc / a[0];
  d[2] = 4.0 * M_PI * M_PI * fc * fc / a[0];
  
  a[0] = 1.0;
}

inline void IIR_HPF(double fc, double Q, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = 1.0 / a[0];
  d[1] = -2.0 / a[0];
  d[2] = 1.0 / a[0];
  
  a[0] = 1.0;
}

inline void IIR_BPF(double fc1, double fc2, double a[], double d[])
{
  fc1 = tan(M_PI * fc1) / (2.0 * M_PI);
  fc2 = tan(M_PI * fc2) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2;
  a[1] = (8.0 * M_PI * M_PI * fc1 * fc2 - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2) / a[0];
  d[0] = 2.0 * M_PI * (fc2 - fc1) / a[0];
  d[1] = 0.0;
  d[2] = -2.0 * M_PI * (fc2 - fc1) / a[0];
  
  a[0] = 1.0;
}

inline void IIR_BEF(double fc1, double fc2, double a[], double d[])
{
  fc1 = tan(M_PI * fc1) / (2.0 * M_PI);
  fc2 = tan(M_PI * fc2) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2;
  a[1] = (8.0 * M_PI * M_PI * fc1 * fc2 - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2) / a[0];
  d[0] = (4.0 * M_PI * M_PI * fc1 * fc2 + 1.0) / a[0];
  d[1] = (8.0 * M_PI * M_PI * fc1 * fc2 - 2.0) / a[0];
  d[2] = (4.0 * M_PI * M_PI * fc1 * fc2 + 1.0) / a[0];
  
  a[0] = 1.0;
}

inline void IIR_resonator(double fc, double Q, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = 2.0 * M_PI * fc / Q / a[0];
  d[1] = 0.0;
  d[2] = -2.0 * M_PI * fc / Q / a[0];
  
  a[0] = 1.0;
}

inline void IIR_notch(double fc, double Q, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = (4.0 * M_PI * M_PI * fc * fc + 1.0) / a[0];
  d[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  d[2] = (4.0 * M_PI * M_PI * fc * fc + 1.0) / a[0];
  
  a[0] = 1.0;
}

inline void IIR_low_shelving(double fc, double Q, double g, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = (1.0 + sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / a[0];
  d[1] = (8.0 * M_PI * M_PI * fc * fc * (1.0 + g) - 2.0) / a[0];
  d[2] = (1.0 - sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / a[0];
  
  a[0] = 1.0;
}

inline void IIR_high_shelving(double fc, double Q, double g, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = ((1.0 + g) + sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0 * (1.0 + g)) / a[0];
  d[2] = ((1.0 + g) - sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  
  a[0] = 1.0;
}

inline void IIR_peaking(double fc, double Q, double g, double a[], double d[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  a[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  a[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  a[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[0] = (1.0 + 2.0 * M_PI * fc / Q * (1.0 + g) + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  d[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / a[0];
  d[2] = (1.0 - 2.0 * M_PI * fc / Q * (1.0 + g) + 4.0 * M_PI * M_PI * fc * fc) / a[0];
  
  a[0] = 1.0;
}
