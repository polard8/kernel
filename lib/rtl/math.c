
// #todo
// Remember: double is double precision float.

// x to power of y
double pow (double __x, double __y)
{
    return 0;
}

// returns square root of x
double sqrt (double __x)
{
    return 0;
}


double floor (double __x)
{
    return 0;
}


double ceil (double __x)
{
    return 0;
}


// arc tangent of x
double atan (double __x)
{
    return 0;
}


double acos (double __x)
{
    return 0;
}


double asin (double __x)
{
    return 0;
}


double tan (double __x)
{
    return 0;
}


double cos (double __x)
{
    return 0;
}


double sin (double __x)
{
    return 0;
}



/*
unsigned long round ( unsigned long v, unsigned long r);
unsigned long round ( unsigned long v, unsigned long r){

    r--;
    v += r;
    v &= ~(long)r;

    return (v);
}
*/


/*
double factorial(double n)// not needed by SineN2, CosineN2 functions
{
	if (n<=1.0)
		return(1.0);
	else
		n=n*factorial(n-1.0); // notice we just keep calling this over until we get to 1!
	return(n);
}    
*/


/*
// this method uses the recursion relation for the series
// to generate the next coefficient from the last.
// Advantages: 1) No need to find n! for each term.
// 2) No need to call pow(x,n) each term.
double SineN2(const double& x, const int& n, double* p_err )
{
	double a = 1.0*x;// 1st term
	double sum = 0.0;

	if(n > 0)
	{
		for(int j=1; j<=n; j++)// for sine
		{
			sum += a;
			a *= -1.0*x*x/( (2*j+1)*(2*j) );// next term from last
		//	sum += a;
		}
		*p_err = a;// max. error = 1st term not taken for alternating series
	}
	else
		cout << " n must be > 0";

	return sum;
}// end of SineN2()

*/


/*
double CosineN2(const double& x, const int& n, double* p_err )
{
	double a = 1.0;// 1st term
	double sum = 0.0;

	if(n > 0)
	{
		for(int j=0; j<n; j++)// for cosine
		{
			sum += a;
			a *= -1.0*x*x/( (2*j+1)*(2*j+2) );// next term from last
		//	sum += a;
		}
		*p_err = a;// max. error = 1st term not taken for alternating series
	}
	else
		cout << " n must be > 0";

	return sum;
}// end of CosineN2() 
 */







