/***********************************************************************************
	Copyright 2006. Akshay Mishra	

	This file is part of WaveVIZ.

	WaveVIZ is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	WaveVIZ is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with WaveVIZ; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
************************************************************************************/	



////////////////////////////////////////////////////////
// main.c
//
// The entry point for application.
////////////////////////////////////////////////////////

#include "WaveVizUI.h"

// function declarations
// compute functions
complex ComputeFunc (int x, int y, int z, int time);

// GUI procesor
void ChoiceProcessor (void);

// helper functions
int factorial (int n);
float L (int n, int l, float x);
float P_lm(float x, int l, int m);


// global vars - for the UI
WaveVizUI *window=0;
int morphtime=0;
bool harmonic=false, box=false, oneelectron=false;
bool morph=false;
bool morph12=true, morph21=false;
float w0=0, w1=0, w2=0, w3=0, w4=0;
float nx1=0, nx2=0, nx3=0, nx4=0,
	ny1=0, ny2=0, ny3=0, ny4=0,
	nz1=0, nz2=0, nz3=0, nz4=0;
float Lx=0, Ly=0, Lz=0;
float Z=0, n1=0, l1=0, m1=0,
	n2=0, l2=0, m2=0,
	n3=0, l3=0, m3=0,
	n4=0, l4=0, m4=0;
float re11=1, re12=1, re13=1, re14=1,
	im11=0, im12=0, im13=0, im14=0;
float re21=1, re22=1, re23=1, re24=1,
	im21=0, im22=0, im23=0, im24=0;
bool wave1=false, wave2=false,
	wave3=false, wave4=false;


/////////
// Main
/////////
int main(int argc, char** argv)
{	
	window = new WaveVizUI();
	window->app->m_genfunc=ChoiceProcessor;
	window->show (argc, argv, 0);
	//window->app->m_renderer->setShaders ("minimal.vert", "minimal.frag");
	// Main loop
	Fl::run();	
	
	// clean up
	delete window;
	
	return 0;
}


/////////////////////////////////////////////
// Processes the choice made through the GUI
/////////////////////////////////////////////
void ChoiceProcessor ()
{
	if (!window->btnCompute->value())
	{
		printf ("Stopping computation...\n");
		return;
	}
	
	
	// assign UI values to UI globals
	harmonic=window->radHarmonic->value(); box=window->radBox->value(); oneelectron=window->radOneElectron->value();	
	morphtime = atoi(window->txtmorph->value());
	morph=window->chkmorph->value();
	morph12=window->radmorph12->value(); morph21=window->radmorph21->value();
	wave1=window->chkwave1->value(); wave2=window->chkwave2->value();
	wave3=window->chkwave3->value(); wave4=window->chkwave4->value();
	w0=atof(window->txtw0->value()); w1=atof(window->txtw1->value()); w2=atof(window->txtw2->value()); w3=atof(window->txtw3->value());
	Lx=atof(window->txtlx->value()); Ly=atof(window->txtly->value()); Lz=atof(window->txtlz->value());
	nx1=atof(window->txtnx1->value()); nx2=atof(window->txtnx2->value()); nx3=atof(window->txtnx3->value()); nx4=atof(window->txtnx4->value());
	ny1=atof(window->txtny1->value()); ny2=atof(window->txtny2->value()); ny3=atof(window->txtny3->value()); ny4=atof(window->txtny4->value());
	nz1=atof(window->txtnz1->value()); nz2=atof(window->txtnz2->value()); nz3=atof(window->txtnz3->value()); nz4=atof(window->txtnz4->value());
	Z=atof(window->txtz->value());
	n1=atof(window->txtn1->value()); n2=atof(window->txtn2->value()); n3=atof(window->txtn3->value()); n4=atof(window->txtn4->value());
	m1=atof(window->txtm1->value()); m2=atof(window->txtm2->value()); m3=atof(window->txtm3->value()); m4=atof(window->txtm4->value());
	l1=atof(window->txtl1->value()); l2=atof(window->txtl2->value()); l3=atof(window->txtl3->value()); l4=atof(window->txtl4->value());
	re11=atof(window->txtre11->value()); re12=atof(window->txtre12->value()); re13=atof(window->txtre13->value()); re14=atof(window->txtre14->value());
	im11=atof(window->txtim11->value()); im12=atof(window->txtim12->value()); im13=atof(window->txtim13->value()); im14=atof(window->txtim14->value());
	re21=atof(window->txtre21->value()); re22=atof(window->txtre22->value()); re23=atof(window->txtre23->value()); re24=atof(window->txtre24->value());
	im21=atof(window->txtim21->value()); im22=atof(window->txtim22->value()); im23=atof(window->txtim23->value()); im24=atof(window->txtim24->value());
	
	window->app->setComputeFunc (ComputeFunc);	
}




