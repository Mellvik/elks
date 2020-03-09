#include <malloc.h>
#include <string.h>

char *
strdup(char * s)
{
   register size_t len;
   register char * p;

   len = strlen(s)+1;
   p = (char *) malloc(len);
   if (p) memcpy(p, s, len); /* Faster than strcpy */
   return p;
}
