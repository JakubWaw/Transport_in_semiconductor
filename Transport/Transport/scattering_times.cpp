#include "class.h"

// AKUSTYCZNE 

double tau_ac_temp(material Mat, double T_new)
{
    double tau_new = Mat.tau_ac * Mat.T / T_new;
    return tau_new;
}


// OPTYCZNE

double tau_op_temp(material Mat, double T_new)
{
    double tau_new = 
    return tau_new;
}
// DLA JONOW TAKIE SAMO TAU CIĄGLE