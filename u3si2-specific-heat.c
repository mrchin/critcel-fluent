/**************************************************************/
/*                                                            */
/* U3Si2 Nuclear Fuel                                         */
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


DEFINE_PROPERTY(user_u3si2_cp, cell, thread)

{

  real temp, cp;

  temp = C_T(cell, thread);

  {

/* If the temperature is lower than the reactor inlet, use the boundary specific heat */

  if (temp <= 25 )
      cp = 202;

/* If the temperature is higher than the reactor outlet, use the boundary specific heat */

  else if (temp >= 2000.)
      cp = 407;

/* I2S-LWR Reference for U3Si2 in temperature range of interest */

  else
      cp = 199 + 0.104*temp;

   }
  return cp;
}

