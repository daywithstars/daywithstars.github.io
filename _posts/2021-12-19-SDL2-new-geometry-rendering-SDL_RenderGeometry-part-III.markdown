---
layout: post
title:  "SDL2 SDL_RenderGeometry Part III"
date:   2021-12-19 14:56:40 -0300
categories: SDL2 geometry
---

<script async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js?client=ca-pub-1870599781062797"
     crossorigin="anonymous"></script>


Welcome to the last part of the series that covers almost everything you can do with SDL_RenderGeometry. In the future, I will cover more techniques and post more content instead of SDL2.
In this post tutorial, we will draw different 2D shapes and give textures to our shapes. It will be divided into two parts: **Drawing different shapes** and **Adding textures**, which you can see right below:


## Drawing different shapes

We will draw those shapes: 

![2D shapes](/assets/21-12-19/shapes.png)

For this tutorial I’m using the software **geogebra** to assist in getting the right coordinate, it’s simple to use, just right click on the canvas, then go to graphics then extend the length x max to something close to window width and y max to window height, now put your points where you want. Note that the SDL_Render renderer coordinate system starts at (0,0) on the top left then goes to the positive (window.width, window.height) bottom right. So, just ignore the negative value from the y axis on geogebra. You can download the project I’ve used: <a href="/assets/21-12-19/project.ggb" download>link</a> the project is from geogebra 4, but maybe work on later versions. 

Here is a screenshot from the project: 

![geogebra screenshot](/assets/21-12-19/geogebra.png)

The first shape is our triangle: 

```c
//Triangle vertex  
#define NUM_TRIANGLE_VERTEX 3
const SDL_Vertex triangleVertex[NUM_TRIANGLE_VERTEX] = {
	{
		{ 25.f, 20.f }, 
		{ 255, 251, 124, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 0.f, 80.f }, 
		{ 255, 251, 124, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 50.f, 80.f }, 
		{ 255, 251, 124, 0xFF },
		{ 0.f, 0.f }
	}
};
```

{% include adsense.html %}

The rest of the code remains the same, but for your triangle, we will use a definition to better understand what shape vertex we are using on construction and drawing. According to our **E** dot on screenshot it is located at: (x=25,y=20), **F** at (x=0,y=80) and **G** at (x=50,y=80). Also, we set each vertex the same color. Below is the render function:

```c
//Triangle
if ( SDL_RenderGeometry(renderer, NULL, triangleVertex, NUM_TRIANGLE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}
```

Now let's draw something different, to draw a rectangle we need 2 triangles, one normal triangle and another inverted, which means 6 vertexes. Let's see the dots **A**, **B**, **C**, **D**, I change a little bit the color from each triangle to see how they are disposed of:

```c
//Rectangle vertex 
#define NUM_RECTANGLE_VERTEX 6
const SDL_Vertex rectangleVertex[NUM_RECTANGLE_VERTEX] = {
	{
		{ 80.f, 20.f }, 
		{ 93, 157, 255, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 80.f, 80.f }, 
		{ 93, 157, 255, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 120.f, 20.f }, 
		{ 93, 157, 255, 0xFF },
		{ 0.f, 0.f }
	},
	
	{
		{ 80.f, 80.f }, 
		{ 22, 106, 197, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 120.f, 80.f }, 
		{ 22, 106, 197, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 120.f, 20.f }, 
		{ 22, 106, 197, 0xFF },
		{ 0.f, 0.f }
	}
};
```

And the render function call:

```c
//Rectangle
if ( SDL_RenderGeometry(renderer, NULL, rectangleVertex, NUM_RECTANGLE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}
```

Finally the third shape: Trapeze. 

For this shape we will use 9 vertexes of three triangles: 

