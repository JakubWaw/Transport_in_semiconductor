#include "class.h"
#include <math.h>

// AKUSTYCZNE 

double tau_ac_temp(material Mat, double T_new)
{
    double tau_new = Mat.tau_ac * Mat.T / T_new;
    return tau_new;
}


// OPTYCZNE

double tau_op_temp(material Mat, double T_new)
{
    double tau_new = Mat.tau_op *(1/(2/(exp(Mat.omega_0/(kB * Mat.T))-1)+1) * (2/(exp(Mat.omega_0/(kB * T_new))-1)+1));
    return tau_new;
}

// DLA JONOW TAKIE SAMO TAU CIĄGLE