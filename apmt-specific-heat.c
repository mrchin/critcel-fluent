/**************************************************************/
/*                                                            */
/* APMT ODS Stainless Steel                                   */
/*                                                            */
/* User-Defined Functions for temperature-dependent specific  */
/* heat at constant pressure                                  */
/*                                                            */
/* Units are in Pa-s                                          */
/*                                                            */
/* FLUENT 14.5.7                                              */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_PROPERTY(user_apmt_cp, cell, thread)

{

  real temp, cp;

  temp = C_T(cell, thread);

  {

/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (temp <= 0.0 )
      cp = 464.2;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (temp >= 1200.)
      cp = 700.90096;

/* I2S-LWR Reference for APMT ODS Steel in temperature range of interest */

  else
      cp = 2.5532E-07*pow(temp,3) - 6.8145E-04*pow(temp,2) + 6.4698E-01*temp + 464.62;

   }
  return cp;
}

