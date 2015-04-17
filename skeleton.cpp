// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	while( NoQuitMessageSDL() )
	{
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}
void Interpolate(vec3 a, vec3 b, vector<vec3> &result)
{
	int length = result.size();
	if (length == 1) result[0] = a;
	else{
			for (int i = 0; i < length; i++){
		
				float stepx = (b.x - a.x) / (length - 1);
				float stepy = (b.y - a.y) / (length - 1);
				float stepz = (b.z - a.z) / (length - 1);
				//vec3 step(stepx,stepy,stepz);
				//result[i] = a + step*i;
				result[i].x = a.x + stepx*i;
				result[i].y = a.y + stepy*i;
				result[i].z = a.z + stepz*i;
			
		}
	}

}
void Draw()
{

	vec3 topLeft(1,0,0); // red
	vec3 topRight(0,0,1); // blue
	vec3 bottomLeft(0,1,0); // green
	vec3 bottomRight(1,1,0); // yellow

	vector<vec3> leftSide( SCREEN_HEIGHT);
	vector<vec3> rightSide( SCREEN_HEIGHT);
	Interpolate(topLeft, bottomLeft, leftSide );
	Interpolate(topRight, bottomRight, rightSide );

	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{
		vector<vec3> color(SCREEN_WIDTH);
		Interpolate(leftSide[y],rightSide[y],color);
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{

			//vec3 color(0,0,1);
			PutPixelSDL( screen, x, y, color[x] );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}
