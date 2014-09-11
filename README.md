waveviz
=======

An OpenGL/FLTK based library to simulate quantum wavefunction measurement

***********************************************************************************
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
************************************************************************************

WaveVIZ - Wavefunction visualization tool - README
==================================
This readme lists system requirements, installation procedure and contact info (in case of reporting bugs/comments/suggestions) for WaveVIZ demo, WaveVIZ source and the WaveVIZ libraries.


================
1. System Requirements
================

Hardware Requirements:
-------------------------------------------
- An x86 compatible PC with at least 128MB memory
- An OpenGL 2.0 compliant VGA card with SM 3.0 support and the latest drivers installed (any of the following):
	-nVidia GeForce 7950 series
	-nVidia GeForce 7900 series
	-nVidia GeForce 7800 series
	-nVidia GeForce 7600 series
	-nVidia GeForce 6800 series
	-nVidia GeForce 6600 series
	-ATi Radeon x1300 series
	-ATi Radeon x1600 series
	-ATi Radeon x1800 series
	-ATi Radeon x1900 series
	-other cards which fully support OpenGL 2.0/GLSL v1.1 may also work
	Please note that SM 2.0/SM 2.0a cards MAY NOT work with this program (particularly, the GeForce FX series or the Radeon X700/800 series)
- At least 10MB of free hard-disk space (during installation)

Software Requirements:
-----------------------------------------
- Operating System - GNU/Linux with X-Windows support (Redhat, Debian, SuSE, Slackware etc.)
- The GNU C++ compiler and the C++-standard runtime library
- The Fast Light Toolkit (FLTK) v1.1 - available at http://www.fltk.org
- The OpenGL Extension Wrangler (GLEW) v1.3 - available at http://glew.sourceforge.net
- OpenGL and GLU libraries and header files (these might be already present on your system)

=================
2. Installation Procedure
=================
Please note that FLTK and GLEW MUST be installed before installing WaveVIZ.

* Uncompress the distribution tarball (waveviz.tar.gz) into an empty directory
* Open a shell (such as bash) and type "make" after switching to the directory containing the distribution - this should ideally build the WaveVIZ demo (NOTE: before you do this you may have to edit the makefile to refer to the location of your libraries and include headers - see Makefile for details)

* To make the raycasting "fog" demo, type make "make visfog" at the shell prompt.
* To make the shared-library WaveVIZ application widget for linking with your own applications in FLTK mode, use "make libvis"
* To make the equivalent .so for the raycasting fog widget, use "make libvisfog"

* Once the build procedure is complete without errors (you should see something like "rm *.o" as the last echoed line), you can launch the demo tool using "./visapp" (or "./visfog" for the fog-based demo).
(NOTE: If your GLEW installation is not in its usual dierctory (usually /usr/lib) then you might have to use the following before you can launch the demo tool:
	export LD_LIBRARY_PATH=/your/GLEW/libpath
)

==========
3. Contact Info
==========
Further documentation for developers and users is provided in the files "developer-manual" and "user-manual" respectively. Documentation regarding the use of the demo tool is included in the "demo-manual". If you encounter any bugs or want to make comments/suggestions etc. please drop a a mail at akshaym@iitkgp.ac.in

===============
4. Acknowledgements
===============
WaveVIZ was coded by me as part of a summer project in real-time 3D rendering at the Department of Applied Mathematics and Theoretical Physics (DAMTP), University of Cambridge, UK. 
Instrumental to the project were my supervisors - Dr. Sonia G Schirmer (DAMTP, University of Cambridge) and Dr. Frank C. Langbein (School of Computer Science, Cardiff University) - who initiated the project as an idea and provided essential insight into the architecture and implementation of both the renderer and the demo tool.

-Akshay Mishra,
Department of Mechanical Engineering,
Indian Institute of Technology, Kharagpur (WB) - India
(akshaym@iitkgp.ac.in - http://akshay.6te.net)
