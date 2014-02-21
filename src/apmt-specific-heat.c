/**************************************************************/
/*                                                            */
/* APMT ODS Stainless Steel                                   */
/*                                                            */
/* User-Defined Functions for temperature-dependent specific  */
/* heat at constant pressure                                  */
/*                                                            */
/* Units are in Pa-s                                          */
/*                                                            */
/* FLUENT 15.0                                                */
/*                                                            */
/* Author: Michael Chin                                       */
/*   Date: December 2013                                      */
/*                                                            */
/**************************************************************/



#include "udf.h"


DEFINE_SPECIFIC_HEAT(user_apmt_cp, T, Tref, h, yi)

{

  real cp;
  real TT=T-273.15;  // Conversion from Kelvin to Celsius

  {

/* Units from I2S-LWR Property Database are in degrees Celsius (conversion to Kelvin here) */


/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (TT <= 0.0 )
      cp = 464.2;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (TT >= 1200.)
      cp = 700.90096;

/* I2S-LWR Reference for APMT ODS Steel in temperature range of interest */

  else
      cp = 2.5532E-07*pow(TT,3) - 6.8145E-04*pow(TT,2) + 6.4698E-01*TT + 464.62;

   }

  TT=TT+273.15;         // Convert Celsius back to Kelvin
  *h = cp*(TT-Tref);   // Calculate specific heat

  return cp;
}

