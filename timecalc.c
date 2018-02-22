

#include <stdio.h>
#if defined(__linux__)
#define MYOS 1
#elif defined(_WIN32)
#define MYOS 2
#elif defined(_WIN64)
#define MYOS 3
#elif defined(__unix__)
#define MYOS 4
#define PATH_MAX 2500
#else
#define MYOS 0
#endif



#include <stdlib.h>
#include <string.h>
#include <dirent.h> 
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>  
#include <time.h>

#include <ncurses.h>
int rows,cols; 



char *strtimesub_old( int h1, int m1, int s1, int h2, int m2, int s2) 
{
  int h3, m3 , s3 ; 
  int foo; char ptr[PATH_MAX];

  //s3=(s2-s1)%60;
  //m3=(m2-m1+((s2-s1)/60))%60;
  //h3=(h2-h1+((m2-m1)/60));
  foo = snprintf( ptr , PATH_MAX , "%2.2d:%2.2d:%2.2d\n", h3, m3, s3);
  size_t siz = sizeof ptr ; 
  char *r = malloc( sizeof ptr );
  return r ? memcpy(r, ptr, siz ) : NULL;
}



char *strtimesub( int h1, int m1, int s1, int h2, int m2, int s2) 
{
 int hour, min, sec;
 int start_sec = 0;
 int start_hour = h1;
 int start_min = m1;
 int end_sec  = 0;
 int end_hour = h2;
 int end_min  = m2;
 int foo; char ptr[PATH_MAX];

 if (end_sec < start_sec)
 {
  if (end_min > 0)
  {
   end_min--;
   sec = 60 + end_sec - start_sec;
  }
  else
  {
   end_hour--;
   end_min += 59; // end seconds borrowed 1 min
   end_sec += 60;

   sec = end_sec - start_sec;
  }
 }
 else
     sec = end_sec - start_sec;


 if (end_min < start_min)
 {
  if (end_hour > 0)
  {
   end_hour--;
   min = 60 + end_min -start_min;
  }
 }
 else
     min = end_min - start_min;

   hour = end_hour - start_hour;


  //Print time in default form dd:dd:dd
  //if (strcmp((char*) option, "default") == 0)
  // printf("Calc: %02d:%02d:%02d\n", hour, min, sec);

  foo = snprintf( ptr , PATH_MAX , "%2.2d:%2.2d:%2.2d\n", hour, min, sec );
  size_t siz = sizeof ptr ; 
  char *r = malloc( sizeof ptr );
  return r ? memcpy(r, ptr, siz ) : NULL;
}




 
char *strtimeadd( int h1, int m1, int s1, int h2, int m2, int s2) 
{
  int h3, m3 , s3 ; 
  int foo; char ptr[PATH_MAX];
  s3=(s1+s2)%60;
  m3=(m1+m2+((s1+s2)/60))%60;
  h3=(h1+h2+((m1+m2)/60));
  foo = snprintf( ptr , PATH_MAX , "%2.2d:%2.2d:%2.2d\n", h3, m3, s3);
  size_t siz = sizeof ptr ; 
  char *r = malloc( sizeof ptr );
  return r ? memcpy(r, ptr, siz ) : NULL;
}






void mvcenter( int myposypass, char *mytext )
{
      mvprintw( myposypass, cols/2 - strlen( mytext )/2  , "%s", mytext );
}




////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////
char *strcut( char *str , int myposstart, int myposend )
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}




