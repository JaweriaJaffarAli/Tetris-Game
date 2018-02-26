#include<iostream>
#include <SDL.h>

#include<SDL_gfx.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<iomanip>
#include<fstream>
using namespace std;
int o = 10;

static SDL_Surface *scoree;
static SDL_Texture *scoretext;
static SDL_Color scorecolor = { 250,250,250 }; //text color
static TTF_Font *scorefont; // text font
static SDL_Window  *wind;
static SDL_Renderer *re;
static SDL_Surface *img;
static SDL_Texture *background;
class HighScore
{ 


   long double score;
   int id;                 //player id
   static int count;
   
public:
	HighScore *next;
	
	HighScore(long double sc)
	{ 
	 score =sc;
	 next=NULL;
	 count++;
	 id = count;
	}
	HighScore(int x)
	{}
	
	void show()
	{
		
		string scor = to_string(score);       //converting score into string
		SDL_Rect scorerect;
		scorerect.x = 200;                   // setting coordinates
		scorerect.y = 100+o;
		scorerect.w = 150;  scorerect.h = 30;
		scoree = TTF_RenderText_Blended(scorefont, scor.c_str(), scorecolor);
		scoretext = SDL_CreateTextureFromSurface(re, scoree);
		SDL_RenderCopy(re, scoretext, NULL, &scorerect);
		SDL_RenderPresent(re);
		o += 20;
	}

	long double getScore()
	{
		return score;
	}
	int getId()
	{
		return id;
	}
	void setCount(int c)
	{
		count = c;
	}
	static int getCount()
	{
		return count;
	}
 };

int HighScore::count = 0;

class PlayerRecord
{  
	HighScore *list;            //head pointer

public:
   PlayerRecord()
  {  list=NULL;   }

  void add(long double x)
  {

	HighScore *p = new HighScore(x);
	HighScore *temp = list;
	HighScore *prev = list;
	if (list==NULL) 
	{
    list=p;
	}
	else
	{
	while (temp!=NULL)
    { // Compare priority
	if (temp->getScore() < p->getScore())
	{
	if(temp==list) 
	{
	p->next=list;
	list=p;				
	break;
	}
	p->next=temp;
	prev->next=p;
	break;
	}//if
	prev=temp; //moving forward
	temp=temp->next;
	}//while
if (temp==NULL)
{
prev->next = p;

   }  //if end
	} //else
  }

  int displayall()
  { 
	 // const SDL_RendererInfo *info;

	  //Uint32 videoflags;
	  if (SDL_Init(SDL_INIT_VIDEO) != 0)
	  {
		  fprintf(stderr, "SDL_Init Error: %s", SDL_GetError());
		  return 1;
	  }

	  if (TTF_Init()<0)
	  {
		  fprintf(stderr, "TTF_Init Error: %s", TTF_GetError());
		  return 1;
	  }
	  wind = SDL_CreateWindow("Tetris",
		  SDL_WINDOWPOS_UNDEFINED,
		  SDL_WINDOWPOS_UNDEFINED,
		  600, 550,
		  SDL_WINDOW_OPENGL);

	  if (wind == NULL) {
		  fprintf(stderr, "SDL_CreateWindow Error: %s", SDL_GetError());
		  SDL_Quit();
		  return 1;
	  }

	  re = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	  if (re == NULL) {
		  SDL_DestroyWindow(wind);
		  fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
		  SDL_Quit();
		  return 1;
	  }

	  //creating rectangle to dispaly score.

	  SDL_Rect scorerect;
	  scorerect.x = 200; scorerect.y = 250;
	  scorerect.w = 100;  scorerect.h = 15;

	  img = SDL_LoadBMP("highscore1.bmp");
	  background = SDL_CreateTextureFromSurface(re, img);
	  SDL_FreeSurface(img);
	  SDL_RenderCopy(re, background, NULL, NULL);

	  scorefont = TTF_OpenFont("TimeRoman.ttf", 29);
	 system("cls");
	  if(list==NULL)
    cout<<"NO record..!";
  else
  {  HighScore *temp=list;
  int i=1;
      while(temp!=NULL)
	  {
		  if(i<21)
		{  
		  temp->show(); } 
		 
		 
	  temp=temp->next;
	  i++;
	  }
    }//else  end
	  return 1;
  }

  void remove(long double sc)
  { 
     int found=0;

	if(list==NULL)
		cout<<"no record..!";
	else
	{  HighScore *temp=list;
	   HighScore *pre=list;
	  while(temp!=NULL)
	  { if( temp->getScore() == sc)
	       {   found=1;
		    HighScore *e=temp;
		    e->show();
		   if(temp==list) //first item to b removed
			list=list->next;
		   else
		    pre->next=temp->next;
	    delete e;  
		cout<<"record deleted"<<endl;
		break;
	     }
	    pre=temp;
	    temp=temp->next;  
        }//while end
	if(found==0)
	cout<<"Record not found."<<endl;
	}//else end
  }

  // saving into file

  void save()
{ 
	ofstream out;
  out.open("score",ios::out | ios::binary);
  if(!out)
	 cout<<"cannot save..";
  else
   {  HighScore *temp=list;
	 while(temp!=NULL)
     {	out.write((char*) temp,sizeof(HighScore));
	    temp=temp->next;
      }
	 out.close();
   }

  }
  void reterive()
  { ifstream in;
  in.open("score",ios::in | ios::binary);
  if(!in)
	 cout<<"cannot reterive..";
  else
  { HighScore *temp=NULL;
  HighScore e(0);
     while(1)
	{ in.read((char*) &e,sizeof(HighScore));
	  HighScore *p=new HighScore(e);      
	if(list==NULL)
            {list=p;
		    temp=list;}
         else{
             temp->next=p;
			 temp=temp->next;
			 if(e.next==NULL)
			 {  
				 e.setCount(e.getId());
				 break;}			
			 }         
       }
	 in.close(); 
	}
  
  }

  void cleanUp()
  {
	  SDL_DestroyTexture(background);
	  SDL_DestroyRenderer(re);
	  SDL_DestroyTexture(scoretext);
	  SDL_DestroyWindow(wind);
	  SDL_Quit();
	  TTF_Quit();
  }
};
