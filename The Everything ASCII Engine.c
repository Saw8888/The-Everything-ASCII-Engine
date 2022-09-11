#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int playerX = 10;
int playerY = 0;

const int sizeX = 20;
const int sizeY = 20;
const int dead = 0;
const int stone = 1;
const int sand = 2;
const int water = 3;
const int acid = 4;
const int player = 99;

char ch;
int randNum;
int dieProb;
int itemChoice = 2;

int grid[20][20];

void draw_screen(){
 system("cls");
 int y,x;
 for(y=0;y<sizeY;y++){
  for(x=0;x<sizeX;x++){
		 if(grid[y][x] == 1){
		 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN);
    putc(' ', stdout);
   }
   if(grid[y][x] == 2){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE/255 | BACKGROUND_GREEN);
    putc(' ', stdout);
   }
   if(grid[y][x] == 3){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED/255 | BACKGROUND_BLUE | BACKGROUND_GREEN/255);
    putc(' ', stdout);
   }
   if(grid[y][x] == 4){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED/255 | BACKGROUND_BLUE/255 | BACKGROUND_GREEN);
    putc(' ', stdout);
   }                  
   if(grid[y][x] == 99){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_BLUE/255 | BACKGROUND_GREEN/255);
    putc(' ', stdout);
   }
   if(grid[y][x] == dead){
   	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED/255 | BACKGROUND_BLUE/255 | BACKGROUND_GREEN/255);
    putc(' ', stdout);
   }
  }
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

  if(y == 1){
  	switch(itemChoice){
  		case 2:
  	  printf("Current Item : sand");
  	  break;
  		case 3:
  	  printf("Current Item : water");
  	  break;
  	 case 4:
  	 	printf("Current Item : acid");
  	  break;
  	 case 1:
  	  printf("Current Item : stone");
  	  break;
   }
  }
  putc('\n', stdout);
 }
}

int randRange(int min, int max){
 return min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1));
}

