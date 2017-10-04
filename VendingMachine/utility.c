#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine() {
   int ch;
   while (ch = getc(stdin), ch != EOF && ch != '\n') {} /* Gobble each character. */

   /* Reset the error status of the stream. */
   clearerr(stdin);
}

unsigned getNumberLength(unsigned len) {
   int tempAmount = len;
   len = 0;

   while((double) tempAmount / 10 > 0) {
      len++;
      if ((double) tempAmount / 10 < 1) {
         break;
      }
      tempAmount /= 10;
   }

   return len;
}