```c
//Trapeze vertex 
#define NUM_TRAPEZE_VERTEX 9
const SDL_Vertex trapezeVertex[NUM_TRAPEZE_VERTEX] = {
	{
		{ 180.f, 20.f }, 
		{ 255, 77, 77, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 160.f, 80.f }, 
		{ 255, 77, 77, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 200.f, 80.f }, 
		{ 255, 77, 77, 0xFF },
		{ 0.f, 0.f }
	},
	
	{
		{ 180.f, 20.f }, 
		{ 230, 30, 30, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 200.f, 80.f }, 
		{ 230, 30, 30, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 220.f, 20.f }, 
		{ 230, 30, 30, 0xFF },
		{ 0.f, 0.f }
	},
	
	{
		{ 200.f, 80.f }, 
		{ 255, 77, 77, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 220.f, 20.f }, 
		{ 255, 77, 77, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 240.f, 80.f }, 
		{ 255, 77, 77, 0xFF },
		{ 0.f, 0.f }
	}
};
```

Also the render call function:

```c
//Trapeze
if ( SDL_RenderGeometry(renderer, NULL, trapezeVertex, NUM_TRAPEZE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}
```

And it's it, for this part of the tutorial III, you can download the source code from the above example here: <a href="/assets/21-12-19/example1.c" download>link</a>.


## Adding textures

Let's see things getting more interesting, in order to use texture we need to use the third property from SDL_Vetex, which is an SDL_FPoint representing the texture coordinate on our shape, these values go from 0 to 1, 1 means 100% of the width or height from our texture. Let's see how it works, the first thing you can think is we are not mapping the texture to the shape in pixel because if we change the size of the shape we need manually change the texture map values, but working with the percent of the texture we can easily transform, scale the shape without worry about the texture. 

See the image below:

![sdl2 texture mapping representation](/assets/21-12-19/sdl2-texture-mapping.png)

If we have an image from 50x80 pixels and we want to "copy" to a triangle we need to put those values into the texture map coordinate that is your third attribute from SDL_Vertex, we going to map the texture coordinate into each vertice from our triangle. See the image below:

![sdl2 texture mapping representation](/assets/21-12-19/sdl2-texture-mapping-triangle.png)

Now you have the idea you can use this texture for the triangle: <a href="/assets/21-12-19/triangle-texture.bmp" download>link</a>, the image is on format .bmp because we are going to use SDL_LoadBMP function, but you can use SDL_image to use different image formats. Below you can see the code to read the texture file, I choose to load the texture before the vertex initialization:

```c
//Loads the triangle texture
SDL_Texture* triangleTexture = NULL;
SDL_Surface* loadedSurface = SDL_LoadBMP("../triangle-texture.bmp");
if ( !loadedSurface )
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 4;
}

triangleTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
SDL_FreeSurface(loadedSurface);
```

Of curse we need to free the texture after using it: 

```c
if ( triangleTexture )
{
	SDL_DestroyTexture(triangleTexture);
}

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
```

And before mapping it to the vertex, let's supply the texture we are going to use on the triangle: 

```c
//Triangle
if ( SDL_RenderGeometry(renderer, triangleTexture, triangleVertex, 
	NUM_TRIANGLE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}
```

We're ready to map the texture now:

```c
//Triangle vertex  
#define NUM_TRIANGLE_VERTEX 3
const SDL_Vertex triangleVertex[NUM_TRIANGLE_VERTEX] = {
	{
		{ 25.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.5f, 0.f }
	},
	{
		{ 0.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 1.f }
	},
	{
		{ 50.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 1.f }
	}
};
```

As you can see the first vertex use 0.5, and 0 this means the top of the triangle will stick from the x = 25px and y = 0px(considering the image 50x80). The second vertex will be x = 0, y = 1 that is 0px to 80px, the third vertex will be x = 1, y = 1 that is 50px to 80px, now it will be "stretch" and the edges out of the triangle will be cut out. But if you want the entire image to be on the shape do not map the texture using the max value 1, and remember the shape must have a decent size to properly see the texture.

Let's see the rest of the code: 

download the rectangle texture: <a href="/assets/21-12-19/rectangle-texture.bmp" download>link</a>.
download the trapeze texture: <a href="/assets/21-12-19/trapeze-texture.bmp" download>link</a>.

The loading: 