////////////////////////
////////////////////////
////////////////////////
char *strninput( char *myinitstring )
{

   int strninput_gameover = 0; 
   char strmsg[PATH_MAX];
   char charo[PATH_MAX];
   strncpy( strmsg, myinitstring , PATH_MAX );

   int ch ;  int foo ; 
   int fooj; 
   while ( strninput_gameover == 0 )
   {
                  getmaxyx( stdscr, rows, cols);
                  attroff( A_REVERSE );
                  for ( fooj = 0 ; fooj <= cols-1;  fooj++)
                  {
                    mvaddch( rows-1, fooj , ' ' );
                  }

                  mvprintw( rows-1, 0, ":> %s" , strrlf( strmsg ) );
                  ////////////////mvcenter( rows/2, "             " ); 
                  //mvcenter( rows/2, strmsg ); 
                  attron( A_REVERSE );
                  printw( " " );
                  attroff( A_REVERSE );
                  attroff( A_REVERSE );
                  attroff( A_BOLD );
                  refresh() ; 

                  curs_set( 0 );
                  ch = getch();

  if ( ch == 8 ) 
    strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );

   else if ( ch == 4 ) strncpy( strmsg, ""  ,  PATH_MAX );

  else if ( ch == 27 )  
  {
    strncpy( strmsg, ""  ,  PATH_MAX );
    strninput_gameover = 1;
  }

  else if ( ch == 274 )  
  {
    strncpy( strmsg, ""  ,  PATH_MAX );
    strninput_gameover = 1;
  }

  else if ( ch == 263 )  
    strncpy( strmsg, strcut( strmsg, 1 , strlen( strmsg ) -1 )  ,  PATH_MAX );

               else if ( ch == 8 ) strncpy( strmsg, ""  ,  PATH_MAX );
               else if ( ch == 4 ) strncpy( strmsg, ""  ,  PATH_MAX );

		  else if ( ch == 4 ) strncpy( strmsg, ""  ,  PATH_MAX );
		  

		  else if ( ch == 27 ) 
		  {
			   strncpy( strmsg, ""  ,  PATH_MAX );
		  }
	          else if (
			(( ch >= 'a' ) && ( ch <= 'z' ) ) 
		        || (( ch >= 'A' ) && ( ch <= 'Z' ) ) 
		        || (( ch >= '1' ) && ( ch <= '9' ) ) 
		        || (( ch == '0' ) ) 
		        || (( ch == '~' ) ) 
		        || (( ch == '!' ) ) 
		        || (( ch == '&' ) ) 
		        || (( ch == '=' ) ) 
		        || (( ch == ':' ) ) 
		        || (( ch == ';' ) ) 
		        || (( ch == '<' ) ) 
		        || (( ch == '>' ) ) 
		        || (( ch == ' ' ) ) 
		        || (( ch == '|' ) ) 
		        || (( ch == '#' ) ) 
		        || (( ch == '?' ) ) 
		        || (( ch == '+' ) ) 
		        || (( ch == '/' ) ) 
		        || (( ch == '\\' ) ) 
		        || (( ch == '.' ) ) 
		        || (( ch == '$' ) ) 
		        || (( ch == '%' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == ',' ) ) 
		        || (( ch == '{' ) ) 
		        || (( ch == '}' ) ) 
		        || (( ch == '(' ) ) 
		        || (( ch == ')' ) ) 
		        || (( ch == ']' ) ) 
		        || (( ch == '[' ) ) 
		        || (( ch == '*' ) ) 
		        || (( ch == '"' ) ) 
		        || (( ch == '@' ) ) 
		        || (( ch == '-' ) ) 
		        || (( ch == '_' ) ) 
		        || (( ch == '^' ) ) 
		        || (( ch == '\'' ) ) 
	             ) 
		  {
                           foo = snprintf( charo, PATH_MAX , "%s%c",  strmsg, ch );
			   strncpy( strmsg,  charo ,  PATH_MAX );
		  }
		  else if ( ch == 10 ) 
		  {
                        strninput_gameover = 1;
		  }
     }
     char ptr[PATH_MAX];
     strncpy( ptr, strmsg, PATH_MAX );
     size_t siz = sizeof ptr ; 
     char *r = malloc( sizeof ptr );
     return r ? memcpy(r, ptr, siz ) : NULL;
}






void gfxrectangle( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
     for( foox = x1 ; foox <= x2 ; foox++) 
      mvaddch( fooy , foox , ' ' );
}

