// colormind - mastermind clone
#include "cmind.h"

int main(int argc, char *argv[])
{
  int i, c, victory=0;
  myname=argv[0];
  
  // parse command line options
  while ((c = getopt(argc, argv, ":c:t:r")) != -1)
   switch (c) {
	case 'c':
     if ((i=atoi(optarg))<=MAXCOLORS && i>=MINCOLORS)
      nocolors=atoi(optarg);
     else
      showusage();
    break;
    case 't':
     if ((i=atoi(optarg))<=MAXTRIES && i>=MINTRIES)
      maxtries=atoi(optarg);
     else
      showusage();
    break;
    case 'r':
     reveal=true;
    break;
    case '?':
     showusage();
    break;
    default:
     abort();
  break; }
  
  // initialization
  srand(time(NULL));
  generatecolorcode();
  showinformation(1);
  
   // loop
   while (tries<maxtries) {
    // read text line and parse it
    readnextline();
    if (!parsercommand) {
     // parse given code
     cmindengine();
     // award pegs
     showcurrentpegs();
     // see if code has been found
     if ((victory=estimatevictory()))
    break; }
   ++tries; }
   
   showvictoryorloss(victory);

 return 0;
}