void keyboardInput(){
	if(kbhit()){
 	 ch = getch();
 	 switch(ch){
	   case 'a':
	   	if(playerX > 0 && grid[playerY][playerX-1]==dead){playerX--;}
	   	break;
	   	
				case 'd':
					if(playerX < sizeX-1 && grid[playerY][playerX+1]==dead){playerX++;}
				 break;
        
				case 'w':
					if(playerY > 0 && grid[playerY-1][playerX]==dead){playerY--;}
				 break;
       
				case 's':
				 	if(playerY < sizeY-1 && grid[playerY+1][playerX]==dead){playerY++;}
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
				 
				case '4':
					itemChoice = acid;
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
	randNum = randRange(0,1);
 if(grid[y][x] == dead || y >= sizeY - 1){ // do nothing if dead or already at the bottom of the screen
  return;
 }
 else if(grid[y+1][x] == dead){ // move down if empty
  grid[y][x] = dead;
  grid[y+1][x] = sand;
 }
 else if(x > 0 && grid[y+1][x-1] == dead && randNum == 0){ // move down and left if empty
  grid[y][x] = dead;
  grid[y+1][x-1] = sand;
 }
 else if(x < sizeX - 1 && grid[y+1][x+1] == dead && randNum == 1){ // move down and right if empty
  grid[y][x] = dead;
  grid[y+1][x+1] = sand;
 }
}

void simulate_acid(int grid[sizeX][sizeY],int x,int y){
	randNum = randRange(0,1);
	dieProb = randRange(0,40);
	if(dieProb == 21){
		grid[y][x] = dead;
	}
	if(grid[y][x] == dead || y >= sizeY - 1){ // do nothing if dead or already at the bottom of the screen
  return;
 }
 else if(grid[y+1][x] == dead){ // move down if empty
  grid[y][x] = dead;
  grid[y+1][x] = acid;
 }                     
	else if(x > 0 && grid[y+1][x-1] == dead && randNum == 0){ // move down and left if empty
	 grid[y][x] = dead;
  grid[y+1][x-1] = acid;
 }
 else if(x < sizeX - 1 && grid[y+1][x+1] == dead && randNum == 1){ // move down and right if empty
  grid[y][x] = dead;
  grid[y+1][x+1] = acid;
 }
 else if(x < sizeX - 1 && grid[y][x+1] == dead && randNum == 0){
 	grid[y][x] = dead;
 	grid[y][x+1] = acid;
 }
 else if(x > 0 && grid[y][x-1] == dead && randNum == 1){
 	grid[y][x] = dead;
 	grid[y][x-1] = acid;
 }
 else{
 	if(randNum==1){
	 	if(grid[y+1][x] == stone || grid[y+1][x] == sand){grid[y+1][x] = dead;}
	  else if(grid[y+1][x+1] == stone || grid[y+1][x+1] == sand){grid[y+1][x+1] = dead;}
	  else if(grid[y+1][x-1] == stone || grid[y+1][x-1] == sand){grid[y+1][x-1] = dead;}
	  else if(grid[y][x-1] == stone || grid[y][x-1] == sand){grid[y][x-1] = dead;}
	  else if(grid[y][x+1] == stone || grid[y][x+1] == sand){grid[y][x+1] = dead;}
	  else if(grid[y-1][x] == stone || grid[y-1][x] == sand){grid[y+1][x] = dead;}
	  else if(grid[y-1][x-1] == stone || grid[y-1][x-1] == sand){grid[y+1][x] = dead;}
	  else if(grid[y-1][x+1] == stone || grid[y-1][x+1] == sand){grid[y+1][x] = dead;}
  }
 }
}

void simulate_water(int grid[sizeX][sizeY],int x,int y){
	randNum = randRange(0,1);
 if(grid[y][x] == dead || y >= sizeY - 1){ // do nothing if dead or already at the bottom of the screen
  return;
 }
 else if(grid[y+1][x] > 0 && grid[y+1][x+1] > 0 && grid[y+1][x-1] > 0 && grid[y][x+1] > 0 && grid[y][x-1] > 0 && randNum == 1){
 	grid[y][x] = dead;
 	grid[y-1][x] = water;
 }
 else if(grid[y+1][x] == dead){ // move down if empty
  grid[y][x] = dead;
  grid[y+1][x] = water;
 }
 else if(x > 0 && grid[y+1][x-1] == dead && randNum == 0){ // move down and left if empty
  grid[y][x] = dead;
  grid[y+1][x-1] = water;
 }
 else if(x < sizeX - 1 && grid[y+1][x+1] == dead && randNum == 1){ // move down and right if empty
  grid[y][x] = dead;
  grid[y+1][x+1] = water;
 }
 else if(x < sizeX - 1 && grid[y][x+1] == dead && randNum == 0){
 	grid[y][x] = dead;
 	grid[y][x+1] = water;
 }
 else if(x > 0 && grid[y][x-1] == dead && randNum == 1){
 	grid[y][x] = dead;
 	grid[y][x-1] = water;
 }
}

int main(void){
 int x,y;
 float frameTime, FPS;
 grid[playerY][playerX]=player;
 
 while(1){
 	clock_t start = clock();
  keyboardInput();
  for(y=sizeY-1;y>=0;y--){
   for(x=sizeX-1;x>=0;x--){
   	if(grid[y][x] == player){
   		grid[y][x] = 0;
   		grid[playerY][playerX]=player;
   	}
			 if(grid[y][x] == sand){
     simulate_sand(grid, x, y);
    }
    if(grid[y][x] == water){
    	simulate_water(grid, x, y);
    }
    if(grid[y][x] == acid){
    	simulate_acid(grid, x, y);
    }
   }
  }  
  draw_screen();
  clock_t stop = clock();
  frameTime = (float)(stop - start) / CLOCKS_PER_SEC;
  FPS = 1.0 / frameTime;
  printf("FPS: %f\n",FPS);
 }
}

