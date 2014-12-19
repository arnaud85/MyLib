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



/***************************************************************************
							SETVECTOR
			

	NAME: 

		setVector

	PURPOSE: 

		Set coordinates of a Vector structure :

				struct Vector
				{
					double x;
					double y;
					double z;
				};

	CALLING SEQUENCE: 

		int setVector(struct Vector *v, float vx, float vy, float vz)
	
	INPUTS :	
		
		
		X coordinate : float vx
		Y coordinate : float vy
		Z coordinate : float vz
 
      
	OUTPUTS : 
    
       	Pointer to struct Vector : struct Vector *v

    
    RETURN : 

    	error code
       
*****************************************************************************/
int setVector(struct Vector *v, float vx, float vy, float vz)
{
	v->x = vx;
	v->y = vy;
	v->z = vz;

	return 0;
}

/***************************************************************************
							DOTPRODUCT
			

	NAME: 

		dotProduct

	PURPOSE: 

		Return the scalar product (dot product) of 2 vectors

	CALLING SEQUENCE: 

		double scalar = dotProduct(struct Vector *A, struct Vector *B)
	
	INPUTS :	
		
		struct Vector *A : Vector 1
		struct Vector *B : Vector 2
 
      
	OUTPUTS : 
       	
		No outputs
    
    RETURN : 

    	A double which is the dot product of the 2 vectors
       
*****************************************************************************/
double dotProduct(struct Vector *A, struct Vector *B)
{
	return A->x*B->x + A->y*B->y + A->z*B->z;
}


/***************************************************************************
							GETANGLE
			

	NAME: 

		getAngle

	PURPOSE: 

		Return the angle between two coplanar vector 2D vector

	CALLING SEQUENCE: 

		double angle = double getAngle(struct Vector *A, struct Vector *B)
	
	INPUTS :	
		
		struct Vector *A : Vector 1
		struct Vector *B : Vector 2
 
      
	OUTPUTS : 
       	
		No outputs
    
    RETURN : 

    	A double which is the angle between the vectors
       
*****************************************************************************/
double getAngle(struct Vector *A, struct Vector *B)
{
	double s;
	double A_norm;
	double B_norm;
	double angle;

	s = scalar(A, B);
	A_norm = sqrt(A->x*A->x + A->y*A->y);
	B_norm = sqrt(B->x*B->x + B->y*B->y);

	angle = acos(s/(A_norm*B_norm));

	return angle;
}


/***************************************************************************
							CROSSPRODUCT
			

	NAME: 

		crossProduct

	PURPOSE: 

		Set coordinate of a Vector structure which is the cross product
		of two vectors 

	CALLING SEQUENCE: 

		int crossProduct(struct Vector *v1, struct Vector *v2, struct Vector *v3)
	
	INPUTS :	
		
		struct Vector *v1 : Vector 1
		struct Vector *v2 : Vector 2
		
 
      
	OUTPUTS : 
       	
		struct Vector *v3 : Vector which is the cross product
		of two first one 
    
    RETURN : 

    	Error code
       
*****************************************************************************/
int crossProduct(struct Vector *v1, struct Vector *v2, struct Vector *v3)
{
	v3->x = v1->y*v2->z - v1->z*v2->y;
	v3->y = -v1->x*v2->z + v1->z*v2->x;
	v3->z = v1->x*v2->y - v1->y*v2->x;

	return 0;
}


/***************************************************************************
							SAMESIDE
			

	NAME: 

		sameSide

	PURPOSE: 

		This function tell us if a  vector is in the same side of a plan
		with the third coordinate when the line joining the two first 
		coordinates cut the plan into two subplans
		

	CALLING SEQUENCE: 

		s = sameSide(struct Vector *AB, struct Vector *AD, struct Vector *AC);
	
	INPUTS :	
		
		struct Vector *AB : Line separation between two plans
		struct Vector *AD : Line joining a first point in one side
		struct Vector *AC : Line joining the second point in the other side
 
      
	OUTPUTS : 
       	
		No outputs
    
    RETURN : 

    	Return code with a boolean effect :

    		* 0 : same side (True)
    		* 1 : other side (False)
       
*****************************************************************************/
int sameSide(struct Vector *v1, struct Vector *v2, struct Vector *v3)
{
	struct Vector cp_v1_v2;
	struct Vector cp_v1_v3;

	crossProduct(v1, v2, &cp_v1_v2);
	crossProduct(v1, v3, &cp_v1_v3);

	if (dotProduct(&cp_v1_v2, &cp_v1_v3) >= 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


/***************************************************************************
							ISINTRIANGLE
			

	NAME: 

		isInTriangle

	PURPOSE: 

		Giving a triangle ABC, this function tell us a point D is 
		inside this triangle or not. This function uses the 
		SAMESIDE function described below.
		

	CALLING SEQUENCE: 

		int inTrinagle = isInTriangle()
	
	INPUTS :	
		
		struct Vector *AB : Line joining the A vertex with his first coordinate B
		struct Vector *AD : Line joining the point D for the A vertex
		struct Vector *AC : Line joining the A vertex with his second coordinate C

		struct Vector *CA : Line joining the C vertex with his first coordinate A
		struct Vector *CD : Line joining the point D for the C vertex
		struct Vector *CB : Line joining the C vertex with his second coordinate D

		struct Vector *BA : Line joining the B vertex with his first coordinate A
		struct Vector *BD : Line joining the point D for the B vertex
		struct Vector *BC : Line joining the B vertex with his second coordinate C
 
      
	OUTPUTS : 
       	
		No outputs
    
    RETURN : 

    	Return code with a boolean effect :

    		* 0 : inside the triangle (True)
    		* 1 : outside the triangle (False)
       
*****************************************************************************/
int isInTriangle(struct Vector *AB, struct Vector *AD, struct Vector *AC,
				 struct Vector *CA, struct Vector *CD, struct Vector *CB,
				 struct Vector *BA, struct Vector *BD, struct Vector *BC)
{
	int s1;
	int s2;
	int s3;

	s1 = sameSide(&AB, &AD, &AC);
	s2 = sameSide(&CA, &CD, &CB);
	s3 = sameSide(&BA, &BD, &BC);

	if ((s1 == 0) && (s2 == 0) && (s3 == 0))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}