#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>

#define WINDOW_WIDTH 579
#define WINDOW_HEIGHT 579

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int Q[69][2] = {{0,0},{320,542},{320,516},{320,489},{320,462},{320,436},{320,409},{320,382},{320,356},{356,320},{382,320},{409,320},{436,320},{462,320},{489,320},{516,320},{542,320},{542,258},{542,196},{516,196},{489,196},{462,196},{436,196},{409,196},{382,196},{356,196},{320,196},{320,169},{320,142},{320,116},{320,89},{320,62},{320,36},{320,9},{258,9},{196,9},{196,36},{196,62},{196,89},{196,116},{196,142},{196,169},{196,196},{197,197},{169,196},{142,196},{116,196},{89,196},{62,196},{36,196},{9,196},{9,258},{9,320},{36,320},{62,320},{89,320},{116,320},{142,320},{169,320},{196,320},{196,356},{196,382},{196,409},{196,436},{196,462},{196,489},{196,516},{196,542},{258,542}};
int B[8][2] = {{258,516},{258,489},{258,462},{258,436},{258,409},{258,382},{258,356},{258,329}};
int Y[8][2] = {{516,258},{489,258},{462,258},{436,258},{409,258},{382,258},{356,258},{329,258}};
int G[8][2] = {{258,36},{258,62},{258,89},{258,116},{258,142},{258,169},{258,196},{258,222}};
int R[8][2] = {{36,258},{62,258},{89,258},{116,258},{142,258},{169,258},{196,258},{222,258}};

int l = 0;
int tableau[10000];

struct pion
{ 
	int c;
	int f;
	int x;
	int y;
	int T[73][2];
} b1, b2, b3, b4, y1, y2, y3, y4, g1, g2, g3, g4, r1, r2, r3, r4;

struct pion *Blue[4];
struct pion *Yellow[4];
struct pion *Green[4];
struct pion *Red[4];
struct pion *Pion[16];

void generateurCongruentiel(long long x,int* T)
{
	long long liste[10000];
	int i;
	liste[0]=x;
	for(i=0;i<9999;i++)
	{
		liste[i+1]=(liste[i]*16807)%2147483647;
	}
	for(i=0;i<10000;i++)
	{
		if(0<=liste[i] && liste[i]<357913941)
			T[i]=1;
		else if(357913941<=liste[i] && liste[i]<715827882)
			T[i]=2;
		else if(715827882<=liste[i] && liste[i]<1073741824)
			T[i]=3;
		else if(1073741824<=liste[i] && liste[i]<1431655765)
			T[i]=4;
		else if(1431655765<=liste[i] && liste[i]<1789569706)
			T[i]=5;
		else
			T[i]=6;
	}
}

int random()
{
	int pas = 0;
	pas = tableau[l];
	l ++;
	if(l >= 10000)
	{
		long long n = 0;
		srand(time(NULL));
		n = (rand() % (9999999 - 1111111 + 1)) + 1111111;
		generateurCongruentiel(n,tableau);
		l = 0;
	}
	return pas;
}

void Debut()
{
	l = 0;
	int i, j;

	Blue[0] = &b1;	Blue[1] = &b2;	Blue[2] = &b3;	Blue[3] = &b4;
	Yellow[0] = &y1;	Yellow[1] = &y2;	Yellow[2] = &y3;	Yellow[3] = &y4;
	Green[0] = &g1;	Green[1] = &g2;	Green[2] = &g3;	Green[3] = &g4;
	Red[0] = &r1;	Red[1] = &r2;	Red[2] = &r3;	Red[3] = &r4;
	Pion[0] = &b1;	Pion[1] = &b2;	Pion[2] = &b3;	Pion[3] = &b4;	Pion[4] = &y1;	Pion[5] = &y2;	Pion[6] = &y3;	Pion[7] = &y4;	Pion[8] = &g1;	Pion[9] = &g2;	Pion[10] = &g3;	Pion[11] = &g4;	Pion[12] = &r1;	Pion[13] = &r2;	Pion[14] = &r3;	Pion[15] = &r4;

	for(i=0; i<16; i++)
	{
		Pion[i]->c = 0;
		Pion[i]->f = 0;
	}

	b1.T[0][0] = 382 + 188/2 - 10 - 50;		b1.T[0][1] = 382 + 188/2 - 10 - 50;
	b2.T[0][0] = 382 + 188/2 - 10 + 50;		b2.T[0][1] = 382 + 188/2 - 10 - 50;
	b3.T[0][0] = 382 + 188/2 - 10 - 50;		b3.T[0][1] = 382 + 188/2 - 10 + 50;
	b4.T[0][0] = 382 + 188/2 - 10 + 50;		b4.T[0][1] = 382 + 188/2 - 10 + 50;
	for(i = 1; i<=64; i++)
	{
		j = i + 4;
		b1.T[i][0] = b2.T[i][0] = b3.T[i][0] = b4.T[i][0] = Q[j][0];
		b1.T[i][1] = b2.T[i][1] = b3.T[i][1] = b4.T[i][1] = Q[j][1];
	}
	for(i = 65; i<=72; i++)
	{
		b1.T[i][0] = b2.T[i][0] = b3.T[i][0] = b4.T[i][0] = B[i-65][0] + 63/2 - 10;
		b1.T[i][1] = b2.T[i][1] = b3.T[i][1] = b4.T[i][1] = B[i-65][1] + 27/2 - 10;
	}

	y1.T[0][0] = 382 + 188/2 - 10 - 50;		y1.T[0][1] = 9 + 188/2 - 10 - 50;
	y2.T[0][0] = 382 + 188/2 - 10 + 50;		y2.T[0][1] = 9 + 188/2 - 10 - 50;
	y3.T[0][0] = 382 + 188/2 - 10 - 50;		y3.T[0][1] = 9 + 188/2 - 10 + 50;
	y4.T[0][0] = 382 + 188/2 - 10 + 50;		y4.T[0][1] = 9 + 188/2 - 10 + 50;
	for(i = 1; i<=64; i++){
		j = i + 21;
		if(j>68) j-=68;
		y1.T[i][0] = y2.T[i][0] = y3.T[i][0] = y4.T[i][0] = Q[j][0];
		y1.T[i][1] = y2.T[i][1] = y3.T[i][1] = y4.T[i][1] = Q[j][1];
	}
	for(i = 65; i<=72; i++)
	{
		y1.T[i][0] = y2.T[i][0] = y3.T[i][0] = y4.T[i][0] = Y[i-65][0] + 27/2 - 10;
		y1.T[i][1] = y2.T[i][1] = y3.T[i][1] = y4.T[i][1] = Y[i-65][1] + 63/2 - 10;
	}

	g1.T[0][0] = 9 + 188/2 - 10 - 50;		g1.T[0][1] = 9 + 188/2 - 10 - 50;
	g2.T[0][0] = 9 + 188/2 - 10 + 50;		g2.T[0][1] = 9 + 188/2 - 10 - 50;
	g3.T[0][0] = 9 + 188/2 - 10 - 50;		g3.T[0][1] = 9 + 188/2 - 10 + 50;
	g4.T[0][0] = 9 + 188/2 - 10 + 50;		g4.T[0][1] = 9 + 188/2 - 10 + 50;
	for(i = 1; i<=64; i++){
		j = i + 38;
		if(j>68) j-=68;
		g1.T[i][0] = g2.T[i][0] = g3.T[i][0] = g4.T[i][0] = Q[j][0];
		g1.T[i][1] = g2.T[i][1] = g3.T[i][1] = g4.T[i][1] = Q[j][1];
	}
	for(i = 65; i<=72; i++)
	{
		g1.T[i][0] = g2.T[i][0] = g3.T[i][0] = g4.T[i][0] = G[i-65][0] + 63/2 - 10;
		g1.T[i][1] = g2.T[i][1] = g3.T[i][1] = g4.T[i][1] = G[i-65][1] + 27/2 - 10;
	}

	r1.T[0][0] = 9 + 188/2 - 10 - 50;		r1.T[0][1] = 382 + 188/2 - 10 - 50;
	r2.T[0][0] = 9 + 188/2 - 10 + 50;		r2.T[0][1] = 382 + 188/2 - 10 - 50;
	r3.T[0][0] = 9 + 188/2 - 10 - 50;		r3.T[0][1] = 382 + 188/2 - 10 + 50;
	r4.T[0][0] = 9 + 188/2 - 10 + 50;		r4.T[0][1] = 382 + 188/2 - 10 + 50;
	for(i = 1; i<=64; i++){
		j = i + 55;
		if(j>68) j-=68;
		r1.T[i][0] = r2.T[i][0] = r3.T[i][0] = r4.T[i][0] = Q[j][0];
		r1.T[i][1] = r2.T[i][1] = r3.T[i][1] = r4.T[i][1] = Q[j][1];
	}
	for(i = 65; i<=72; i++)
	{
		r1.T[i][0] = r2.T[i][0] = r3.T[i][0] = r4.T[i][0] = R[i-65][0] + 27/2 - 10;
		r1.T[i][1] = r2.T[i][1] = r3.T[i][1] = r4.T[i][1] = R[i-65][1] + 63/2 - 10;
	}
}

