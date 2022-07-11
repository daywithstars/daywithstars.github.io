---
layout: post
title:  "SDL2 SDL_RenderGeometry Part I"
date:   2021-12-03 14:56:40 -0300
categories: SDL2 geometry
---

<script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-1870599781062797"
     crossorigin="anonymous"></script>

# SDL2.0.18 New way to render shapes - SDL_RenderGeometry


Recently SDL2 has released an update, the SDL2.0.18, and within this new version they come with functions to render geometry based on triangles. We will cover everything new with these new functions.

Today I will show some example of how to setup a basic boilerplate for our code and give some ideas. In the end, we will have a shape on the screen. 

Below are the basic boilerplate for this tutorial:


```c
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main(int argc, char** argv)
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("Rendering Geometry", 0, 0, 640, 360, 0);
	if ( !window )
	{
		SDL_Quit();
		return 2;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if ( !renderer )
	{
		SDL_DestroyWindow(window);
		return 3;
	}
	
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
		SDL_RenderPresent(renderer);
	}
	
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
```

{% include adsense.html %}

We are looking for [SDL_RenderGeometry](https://wiki.libsdl.org/SDL_RenderGeometry) function. 

The parameters are:

- texture - (optional) THe SDL texture to use.
  - `SDL_Texture` pointer.
- vertices - Vertices of our triangle or triangles. 
  - `const SDL_Vertex` pointer to an array.
- num_vertices - Number of vertices.
  - `int`
- indices - (optional) An array of integer indices into the 'vertices' array, if NULL all vertices will be rendered in sequential order.
  - `const int` pointer to an integer array.
- num_indices - Number of indices. 
  - `int`

Here we going to use, the new type SDL_Vertex to set the vertex position, vertex color. Since this tutorial has been written, there's no documentation on wiki about the SDL_Vertex type, so I will paste the code from [SDL_renderer.h](https://github.com/libsdl-org/SDL/blob/b7a0200aab8088e04800d33cc88fee384df0d78c/include/SDL_render.h) header. 

```c
/**
 *  Vertex structure
 */
typedef struct SDL_Vertex
{
    SDL_FPoint position;        /**< Vertex position, in SDL_Renderer coordinates  */
    SDL_Color  color;           /**< Vertex color */
    SDL_FPoint tex_coord;       /**< Normalized texture coordinates, if needed */
} SDL_Vertex;
```

Finally, let's see the final code and in the next post, I will explain each piece of the code. 

```c
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

int main(int argc, char** argv)
{
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow("Rendering Geometry", 0, 0, 640, 360, 0);
	if ( !window )
	{
		SDL_Quit();
		return 2;
	}
	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if ( !renderer )
	{
		SDL_DestroyWindow(window);
		return 3;
	}
	
	const SDL_Vertex triangleVertex[3] = {
		{
			{ 10.f, 10.f }, 
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 10.f, 310.f }, 
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 310.f, 120.f }, 
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
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
```

Now you can see a white triangle on the screen. If you want to know more about the setup to use the new SDL2.0.18 version send me an email then I will create a post on how to create a setup to test SDL's features in a separate way from the OS basic environment. 

[Next Post->](https://daywithstars.github.io/sdl2/geometry/2021/12/07/SDL2-Geometry-render-part-II.html)

