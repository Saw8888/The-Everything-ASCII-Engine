#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

int sizeX = 20;
int sizeY = 20;

int grid[20][20] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0},
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
                    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};

int count_nbr(int grid[sizeX][sizeY], int x, int y){
 int n_count = 0;
 if (grid[x-1][y-1]==1) //Top Right
     n_count++;

 if(grid[x-1][y]==1) //Top
     n_count++;

 if(grid[x-1][y+1]==1) //Top Left
     n_count++;

 if(grid[x][y-1]==1) //Right
     n_count++;

 if(grid[x][y+1]==1) //Left
     n_count++;

 if(grid[x+1][y-1]==1) //Bottom Right
     n_count++;

 if(grid[x+1][y]==1) //Bottom
     n_count++;
     
 if(grid[x+1][y+1]==1) //Bottom left
     n_count++;
 return n_count;
}

int main(void){
 int neighbour_count[sizeX][sizeY];
    int x,y,iterations;

 for(iterations=0;iterations<500;iterations++){
  system("cls"); //Clear screen
  for(x=0;x<sizeX;x++){
    printf("\n");
    for(y=0;y<sizeY;y++){
     if(grid[x][y]==1){
      printf("@");
             }
    else{
      printf(" ");
    }
    neighbour_count[x][y] = count_nbr(grid,x,y);
         }
  }
                    
  for(x=0;x<sizeX;x++){
     for(y=0;y<sizeY;y++){
        if(neighbour_count[x][y] < 2 || neighbour_count[x][y] > 3)
     grid[x][y] = 0;
    else if(neighbour_count[x][y] == 3)
     grid[x][y]=1;
   }
  }
  printf("\n");
 }
}