void gfxframe( int y1, int x1, int y2, int x2 )
{
    int foo, fooy , foox ;
    foo = x1;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
        mvaddch( fooy , foo , ACS_VLINE );
    foo = x2;
    for( fooy = y1 ; fooy <= y2 ; fooy++) 
         mvaddch( fooy , foo , ACS_VLINE );
    foo = y1;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    foo = y2;
    for( foox = x1 ; foox <= x2 ; foox++) 
         mvaddch( foo , foox , ACS_HLINE );
    mvaddch( y1 , x1 , ACS_ULCORNER );
    mvaddch( y1 , x2 , ACS_URCORNER );
    mvaddch( y2 , x1 , ACS_LLCORNER );
    mvaddch( y2 , x2 , ACS_LRCORNER );
}

////////////////////////////////
void ncurses_runcmd( char *thecmd   )
{
       char rncmdi[PATH_MAX];
       def_prog_mode();
       endwin();
       strncpy( rncmdi , "  " , PATH_MAX );
       strncat( rncmdi , thecmd , PATH_MAX - strlen( rncmdi ) -1 );
       strncat( rncmdi , " " , PATH_MAX - strlen( rncmdi ) -1 );
       system( rncmdi );
       reset_prog_mode();
}











void ndesk_menu_timecalc()
{
         int ndesk_menu_timecalc_gameover = 0; int ch ; 
         char cmtime1[PATH_MAX]; strncpy( cmtime1, "09:00", PATH_MAX );
         char cmtime2[PATH_MAX]; strncpy( cmtime2, "10:00", PATH_MAX );
         char cmtime3[PATH_MAX]; strncpy( cmtime3, "", PATH_MAX );
         char cmtime4[PATH_MAX]; strncpy( cmtime4, "", PATH_MAX );
         
         int usersel = 1;
         
         int cmh1, cmm1, cmh2, cmm2 ; 

         while( ndesk_menu_timecalc_gameover == 0)
         {

                    cmh1 = atoi( strcut( cmtime1, 1 , 2 ) );
                    cmm1 = atoi( strcut( cmtime1, 4 , 5 ) );
                    cmh2 = atoi( strcut( cmtime2, 1 , 2 ) );
                    cmm2 = atoi( strcut( cmtime2, 4 , 5 ) );
                    strncpy( cmtime3, strrlf( strtimeadd( cmh1, cmm1, 0 , cmh2, cmm2, 0 ) ) ,  PATH_MAX );
                    strncpy( cmtime4, strrlf( strtimesub( cmh1, cmm1, 0 , cmh2, cmm2, 0 ) ) ,  PATH_MAX );

               erase();
               color_set( 13, NULL ); attroff( A_REVERSE );

               gfxrectangle( rows*25/100, cols*25/100 , rows*75/100, cols*75/100 );
               gfxframe( rows*25/100, cols*25/100 , rows*75/100, cols*75/100 );
               color_set( 17, NULL ); attron( A_REVERSE );

               mvcenter( rows*25/100, "| Menu |" );
               color_set( 13, NULL ); attroff( A_REVERSE );

               if ( usersel == 1 ) mvprintw( rows*25/100 +2, cols*25/100+2, ">" );
               mvprintw( rows*25/100 +2, cols*25/100+3, "Time 1: %s", cmtime1 );

               if ( usersel == 2 ) mvprintw( rows*25/100 +3, cols*25/100+2, ">" );
               mvprintw( rows*25/100 +3, cols*25/100+3, "Time 2: %s", cmtime2 );

               if ( usersel == 3 ) mvprintw( rows*25/100 +4, cols*25/100+2, ">" );
               mvprintw( rows*25/100 +4, cols*25/100+3, "Time Add: %s", cmtime3 );
               mvprintw( rows*25/100 +5, cols*25/100+3, "Time Sub: %s", cmtime4 );

               color_set( 5, NULL ); attron( A_REVERSE );
               mvcenter( rows*75/100 -1, "[ Esc: Cancel ]" );

               color_set( 0, NULL ); 
               attroff( A_REVERSE );
               gfxrectangle( rows-1 , 0 , rows-1, cols -1 );

               ch = getch();

               if ( ch == 'j' )  usersel++;
               else if ( ch == 'k' )  usersel--;

               else if ( ch == 'i' )  ndesk_menu_timecalc_gameover = 1;
               else if ( ch == 'q' )  ndesk_menu_timecalc_gameover = 1;
               else if ( ch == 27 )  ndesk_menu_timecalc_gameover = 1;

               else if ( ch == '1' )  strncpy( cmtime1, strninput( cmtime1 ), PATH_MAX ); 
               else if ( ch == '2' )  strncpy( cmtime2, strninput( cmtime2 ), PATH_MAX ); 

               else if (( ch == 10 )  || ( ch == 'l' ))
               {
                  if ( usersel == 1 )       strncpy( cmtime1, strninput( cmtime1 ), PATH_MAX ); 
                  else if ( usersel == 2 )  strncpy( cmtime2, strninput( cmtime2 ), PATH_MAX ); 
                  else if ( usersel == 3 )
                   {
                    cmh1 = atoi( strcut( cmtime1, 1 , 2 ) );
                    cmm1 = atoi( strcut( cmtime1, 4 , 5 ) );
                    cmh2 = atoi( strcut( cmtime2, 1 , 2 ) );
                    cmm2 = atoi( strcut( cmtime2, 4 , 5 ) );
                    strncpy( cmtime3, strrlf( strtimeadd( cmh1, cmm1, 0 , cmh2, cmm2, 0 ) ) ,  PATH_MAX );
                    strncpy( cmtime4, strrlf( strtimesub( cmh1, cmm1, 0 , cmh2, cmm2, 0 ) ) ,  PATH_MAX );
                   }
               }

               else if ( ch == 'c' )  
               {
                   cmh1 = atoi( strcut( cmtime1, 1 , 2 ) );
                   cmm1 = atoi( strcut( cmtime1, 4 , 5 ) );
                   cmh2 = atoi( strcut( cmtime2, 1 , 2 ) );
                   cmm2 = atoi( strcut( cmtime2, 4 , 5 ) );
                   strncpy( cmtime3, strrlf( strtimeadd( cmh1, cmm1, 0 , cmh2, cmm2, 0 ) ) ,  PATH_MAX );
                   strncpy( cmtime4, strrlf( strtimesub( cmh1, cmm1, 0 , cmh2, cmm2, 0 ) ) ,  PATH_MAX );
               }
         }
}



