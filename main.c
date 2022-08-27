#include<stdio.h>
#include <conio.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

/*
w == 119
a == 97
s == 115
d == 100
*/

int playerX = 10;
int playerY = 0;

const int sizeX = 20;
const int sizeY = 20;
const int dead = 0;
const int stone = 1;
const int sand = 2;
const int water = 3;

char ch;
int itemChoice = 2;

int grid[20][20] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
};

void draw_screen(){
 system("cls");
 int y,x;
 for(y=0;y<sizeY;y++){
  for(x=0;x<sizeX;x++){
		 if(grid[y][x] >= 1 || y == playerY && x == playerX){
    putc('@', stdout);
   }
   if(grid[y][x] == dead){
    putc(' ', stdout);
   }
  }
  if(y == 1){
  	switch(itemChoice){
  		case 2:
  	  printf("Current Item : sand");
  	  break;
  		case 3:
  	  printf("Current Item : water");
  	  break;
  	 case 1:
  	  printf("Current Item : stone");
  	  break;
   }
  }
  putc('\n', stdout);
 }
}

void keyboardInput(){
	if(kbhit()){
 	 ch = getch();
 	 switch(ch){
	   case 'a':
	   	playerX--;
	   	break;
	   	
				case 'd':
				 playerX++;
				 break;
        
				case 'w':
				 playerY--;
				 break;
       
				case 's':
				 playerY++;
				 break;
				   
				case '1':
				 itemChoice = stone;
				 break;
				  
				case '2':
				 itemChoice = sand;
				 break;
		
				case '3':
				 itemChoice = water;
				 break;
				 
				case ' ':
					if(grid[playerY+1][playerX] == dead){
					 grid[playerY+1][playerX] = itemChoice;
					}
					break;
		 }
		}
}

void simulate_sand(int grid[sizeX][sizeY],int x,int y){
 if(grid[y][x] == dead || y >= sizeY - 1){ // do nothing if dead or already at the bottom of the screen
  return;
 }
 else if(grid[y+1][x] == dead){ // move down if empty
  grid[y][x] = dead;
  grid[y+1][x] = sand;
 }
 else if(x > 0 && grid[y+1][x-1] == dead){ // move down and left if empty
  grid[y][x] = dead;
  grid[y+1][x-1] = sand;
 }
 else if(x < sizeX - 1 && grid[y+1][x+1] == dead){ // move down and right if empty
  grid[y][x] = dead;
  grid[y+1][x+1] = sand;
 }
}

void simulate_water(int grid[sizeX][sizeY],int x,int y){
 if(grid[y][x] == dead || y >= sizeY - 1){ // do nothing if dead or already at the bottom of the screen
  return;
 }
 else if(grid[y+1][x] == dead){ // move down if empty
  grid[y][x] = dead;
  grid[y+1][x] = water;
 }
 else if(x > 0 && grid[y+1][x-1] == dead){ // move down and left if empty
  grid[y][x] = dead;
  grid[y+1][x-1] = water;
 }
 else if(x < sizeX - 1 && grid[y+1][x+1] == dead){ // move down and right if empty
  grid[y][x] = dead;
  grid[y+1][x+1] = water;
 }
 else if(x < sizeX - 1 && grid[y][x+1] == dead){
 	grid[x][y] = dead;
 	grid[y][x+1] = water;
 }
 else if(x > 0 && grid[y][x-1] == dead){
 	grid[x][y] = dead;
 	grid[y][x-1] = water;
 }
}

int main(void){
 int iterations,x,y;
 
 for(iterations=0;iterations<1000;iterations++){
  keyboardInput();
  for(y=sizeY-1;y>=0;y--){
   for(x=sizeX-1;x>=0;x--){
			 if(grid[y][x] == sand){
     simulate_sand(grid, x, y);
    }
    if(grid[y][x] == water){
    	simulate_water(grid, x, y);
    }
   }
  }
 draw_screen();
 sleep(0.01);
 }
}
