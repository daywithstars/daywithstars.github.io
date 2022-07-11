---
layout: post
title:  "SDL2 SDL_RenderGeometry Part II"
date:   2021-12-07 14:56:40 -0300
categories: SDL2 geometry
---

<script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-1870599781062797"
     crossorigin="anonymous"></script>

# SDL2.0.18 New way to render shapes - SDL_RenderGeometry part II


Welcome to the second part of the tutorial covering the new SDL2 geometry rendering. As I said in the previous tutorial we will see every chunk of the code and explain it. 

Our code is in C, so the first thing we do is include the headers needed for this demo: 

```c
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
```

We define our main function, with or without the parameters:

```c
int main(int argc, char** argv)
```
Then we call the SDL2 basic initialize function:

```c
if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
{
	return 1;
}
```

Next, create the window, test if it succeded:

```c
SDL_Window* window = SDL_CreateWindow("Rendering Geometry II", 0, 0, 640, 360, 0);
if ( !window )
{
	SDL_Quit();
	return 2;
}
```

The same to the renderer:

```c
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
if ( !renderer )
{
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 3;
}
```

{% include adsense.html %}

Now we define our SDL_Vertex, but what is SDL_Vertex? Well, if you know a little bit of graphics programming it is the custom vertice from a shader but with vertex position, vertex color, and texture map normalized in one place. If you don't know, there are just properties that we gonna use to draw our colored shapes with or without textures:

```c
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
```

Since we are on a space width = (0, 640) height = (0, 360) the first property from SDL_Vertex is the position in float point for the x and y-axis on our window coordinate system, so to draw our triangle we need 3 positions, the bottom left, top, and bottom right then the program will create our triangle. Let's create a triangle starting with the bottom left, then top and bottom right, replace the 3 vertex positions with these positions: 

```c
	const SDL_Vertex triangleVertex[3] = {
		{
			{ 0.f, 200.f }, 
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 100.f, 0.f },
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		},
		{
			{ 200.f, 200.f },
			{ 220, 220, 220, 0xFF },
			{ 0.f, 0.f }
		}
	};
```

Compile and run again, you will see a different triangle, now you know how to draw the triangle in the position you want on the screen. The second SDL_Vertex property is the vertex color, you should be familiar with SDL_Color, and with SDL_Color you can change each of the three vertex colors. The third property we will talk about in a later post. 

Following we have a basic main loop for the application to stay running until we close the window:

```c
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
```

While the application is running we clear the screen with the render color, then call the SDL_RenderGeometry and Present it to the window with SDL_RenderPresent:

```c
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
```

Finally, we free our SDL structures then finalize the application:

```c
SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
```

In the next tutorial, I will show some basic shapes drawings, then how to use textures.  Try to change the color of each vertex and see what happens. 

You can download the source code for this tutorial here: <a href="/assets/21-12-07/main.c" download>download</a>

[<-Previous Post]({% link _posts/2021-12-03-SDL2-new-geometry-rendering-SDL_RenderGeometry.markdown %})|[Next Post->]({% link _posts/2021-12-19-SDL2-new-geometry-rendering-SDL_RenderGeometry-part-III.markdown %})

