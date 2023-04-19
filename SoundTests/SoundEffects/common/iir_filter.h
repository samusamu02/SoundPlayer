#define _USE_MATH_DEFINES
#include <cmath>

inline void IIR_LPF(double fc, double Q, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = 4.0 * M_PI * M_PI * fc * fc / attenuation[0];
  delay[1] = 8.0 * M_PI * M_PI * fc * fc / attenuation[0];
  delay[2] = 4.0 * M_PI * M_PI * fc * fc / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_HPF(double fc, double Q, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = 1.0 / attenuation[0];
  delay[1] = -2.0 / attenuation[0];
  delay[2] = 1.0 / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_BPF(double fc1, double fc2, double attenuation[], double delay[])
{
  fc1 = tan(M_PI * fc1) / (2.0 * M_PI);
  fc2 = tan(M_PI * fc2) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2;
  attenuation[1] = (8.0 * M_PI * M_PI * fc1 * fc2 - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2) / attenuation[0];
  delay[0] = 2.0 * M_PI * (fc2 - fc1) / attenuation[0];
  delay[1] = 0.0;
  delay[2] = -2.0 * M_PI * (fc2 - fc1) / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_BEF(double fc1, double fc2, double attenuation[], double delay[])
{
  fc1 = tan(M_PI * fc1) / (2.0 * M_PI);
  fc2 = tan(M_PI * fc2) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2;
  attenuation[1] = (8.0 * M_PI * M_PI * fc1 * fc2 - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * (fc2 - fc1) + 4.0 * M_PI * M_PI * fc1 * fc2) / attenuation[0];
  delay[0] = (4.0 * M_PI * M_PI * fc1 * fc2 + 1.0) / attenuation[0];
  delay[1] = (8.0 * M_PI * M_PI * fc1 * fc2 - 2.0) / attenuation[0];
  delay[2] = (4.0 * M_PI * M_PI * fc1 * fc2 + 1.0) / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_resonator(double fc, double Q, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = 2.0 * M_PI * fc / Q / attenuation[0];
  delay[1] = 0.0;
  delay[2] = -2.0 * M_PI * fc / Q / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_notch(double fc, double Q, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = (4.0 * M_PI * M_PI * fc * fc + 1.0) / attenuation[0];
  delay[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  delay[2] = (4.0 * M_PI * M_PI * fc * fc + 1.0) / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_low_shelving(double fc, double Q, double g, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = (1.0 + sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / attenuation[0];
  delay[1] = (8.0 * M_PI * M_PI * fc * fc * (1.0 + g) - 2.0) / attenuation[0];
  delay[2] = (1.0 - sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc * (1.0 + g)) / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_high_shelving(double fc, double Q, double g, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = ((1.0 + g) + sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0 * (1.0 + g)) / attenuation[0];
  delay[2] = ((1.0 + g) - sqrt(1.0 + g) * 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  
  attenuation[0] = 1.0;
}

inline void IIR_peaking(double fc, double Q, double g, double attenuation[], double delay[])
{
  fc = tan(M_PI * fc) / (2.0 * M_PI);
  
  attenuation[0] = 1.0 + 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc;
  attenuation[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  attenuation[2] = (1.0 - 2.0 * M_PI * fc / Q + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[0] = (1.0 + 2.0 * M_PI * fc / Q * (1.0 + g) + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  delay[1] = (8.0 * M_PI * M_PI * fc * fc - 2.0) / attenuation[0];
  delay[2] = (1.0 - 2.0 * M_PI * fc / Q * (1.0 + g) + 4.0 * M_PI * M_PI * fc * fc) / attenuation[0];
  
  attenuation[0] = 1.0;
}