////////////////////////////////
// Computes particle in a box 
// wavefunctions
////////////////////////////////
complex ParticleinaBox (int x, int y, int z, int time, float nx, float ny, float nz)
{
	complex psi={0.0f, 0.0f};
		
	float psi_1=0.0f, E=0.0f;
	
	// calculate energy
	E=100*((nx/Lx)*(nx/Lx)+(ny/Ly)*(ny/Ly)+(nz/Lz)*(nz/Lz));	
	
	
	// do space-varying calculations here		
	if (abs(x)<Lx/2 && abs(y)<Ly/2 && abs(z)<Lz/2)
	{
		x-=Lx/2.0f; y-=Ly/2.0f; z-=Lz/2.0f;
		// initial wave function
		psi_1 = sqrt (2.0f/Lx)*sin (nx*3.141592f*x/Lx)
				*sqrt (2.0f/Ly)* sin (ny*3.141592f*y/Ly)
				*sqrt (2.0f/Lz)* sin (nz*3.141592f*z/Lz);
		psi.imag = psi_1*sin(E*time);
		psi.real = psi_1*cos(E*time);		
	}
	else
	{
		psi.real=0;
		psi.imag=0;
	}
		
	return psi;	
}



//////////////////////////////
// computes one-electron atom
// wavefunctions
//////////////////////////////
// factorial function
int factorial (int n)
{
	int fac=1;
	for (int i=1; i<n+1; i++)
	{
		fac*=i;
	}
	return fac;
}


// get laguerre polynomial
float L (int n, int l, float x)
{
	float sum=0.0f;
	float fac_nl=factorial (n+l);
	for (int k=0; k<n-l; k++)
	{
		sum+=pow(-1, k)*fac_nl*fac_nl/(factorial(n-l-1-k)*factorial(2*l+1+k)*factorial(k))
				*pow(x, k);
	}
	return sum;
}


// evaluates P (spherical modulator)
float P_lm(float x, int l, int m)
{
	float t=1-x*x;
	
	// s-orbital
	if (l==0)
	{
		return 1.0f;
	}
	
	// p-orbital
	if (l==1)
	{
		if (m==0)
			return x;
		if (abs(m)==1)
			return sqrt (t);
	}
	
	// d-orbital
	if (l==2)
	{
		if (m==0)
			return (3*x*x-1)/2.0f;
		if (abs(m)==1)
			return 3*x*sqrt(t);
		if (abs(m)==2)
			return 3*(t);
	}

	// f-orbital
	if (l==3)
	{
		if (m==0)
			return (5*x*x*x-3*x)/2.0f;
		if (abs(m)==1)
			return (15*x*x-3)*sqrt(t)/2.0f;
		if (abs(m)==2)
			return 15*x*(t);
		if (abs(m)==3)
			return 15*sqrt (t*t*t);
	}
	
	return 1.0f;
}

