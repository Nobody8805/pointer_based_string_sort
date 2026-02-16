/*
* FOCUS POINTS FOR THIS MODULE:-
* 1. User types in the strings. Each string is stored in a common char arr sequentially.
* 2. Each new line '\n' or EOF is replaced by a null terminator '\0' to keep track of a new str.
* 3. We store the ptr to the start of each str in a ptr array.
*
*/

#include <stdio.h>

#define CHARBUFFER 10000
#define MAXLINES 1000

static char buffer[CHARBUFFER];
static char *lineptr[MAXLINES];

//Function reads one line into the buffer and returns the length of the line or EOF
static int get_line(char *buf, int max)
{
    int c;
    int len = 0;
    
    while(len < max - 1 && (c = getchar()) != EOF && c != '\n')
        buf[len++] = c;

    if (c == '\n')
        buf[len++] = '\0'; //null terminator when a new line is there
    else if (c == EOF && len == 0)
            return EOF;
    else 
        buf[len] = '\0';

    return len;
}

//Function to read lines and return the number if lines read.
int readlines(void)
{
    int nlines = 0;
    int len;
    char *bufp = buffer;
    
    while(1)
    {
        int remaining = CHARBUFFER - (bufp - buffer);  //bufp - buffer ---> How many chars are already used in buffer
        len = get_line(bufp, remaining);

        if (len == EOF)
            break;

        if (nlines >= MAXLINES)
            return -1;

        lineptr[nlines++] = bufp; //store start of line

        bufp += len; //to update the buffer pointer to the next line
    }
    return nlines;
}

//Accessor func so that other .c files can use the pointers
char **get_lineptr(void)
{
    return lineptr;
}


int main(void)
{
    int n = readlines();
    char **lines = get_lineptr();

    for (int i = 0; i < n; i++)
        printf("%s\n", lines[i]);

    return 0;
}
