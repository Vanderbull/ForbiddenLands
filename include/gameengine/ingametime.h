#ifndef INGAMETIME_H
#define INGAMETIME_H

#include <string>
using namespace std;

#include <SDL2/SDL.h>
#include "gameengine.h"
#include "gamestate.h"

struct InGameTime
{
  int tm_sec = 0;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min = 0;			/* Minutes.	[0-59] */
  int tm_hour = 0;			/* Hours.	[0-23] */
  int tm_mday = 1;			/* Day.		[1-31] */
  int tm_mon = 0;			/* Month.	[0-11] */
  int tm_year = 0;			/* Year.  */
  int tm_wday = 0;			/* Day of week.	[0-6] */
  int tm_yday = 0;			/* Days in year.[0-365]	*/
};

#endif
