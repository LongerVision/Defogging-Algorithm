/*Include all the libraries that are needed */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DataTypes.h"

/* The following few lines of code are for a function that returns a minimum value of array along with index, To do that We are using a struct with minimum value and it's index as fields */

/* Defnition of above defined strcut */
typedef struct min_ret{
unsigned char min_val;
int index;
}min_ret; 

/* Defnition of the minimum function */  
min_ret minimum(unsigned char* start,int size)
{
 int min_val=*(start);
 min_ret ret;
 int i;
  for(i=0;i<size;i++)
   if(*(start+i)<min_val)
    {
     ret.min_val=*(start+i);
     ret.index=i;
    }
 return ret;
}

/* Function for Atmospheric Light Estimation */    
unsigned char* estimateA(ImageData i, unsigned char* J,int numPixels)
{
  int r,c,k,f;
  unsigned char brightJ[numPixels];
  int brightJindex[numPixels];
  unsigned char* A=(unsigned char*)calloc(3,sizeof(char));
  *(A)=0;*(A+1)=0;*(A+2)=0;
  min_ret ret;
  for (k=0;k<(numPixels);k++)
  brightJ[k]=0;
  for (r=0;r<(i.height);r++)
  {
   for (c=0;c<(i.width);c++)
    {
     ret=minimum(brightJ,numPixels);
     if(*(J+(r*(i.width)+c))>ret.min_val)
     {
      brightJ[ret.index]=*(J+(r*(i.width)+c));
      brightJindex[ret.index]=(r*(i.width)+c);
      }
     }
   }
  
  for (k=0;k<numPixels;k++)
  {
   f=(int)(*(i.rdata+brightJindex[k]))+(int)(*(i.gdata+brightJindex[k]))+(int)(*(i.bdata+brightJindex[k]));
   if(f>(*(A+0)+ *(A+1)+ *(A+2)))
   {
    *(A+0)=*(i.rdata+brightJindex[k]);
    *(A+1)=*(i.gdata+brightJindex[k]);
    *(A+2)=*(i.bdata+brightJindex[k]);
   }
  }
 return A;
}
int main(void)
{
 return 0;
 }   