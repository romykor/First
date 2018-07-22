//
// Data preparation for geoid fit
//
// 19-07-2018 - v. 2
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

	long double const zer=0.0000000000000000000;
	long double const one=1.0000000000000000000;
//	long double const a=6378137.0;
//	long double const finv=298.257223563;
	long double const a=one;
//	long double const finv=100.0;
	long double const pi=4.*atan(1.);
	long double const ras=648000./pi;	// Conversion from rad to arcsec
	long double const d2r=pi/180.;	    // Conversion from deg to rad

int main()
{
	int i,j,k,m,nlat,nlon,cps=CLOCKS_PER_SEC;
	long double rmax=one*RAND_MAX;

	long double phi,lam,f,me2,e2,sp,rp,Ne,h,R;
	long double dN,latstep,lonstep,rl,x,y,z;
	long double const ds=0.75;

	clock_t t1, t2;

//	f=one/finv;
	f=zer;
//	e2=f*(2.-f);
//	me2=(one-e2);
	e2=zer;
	me2=one;

	ofstream res("count-data2.txt");
	res<<fixed<<setprecision(2);

//	srand(time(0));

	t1=clock();

/*
//  --  Parameters
//	dN=10.0;			// (max-min) range of geoid undulation (m)
	dN=0.0;				// (max-min) range of geoid undulation (m)
	latstep=3.0;		// increment step for latitude, in degrees   (index i) - limit = 0.05
	lonstep=3.0;		// increment step for longitude, in degrees  (index j) - limit = 0.05
	nlat=180/latstep;
	nlon=360/lonstep;
//  --
*/

	latstep=ds;

  do {
	lonstep=latstep;
	nlat=180/latstep;
	nlon=360/lonstep;

/*
//  South pole
	phi=-90.0;
	lam=0.0;
	rp=phi*d2r;
	sp=sin(rp);
	Ne=a/sqrt(one-e2*sp*sp);
//	h=-3.+rand()/rmax*dN;
	h=0.;
	R=Ne+h;
	x=0.0;
	y=0.0;
	z=R*me2*sp;
	res<<endl<<setw(16)<<x<<setw(16)<<y<<setw(16)<<z;
*/

	k=2;
//  Grid of points
	for (i=1;i<nlat;i++)  {
		/*
		phi=phi+latstep;
		rp=phi*d2r;
		sp=sin(rp);
		Ne=a/sqrt(one-e2*sp*sp);
		lam=-lonstep;
		*/
		for (j=0;j<nlon;j++)  {
			/*
			lam=lam+lonstep;
			rl=lam*d2r;
//			h=-3.+rand()/rmax*dN;
			h=0.;
			R=Ne+h;
			x=R*cos(rp)*cos(rl);
			y=R*cos(rp)*sin(rl);
			z=R*me2*sp;
			res<<endl<<setw(16)<<x<<setw(16)<<y<<setw(16)<<z;
			*/
			k++;
		}
	}

/*
//  North pole
	phi=90.0;
	lam=0.0;
	rp=phi*d2r;
	sp=sin(rp);
	Ne=a/sqrt(one-e2*sp*sp);
//	h=-3.+rand()/rmax*dN;
	h=0.;
	R=Ne+h;
	x=0.0;
	y=0.0;
	z=R*me2*sp;
	res<<endl<<setw(16)<<x<<setw(16)<<y<<setw(16)<<z;
*/

	res<<"\n  Latitude step = "<<latstep<<" degrees \n";
	res<<"\n Longitude step = "<<lonstep<<" degrees \n";
	res<<"\n Data points = "<<k<<endl<<endl;

	latstep=latstep*2.0;
  }
  while (latstep<7.0);

	t2=clock()-t1;
	res<<"\n\n Computing time : "<<float(t2)/cps<<" seconds \n"<<endl;

	return 0;
}
