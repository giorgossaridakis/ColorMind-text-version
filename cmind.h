// colormind headers

// included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include "dynamicarrays.c"

// constant definitions
#define UP 259
#define LEFT 260
#define RIGHT 261
#define DOWN 258
#define ESC 27
#define SPACE 32
#define MAXCOLORS 6
#define MINCOLORS 2
#define STANDARDCOLORSNO 4
#define MAXTRIES 16
#define MINTRIES 2
#define STANDARDTRIESNO 8
#define MAXLINE 80
#define CWHITE 0
#define CBLACK 1
#define VERSION 1.0

// variables, classes, structures
bool reveal=false;
int colorcode[2][MAXCOLORS], guessedcolors[MAXTRIES][MAXCOLORS]={ 0, 0 }, guessedsumcolors[2][MAXCOLORS]={ 0, 0 }, pegshistory[MAXTRIES][2]={ 0, 0 }, maxtries=STANDARDTRIESNO, tries=0, nocolors=STANDARDCOLORSNO, whitepegs, blackpegs, parsercommand;
const char *COLORNAMES[]={ "red", "green", "blue", "black", "cyan", "magenta", "brown", "white" }, *PEGNAMES[]={ "white", "black" }, *PASSWORD="reveal";
char *myname, guessline[MAXLINE];
daString words;

// function definitions
// cmindengine
int cmindengine();
void generatecolorcode();
// cmindlibrary
int estimatevictory();
void separatewords(char formula[]);
void showtrynumber();
void repeatwrongcode();
void readnextline();
int readline(char line[]);
void showpegshistory();
void revealcolorcode();
void showusage();
void showcurrentpegs();
void showhelp();

// locally included files
#include "cmindengine.c"
#include "cmindlibrary.c"
