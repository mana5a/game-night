#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <iomanip>
#include<sstream>
#include<graphics.h>

using namespace std;



struct location
{
  int x;
  int y;
};

void back_up();
void start_new_game();
int check();
void print();
void new_tile();
int move_up(int );
int move_down(int);
int move_left(int);
int move_right(int);
void undo();
void chk_2048(int);

int grid[4][4], grid_bck[4][4];
int scr,genius=0;

void gotoxy( short x, short y)
{

    COORD pos= {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

}


int main()

{
  int gd = DETECT, gm;
  initwindow(1500,1200,"2048");                      //INITIALISES GRAPHIC WINDOW


  char ch;
  char exit_var;
  char bk_to_gm;



  int x, y, color, angle = 0;
  struct arccoordstype a, b;;

 delay(200);

   while(angle<=360)
   {
      settextstyle(10,HORIZ_DIR,2);                          //PRINTS LOADING SCREEN
      setcolor(WHITE);
      outtextxy(620,390,"Loading...");
      setcolor(BLACK);
      arc(getmaxx()/2.25,getmaxy()/3,angle,angle+2,100);
      setcolor(COLOR(255,0,0));
      getarccoords(&a);
      circle(a.xstart,a.ystart,25);
      setcolor(BLACK);
      delay(15);
      arc(getmaxx()/2.25,getmaxy()/3,angle+20,angle+22,150);
      getarccoords(&a);
      setcolor(COLOR(255,128,0));
      circle(a.xstart,a.ystart,35);
      setcolor(BLACK);
      delay(15);
      arc(getmaxx()/2.25,getmaxy()/3,angle+40,angle+42,200);
      setcolor(YELLOW);
      getarccoords(&a);
      circle(a.xstart,a.ystart,45);
      setcolor(BLACK);
      delay(15);
      arc(getmaxx()/2.25,getmaxy()/3,angle+60,angle+62,250);
      setcolor(GREEN);
      getarccoords(&a);
      circle(a.xstart,a.ystart,55);
      setcolor(BLACK);
      delay(15);
      arc(getmaxx()/2.25,getmaxy()/3,angle+80,angle+82,300);
      setcolor(COLOR(0,150,255));
      getarccoords(&a);
      circle(a.xstart,a.ystart,50);
      setcolor(BLACK);

      angle = angle+5;
      delay(35);
      if(kbhit())
        {
            char let=getch();
            if(let=='z')
            {
             break;
            }
        }
   }


     cleardevice();
     delay(2);
     setcolor(MAGENTA);
     for (int h=0;h<48;h++)                      //PRINTS OPENING SCREEN
     {
     delay(150);
     setfillstyle(h%12,(h+2)%12);
     floodfill(625,375,MAGENTA);
     settextstyle(10,HORIZ_DIR,10);
	 setcolor(COLOR(250,0,0));
	 outtextxy(450+20, 200, "2");
	 setcolor(COLOR(255,51,51));
	 outtextxy(525+20,200,"0");
	 setcolor(COLOR(255,102,102));
	 outtextxy(600+20,200,"4");
	 setcolor(COLOR(255,153,153));
	 outtextxy(675+20,200,"8");
     settextstyle(3,HORIZ_DIR,7);
     setcolor(COLOR(102,0,204));
     outtextxy(330, 340, "Do you want to play?");
     settextstyle(3,HORIZ_DIR,5);
     setcolor(COLOR(204,0,102));
	 outtextxy(360, 420, "Touch any key to continue");
	 setbkcolor(BLACK);
     if(kbhit())break;
     }

  C: getch();                                 //PRINTS OPTIONS
	 cleardevice();
     setcolor(9);
     settextstyle(3,HORIZ_DIR,6);
	 outtextxy(500,250,"1.New Game");
	 outtextxy(500,320,"2.Instructions");
	 outtextxy(500,390,"3.Exit");

  T: ch=getch();
	 switch(ch)   //INPUT CHOICE
	 {

        case '1':                                //STARTS A NEW GAME DIRECTLY
            for(int i=0;i<=3;i++)
            {
              for( int j=0;j<=3;j++)             //INITIALISES MATRIX WITH 0s
                {
                   grid[i][j]=0;
                }
             }
               goto Y;
               break;
        case '2':
     cleardevice();
     setlinestyle(1,7,5);                                   //PRINTS INSTRUCTION SCREEN- BOXES ON SIDE
     setfillstyle(8,CYAN);
     setcolor(CYAN);
     bar3d(870,130,930,190,20,1);
     setfillstyle(8,COLOR(255,0,127));
     setcolor(COLOR(255,0,127));
     bar3d(960,190,1020,250,20,1);
     setfillstyle(8,LIGHTBLUE);
     setcolor(LIGHTBLUE);
     bar3d(870,260,930,320,20,1);
     setfillstyle(8,CYAN);
     setcolor(CYAN);
     bar3d(960,330,1020,390,20,1);
     setfillstyle(8,COLOR(255,0,127));
     setcolor(COLOR(255,0,127));
     bar3d(870,400,930,460,20,1);
     setfillstyle(8,LIGHTBLUE);
     setcolor(LIGHTBLUE);
     bar3d(960,470,1020,530,20,1);

     //PRINTS RECTANGLE AND INSTRUCTIONS
	 setlinestyle(1,4,3);
	 setcolor(BLUE);
	 rectangle(220,140,840,530);
	 setlinestyle(1,4,5);
	 setcolor(CYAN);
	 rectangle(230,130,850,520);
	 setfillstyle(8,CYAN);
     settextstyle(7,HORIZ_DIR,5);
     setcolor(COLOR(255,0,0));
	 outtextxy(300,200,"Move the tiles using:");
	 setcolor(LIGHTRED);
	 outtextxy(300,240," w -- move up");
	 setcolor(YELLOW);
     outtextxy(300,280," s -- move down");
     setcolor(LIGHTGREEN);
	 outtextxy(300,320," d -- move right");
	 setcolor(GREEN);
	 outtextxy(300,360," a -- move left");
	 setcolor(LIGHTBLUE);
     outtextxy(250,400,"backspace -undo 1 move");
     setcolor(COLOR(0,255,255));
     outtextxy(300,440," esc -- Quit ");
	 getch();
     cleardevice();
     setcolor(COLOR(0,255,0));
	 outtextxy(275,290,"Merge two equal tiles to create");
     outtextxy(275,330,"a new tile of double the value");
	 getch();
	 cleardevice();
	 outtextxy(200,300,"Create the 2048 tile to win the game!");
	 getch();
	 goto C;
	 break;
        case '3':                      //EXIT
            cleardevice();
            settextstyle(8,HORIZ_DIR,10);
            outtextxy(400,250,"BYEBYE");
            exit_var=getchar();
            if(exit_var=='27');
            exit(0);
            break;
        default:
             goto T;           //GO BACK TO INPUT CHOICE

	 }
Y:
	 cleardevice();
	 outtextxy(500,250,"Get Ready!");

	  cleardevice();
      start_new_game();



	R:  while(check())          //RUNS WHILE THERE ARE MOVES STILL LEFT, i.e, MATRIX IS NOT FULL
	 {
	    M: fflush(stdin);
           ch=getch();
           printf("\r \r");

		switch(ch)
		{
		 case 'a':case 'A': back_up(); setbkcolor(BLACK); move_left(1);break;
		 case 'd':case 'D': back_up(); setbkcolor(BLACK); move_right(1); break;
		 case 'w': case 'W': back_up(); setbkcolor(BLACK);move_up(1); break;
		 case 's': case 'S': back_up(); setbkcolor(BLACK);move_down(1); break;
  Q:     case 8: undo(); break;
		 case 27: cleardevice();  settextstyle(8,HORIZ_DIR,10);outtextxy(550,300,"BYE"); system("pause"); if(kbhit())exit(0);
		 case 'm':case'M': goto C; break;
		}

	  }

        cleardevice();
        settextstyle(8,HORIZ_DIR,20);
        outtextxy(375,275,"GAME OVER");
        settextstyle(8,HORIZ_DIR,4);
        outtextxy(280,370,"Press Backspace  to Undo last Move");


        bk_to_gm=getch();
        if(bk_to_gm=='\b')            //GIVES OPTION TO UNDO LAST MOVE AFTER MATRIX IS FULL
            goto Q;
        else
            exit(0);

}

  void start_new_game()                 //NEW GAME
 {

	 scr=0;
	 int n=3;
	 srand(time(NULL));
	 location l1, l2;
	 int range=4;
	 l1.x=rand()%4;                  //GENERATES TWO RANDOM LOCATION VARIABLES
	 l1.y=rand()%4;
	 l2.x=rand()%4;
A:  l2.y=rand()%4;
	 if(l1.x==l2.x&&l1.y==l2.y)
		 {
			goto A;
		 }

	 grid[l1.y][l1.x]=2;           //INTIALISES THE RANDOM LOCATIONS WITH TWOs
	 grid[l2.y][l2.x]=2;
	 back_up();
	 setbkcolor(BLACK);
	 print();
 }

int score_game(int val)                         //SCORE FUNCTION
{
 int score;
 score= (((log2(val))-1)*val);
 return score;

}

int move_left(int to_move)                         //MOVE LEFT
{
  int i,j,k,a,ct=0,num;
  int pos;
  for( j=0; j<=3;j++)                      //ROW INDEX
  {
	 for( i=0;i<=3;i++)                    //
	 {
		if(grid[i][j]!=0)
		 {
			 pos=i-1;
			 num=grid[i][j];
			 for(  k=pos; k>=0;k--)            //TO CHECK FOR EMPTY TILES TO THE LEFT OF THE NUMBER TILE AND TO MOVE LEFT
			  {
					if(grid[k][j]==0)
					{
						if(to_move==1)
						{
						  grid[k][j]=num;
							 grid[k+1][j]=0;
						  }
						 ct++;
					 }
					 else if(grid[k][j]!=0)        //MERGES TILES IF THEY ARE OF EQUAL VALUE
						 {
						  if(grid[k][j]==num)
							 {
								 if(to_move==1)
									{
									  grid[k][j]=-2*num;
									  grid[k+1][j]=0;
										  scr+= score_game(abs(grid[k][j]));
										 chk_2048(grid[k][j]);


									  }
									ct++;
							  }
							  break;

						}
					}
			  }
		  }
  }

 if(to_move==1)                      //SPAWNS  A NEW TILE IF A MOVE HAS BEEN MADE
  {
    new_tile();
	print();

  }
 return ct;
}



int move_right(int to_move)                 //MOVE RIGHT
{
  int i,j,k,a,pos,num,ct=0;

  for( j=3; j>=0;j--)                  //ROW INDEX
	{
	 for( i=3;i>=0;i--)                  //COLUMN INDEX
		{
			if(grid[i][j]!=0)                    //TO CHECK FOR EMPTY TILES TO THE RIGHT OF THE NUMBER TILE AND TO MOVE RIGHT
			 {
				pos=i+1;
				num=grid[i][j];
				for(  k=pos; k<=3;k++)
				 {
					  if(grid[k][j]==0)
					 {
						 if(to_move==1)
						{
						 grid[k][j]=num;
						 grid[k-1][j]=0;
						}
					 ct++;
					  }
					  else if(grid[k][j]!=0)                             //MERGES TILES IF THEY ARE OF EQUAL VALUE
					  {
						  if(grid[k][j]==num)
							 {
								if(to_move==1)
								 {
									 grid[k][j]=-2*num;
										 grid[k-1][j]=0;
										scr+= score_game(abs(grid[k][j]));
										chk_2048(grid[k][j]);

									 }
							 ct++;
							  }
						 break;
					  }
					}
				}
			}
	  }

  if(to_move==1)                              //SPAWNS  A NEW TILE IF A MOVE HAS BEEN MADE
  {
		new_tile();
	print();
  }
 return ct;
}



int move_down(int to_move)                 //MOVE DOWN
{
  int i,j,k,pos,a,num,ct=0;

  for( i=3; i>=0;i--)                       //COLUMN INDEX
  {
	 for( j=3;j>=0;j--)                         //ROW INDEX
	{
	  if(grid[i][j]!=0)                          //TO CHECK FOR EMPTY TILES BELOW THE NUMBER TILE AND TO MOVE DOWN
		{
			pos=j+1;
		  num=grid[i][j];
		 for(  k=pos; k<=3;k++)
		  {
			 if(grid[i][k]==0)
				  {
					 if(to_move==1)
					 {
						grid[i][k]=num;
						grid[i][k-1]=0;
					 }
				 ct++;
				  }
			  else if(grid[i][k]!=0)                    //MERGES TILES IF THEY ARE OF EQUAL VALUE
				{
				  if(grid[i][k]==num)
					{
						if(to_move==1)
						 {
							 grid[i][k]=-2*num;
							 grid[i][k-1]=0;
							 scr+= score_game(abs(grid[i][k]));
							 chk_2048(grid[i][k]);

						  }
						ct++;
					  }
				  break;
				}
			}
		}
	 }
 }

 if(to_move==1)                                   //SPAWNS  A NEW TILE IF A MOVE HAS BEEN MADE
  {
    new_tile();
	print();
  }
 return ct;
}


int move_up(int to_move)                        //MOVE UP
{
  int i,j,a,k,ct=0,num,pos;

  for( i=0; i<=3;i++)                        //COLUMN INDEX
  {
	 for( j=0;j<=3;j++)                    //ROW INDEX
	  {
		 if(grid[i][j]!=0)
		  {
				pos=j-1;
			  num=grid[i][j];
				for( k=pos; k>=0;k--)          //TO CHECK FOR EMPTY TILES ABOVE THE NUMBER TILE AND TO MOVE UP
				 {
				  if(grid[i][k]==0)
					 {
					 if(to_move==1)
					  {
						 grid[i][k]=num;
						 grid[i][k+1]=0;
					  }
				  ct++;
					 }
					else if(grid[i][k]!=0)                    //MERGES TILES IF THEY ARE OF EQUAL VALUE
					 {
						if(grid[i][k]==num)
						 {
						  if(to_move==1)
							 {
								grid[i][k]=-2*num;
								grid[i][k+1]=0;
								scr+= score_game(abs(grid[i][k]));
								chk_2048(grid[i][k]);

							 }
						 ct++;                        //RETURNS THE
						  }
					 break;
					  }
				 }
			}
		 }
  }

 if(to_move==1)                            //SPAWNS  A NEW TILE IF A MOVE HAS BEEN MADE
  {
    new_tile();
	print();
	}

 return ct;
}


int check()                             //CHECKS GAME OVER OR NOT BY COUNTING NUMBER OF MOVES LEFT
{

	 if(move_up(0)!=0) return 1;
	 else if( move_down(0)!=0) return 1;
	 else if( move_left(0)!=0) return 1;
	 else if( move_down(0)!=0) return 1;
	 else return 0;
}



void print()                                //PRINTING MATRIX AND SCORE AND INSTRUCTIONS
 {
  int i,j;
  char buffer1[30],buffer2[30];
  cleardevice();
  setbkcolor(BLACK);

  settextstyle(8,HORIZ_DIR,5);                         //PRINTS SCORE
  bgiout<<"SCORE "<<scr;
  outstreamxy(510,40);
  setlinestyle(DOTTED_LINE,3,2);



    for(i=0;i<=3;i++)
	{

	  for(j=0;j<=3;j++)
	  {

			grid[i][j]=abs(grid[i][j]);
			switch(grid[i][j])                                  //SETS A DIFFERENT COLOUR FOR EVERY TILE
			{
			  case 2: setcolor(COLOR(255,0,0)); break;
			  case 4: setcolor(COLOR(255,128,0)); break;
			  case 8: setcolor(COLOR(255,255,0)); break;
			  case 16: setcolor(COLOR(120,205,41)); break;
			  case 32: setcolor(COLOR(0,255,0));break;
			  case 64: setcolor(COLOR(0,255,128));break;
			  case 128: setcolor(COLOR(0,255,255));break;
			  case 256:setcolor(COLOR(0,128,255));break;
			  case 512: setcolor(COLOR(127,0,255));break;
			  case 1024:setcolor(COLOR(255,0,255));break;
			  case 2048: setcolor(COLOR(255,0,127));break;
			  case 4096: setcolor(COLOR(153,0,76)); break;
			  case 8192: setcolor(COLOR(102,0,102));break;
			  default:setcolor(WHITE);


			}
			if(grid[i][j]==0)                        //DISPLAYS CIRCLES FOR EACH TILE, AND DISPLAYS NUMBERS
            {
              setbkcolor(BLACK);
              settextstyle(8,HORIZ_DIR,4);
              bgiout<<" "<<" ";
              outstreamxy(415+i*140,155+j*120) ;
              circle(420+i*140,180+j*120,55);

            }
            else if(grid[i][j]>10&&grid[i][j]<100)
            {
              setbkcolor(BLACK);
              settextstyle(8,HORIZ_DIR,4);
              bgiout<<grid[i][j]<<" ";
              outstreamxy(410+i*140,155+j*120) ;
              circle(420+i*140,180+j*120,55);

            }
            else if(grid[i][j]>100&&grid[i][j]<1000)
            {
              setbkcolor(BLACK);
              settextstyle(8,HORIZ_DIR,4);
              bgiout<<grid[i][j]<<" ";
              outstreamxy(390+i*140,155+j*120) ;
              circle(420+i*140,180+j*120,55);

            }
            else if(grid[i][j]>1000)
            {
              setbkcolor(BLACK);
              settextstyle(8,HORIZ_DIR,4);
              bgiout<<grid[i][j]<<" ";
              outstreamxy(370+i*140,155+j*120) ;
              circle(420+i*140,180+j*120,55);

            }
            else
            {
              setbkcolor(BLACK);
              settextstyle(8,HORIZ_DIR,4);
              bgiout<<grid[i][j]<<" ";
              outstreamxy(415+i*140,155+j*120) ;
              circle(420+i*140,180+j*120,55);

            }
	  }
    }

// PRINT INSTRUCTIONS AT THE BOTTOM OF THE SCREEN
setcolor(LIGHTBLUE);
settextstyle(8,HORIZ_DIR,3);
outtextxy(40,595,"______________________________________________________________________________________");
outtextxy(320,620,"w - move up    s- move down  esc- exit   m-main menu");
outtextxy(320,660,"a - move left  d - move right  backspace - undo");
settextstyle(8,HORIZ_DIR,4);
outtextxy(240,700,"A MANASA JAGADEESH AND MEHAK ARORA ENTERPRISE");
}

 void back_up()                  //BACKS UP MATRIX TO BE USED FOR UNDO-ING THE LAST MOVE
 {
	int i,j;

	 for(i=0;i<=3;i++)
	 {
		for(j=0;j<=3;j++)
		{
		  grid_bck[i][j] = grid[i][j];

		}

	 }

 }

 void undo()                                    //UNDOES THE LAST MOVE BY CALLING BACK-UP FUNCTION
 {
	  int i,j;
	  for(i=0;i<=3;i++)
	 {
		for(j=0;j<=3;j++)
		{
		  grid[i][j] = grid_bck[i][j];

		}

	 }
	 print();
 }

void new_tile()                                //SPAWNS A NEW TILE BY GENERATING TWO RANDOM LOCATIONS
{
	 location L[16], new_loc;
	 int i,j,k=0;
	 for(i=0;i<=3;i++)
	  {
		for(j=0;j<=3;j++)
		 {
		  if(grid[i][j]==0)
			{
			 L[k].x=j;
			 L[k++].y=i;
			}
		 }
	  }

    if(k==0)
        return;

	 int n=rand()%(k);
	 new_loc=L[n];


	 if( rand()%2==0)                      //RANDOMLY GENERATES A 2 OR A 4 TO ASSIGN IN THE RANDOM LOCATION PREVIOSLY GENERATED
	 grid[new_loc.y][new_loc.x]=2;
	 else grid[new_loc.y][new_loc.x]=4;

}

void chk_2048(int num)         //CHECK IF GAME HAS BEEN WON OR NOT
 {
     if(num==-2048)
	{
     if(genius==0)
    {
      cleardevice();
        genius++;
        setcolor(MAGENTA);
        settextstyle(3,HORIZ_DIR,8);
        outtextxy(300,200,"YAAY! You have made 2048");
        outtextxy(300,250,"Press any key to continue with the game");

        getchar();
        cleardevice();

    }
    }

 }