```c
//Loads the triangle texture
SDL_Texture* triangleTexture = NULL;
SDL_Surface* loadedSurface = SDL_LoadBMP("../triangle-texture.bmp");
if ( !loadedSurface )
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 4;
}

triangleTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
SDL_FreeSurface(loadedSurface);

//Loads the rectangle texture
SDL_Texture* rectangleTexture = NULL;
loadedSurface = SDL_LoadBMP("../rectangle-texture.bmp");
if ( !loadedSurface )
{
	if ( triangleTexture )
	{
		SDL_DestroyTexture(triangleTexture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 5;
}

rectangleTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
SDL_FreeSurface(loadedSurface);

//Loads the trapeze texture
SDL_Texture* trapezeTexture = NULL;
loadedSurface = SDL_LoadBMP("../trapeze-texture.bmp");
if ( !loadedSurface )
{
	if ( triangleTexture )
	{
		SDL_DestroyTexture(triangleTexture);
	}
	if ( rectangleTexture )
	{
		SDL_DestroyTexture(rectangleTexture);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 6;
}

trapezeTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
SDL_FreeSurface(loadedSurface);
```

freeing:

```c
if ( triangleTexture )
{
	SDL_DestroyTexture(triangleTexture);
}
if ( rectangleTexture )
{
	SDL_DestroyTexture(rectangleTexture);
}
if ( trapezeTexture )
{
	SDL_DestroyTexture(trapezeTexture);
}

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
return 0;
```

Rendering:

```c
SDL_RenderClear(renderer);

//Triangle
if ( SDL_RenderGeometry(renderer, triangleTexture, triangleVertex, 
	NUM_TRIANGLE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}

//Rectangle
if ( SDL_RenderGeometry(renderer, rectangleTexture, rectangleVertex, 
	NUM_RECTANGLE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}

//Trapeze
if ( SDL_RenderGeometry(renderer, trapezeTexture, trapezeVertex, 
	NUM_TRAPEZE_VERTEX, NULL, 0) < 0 )
{
	SDL_Log("%s\n", SDL_GetError());
}


SDL_RenderPresent(renderer);
```

The vertexes values:

```c
//Triangle vertex  
#define NUM_TRIANGLE_VERTEX 3
const SDL_Vertex triangleVertex[NUM_TRIANGLE_VERTEX] = {
	{
		{ 25.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.5f, 0.f }
	},
	{
		{ 0.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 1.f }
	},
	{
		{ 50.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 1.f }
	}
};

//Rectangle vertex 
#define NUM_RECTANGLE_VERTEX 6
const SDL_Vertex rectangleVertex[NUM_RECTANGLE_VERTEX] = {
	{
		{ 80.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 80.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 1.f }
	},
	{
		{ 120.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 0.f }
	},
	
	{
		{ 80.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 1.f }
	},
	{
		{ 120.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 1.f }
	},
	{
		{ 120.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 0.f }
	}
};

//Trapeze vertex 
#define NUM_TRAPEZE_VERTEX 9
const SDL_Vertex trapezeVertex[NUM_TRAPEZE_VERTEX] = {
	{
		{ 180.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.5f, 0.f }
	},
	{
		{ 160.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 1.f }
	},
	{
		{ 200.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 1.f }
	},
	
	{
		{ 180.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 200.f, 80.f }, 
		{ 255, 255, 255, 0xFF },
		{ 0.5f, 1.f }
	},
	{
		{ 220.f, 20.f }, 
		{ 255, 255, 255, 0xFF },
		{ 1.f, 0.f }
	},
	
	{
		{ 200.f, 80.f }, 
		{ 238, 151, 36, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 220.f, 20.f }, 
		{ 0, 0, 0, 0xFF },
		{ 0.f, 0.f }
	},
	{
		{ 240.f, 80.f }, 
		{ 0, 0, 0, 0xFF },
		{ 0.f, 0.f }
	}
};
```

The result:

![final result, shapes with textures](/assets/21-12-19/result.png)

The complete **source code:** <a href="/assets/21-12-19/example2.c" download>link</a>.

Go ahead and create more shapes with different textures.

If you want to receive a notification when a new post is released follow me on:


instagram: @daywithstars 

[<-Previous Post]({% link _posts/2021-12-07-SDL2-Geometry-render-part-II.markdown %})