void Image(char* picture, int X, int Y, int W, int H)
{
	SDL_Surface *image = NULL;
	SDL_Texture *texture = NULL;
	image = IMG_Load(picture);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_Rect rectangle;
	rectangle.x = X;
	rectangle.y = Y;
	rectangle.w = W;
	rectangle.h = H;
	SDL_RenderCopy(renderer, texture, NULL, &rectangle);
	SDL_FreeSurface(image);
	SDL_DestroyTexture(texture);
}

void Des(int tour, int rand)
{
	switch(rand)
	{
		case 1:
			if(tour == 1) Image("1.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("1.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("1.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("1.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 2:
			if(tour == 1) Image("2.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("2.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("2.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("2.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 3:
			if(tour == 1) Image("3.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("3.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("3.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("3.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 4:
			if(tour == 1) Image("4.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("4.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("4.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("4.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 5:
			if(tour == 1) Image("5.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("5.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("5.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("5.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 6:
			if(tour == 1) Image("6.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("6.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("6.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("6.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 10:
			if(tour == 1) Image("10.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("10.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("10.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("10.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		case 20:
			if(tour == 1) Image("20.png", 382 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			if(tour == 2) Image("20.png", 382 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 3) Image("20.png", 9 + 188/2 - 20, 9 + 188/2 - 20, 40, 40);
			if(tour == 4) Image("20.png", 9 + 188/2 - 20, 382 + 188/2 - 20, 40, 40);
			break;
		default:
			break;
	}
	SDL_RenderPresent(renderer);
}

void Modifier()
{
	Image("table.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	Image("blue.png", b1.x, b1.y, 20, 20);
	Image("blue.png", b2.x, b2.y, 20, 20);
	Image("blue.png", b3.x, b3.y, 20, 20);
	Image("blue.png", b4.x, b4.y, 20, 20);

	Image("yellow.png", y1.x, y1.y, 20, 20);
	Image("yellow.png", y2.x, y2.y, 20, 20);
	Image("yellow.png", y3.x, y3.y, 20, 20);
	Image("yellow.png", y4.x, y4.y, 20, 20);

	Image("green.png", g1.x, g1.y, 20, 20);
	Image("green.png", g2.x, g2.y, 20, 20);
	Image("green.png", g3.x, g3.y, 20, 20);
	Image("green.png", g4.x, g4.y, 20, 20);

	Image("red.png", r1.x, r1.y, 20, 20);
	Image("red.png", r2.x, r2.y, 20, 20);
	Image("red.png", r3.x, r3.y, 20, 20);
	Image("red.png", r4.x, r4.y, 20, 20);

	SDL_RenderPresent(renderer);
}

int blue_auto(int rand)
{
	if(b1.f == 1)
	{
		b1.c += rand;
		return 1;
	}
	if(b2.f == 1)
	{
		b2.c += rand;
		return 2;
	}
	if(b3.f == 1)
	{
		b3.c += rand;
		return 3;
	}
	if(b4.f == 1)
	{
		b4.c += rand;
		return 4;
	}
}

int blue(int rand)
{
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(b1.f == 1 && X >= b1.x && X <= (b1.x + 20) && Y >= b1.y && Y <= (b1.y + 20))
						{
							b1.c += rand;
							return 1;
						}
						if(b2.f == 1 && X >= b2.x && X <= (b2.x + 20) && Y >= b2.y && Y <= (b2.y + 20))
						{
							b2.c += rand;
							return 2;
						}
						if(b3.f == 1 && X >= b3.x && X <= (b3.x + 20) && Y >= b3.y && Y <= (b3.y + 20))
						{
							b3.c += rand;
							return 3;
						}
						if(b4.f == 1 && X >= b4.x && X <= (b4.x + 20) && Y >= b4.y && Y <= (b4.y + 20))
						{
							b4.c += rand;
							return 4;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return -1;
					break;
				default:
					continue;
			}
		}
	}
}

int yellow_auto(int rand)
{
	if(y1.f == 1)
	{
		y1.c += rand;
		return 1;
	}
	if(y2.f == 1)
	{
		y2.c += rand;
		return 2;
	}
	if(y3.f == 1)
	{
		y3.c += rand;
		return 3;
	}
	if(y4.f == 1)
	{
		y4.c += rand;
		return 4;
	}
}

int yellow(int rand)
{
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(y1.f == 1 && X >= y1.x && X <= (y1.x + 20) && Y >= y1.y && Y <= (y1.y + 20))
						{
							y1.c += rand;
							return 1;
						}
						if(y2.f == 1 && X >= y2.x && X <= (y2.x + 20) && Y >= y2.y && Y <= (y2.y + 20))
						{
							y2.c += rand;
							return 2;
						}
						if(y3.f == 1 && X >= y3.x && X <= (y3.x + 20) && Y >= y3.y && Y <= (y3.y + 20))
						{
							y3.c += rand;
							return 3;
						}
						if(y4.f == 1 && X >= y4.x && X <= (y4.x + 20) && Y >= y4.y && Y <= (y4.y + 20))
						{
							y4.c += rand;
							return 4;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return -1;
					break;
				default:
					continue;
			}
		}
	}
}

int green_auto(int rand)
{
	if(g1.f == 1)
	{
		g1.c += rand;
		return 1;
	}
	if(g2.f == 1)
	{
		g2.c += rand;
		return 2;
	}
	if(g3.f == 1)
	{
		g3.c += rand;
		return 3;
	}
	if(g4.f == 1)
	{
		g4.c += rand;
		return 4;
	}
}

int green(int rand)
{
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(g1.f == 1 && X >= g1.x && X <= (g1.x + 20) && Y >= g1.y && Y <= (g1.y + 20))
						{
							g1.c += rand;
							return 1;
						}
						if(g2.f == 1 && X >= g2.x && X <= (g2.x + 20) && Y >= g2.y && Y <= (g2.y + 20))
						{
							g2.c += rand;
							return 2;
						}
						if(g3.f == 1 && X >= g3.x && X <= (g3.x + 20) && Y >= g3.y && Y <= (g3.y + 20))
						{
							g3.c += rand;
							return 3;
						}
						if(g4.f == 1 && X >= g4.x && X <= (g4.x + 20) && Y >= g4.y && Y <= (g4.y + 20))
						{
							g4.c += rand;
							return 4;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return -1;
					break;
				default:
					continue;
			}
		}
	}
}

int red_auto(int rand)
{
	if(r1.f == 1)
	{
		r1.c += rand;
		return 1;
	}
	if(r2.f == 1)
	{
		r2.c += rand;
		return 2;
	}
	if(r3.f == 1)
	{
		r3.c += rand;
		return 3;
	}
	if(r4.f == 1)
	{
		r4.c += rand;
		return 4;
	}
}

int red(int rand)
{
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(r1.f == 1 && X >= r1.x && X <= (r1.x + 20) && Y >= r1.y && Y <= (r1.y + 20))
						{
							r1.c += rand;
							return 1;
						}
						if(r2.f == 1 && X >= r2.x && X <= (r2.x + 20) && Y >= r2.y && Y <= (r2.y + 20))
						{
							r2.c += rand;
							return 2;
						}
						if(r3.f == 1 && X >= r3.x && X <= (r3.x + 20) && Y >= r3.y && Y <= (r3.y + 20))
						{
							r3.c += rand;
							return 3;
						}
						if(r4.f == 1 && X >= r4.x && X <= (r4.x + 20) && Y >= r4.y && Y <= (r4.y + 20))
						{
							r4.c += rand;
							return 4;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return -1;
					break;
				default:
					continue;
			}
		}
	}
}

void Position()
{
	int i, j, k;

	b1.x = b1.T[b1.c][0];	b1.y = b1.T[b1.c][1];
	b2.x = b2.T[b2.c][0];	b2.y = b2.T[b2.c][1];
	b3.x = b3.T[b3.c][0];	b3.y = b3.T[b3.c][1];
	b4.x = b4.T[b4.c][0];	b4.y = b4.T[b4.c][1];

	y1.x = y1.T[y1.c][0];	y1.y = y1.T[y1.c][1];
	y2.x = y2.T[y2.c][0];	y2.y = y2.T[y2.c][1];
	y3.x = y3.T[y3.c][0];	y3.y = y3.T[y3.c][1];
	y4.x = y4.T[y4.c][0];	y4.y = y4.T[y4.c][1];

	g1.x = g1.T[g1.c][0];	g1.y = g1.T[g1.c][1];
	g2.x = g2.T[g2.c][0];	g2.y = g2.T[g2.c][1];
	g3.x = g3.T[g3.c][0];	g3.y = g3.T[g3.c][1];
	g4.x = g4.T[g4.c][0];	g4.y = g4.T[g4.c][1];

	r1.x = r1.T[r1.c][0];	r1.y = r1.T[r1.c][1];
	r2.x = r2.T[r2.c][0];	r2.y = r2.T[r2.c][1];
	r3.x = r3.T[r3.c][0];	r3.y = r3.T[r3.c][1];
	r4.x = r4.T[r4.c][0];	r4.y = r4.T[r4.c][1];

	for(k=1; k<69; k++)
	{
		for(i=0; i<16; i++)
		{
			if(Pion[i]->T[Pion[i]->c][0] == Q[k][0] && Pion[i]->T[Pion[i]->c][1] == Q[k][1])
			{
				if((k>=1 && k<=8) || (k>=26 && k<=42) || (k>=60 && k<=68))
				{
					Pion[i]->x += (63/2 - 10);
					Pion[i]->y += (27/2 - 10);
				}
				else
				{
					Pion[i]->x += (27/2 - 10);
					Pion[i]->y += (63/2 - 10);
				}
			}
		}
	}

	for(k=1; k<69; k++)
	{
		for(i=0; i<15; i++)
		{
			for(j=i+1; j<16; j++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == Pion[j]->T[Pion[j]->c][0] && Pion[i]->T[Pion[i]->c][0] == Q[k][0] && Pion[i]->T[Pion[i]->c][1] == Pion[j]->T[Pion[j]->c][1] && Pion[i]->T[Pion[i]->c][1] == Q[k][1])
				{
					if((k>=1 && k<=8) || (k>=26 && k<=42) || (k>=60 && k<=68))
					{
						Pion[i]->x -= 11;
						Pion[j]->x += 11;
					}
					else
					{
						Pion[i]->y -= 11;
						Pion[j]->y += 11;
					}
				}
			}
		}
	}

	for(k=0; k<8; k++)
	{
		for(i=0; i<3; i++)
		{
			for(j=i+1; j<4; j++)
			{
				if(Blue[i]->T[Blue[i]->c][0] == Blue[j]->T[Blue[j]->c][0] && Blue[i]->T[Blue[i]->c][0] == (B[k][0] + 63/2 - 10) && Blue[i]->T[Blue[i]->c][1] == Blue[j]->T[Blue[j]->c][1] && Blue[i]->T[Blue[i]->c][1] == (B[k][1] + 27/2 - 10))
				{
					Blue[i]->x -= 11;
					Blue[j]->x += 11;
				}

				if(Yellow[i]->T[Yellow[i]->c][0] == Yellow[j]->T[Yellow[j]->c][0] && Yellow[i]->T[Yellow[i]->c][0] == (Y[k][0] + 27/2 - 10) && Yellow[i]->T[Yellow[i]->c][1] == Yellow[j]->T[Yellow[j]->c][1] && Yellow[i]->T[Yellow[i]->c][1] == (Y[k][1] + 63/2 - 10))
				{
					Yellow[i]->y -= 11;
					Yellow[j]->y += 11;
				}

				if(Green[i]->T[Green[i]->c][0] == Green[j]->T[Green[j]->c][0] && Green[i]->T[Green[i]->c][0] == (G[k][0] + 63/2 - 10) && Green[i]->T[Green[i]->c][1] == Green[j]->T[Green[j]->c][1] && Green[i]->T[Green[i]->c][1] == (G[k][1] + 27/2 - 10))
				{
					Green[i]->x -= 11;
					Green[j]->x += 11;
				}

				if(Red[i]->T[Red[i]->c][0] == Red[j]->T[Red[j]->c][0] && Red[i]->T[Red[i]->c][0] == (R[k][0] + 27/2 - 10) && Red[i]->T[Red[i]->c][1] == Red[j]->T[Red[j]->c][1] && Red[i]->T[Red[i]->c][1] == (R[k][1] + 63/2 - 10))
				{
					Red[i]->y -= 11;
					Red[j]->y += 11;
				}
			}
		}
	}
}

void Normal()
{
	int i;
	for(i=0; i<16; i++)
	{
		if(Pion[i]->c == 0 || Pion[i]->c == 72) Pion[i]->f = 0;
		if(Pion[i]->c != 0 && Pion[i]->c != 72) Pion[i]->f = 1;
	}
}

void _72(int rand)
{
	int i;
	for(i=0; i<16; i++)
	{
		if(Pion[i]->c + rand > 72) Pion[i]->f = 0;
	}
}

void Bloquage(int tour, int rand)
{
	int i, j, k, h;
	_72(rand);
	switch(tour)
	{
		case 1:
			for(h=0; h<4; h++)
			{
				for(k=1; k<=rand; k++)
				{
					if(k == rand && (Blue[h]->c)+k == 72) 
						continue;
					for(i=0; i<15; i++)
					{
						for(j=i+1; j<16; j++)
						{
							if(Blue[h]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Pion[j]->T[Pion[j]->c][0] && Pion[i]->T[Pion[i]->c][0] == Blue[h]->T[(Blue[h]->c)+k][0] && Pion[i]->T[Pion[i]->c][1] == Pion[j]->T[Pion[j]->c][1] && Pion[i]->T[Pion[i]->c][1] == Blue[h]->T[(Blue[h]->c)+k][1])
							{
								Blue[h]->f = 0;
							}
						}
					}
				}
			}
			break;
		case 2:
			for(h=0; h<4; h++)
			{
				for(k=1; k<=rand; k++)
				{
					if(k == rand && (Yellow[h]->c)+k == 72) 
						continue;
					for(i=0; i<15; i++)
					{
						for(j=i+1; j<16; j++)
						{
							if(Yellow[h]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Pion[j]->T[Pion[j]->c][0] && Pion[i]->T[Pion[i]->c][0] == Yellow[h]->T[(Yellow[h]->c)+k][0] && Pion[i]->T[Pion[i]->c][1] == Pion[j]->T[Pion[j]->c][1] && Pion[i]->T[Pion[i]->c][1] == Yellow[h]->T[(Yellow[h]->c)+k][1])
							{
								Yellow[h]->f = 0;
							}
						}
					}
				}
			}
			break;
		case 3:
			for(h=0; h<4; h++)
			{
				for(k=1; k<=rand; k++)
				{
					if(k == rand && (Green[h]->c)+k == 72) 
						continue;
					for(i=0; i<15; i++)
					{
						for(j=i+1; j<16; j++)
						{
							if(Green[h]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Pion[j]->T[Pion[j]->c][0] && Pion[i]->T[Pion[i]->c][0] == Green[h]->T[(Green[h]->c)+k][0] && Pion[i]->T[Pion[i]->c][1] == Pion[j]->T[Pion[j]->c][1] && Pion[i]->T[Pion[i]->c][1] == Green[h]->T[(Green[h]->c)+k][1])
							{
								Green[h]->f = 0;
							}
						}
					}
				}
			}
			break;
		case 4:
			for(h=0; h<4; h++)
			{
				for(k=1; k<=rand; k++)
				{
					if(k == rand && (Red[h]->c)+k == 72) 
						continue;
					for(i=0; i<15; i++)
					{
						for(j=i+1; j<16; j++)
						{
							if(Red[h]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Pion[j]->T[Pion[j]->c][0] && Pion[i]->T[Pion[i]->c][0] == Red[h]->T[(Red[h]->c)+k][0] && Pion[i]->T[Pion[i]->c][1] == Pion[j]->T[Pion[j]->c][1] && Pion[i]->T[Pion[i]->c][1] == Red[h]->T[(Red[h]->c)+k][1])
							{
								Red[h]->f = 0;
							}
						}
					}
				}
			}
			break;
		default:
			break;
	}
}

int Five_Kill(int tour)
{
	int i;
	switch(tour)
	{
		case 1:
			for(i=4; i<16; i++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == b1.T[1][0] && Pion[i]->T[Pion[i]->c][1] == b1.T[1][1])
					return 1;
			}
			return 0;
			break;
		case 2:
			for(i=0; i<4; i++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == y1.T[1][0] && Pion[i]->T[Pion[i]->c][1] == y1.T[1][1])
					return 1;
			}
			for(i=8; i<16; i++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == y1.T[1][0] && Pion[i]->T[Pion[i]->c][1] == y1.T[1][1])
					return 1;
			}
			return 0;
			break;
		case 3:
			for(i=0; i<8; i++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == g1.T[1][0] && Pion[i]->T[Pion[i]->c][1] == g1.T[1][1])
					return 1;
			}
			for(i=12; i<16; i++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == g1.T[1][0] && Pion[i]->T[Pion[i]->c][1] == g1.T[1][1])
					return 1;
			}
			return 0;
			break;
		case 4:
			for(i=0; i<12; i++)
			{
				if(Pion[i]->T[Pion[i]->c][0] == r1.T[1][0] && Pion[i]->T[Pion[i]->c][1] == r1.T[1][1])
					return 1;
			}
			return 0;
			break;
		default:
			return 0;
			break;
	}
}

int Kill(int tour, int rand)
{
	int i, x, y;
	int k1=0;
	int k2=0;
	int k3=0;
	int k4=0;
	switch(tour)
	{
		case 1:
			for(i=4; i<16; i++)
			{
				x = Pion[i]->T[Pion[i]->c][0];
				y = Pion[i]->T[Pion[i]->c][1];
				if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
					(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
				{
					continue;
				}
				else
				{
					if(Blue[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[0]->T[(Blue[0]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Blue[0]->T[(Blue[0]->c)+rand][1])
						k1 = 1;
					if(Blue[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[1]->T[(Blue[1]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Blue[1]->T[(Blue[1]->c)+rand][1])
						k2 = 1;
					if(Blue[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[2]->T[(Blue[2]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Blue[2]->T[(Blue[2]->c)+rand][1])
						k3 = 1;
					if(Blue[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[3]->T[(Blue[3]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Blue[3]->T[(Blue[3]->c)+rand][1])
						k4 = 1;
				}
			}
			if(k1==1 || k2==1 || k3==1 || k4==1)
			{
				if(k1 == 0) b1.f = 0;
				if(k2 == 0) b2.f = 0;
				if(k3 == 0) b3.f = 0;
				if(k4 == 0) b4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 2:
			for(i=0; i<4; i++)
			{
				x = Pion[i]->T[Pion[i]->c][0];
				y = Pion[i]->T[Pion[i]->c][1];
				if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
					(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
				{
					continue;
				}
				else
				{
					if(Yellow[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[0]->T[(Yellow[0]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[0]->T[(Yellow[0]->c)+rand][1])
						k1 = 1;
					if(Yellow[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[1]->T[(Yellow[1]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[1]->T[(Yellow[1]->c)+rand][1])
						k2 = 1;
					if(Yellow[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[2]->T[(Yellow[2]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[2]->T[(Yellow[2]->c)+rand][1])
						k3 = 1;
					if(Yellow[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[3]->T[(Yellow[3]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[3]->T[(Yellow[3]->c)+rand][1])
						k4 = 1;
				}
			}
			for(i=8; i<16; i++)
			{
				x = Pion[i]->T[Pion[i]->c][0];
				y = Pion[i]->T[Pion[i]->c][1];
				if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
					(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
				{
					continue;
				}
				else
				{
					if(Yellow[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[0]->T[(Yellow[0]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[0]->T[(Yellow[0]->c)+rand][1])
						k1 = 1;
					if(Yellow[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[1]->T[(Yellow[1]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[1]->T[(Yellow[1]->c)+rand][1])
						k2 = 1;
					if(Yellow[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[2]->T[(Yellow[2]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[2]->T[(Yellow[2]->c)+rand][1])
						k3 = 1;
					if(Yellow[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[3]->T[(Yellow[3]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[3]->T[(Yellow[3]->c)+rand][1])
						k4 = 1;
				}
			}
			if(k1==1 || k2==1 || k3==1 || k4==1)
			{
				if(k1 == 0) y1.f = 0;
				if(k2 == 0) y2.f = 0;
				if(k3 == 0) y3.f = 0;
				if(k4 == 0) y4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 3:
			for(i=0; i<8; i++)
			{
				x = Pion[i]->T[Pion[i]->c][0];
				y = Pion[i]->T[Pion[i]->c][1];
				if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
					(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
				{
					continue;
				}
				else
				{
					if(Green[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[0]->T[(Green[0]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[0]->T[(Green[0]->c)+rand][1])
						k1 = 1;
					if(Green[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[1]->T[(Green[1]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[1]->T[(Green[1]->c)+rand][1])
						k2 = 1;
					if(Green[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[2]->T[(Green[2]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[2]->T[(Green[2]->c)+rand][1])
						k3 = 1;
					if(Green[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[3]->T[(Green[3]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[3]->T[(Green[3]->c)+rand][1])
						k4 = 1;
				}
			}
			for(i=12; i<16; i++)
			{
				x = Pion[i]->T[Pion[i]->c][0];
				y = Pion[i]->T[Pion[i]->c][1];
				if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
					(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
				{
					continue;
				}
				else
				{
					if(Green[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[0]->T[(Green[0]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[0]->T[(Green[0]->c)+rand][1])
						k1 = 1;
					if(Green[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[1]->T[(Green[1]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[1]->T[(Green[1]->c)+rand][1])
						k2 = 1;
					if(Green[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[2]->T[(Green[2]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[2]->T[(Green[2]->c)+rand][1])
						k3 = 1;
					if(Green[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[3]->T[(Green[3]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Green[3]->T[(Green[3]->c)+rand][1])
						k4 = 1;
				}
			}
			if(k1==1 || k2==1 || k3==1 || k4==1)
			{
				if(k1 == 0) g1.f = 0;
				if(k2 == 0) g2.f = 0;
				if(k3 == 0) g3.f = 0;
				if(k4 == 0) g4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 4:
			for(i=0; i<12; i++)
			{
				x = Pion[i]->T[Pion[i]->c][0];
				y = Pion[i]->T[Pion[i]->c][1];
				if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
					(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
				{
					continue;
				}
				else
				{
					if(Red[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[0]->T[(Red[0]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Red[0]->T[(Red[0]->c)+rand][1])
						k1 = 1;
					if(Red[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[1]->T[(Red[1]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Red[1]->T[(Red[1]->c)+rand][1])
						k2 = 1;
					if(Red[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[2]->T[(Red[2]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Red[2]->T[(Red[2]->c)+rand][1])
						k3 = 1;
					if(Red[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[3]->T[(Red[3]->c)+rand][0] && Pion[i]->T[Pion[i]->c][1] == Red[3]->T[(Red[3]->c)+rand][1])
						k4 = 1;
				}
			}
			if(k1==1 || k2==1 || k3==1 || k4==1)
			{
				if(k1 == 0) r1.f = 0;
				if(k2 == 0) r2.f = 0;
				if(k3 == 0) r3.f = 0;
				if(k4 == 0) r4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		default:
			return 0;
			break;
	}
}

void After_Kill(int tour, int game)
{
	int i;
	switch(tour)
	{
		case 1:
			for(i=0; i<4; i++)
			{
				if(Yellow[i]->T[Yellow[i]->c][0] == Blue[game-1]->T[Blue[game-1]->c][0] && Yellow[i]->T[Yellow[i]->c][1] == Blue[game-1]->T[Blue[game-1]->c][1])
					Yellow[i]->c = 0;
				if(Green[i]->T[Green[i]->c][0] == Blue[game-1]->T[Blue[game-1]->c][0] && Green[i]->T[Green[i]->c][1] == Blue[game-1]->T[Blue[game-1]->c][1])
					Green[i]->c = 0;
				if(Red[i]->T[Red[i]->c][0] == Blue[game-1]->T[Blue[game-1]->c][0] && Red[i]->T[Red[i]->c][1] == Blue[game-1]->T[Blue[game-1]->c][1])
					Red[i]->c = 0;
			}
			break;
		case 2:
			for(i=0; i<4; i++)
			{
				if(Blue[i]->T[Blue[i]->c][0] == Yellow[game-1]->T[Yellow[game-1]->c][0] && Blue[i]->T[Blue[i]->c][1] == Yellow[game-1]->T[Yellow[game-1]->c][1])
					Blue[i]->c = 0;
				if(Green[i]->T[Green[i]->c][0] == Yellow[game-1]->T[Yellow[game-1]->c][0] && Green[i]->T[Green[i]->c][1] == Yellow[game-1]->T[Yellow[game-1]->c][1])
					Green[i]->c = 0;
				if(Red[i]->T[Red[i]->c][0] == Yellow[game-1]->T[Yellow[game-1]->c][0] && Red[i]->T[Red[i]->c][1] == Yellow[game-1]->T[Yellow[game-1]->c][1])
					Red[i]->c = 0;
			}
			break;
		case 3:
			for(i=0; i<4; i++)
			{
				if(Blue[i]->T[Blue[i]->c][0] == Green[game-1]->T[Green[game-1]->c][0] && Blue[i]->T[Blue[i]->c][1] == Green[game-1]->T[Green[game-1]->c][1])
					Blue[i]->c = 0;
				if(Yellow[i]->T[Yellow[i]->c][0] == Green[game-1]->T[Green[game-1]->c][0] && Yellow[i]->T[Yellow[i]->c][1] == Green[game-1]->T[Green[game-1]->c][1])
					Yellow[i]->c = 0;
				if(Red[i]->T[Red[i]->c][0] == Green[game-1]->T[Green[game-1]->c][0] && Red[i]->T[Red[i]->c][1] == Green[game-1]->T[Green[game-1]->c][1])
					Red[i]->c = 0;
			}
			break;
		case 4:
			for(i=0; i<4; i++)
			{
				if(Blue[i]->T[Blue[i]->c][0] == Red[game-1]->T[Red[game-1]->c][0] && Blue[i]->T[Blue[i]->c][1] == Red[game-1]->T[Red[game-1]->c][1])
					Blue[i]->c = 0;
				if(Yellow[i]->T[Yellow[i]->c][0] == Red[game-1]->T[Red[game-1]->c][0] && Yellow[i]->T[Yellow[i]->c][1] == Red[game-1]->T[Red[game-1]->c][1])
					Yellow[i]->c = 0;
				if(Green[i]->T[Green[i]->c][0] == Red[game-1]->T[Red[game-1]->c][0] && Green[i]->T[Green[i]->c][1] == Red[game-1]->T[Red[game-1]->c][1])
					Green[i]->c = 0;
			}
			break;
		default:
			break;
	}
}

int Five(int tour)
{
	int s = 0;
	switch(tour)
	{
		case 1:
			if(b1.c == 1) s ++;
			if(b2.c == 1) s ++;
			if(b3.c == 1) s ++;
			if(b4.c == 1) s ++;
			if(s < 2 && (b1.c == 0 || b2.c == 0 || b3.c == 0 || b4.c == 0))
			{
				if(b1.c != 0) b1.f = 0;
				if(b2.c != 0) b2.f = 0;
				if(b3.c != 0) b3.f = 0;
				if(b4.c != 0) b4.f = 0;
				if(b1.c == 0) b1.f = 1;
				if(b2.c == 0) b2.f = 1;
				if(b3.c == 0) b3.f = 1;
				if(b4.c == 0) b4.f = 1;
				return 1;
			}
			else
				return 0;
			break;
		case 2:
			if(y1.c == 1) s ++;
			if(y2.c == 1) s ++;
			if(y3.c == 1) s ++;
			if(y4.c == 1) s ++;
			if(s < 2 && (y1.c == 0 || y2.c == 0 || y3.c == 0 || y4.c == 0))
			{
				if(y1.c != 0) y1.f = 0;
				if(y2.c != 0) y2.f = 0;
				if(y3.c != 0) y3.f = 0;
				if(y4.c != 0) y4.f = 0;
				if(y1.c == 0) y1.f = 1;
				if(y2.c == 0) y2.f = 1;
				if(y3.c == 0) y3.f = 1;
				if(y4.c == 0) y4.f = 1;
				return 1;
			}
			else
				return 0;
			break;
		case 3:
			if(g1.c == 1) s ++;
			if(g2.c == 1) s ++;
			if(g3.c == 1) s ++;
			if(g4.c == 1) s ++;
			if(s < 2 && (g1.c == 0 || g2.c == 0 || g3.c == 0 || g4.c == 0))
			{
				if(g1.c != 0) g1.f = 0;
				if(g2.c != 0) g2.f = 0;
				if(g3.c != 0) g3.f = 0;
				if(g4.c != 0) g4.f = 0;
				if(g1.c == 0) g1.f = 1;
				if(g2.c == 0) g2.f = 1;
				if(g3.c == 0) g3.f = 1;
				if(g4.c == 0) g4.f = 1;
				return 1;
			}
			else
				return 0;
			break;
		case 4:
			if(r1.c == 1) s ++;
			if(r2.c == 1) s ++;
			if(r3.c == 1) s ++;
			if(r4.c == 1) s ++;
			if(s < 2 && (r1.c == 0 || r2.c == 0 || r3.c == 0 || r4.c == 0))
			{
				if(r1.c != 0) r1.f = 0;
				if(r2.c != 0) r2.f = 0;
				if(r3.c != 0) r3.f = 0;
				if(r4.c != 0) r4.f = 0;
				if(r1.c == 0) r1.f = 1;
				if(r2.c == 0) r2.f = 1;
				if(r3.c == 0) r3.f = 1;
				if(r4.c == 0) r4.f = 1;
				return 1;
			}
			else
				return 0;
			break;
		default:
			return 0;
			break;
	}
}

int Open_Bloquage(int tour)
{
	int i, h;
	int o1=0;
	int o2=0;
	int o3=0;
	int o4=0;
	switch(tour)
	{
		case 1:
			for(i=0; i<16; i++)
			{
				if(Blue[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[0]->T[(Blue[0]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Blue[0]->T[(Blue[0]->c)][1])
					o1 ++;
				if(Blue[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[1]->T[(Blue[1]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Blue[1]->T[(Blue[1]->c)][1])
					o2 ++;
				if(Blue[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[2]->T[(Blue[2]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Blue[2]->T[(Blue[2]->c)][1])
					o3 ++;
				if(Blue[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Blue[3]->T[(Blue[3]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Blue[3]->T[(Blue[3]->c)][1])
					o4 ++;
			}
			if(o1 >= 2 || o2 >= 2 || o3 >= 2 || o4 >= 2)
			{
				if(o1 < 2) b1.f = 0;
				if(o2 < 2) b2.f = 0;
				if(o3 < 2) b3.f = 0;
				if(o4 < 2) b4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 2:
			for(i=0; i<16; i++)
			{
				if(Yellow[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[0]->T[(Yellow[0]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[0]->T[(Yellow[0]->c)][1])
					o1 ++;
				if(Yellow[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[1]->T[(Yellow[1]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[1]->T[(Yellow[1]->c)][1])
					o2 ++;
				if(Yellow[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[2]->T[(Yellow[2]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[2]->T[(Yellow[2]->c)][1])
					o3 ++;
				if(Yellow[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Yellow[3]->T[(Yellow[3]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Yellow[3]->T[(Yellow[3]->c)][1])
					o4 ++;
			}
			if(o1 >= 2 || o2 >= 2 || o3 >= 2 || o4 >= 2)
			{
				if(o1 < 2) y1.f = 0;
				if(o2 < 2) y2.f = 0;
				if(o3 < 2) y3.f = 0;
				if(o4 < 2) y4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 3:
			for(i=0; i<16; i++)
			{
				if(Green[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[0]->T[(Green[0]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Green[0]->T[(Green[0]->c)][1])
					o1 ++;
				if(Green[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[1]->T[(Green[1]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Green[1]->T[(Green[1]->c)][1])
					o2 ++;
				if(Green[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[2]->T[(Green[2]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Green[2]->T[(Green[2]->c)][1])
					o3 ++;
				if(Green[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Green[3]->T[(Green[3]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Green[3]->T[(Green[3]->c)][1])
					o4 ++;
			}
			if(o1 >= 2 || o2 >= 2 || o3 >= 2 || o4 >= 2)
			{
				if(o1 < 2) g1.f = 0;
				if(o2 < 2) g2.f = 0;
				if(o3 < 2) g3.f = 0;
				if(o4 < 2) g4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		case 4:
			for(i=0; i<16; i++)
			{
				if(Red[0]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[0]->T[(Red[0]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Red[0]->T[(Red[0]->c)][1])
					o1 ++;
				if(Red[1]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[1]->T[(Red[1]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Red[1]->T[(Red[1]->c)][1])
					o2 ++;
				if(Red[2]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[2]->T[(Red[2]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Red[2]->T[(Red[2]->c)][1])
					o3 ++;
				if(Red[3]->f == 1 && Pion[i]->T[Pion[i]->c][0] == Red[3]->T[(Red[3]->c)][0] && Pion[i]->T[Pion[i]->c][1] == Red[3]->T[(Red[3]->c)][1])
					o4 ++;
			}
			if(o1 >= 2 || o2 >= 2 || o3 >= 2 || o4 >= 2)
			{
				if(o1 < 2) r1.f = 0;
				if(o2 < 2) r2.f = 0;
				if(o3 < 2) r3.f = 0;
				if(o4 < 2) r4.f = 0;
				return 1;
			}
			else
				return 0;
			break;
		default:
			return 0;
			break;
	}
}

int Six(int tour)
{
	int i1, i2, i3, i4;
	switch(tour)
	{
		case 1:
			i1=0;	i2=1;	i3=2;	i4=3;
			break;
		case 2:
			i1=4;	i2=5;	i3=6;	i4=7;
			break;
		case 3:
			i1=8;	i2=9;	i3=10;	i4=11;
			break;
		case 4:
			i1=12;	i2=13;	i3=14;	i4=15;
			break;
		default:
			break;
	}
	int open = 0;
	int kill = 0;
	if(Pion[i1]->c == 0 || Pion[i1]->c == 72 || Pion[i2]->c == 0 || Pion[i2]->c == 72 || Pion[i3]->c == 0 || Pion[i3]->c == 72 || Pion[i4]->c == 0 || Pion[i4]->c == 72)
	{
		Normal();
		Bloquage(tour, 6);
		open = Open_Bloquage(tour);
		kill = Kill(tour, 6);
		if(kill==1) return 7;
		else return 6;
	}
	else
	{
		Normal();
		open = Open_Bloquage(tour);
		if(open == 0)
		{
			Normal();
			Bloquage(tour, 12);
			kill = Kill(tour, 12);
			if(kill==1) return 13;
			else
			{
				Normal();
				Bloquage(tour, 6);
				kill = Kill(tour, 6);
				if(kill==1) return 7;
				else
				{
					Normal();
					Bloquage(tour, 12);
					if(Pion[i1]->f == 1 || Pion[i2]->f == 1 || Pion[i3]->f == 1 || Pion[i4]->f == 1)
						return 12;
					else
					{
						Normal();
						Bloquage(tour, 6);
						if(Pion[i1]->f == 1 || Pion[i2]->f == 1 || Pion[i3]->f == 1 || Pion[i4]->f == 1)
							return 6;
						else
							return 6;
					}
				}
			}
		}
		else
		{
			Bloquage(tour, 6);
			if(Pion[i1]->f == 0 && Pion[i2]->f == 0 && Pion[i3]->f == 0 && Pion[i4]->f == 0)
			{
				Normal();
				Bloquage(tour, 12);
				kill = Kill(tour, 12);
				if(kill==1) return 13;
				else
				{
					Normal();
					Bloquage(tour, 6);
					kill = Kill(tour, 6);
					if(kill==1) return 7;
					else
					{
						Normal();
						Bloquage(tour, 12);
						if(Pion[i1]->f == 1 || Pion[i2]->f == 1 || Pion[i3]->f == 1 || Pion[i4]->f == 1)
							return 12;
						else
						{
							Normal();
							Bloquage(tour, 6);
							if(Pion[i1]->f == 1 || Pion[i2]->f == 1 || Pion[i3]->f == 1 || Pion[i4]->f == 1)
								return 6;
							else
								return 6;
						}
					}
				}
			}
			else
			{
				kill = Kill(tour, 6);
				if(kill==1)
				{
					Normal();
					open = Open_Bloquage(tour);
					Bloquage(tour, 12);
					if(Pion[i1]->f == 1 || Pion[i2]->f == 1 || Pion[i3]->f == 1 || Pion[i4]->f == 1)
					{
						kill = Kill(tour, 12);
						if(kill==1)
							return 13;
						else
						{
							Normal();
							open = Open_Bloquage(tour);
							Bloquage(tour, 6);
							kill = Kill(tour, 6);
							return 5;
						}
					}
					else
					{
						Normal();
						open = Open_Bloquage(tour);
						Bloquage(tour, 6);
						kill = Kill(tour, 6);
						return 7;
					}
				}
				else
				{
					Normal();
					open = Open_Bloquage(tour);
					Bloquage(tour, 12);
					if(Pion[i1]->f == 1 || Pion[i2]->f == 1 || Pion[i3]->f == 1 || Pion[i4]->f == 1)
					{
						kill = Kill(tour, 12);
						if(kill==1) return 13;
						else
							return 12;
					}
					else
					{
						Normal();
						open = Open_Bloquage(tour);
						Bloquage(tour, 6);
						return 6;
					}
				}
			}
		}
	}
}

int Parchis(int choix)
{
	int game_blue, game_yellow, game_green, game_red;
	switch(choix)
	{
		case 1:
			game_blue = 1;
			game_yellow = 0;
			game_green = 0;
			game_red = 0;
			break;
		case 2:
			game_blue = 1;
			game_yellow = 0;
			game_green = 1;
			game_red = 0;
			break;
		case 3:
			game_blue = 1;
			game_yellow = 1;
			game_green = 1;
			game_red = 0;
			break;
		case 4:
			game_blue = 1;
			game_yellow = 1;
			game_green = 1;
			game_red = 1;
			break;
		default:
			break;
	}
	Debut();
	long long n = 0;
	srand(time(NULL));
	n = (rand() % (9999999 - 1111111 + 1)) + 1111111;
	generateurCongruentiel(n,tableau);

	int tour = 1;
	int rand = 0;
	int game = 0;
	int kill = 0;
	int rekill = 0;
	int five_out = 0;
	int _10 = 0;
	int etat_six = 0;
	int nbr_six = 0;
	int repeat_five = 0;
	int first_out1 = 0;
	int first_out2 = 0;
	int first_out3 = 0;
	int first_out4 = 0;
	while(game != -1)
	{
		if(repeat_five == 1)
		{
			tour --;
			rand = 5;
		}
		else if(kill == 1)
		{
			tour --;
			rand = 20;
		}
		else if(rekill > 0)
		{
			tour --;
			rand = 20;
			rekill --;
			kill = 0;
		}
		else if(_10 == 1)
		{
			tour --;
			rand = 10;
		}
		else if(nbr_six == 1 || nbr_six == 2)
		{
			tour --;
			rand = random();
		}
		else if(nbr_six == 3)
		{
			rand = random();
			int tour_pre = tour - 1;
			nbr_six = 0;
			if(game == 1 || game == 2 || game == 3 || game == 4)
			{
				int x, y;
				switch(tour_pre)
				{
					case 1:
						x = Blue[game-1]->T[Blue[game -1]->c][0];
						y = Blue[game-1]->T[Blue[game -1]->c][1];
						if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
							(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
							break;
						else if(Blue[game-1]->c >= 65 && Blue[game-1]->c <= 72)
							break;
						else 
						{
							int v = 0;
							for(int i=0; i<4; i++)
							{
								if(Blue[i]->T[Blue[i]->c][0] == x && Blue[i]->T[Blue[i]->c][1] == y)
									v ++;
							}
							if(v < 2) Blue[game-1]->c = 0;
						}
						break;
					case 2:
						x = Yellow[game-1]->T[Yellow[game -1]->c][0];
						y = Yellow[game-1]->T[Yellow[game -1]->c][1];
						if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
							(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
							break;
						else if(Yellow[game-1]->c >= 65 && Yellow[game-1]->c <= 72)
							break;
						else 
						{
							int v = 0;
							for(int i=0; i<4; i++)
							{
								if(Yellow[i]->T[Yellow[i]->c][0] == x && Yellow[i]->T[Yellow[i]->c][1] == y)
									v ++;
							}
							if(v < 2) Yellow[game-1]->c = 0;
						}
						break;
					case 3:
						x = Green[game-1]->T[Green[game -1]->c][0];
						y = Green[game-1]->T[Green[game -1]->c][1];
						if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
							(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
							break;
						else if(Green[game-1]->c >= 65 && Green[game-1]->c <= 72)
							break;
						else 
						{
							int v = 0;
							for(int i=0; i<4; i++)
							{
								if(Green[i]->T[Green[i]->c][0] == x && Green[i]->T[Green[i]->c][1] == y)
									v ++;
							}
							if(v < 2) Green[game-1]->c = 0;
						}
						break;
					case 4:
						x = Red[game-1]->T[Red[game -1]->c][0];
						y = Red[game-1]->T[Red[game -1]->c][1];
						if( (x == Q[5][0] && y == Q[5][1]) || (x == Q[12][0] && y == Q[12][1]) || (x == Q[17][0] && y == Q[17][1]) || (x == Q[22][0] && y == Q[22][1]) || (x == Q[29][0] && y == Q[29][1]) || (x == Q[34][0] && y == Q[34][1]) || 
							(x == Q[39][0] && y == Q[39][1]) || (x == Q[46][0] && y == Q[46][1]) || (x == Q[51][0] && y == Q[51][1]) || (x == Q[56][0] && y == Q[56][1]) || (x == Q[63][0] && y == Q[63][1]) || (x == Q[68][0] && y == Q[68][1]) )
							break;
						else if(Red[game-1]->c >= 65 && Red[game-1]->c <= 72)
							break;
						else 
						{
							int v = 0;
							for(int i=0; i<4; i++)
							{
								if(Red[i]->T[Red[i]->c][0] == x && Red[i]->T[Red[i]->c][1] == y)
									v ++;
							}
							if(v < 2) Red[game-1]->c = 0;
						}
						break;
					default:
						break;
				}
			}
		}
		else
			rand = random();
		if(tour >= 5) tour = 1;
		if(rand == 1 || rand == 2 || rand == 3 || rand == 4 || rand == 5)
			nbr_six = 0;
		Position();
		Modifier();
		if(b1.c == 72 && b2.c == 72 && b3.c == 72 && b4.c == 72)
		{
			SDL_Delay(1000);
			return 1;
		}
		if(y1.c == 72 && y2.c == 72 && y3.c == 72 && y4.c == 72)
		{
			SDL_Delay(1000);
			return 2;
		}
		if(g1.c == 72 && g2.c == 72 && g3.c == 72 && g4.c == 72)
		{
			SDL_Delay(1000);
			return 3;
		}
		if(r1.c == 72 && r2.c == 72 && r3.c == 72 && r4.c == 72)
		{
			SDL_Delay(1000);
			return 4;
		}
		Normal();
		SDL_Delay(100);
		Des(tour, rand);
		_10 = 0;
		five_out = 0;
		kill = 0;
		etat_six = 0;
		if(rand == 5)
		{
			if(repeat_five == 1)
			{
				repeat_five = 0;
				rand = 6;
				five_out = Five(tour);
				Bloquage(tour, rand);
				kill = Kill(tour, rand);
			}
			else
			{
				five_out = Five(tour);
				if(five_out == 1)
				{
					kill = Five_Kill(tour);
					rand = 1;
				}
				else
				{
					Bloquage(tour, rand);
					kill = Kill(tour, rand);
				}
				switch(tour)
				{
					case 1:
						if(first_out1 == 0)
						{
							repeat_five = 1;
							if(kill == 1) rekill ++;
							first_out1 = 1;
						}
						break;
					case 2:
						if(first_out2 == 0)
						{
							repeat_five = 1;
							if(kill == 1) rekill ++;
							first_out2 = 1;
						}
						break;
					case 3:
						if(first_out3 == 0)
						{
							repeat_five = 1;
							if(kill == 1) rekill ++;
							first_out3 = 1;
						}
						break;
					case 4:
						if(first_out4 == 0)
						{
							repeat_five = 1;
							if(kill == 1) rekill ++;
							first_out4 = 1;
						}
						break;
					default:
						break;
				}
			}
		}
		else if(rand == 6)
		{
			int permition_plus = 0;
			switch(tour)
			{
				case 1:
					if(first_out1 == 1) permition_plus = 1;
					break;
				case 2:
					if(first_out2 == 1) permition_plus = 1;
					break;
				case 3:
					if(first_out3 == 1) permition_plus = 1;
					break;
				case 4:
					if(first_out4 == 1) permition_plus = 1;
					break;
				default:
					break;
			}
			etat_six = Six(tour);
			switch(etat_six)
			{
				case 5:
					rand = 6;
					kill = 1;
					if(permition_plus == 1)
					{
						if(nbr_six == 2) nbr_six ++;
						else nbr_six = 0;
					}
					break;
				case 6:
					rand = 6;
					if(permition_plus == 1) nbr_six ++;
					break;
				case 7:
					rand = 6;
					kill = 1;
					if(permition_plus == 1) nbr_six ++;
					break;
				case 12:
					rand = 12;
					if(permition_plus == 1) nbr_six ++;
					break;
				case 13:
					rand = 12;
					kill = 1;
					if(permition_plus == 1) nbr_six ++;
					break;
				default:
					break;
			}
		}
		else
		{
			Bloquage(tour, rand);
			kill = Kill(tour, rand);
		}
		_72(rand);
		if(tour == 1 && b1.f == 0 && b2.f == 0 && b3.f == 0 && b4.f == 0)
		{
			tour ++;
			game = 0;
			SDL_Delay(1000);
			continue;
		}
		else if(tour == 2 && y1.f == 0 && y2.f == 0 && y3.f == 0 && y4.f == 0)
		{
			tour ++;
			game = 0;
			SDL_Delay(1000);
			continue;
		}
		else if(tour == 3 && g1.f == 0 && g2.f == 0 && g3.f == 0 && g4.f == 0)
		{
			tour ++;
			game = 0;
			SDL_Delay(1000);
			continue;
		}
		else if(tour == 4 && r1.f == 0 && r2.f == 0 && r3.f == 0 && r4.f == 0)
		{
			tour ++;
			game = 0;
			SDL_Delay(1000);
			continue;
		}
		else if(tour == 1)
		{
			if(game_blue == 1) game = blue(rand);
			else game = blue_auto(rand);
			if(game == -1) continue;
			if(kill==1) After_Kill(tour, game);
			if(Blue[game-1]->c == 72) _10 = 1;
			tour ++;
			if(game_blue == 0) SDL_Delay(1000);
			continue;
		}
		else if(tour == 2)
		{
			if(game_yellow == 1) game = yellow(rand);
			else game = yellow_auto(rand);
			if(game == -1) continue;
			if(kill==1) After_Kill(tour, game);
			if(Yellow[game-1]->c == 72) _10 = 1;
			tour ++;
			if(game_yellow == 0) SDL_Delay(1000);
			continue;
		}
		else if(tour == 3)
		{
			if(game_green == 1) game = green(rand);
			else game = green_auto(rand);
			if(game == -1) continue;
			if(kill==1) After_Kill(tour, game);
			if(Green[game-1]->c == 72) _10 = 1;
			tour ++;
			if(game_green == 0) SDL_Delay(1000);
			continue;
		}
		else if(tour == 4)
		{
			if(game_red == 1) game = red(rand);
			else game = red_auto(rand);
			if(game == -1) continue;
			if(kill==1) After_Kill(tour, game);
			if(Red[game-1]->c == 72) _10 = 1;
			tour ++;
			if(game_red == 0) SDL_Delay(1000);
			continue;
		}
		else
			continue;
	}
	return 0;
}

int Regles_n(int n)
{
	switch(n)
	{
		case 1:
			Image("regles1.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 2:
			Image("regles2.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 3:
			Image("regles3.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 4:
			Image("regles4.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 5:
			Image("regles5.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		default:
			break;
	}
	SDL_RenderPresent(renderer);
}

int Regles()
{
	int n = 1;
	Regles_n(n);
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(X >= 195 && X <= (195 + 190) && Y >= 500 && Y <= (500 + 65))
						{
							return 1;
						}
						if(n < 5 && X >= 485 && X <= (485 + 65) && Y >= 500 && Y <= (500 + 65))
						{
							n ++;
							Regles_n(n);
						}
						if(n > 1 && X >= 30 && X <= (30 + 65) && Y >= 500 && Y <= (500 + 65))
						{
							n --;
							Regles_n(n);
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return 0;
					break;
				default:
					continue;
			}
		}
	}
}

int Menu()
{
	Image("menu.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_RenderPresent(renderer);
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(X >= 40 && X <= (40 + 225) && Y >= 420 && Y <= (420 + 65))
						{
							return 2;
						}
						if(X >= 315 && X <= (315 + 225) && Y >= 420 && Y <= (420 + 65))
						{
							return 3;
						}
						if(X >= 166 && X <= (166 + 265) && Y >= 500 && Y <= (500 + 60))
						{
							return 1;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return 0;
					break;
				default:
					continue;
			}
		}
	}
}

int Choix()
{
	Image("choix.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_RenderPresent(renderer);
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(X >= 380 && X <= (380 + 175) && Y >= 500 && Y <= (500 + 60))
						{
							return -1;
						}
						if(X >= 164 && X <= (164 + 250) && Y >= 50 && Y <= (50 + 100))
						{
							return 1;
						}
						if(X >= 164 && X <= (164 + 250) && Y >= 190 && Y <= (190 + 100))
						{
							return 2;
						}
						if(X >= 164 && X <= (164 + 250) && Y >= 330 && Y <= (330 + 100))
						{
							return 3;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return 0;
					break;
				default:
					continue;
			}
		}
	}
}

int Winner(int parchis)
{
	switch(parchis)
	{
		case 1:
			Image("blue_win.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 2:
			Image("yellow_win.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 3:
			Image("green_win.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		case 4:
			Image("red_win.png", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			break;
		default:
			break;
	}
	SDL_RenderPresent(renderer);
	SDL_bool program_launched = SDL_TRUE;
	while(program_launched)
	{
		SDL_Event event;
		while(SDL_WaitEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						int X = event.button.x;
						int Y = event.button.y;
						if(X >= 380 && X <= (380 + 175) && Y >= 500 && Y <= (500 + 60))
						{
							return 1;
						}
					}
					break;
				case SDL_QUIT:
					program_launched = SDL_FALSE;
					return 0;
					break;
				default:
					continue;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("PARCHIS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	int menu;
	int regles;
	int parchis;
	int winner;
	int choix;
	while(1)
	{
		menu = Menu();
		if(menu == 0) break;
		if(menu == 1)
		{
			regles = Regles();
			if(regles == 0) break;
			if(regles == 1) continue;
		}
		if(menu == 2)
		{
			parchis = Parchis(4);
			if(parchis == 0) continue;
			else
			{
				winner = Winner(parchis);
				if(winner == 0) break;
				if(winner == 1) continue;
			}
		}
		if(menu == 3)
		{
			choix = Choix();
			if(choix == 0) break;
			if(choix == -1) continue;
			else parchis = Parchis(choix);
			if(parchis == 0) continue;
			else
			{
				winner = Winner(parchis);
				if(winner == 0) break;
				if(winner == 1) continue;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

//cd desktop
//cd Parchis
//gcc src/Parchis.c -o bin/PARCHIS -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image