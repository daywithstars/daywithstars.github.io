/*
Copyright 2021 daywithstars

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main(int argc, char** argv)
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("Rendering Geometry II", 0, 0, 640, 360, 0);
	if ( !window )
	{
		SDL_Quit();
		return 2;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if ( !renderer )
	{
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}
	
	SDL_Vertex triangleVertex[3] = {
		{
			{ 0.f, 200.f }, 
			{ 220, 0, 0, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 100.f, 0.f }, 
			{ 0, 0, 220, 0xFF },
			{ 0.5f, 1.f }
		},
		{
			{ 200.f, 200.f }, 
			{ 220, 220, 0, 0xFF },
			{ 1.f, 0.f }
		}
	};
	
	SDL_bool running = SDL_TRUE;
	SDL_Event ev;
	while ( running )
	{
		while ( SDL_PollEvent(&ev) ) {
			if ( ev.type == SDL_QUIT )
			{
				running = SDL_FALSE;
			}
		}
		
		SDL_RenderClear(renderer);
		if ( SDL_RenderGeometry(renderer, NULL, triangleVertex, 3, NULL, 0) < 0 )
		{
			SDL_Log("%s\n", SDL_GetError());
		}
		SDL_RenderPresent(renderer);
	}
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
