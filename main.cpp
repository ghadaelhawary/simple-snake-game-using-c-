#include <iostream>
#include <algorithm>  // for rand
#include <conio.h>   // to get character from console window we use it in input function
#include <windows.h> // to make console slower => sleep() 
using namespace std;

//global variables
bool gameOver;
const int width = 20;
const int height = 20;
int score =0;
int x ,y; //for head position
int fruitx , fruity ; //for fruit position
//control movement position
enum edirection {stop,
                 l,
				 r,
				 u,
				 d}  ;
edirection direc;
				 
// tail will be consists of two arrays one for x-cor and the other for y-cor with max 100 circle
int tailx [100], taily [100];
int ntail; // specify the length of the tail


void setup(){
	gameOver = false;
	direc = stop;         //to stop them from moving at the begining of the game
	x=width /2;
	y=height/2;         // position to make snake at the senter of the map
	fruitx = rand() % width;
	fruity = rand() % height;
	score = 0;
}
//
void draw(){
	system("cls "); // to clear the console window
	
	//to control borders for width and height

	for (int i = 0; i< width+1 ; i++) {
		cout<<"#";
	} 
	cout<<"\n";
	
	/* to draw map #####
	               #   #
				   #####
				   */
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			if(j == 0 ||j == width-1)
				cout<<"#";
				// to draw head
			if(i == y && j== x)
			    cout<<"0";
			else if( i == fruity && j == fruitx)
			     cout<<"f";
			else
			{
				// draw the snake
				bool print = false;
				for (int k=0; k<ntail ; k++){
					// this will draw the tail but not following the head so we will make a boolean => print to make it one part
				     
					if(tailx[k] == j && taily[k] == i){
						cout<<"0";
						print = true;
					}
				
				}
					if(!print)
					  cout<<" ";
				
			}
		       	
			
		}
	cout<<endl;
	} 
	
	
	for (int k = 0; k< width+1 ; k++) {
		cout<<"#";
	} 
	cout<<"\n";
	cout<<"score  "<<score<<endl;
	
}
//
void input(){
	//kbhit() it returns a positive bool if user entered a no if not it return zero 
	if(_kbhit()){
		// we will make switch to get asci code for the character that the user entered
		// _getch to get asci
		switch(_getch())
		{
			case 'a':
			        direc = l;
			     	break;
			     	
			case 'd':
			     	direc = r;
			     	break;
			case 'w':
			     	direc= u;
			     	break;
			case 's':
			     	direc = d;
			     	break;
			case 'x' :
			     	gameOver = true;
			     	break;
			
				
		}
	}
	
}


void logic(){
	
	// var for the tail
	 int prevx = tailx[0];
	 tailx[0] = x;
	 int prevy = taily[0];
	 taily[0] = y;
	 int prev2x ,prev2y ;
	 
	 //incresing draw the snake starting with 1 cause zero we had reserved
	 for(int i=1; i<ntail; i++){
	 	prev2x = tailx[i];
	 	prev2y = taily[i];
	 	
	 	tailx[i] = prevx;
	 	taily[i] = prevy;
	 	
	 	prevx = prev2x;
	 	prevy = prev2y; 
	 }
	switch(direc){
		case l :
			 x--;
			 break;
		case r :
			 x++;
			 break;
		case u :
			 y--;
			 break;
		case d :
			 y++;
			 break;
		default :
			break;
			 
	}
	// if head reached the wall or get out the boundary => gameover  
	if(x>width || x<0 || y>height || y<0)
	 gameOver = true;
	 
	 //we need to make if i head the body of the snake => game over
	 for (int i = 0 ; i< ntail ; i++){
	 	if (tailx[i] == x && taily[i] == y)
	 	    gameOver = true;
	 }
	 
	 // if head reched the fruit increse the score then i will increse the tail
	 if(x == fruitx && y == fruity)
	 {
	   score ++;
	   ntail ++;
	  
	  // to change fruit position 
	  
	  	fruitx = rand() % width;
    	fruity = rand() % height;
	 }
	  
	
}

int main() {
	
	setup();
	while(!gameOver){
		draw();
		input();
		logic();
		Sleep(50);
	}
	return 0;
}
