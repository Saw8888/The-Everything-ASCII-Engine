#include <stdio.h>
#include <conio.h>
#include <time.h>

#include <windows.h>
#define sleep(x) Sleep(1000 * (x))

int playerX = 10;
int playerY = 0;

#define sizeX 20
#define sizeY 20

const int dead = 0;
const int stone = 1;
const int sand = 2;
const int water = 3;
const int acid = 4;
const int player = 99;


int counter0,counter1,counter2,counter3,counter4; //We make a counter for each particle for the RLE algorithm to determine how long to make the string and what colour

char ch;
int randNum;
int dieProb;
int itemChoice = 2;

int frame = 0;
int run = 1;

int grid[sizeY][sizeX];
int old_grid[sizeY][sizeX]; //To compare and see if there are any changes compared to the new grid
int grid_similarity = 0;

void goTo(int x,int y){printf("%c[%d;%df",0x1B,y,x);}

void colorChar(int r, int g, int b){
	printf("\x1b[48;2;%d;%d;%dm",r,g,b);
}

void print_chars(int number_of_spaces, char character, int r, int g, int b){ //Prints x number of spaces
  char* spaces = malloc(sizeof(char)*number_of_spaces + 1);
  memset (spaces,character,number_of_spaces);
  spaces[number_of_spaces] = '\0';
  //Colour option
  colorChar(r,g,b);
  fputs(spaces, stdout);
  free(spaces);
}

void fullscreen(){
 keybd_event(VK_MENU, 0x38, 0, 0);
 keybd_event(VK_RETURN, 0x1c, 0, 0);
 keybd_event(VK_RETURN, 0X1c, KEYEVENTF_KEYUP, 0);
 keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void cleanup(){
	printf("\x1b[2J");//clean up the alternate buffer
	printf("\x1b[?1049l");	//switch back to the normal buffer
	printf("\x1b[?25h"); //show the cursor again
	printf("\x1b[48;2;12;12;12m"); //Return to the black colour
}

void setup(){
	printf("\x1b[?1049h");
 printf("\x1b[2J");
	printf("\x1b[?25l");
}

void draw_screen(){
 int y, x, simily;
 goTo(0,0);
 for(y=0;y<sizeY;y++){
 	for(simily=0;simily<sizeX;simily++){
 	 if(old_grid[y][simily] != grid[y][simily]){
 	  grid_similarity = 1;
 	 }
  }
  if(grid_similarity == 1 || frame == 0){
		 for(x=0;x<sizeX;x++){
			  if(grid[y][x] == dead){
		   counter0++;
		   if(grid[y][x+1] != 0 || x+1 >= sizeX){
		    print_chars(counter0, ' ', 12,12,12);
		    counter0 = 0;
		   }
		  }
			  else if(grid[y][x] == stone){
		   counter1++;
		   if(grid[y][x+1] != 1 || x+1 >= sizeX){
		    print_chars(counter1, ' ', 255,255,255);
		    counter1 = 0;
		   }
		  }
			  else if(grid[y][x] == sand){
		   counter2++;
		   if(grid[y][x+1] != 1 || x+1 >= sizeX){
		    	print_chars(counter2, ' ', 255,255,0);
		    counter2 = 0;
		   }
		  }
			  else if(grid[y][x] == water){
		   counter3++;
		   if(grid[y][x+1] != 1 || x+1 >= sizeX){
		    print_chars(counter3, ' ', 0,0,255);
		    counter3 = 0;
		   }
		  }
			  else if(grid[y][x] == acid){
		   counter4++;
		   if(grid[y][x+1] != 1 || x+1 >= sizeX){
		    print_chars(counter4, ' ', 0,255,0);
		    counter4 = 0;
		   }
		  }
			  else if(grid[y][x] == player){
		   print_chars(1, ' ', 255,0,0);
		  }
			  grid_similarity = 0;
		 }
		}
	 printf("\n");
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
				
				case 'q':
					run = 0;
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

void simulate_sand(int x,int y){
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

void simulate_acid(int x,int y){
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

void simulate_water(int x,int y){
	randNum = randRange(0,1);
 if(grid[y][x] == dead || y >= sizeY - 1){ // do nothing if dead or already at the bottom of the screen
  return;
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
 
 fullscreen();
 setup();
 while(run == 1){
 	clock_t start = clock();
  keyboardInput();
  
  for(y=0;y<sizeY;y++){
	  for(x=0;x<sizeX;x++){
    old_grid[x][y] = grid[x][y];
   }
  }
  
  for(y=sizeY-1;y>=0;y--){
   for(x=sizeX-1;x>=0;x--){
	  	if(grid[y][x] == player){
	  		grid[y][x] = 0;
	  		grid[playerY][playerX]=player;
	  	}
			 if(grid[y][x] == sand){
	    simulate_sand(x, y);
	   }
	   if(grid[y][x] == water){
	   	simulate_water(x, y);
	   }
	   if(grid[y][x] == acid){
	   	simulate_acid(x, y);
	   }
   }
  }
  draw_screen();
  clock_t stop = clock();
  frameTime = (float)(stop - start) / CLOCKS_PER_SEC;
  FPS = 1.0 / frameTime;
  goTo(100,2);
  colorChar(12,12,12);
  printf("FPS: %f\n",FPS);
  goTo(100,0);
  switch(itemChoice){
	 	case 2:
	   printf("Current Item : sand ");
	   break;
	 	case 3:
	   printf("Current Item : water ");
	   break;
	  case 4:
	  	printf("Current Item : acid ");
		  break;
	  case 1:
    printf("Current Item : stone ");
    break;
	 }
	 if(frame == 0){
	 	frame = 1;
	 }
 }
 fullscreen();
 cleanup();
}
