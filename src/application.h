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

////////////////////////////////////////////////////////////////////
// application.h
//
// Contains the declaration for the Application class used for
// creating a GL-enabled window and running the main loop.
///////////////////////////////////////////////////////////////////



#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "includeall.h"
#include "renderer.h"

////////////////////
// Application mode
////////////////////
enum ApplicationMode
{
	Normal=0,
	FullScreen
};

// Handler function-pointer types
typedef void (*PVOID) (void);
typedef void (*PTIMER) (int);
typedef void (*PKEYBOARD) (unsigned char, int, int);
typedef void (*PMOUSE) (int, int, int, int);
  
/////////////////////
// Application class
/////////////////////
class CApplication: public Fl_Gl_Window
{
	private:
	ApplicationMode m_mode;
	char* m_inifile;
	bool m_ready;
	
		
	void draw();
	int handle (int);
	
	public:
		CApplication(int X, int Y, int W, int H, const char *L);	
		CApplication(int X, int Y, int W, int H);
	public:
	CRenderer* m_renderer;
	PVOID m_genfunc;	
 
	public:
	CApplication();	
	void InitApplication (PCOMPFUNC ptr);
	
	// handler set methods
	void setComputeFunc (PCOMPFUNC ptr);			
  
  	~CApplication();
};


#endif
