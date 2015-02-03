/*

NAME: Utilities.h
DESC:

DATE: February 2 2015
AUTH: Jonatan H Sundqvist

===============================================================================================

SPEC |

TODO | - Move includes to namespace

*/



//-------------------------------------------------------------------------------------------------
// We'll need these
//-------------------------------------------------------------------------------------------------
# pragma once

#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <map>
#include <vector>



//-------------------------------------------------------------------------------------------------
// Forward declarations
//-------------------------------------------------------------------------------------------------
namespace Utilities {

// Values
const double π = M_PI;

// What are these and why are they global?
float dX = 0.0f, dZ = 0.0f;
float Y = 0.0f;
float dCentre = 0.0f;


// Functions
inline double sine(double);
inline double cosine(double);

template<class... Args> int OutputDebugLine(const char*, Args...);

}



//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
inline double Utilities::sine(double angle) { return sin(angle*π/180.0f); }
inline double Utilities::cosine(double angle) { return cos(angle*π/180.0f); }


template<class... Args> int Utilities::OutputDebugLine(const char* format, Args... args) {
	// TODO: Fix this ugly mess
#ifdef _DEBUG
#endif
	char buffer[256];
	sprintf(buffer, format, args...);
	OutputDebugStringA(buffer);
	OutputDebugStringA("\n");
	return 0;
}