/****************************************************************************/
//////////////////////////////////////
// Write your function evaluator here
//////////////////////////////////////
complex OneElectronAtom (int x, int y, int z, int time, float n1, float l1, float m1)
{
	complex psi={0.0f, 0.0f};
	
	
	//// SAMPLE CODE FOR 1-electron atom \\\\
	
	// non-static vars
	float psi_1_real=0.0f, psi_1_imag=0.0f, psi_1=0.0f;	
	float R1=0.0f, Y_real1=0.0f, Y_imag1=0.0f, Y1=0.0f;
	float u1=0.0f, r=0.0f, theta=0.0f, phi=0.0f;
	float P1=0.0f;	
	
	float N1 = 0.0f;
	float pre_P1=0.0f;
	float E1=0.0f;
	float a=52.9f;
	float fact_nl1=0.0f;
	
	E1=0.136f*(Z/n1)*(Z/n1);
	
	// compute N
	fact_nl1=factorial (n1+l1);
		
	N1 = sqrt(factorial(n1-l1-1)/(2*n1*fact_nl1*fact_nl1*fact_nl1))
			*sqrt((2*a/n1)*(2*a/n1)*(2*a/n1));
		
	pre_P1=sqrt((2*l1+1)*factorial(l1-abs(m1))/factorial(1+abs(m1)));	
	
	
	// do space and time-varying calculations here	
	r=sqrt (x*x+y*y+z*z)/0.98;
	phi=acos (z/r);
	
	// calculate radial component
	u1=r/(n1*a);
	R1=N1*L(n1,l1,2*u1)*exp(-u1)*pow(2*u1, l1);
		
	// calculate spherical component
	P1=P_lm (x/(r*sin(phi)), l1, m1);
	Y1=pre_P1*P1;
	Y_imag1=Y1*sin(phi);
	Y_real1=Y1*cos(phi);
	
	psi_1_real=R1*Y_real1; psi_1_imag=R1*Y_imag1;	
	psi_1 = sqrt (psi_1_real*psi_1_real+psi_1_imag*psi_1_imag);
	psi_1_real=psi_1*cos (E1*time);
	psi_1_imag=psi_1*sin (E1*time);	
	
	// always assign the values you have computed
	// to the real and imaginary parts of psi like this
	psi.real=psi_1_real;
	psi.imag=psi_1_imag;	
	
	return psi;
}


// Hermite polynomial
float H (float u, int n)
{
	if (n<0) return 0;
	if (n==0)
		return 1.0f;
	if (n==1)
		return 2*u;
	return 2*u*H(u, n-1)-2*(n-1)*H(u, n-2);	
}

///////////////////////
// Harmonic oscillator
///////////////////////
complex Harmonic (int x, int y, int z, int time, float n)
{
	complex psi={0, 0};
	
	float E=(n+0.5)*w0, psi1=0.0f;
	
	float u=sqrt (x*x+y*y+z*z)/75;
	
	psi1=H (u, n)*exp (-u*u/2);
	psi.real=psi1*cos(E*time);
	psi.imag=psi1*sin(E*time);
	
	return psi;
}