int main()
{

  initscr();	
  curs_set( 0 );
  noecho();            
  keypad( stdscr, TRUE );  // for F...
  start_color();
  init_pair(0,  COLOR_WHITE,     COLOR_BLACK);
  init_pair(1,  COLOR_RED,     COLOR_BLACK);
  init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
  init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
  init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
  init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
  init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
  init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
  init_pair(8,  COLOR_WHITE,   COLOR_RED);
  init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
  init_pair(10, COLOR_BLUE,  COLOR_YELLOW   );
  init_pair(11, COLOR_WHITE,   COLOR_BLUE);
  init_pair(12, COLOR_YELLOW,   COLOR_BLUE);
  init_pair(13, COLOR_BLACK,   COLOR_CYAN);
  init_pair(14, COLOR_BLUE,   COLOR_GREEN);
  init_pair(15, COLOR_BLUE, COLOR_CYAN );
  init_pair(16, COLOR_CYAN, COLOR_WHITE );
  init_pair(17, COLOR_CYAN, COLOR_YELLOW );
  init_pair(18, COLOR_CYAN, COLOR_BLUE);
  init_pair( 19, COLOR_MAGENTA , COLOR_BLUE);
  init_pair( 20 , COLOR_RED , COLOR_BLUE);
  init_pair( 21 , COLOR_BLUE , COLOR_YELLOW);
  init_pair( 22, COLOR_YELLOW,   COLOR_CYAN);
  init_pair( 23, COLOR_WHITE, COLOR_BLUE);
  init_pair( 24, COLOR_GREEN, COLOR_BLUE);
    getmaxyx( stdscr, rows , cols);

    ndesk_menu_timecalc();

    endwin();
    return 0;
}


