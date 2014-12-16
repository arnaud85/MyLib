/*************************************************************************
								MYLIB									
**************************************************************************

	AUTHOR  : ARNAUD BIEGUN
	VERSION : 1.0 (16/12/2014)
	BRIEF   : A C functions collection to help everyone
			  to survive in wild life

**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>



/***************************************************************************
							DAYOFYEAR
			

	NAME: 

		dayOfYear

	PURPOSE: 

		Function to compute the day of the year

	CALLING SEQUENCE: 

		err = dayno(year, month, day, doy);
	
	INPUTS :	
		
		year          - year [1965-2014]
       	month         - month of year [01-12]
       	day           - day of month [01-31]     
 
      
	OUTPUTS : 
    
       	doy           - number of days in the given year

    
    RETURN : 

    	error code
       
*****************************************************************************/


int dayOfYear(int year, int month, int day, int *doy)
{
	int ndays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int i;

	if (year <= 0)
	{
		fprintf(stderr, "[ERROR] : Bad value for the year : %d\n", year);
		
		return -1;
	}
	else if (month <= 0)
	{
		fprintf(stderr, "[ERROR] : Bad value for the month : %d\n", month);

		return -2;
	}
	else if(day <= 0)
	{
		fprintf(stderr, "[ERROR] : Bad value for the day : %d\n", day);

		return -3;
	}

	if (((year%4 == 0) && (year%100 != 0)) ||(year%400 == 0))
	{
		ndays[1]++;
	}
	
	*doy = 0;
	
	for (i = 0; i < month-1; i++)
	{
		*doy += ndays[i];
	} 

	*doy += day;

	return 0;
}