////////////////////////////////
// compute function for renderer
////////////////////////////////
complex ComputeFunc (int x, int y, int z, int time)
{
	
	complex psi_1={0, 0}, psi_2={0, 0}, psi_3={0, 0}, psi_4={0, 0}, psi_target={0, 0};
	complex psi_1t={0, 0}, psi_2t={0, 0}, psi_3t={0, 0}, psi_4t={0, 0};
	complex psi={0, 0};
	
	// static vars
	static float t=0.0f;		// blending factor
	static int old_time=0;	
	
	if (old_time!=time)
	{
		// evaluate variables not dependent on space here
		// calculate morphing factor
		t=time;
		t=(morphtime==0)?t:t/morphtime;
		if (t>1.0f) t=1.0f;
		if (!morph) t=0;
	}
	
	
	// calculate space-dependent vars here
	if (wave1)
	{
		if (harmonic)
		{	psi_1=Harmonic (x, y, z, time, w1);
		}
		else if (box)
		{		
			psi_1=ParticleinaBox (x, y, z, time, nx1, ny1, nz1);
		}
		else if (oneelectron)
		{
			psi_1=OneElectronAtom (x, y, z, time, n1, l1, m1);
		}
	}	
	if (wave2)
	{
		if (harmonic)
		{	psi_2=Harmonic (x, y, z, time, w2);
		}
		else if (box)
		{		
			psi_2=ParticleinaBox (x, y, z, time, nx2, ny2, nz2);
		}
		else if (oneelectron)
		{
			psi_2=OneElectronAtom (x, y, z, time, n2, l2, m2);
		}
	}	
	if (wave3)
	{
		if (harmonic)
		{	psi_3=Harmonic (x, y, z, time, w3);
		}
		else if (box)
		{		
			psi_3=ParticleinaBox (x, y, z, time, nx3, ny3, nz3);
		}
		else if (oneelectron)
		{
			psi_3=OneElectronAtom (x, y, z, time, n3, l3, m3);
		}
	}	
	if (wave4)
	{
		if (harmonic)
		{	psi_4=Harmonic (x, y, z, time, w4);
		}
		else if (box)
		{		
			psi_4=ParticleinaBox (x, y, z, time, nx4, ny4, nz4);
		}
		else if (oneelectron)
		{
			psi_4=OneElectronAtom (x, y, z, time, n4, l4, m4);
		}
	}	
	
	// multiply with coefficients
	psi_target.real=re21*psi_1.real-im21*psi_1.imag
			+re22*psi_2.real-im22*psi_2.imag
			+re23*psi_3.real-im23*psi_3.imag
			+re24*psi_4.real-im24*psi_4.imag;
	psi_target.imag=im21*psi_1.real+re21*psi_1.imag
			+im22*psi_2.real+re22*psi_2.imag
			+im23*psi_3.real+re23*psi_3.imag
			+im24*psi_4.real+re24*psi_4.imag;
	
	psi_1t.real=re11*psi_1.real-im11*psi_1.imag; psi_1t.imag=im11*psi_1.real+re11*psi_1.imag;
	psi_2t.real=re12*psi_2.real-im12*psi_2.imag; psi_2t.imag=im12*psi_2.real+re12*psi_2.imag;
	psi_3t.real=re13*psi_3.real-im13*psi_3.imag; psi_3t.imag=im13*psi_3.real+re13*psi_3.imag;
	psi_4t.real=re14*psi_4.real-im14*psi_4.imag; psi_4t.imag=im14*psi_4.real+re14*psi_4.imag;
	psi_1=psi_1t; psi_2=psi_2t; psi_3=psi_3t; psi_4=psi_4t;
	
	// target wave function
	if (morph)
	{		
		if (morph12)
		{
			psi.real=(1.0f-t)*(psi_1.real+psi_2.real+psi_3.real+psi_4.real)
					+t*psi_target.real;
			psi.imag=(1.0f-t)*(psi_1.imag+psi_2.imag+psi_3.imag+psi_4.imag)
					+t*psi_target.imag;
		}
		if (morph21)
		{
			psi.real=t*(psi_1.real+psi_2.real+psi_3.real+psi_4.real)
					+(1.0f-t)*psi_target.real;
			psi.imag=t*(psi_1.imag+psi_2.imag+psi_3.imag+psi_4.imag)
					+(1.0f-t)*psi_target.imag;	
		}		
	}
	else
	{
		psi.real=psi_1.real+psi_2.real+psi_3.real+psi_4.real;
		psi.imag=psi_1.imag+psi_2.imag+psi_3.imag+psi_4.imag;
	}	
	
	/**********************************************************************/
	// end function evaluation
	old_time=time;	
	return psi;	
}



/****************************************************************************/
// HELP - The general nature of the MyComp() function 
// A skeleton implementaion is shown below

/*

complex MyComp (int x, int y, int z, int time)
{
	complex psi={0.0f, 0.0f};
	static int old_time=0;
	static bool InitOnly=true;
	
	
	// write any code required for your 
	// function evaluation below
	////////////////////////////////////
	
	// define your variables here
	// (variables that are not dependent on space
	// should be defined as "static")
	
	
	
	// non-static vars	
	
	
	// static vars
	
	
	
	if (InitOnly)
	{
		// evaluate constant variables here
		// (variables independet of space and time)
		
	
	}
	
	if (old_time!=time)
	{
		// evaluate variables dependent only on time here
		
	
	}
	
	// do space and time-varying calculations here
		
		
	
	
	// always assign the values you have computed
	// to the real and imaginary parts of psi like this
	psi.real=0.0f;
	psi.imag=0.0f;
	
	
	////////////////////////////////
	// end function evaluation	
	old_time=time;
	InitOnly=false;
	return psi;
}

*/

