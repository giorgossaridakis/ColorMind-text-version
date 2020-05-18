// colormind library

// estimate victory
int estimatevictory()
{
  return (pegshistory[tries][CBLACK]==nocolors) ? 1 : 0;
}


// separate words in string and store in vector inside structure
void separatewords(char formula[])
{
  int i, n;
  char tformula[MAXLINE];
  dastringclear(&words);
    
   for (i=0;i<strlen(formula);i++) {
    n=0;
    while (isspace(formula[i]))
     ++i;
    while (!isspace(formula[i]) && i<strlen(formula))
     tformula[n++]=tolower(formula[i++]);
    tformula[n]='\0';
   dastringinsert(&words, tformula); }
}

// read and parse next line
void readnextline()
{
  int i, i1, correctwords=0;
 
    for (i=0;i<nocolors;i++) {
     guessedsumcolors[0][i]=0; // guessedsumcolors[2] contains given pegs from guessed colors and sum of given guessed colors
    guessedsumcolors[1][i]=0; }
    while (correctwords<nocolors) {
     parsercommand=0;
     correctwords=0;
     showtrynumber();
     while (!(i=readline(guessline)));
     // extra commands
     if (!strcmp(guessline, "history"))
      showpegshistory();
     if (!strcmp(guessline, "information"))
      showinformation(0);
     if (!strcmp(guessline, "help"))
      showhelp();
     if (!strcmp(guessline, "exit")) {
      parsercommand=1;
      tries=maxtries;
     return; }
     if (!strcmp(guessline, PASSWORD) && reveal)
      revealcolorcode();
     // parse words vector
     separatewords(guessline);
     for (i=0;i<words.dasize;i++)
      for (i1=0;i1<nocolors;i1++)
       if (!strcmp(words.dapointers[i], COLORNAMES[i1])) {
        guessedcolors[tries][i]=i1;
     ++correctwords; }
     if (words.dasize!=nocolors)
      correctwords=0;
     if (correctwords==nocolors)
      for (i=0;i<nocolors;i++)
       ++guessedsumcolors[1][guessedcolors[tries][i]]; 
     else if (!parsercommand) 
    repeatwrongcode(); }
}

// try number
void showtrynumber()
{
 printf("try number:%d\n", tries+1);
}

// incomprehensible code
void repeatwrongcode()
{
   printf("\"%s\" is not comprehensible\n", guessline);
}

// read text line
int readline(char line[])
{
  int i=0;
  char c;
  
   while ((c=getchar())!='\n')
    line[i++]=c;
   line[i]='\0'; 
    
 return strlen(line);
}

// show pegs history
void showpegshistory()
{
  int i, i1, i2;
  parsercommand=1;
  
   if (!tries)
    printf("no history recorded\n");
   for (i=0;i<tries;i++) {
    printf("%d:", i+1);
    for (i1=0;i1<nocolors;i1++)
     printf("%s ", COLORNAMES[guessedcolors[i][i1]]);
    printf("-> ");
    for (i1=0;i1<pegshistory[i][CWHITE];i1++)
     printf("%c ", PEGNAMES[CWHITE][0]);
    for (i2=0;i2<pegshistory[i][CBLACK];i2++)
     printf("%c ", PEGNAMES[CBLACK][0]);
    if (!i1 && !i2)
     printf("zero");
   printf("\n"); }
}
        
// reveal code
void revealcolorcode()
{
  int i;
  parsercommand=1;
  
  printf("color code: ");
  for (i=0;i<nocolors;i++)
   printf("%s ", COLORNAMES[colorcode[0][i]]);
  printf("\n");
} 

// show usage
void showusage()
{
  printf("%s [-c <colors&rows, 2..6:>] [-t <tries 2..16>] [-r <reveal code>]\n", myname);
    
 exit(EXIT_FAILURE);  
}

// show pegs for tried line
void showcurrentpegs()
{
  int i1, i2;
  
    for (i1=0;i1<pegshistory[tries][CWHITE];i1++)
     printf("%s ", PEGNAMES[CWHITE]);
    for (i2=0;i2<pegshistory[tries][CBLACK];i2++)
     printf("%s ", PEGNAMES[CBLACK]);
    if (!i1 && !i2)
     printf("zero pegs");
    printf("\n");
}

// show help
void showhelp()
{
   parsercommand=1;
   printf("               ColorMind %.1f - a MasterMind clone for the terminal.\n\nYou, the codebreaker try to guess a color pattern, in both order and color, within a given number of turns, 8 by default. This can be changed, try cmind --help from the terminal for a list of startup options. Each guess is stated with the sequence of colors in a line of text.  Available colors are shown in the start and their number also corresponds to the number of rows. Once a line is correctly stated, the codemaker (the computer) records your selection on the appropriate turn row and respods with a line of text. A black peg is given for each code peg from the guess which is correct in both color and position. A white peg indicates the existence of a correct color code peg placed in the wrong position. If there are duplicate colours in the guess, they cannot all be awarded a key peg unless they correspond to the same number of duplicate colours in the hidden code. For example, if the hidden code is white-white-black-black and the player guesses white-white-white-black, the codemaker will award two colored key pegs for the two correct whites, nothing for the third white as there is not a third white in the code, and a colored key peg for the black. No indication is given of the fact that the code also includes a second black.\n", VERSION);
}

// show colormind information
void showinformation(int flag) // 1 show version as well
{
  int i;
  
   parsercommand=1;
   // show information
   if (flag)
    printf("ColorMind version %.1f\n", VERSION);
   printf("colors:<");
   for (i=0;i<nocolors;i++)
    printf("%s ", COLORNAMES[i]);
   printf("\b> rows:%d\nextra:<history> <information> <help>", nocolors);
   if (reveal)
    printf(" <reveal>");
   printf(" <exit>\n");
}

// show final result for victory or loss
void showvictoryorloss(int victory)
{
  int i;
  
   // final result
   switch (victory) {
    case 0:
     printf("Loss!\ncolor code: ");
     for (i=0;i<nocolors;i++)
      printf("%s ", COLORNAMES[colorcode[0][i]]);
     printf("\n");
    break;
    case 1:
     printf("Victory!\n");
   break; }
}
