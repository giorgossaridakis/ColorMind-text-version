// C dynamic arrays library

#define MAXMEMBERS 99999

typedef struct daSTRING {
    int dasize;
    int daposition;
    char *dapointers[MAXMEMBERS];
} daString;

typedef struct daINTEGER {
    int dasize;
    int daposition;
    int *dapointers[MAXMEMBERS];
} daInteger;

// functions

// auxilliary
// allocate memory for a given size
void *xmalloc(size_t size)
{
 void *value = malloc(size);

return value; // 0 is allocation failure
}

/* empty a string */
void clearstring(char *string)
{
 memset(string, 0, (size_t) sizeof(string));
}

// dynamic string array functions

// add new member in string dynamic array
int dastringinsert(daString *tdastring, char *newmember)
{
  if (!strlen(newmember) || !(tdastring->dapointers[tdastring->dasize]=(char*) xmalloc(sizeof(newmember))))
   return 0;
  memcpy(tdastring->dapointers[tdastring->dasize], newmember, sizeof(newmember));
  ++tdastring->dasize;
    
 return tdastring->dasize;
}

// locate and delete string
int dastringdelete(daString *tdastring, int position)
{
   free(tdastring->dapointers[position]);
   for (;position<tdastring->dasize-1;position++)
    tdastring->dapointers[position]=tdastring->dapointers[position+1];
   --tdastring->dasize;
   
 return tdastring->dasize;
}

// returns string position and sets daposition
int dastringsearch(daString *tdastring, char *token)
{
  int i;
  
   for (i=0;i<tdastring->dasize;i++) {
    if (!strcmp(tdastring->dapointers[i], token)) {
     tdastring->daposition=i;
   return tdastring->daposition; } }
   
 return -1;
}

// copy dynamic array pointers to remote array
void exportdastringpointers(daString *tdastring, char *remote[])
{
  int i;
  
   for (i=0;i<tdastring->dasize;i++)
    remote[i]=tdastring->dapointers[i];
}

// clear dynamic array
int dastringclear(daString *tdastring)
{
  int i;
  
   for (i=0;i<tdastring->dasize;i++)
    free(tdastring->dapointers[i]);
   tdastring->dasize=0;
   tdastring->daposition=0;
    
 return i;
}

// dynamic integer array functions

// add new member in integer dynamic array
int daintegerinsert(daInteger *tdainteger, int newmember)
{
  if (!(tdainteger->dapointers[tdainteger->dasize]=(int*) xmalloc(sizeof(newmember))))
   return 0;
  memcpy(tdainteger->dapointers[tdainteger->dasize], &newmember, sizeof(newmember));
  ++tdainteger->dasize;
    
 return tdainteger->dasize;
}

// locate and delete integer
int daintegerdelete(daInteger *tdainteger, int position)
{
   free(tdainteger->dapointers[position]);
   for (;position<tdainteger->dasize-1;position++)
    tdainteger->dapointers[position]=tdainteger->dapointers[position+1];
   --tdainteger->dasize;
   
 return tdainteger->dasize;
}

// returns string position and sets daposition
int daintegersearch(daInteger *tdainteger, int token)
{
  int i;
  
   for (i=0;i<tdainteger->dasize;i++) {
    if (*tdainteger->dapointers[i]==token) {
     tdainteger->daposition=i;
   return tdainteger->daposition; } }
   
 return -1;
}

// copy dynamic array pointers to remote array
void exportdaintegerpointers(daInteger *tdainteger, int *remote[])
{
  int i;
  
   for (i=0;i<tdainteger->dasize;i++)
    remote[i]=tdainteger->dapointers[i];
}

// clear dynamic array
int daintegerclear(daInteger *tdainteger)
{
  int i;
  
   for (i=0;i<tdainteger->dasize;i++)
    free(tdainteger->dapointers[i]);
   tdainteger->dasize=0;
   tdainteger->daposition=0;
    
 return i;
}
