#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

//structure for the maze
typedef struct mazeStruct
{
 char **arr;//[32][32];  /* allows for a maze of size 30x30 plus outer walls */
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

//structure for the linked list
typedef struct nodeStruct{
    int xcord;
    int ycord;
    struct nodeStruct* next;
} node;

/**********************************************/
//this functions ensure the size from the file is in range
int invalidSize(maze* m){
    //must be larger than 0
    if (m->xsize <= 0 || m->ysize <= 0){
        return TRUE;
    }
    return FALSE;
}
/**********************************************/
// this function ensure the starting point is smaller than the size
int invalidStartingPoint(maze* m){

    if(m->xstart > m->xsize || m->ystart > m->ysize){
        return TRUE;
    }
    return FALSE;
}

/***********************************************/
//this function ensure the ending point is smaller than the size
int invalidEndingPoint(maze* m){
    if (m->xend > m->xsize || m->yend > m->ysize){
        return TRUE;
    }
    return FALSE;
}

/************************************************/
//this function initialize the maze
void mazeBoard(maze* m){
    int row, col;

    //it has to be add by 2 to make up for the border
    m->xsize = m->xsize + 2;
    m->ysize = m->ysize + 2;

    //dynamically the size
    m->arr = (char**) malloc((m->xsize +2) * sizeof(char*));
    for (row = 0; row < m->xsize +2; row++){
        m->arr[row]= (char*)malloc((m->ysize + 2) * sizeof(char));
    }

    //set each position to be empty
    //make board with '.'
    for (row = 0; row < m->xsize + 2; row++){
        for (col = 0; col < m->ysize + 2; col++){
            m->arr[row][col] = '.';
        }
    }
    //make board with '*'
    for (row = 0; row < (m->xsize + 2); row++){
        m->arr[row][0] = '*';
        m->arr[row][m->ysize - 1] = '*';
    }
    for (col = 0; col < (m->ysize + 2); col++){
        m->arr[0][col] = '*';
        m->arr[m->xsize - 1][col] = '*';
    }

    // mark the starting and ending positions in the maze
    m->arr[m->xstart][m->ystart] = 's';
    m->arr[m->xend][m->yend] = 'e';
}

/***********************************************/
//initialize a node to NULL
node* initList(){
    node *list;
    list = NULL;
    return list;
}
/***********************************************/
//this function checks if the stack is empty
int isEmpty(node* head){
    if (head == NULL){
        return TRUE;
    }
    return FALSE;
}

/***********************************************/
//this function puts an element at the front of the list
void push(node** head, int xval, int yval){

    node *tmp = (node*)malloc(sizeof(node));
    tmp->xcord = xval;
    tmp->ycord = yval;
    tmp->next = *head;
    *head = tmp;
}

/************************************************/
// this function remove the front element of the linked list
void pop(node** head){

    if (head != NULL){
        node *tmp = (*head)->next;
        free(*head);
        *head = tmp;
    }
}

/************************************************/
// access the value of the first element
int topXcoor(node* head){

    return head->xcord;
}

int topYcoor(node* head){

    return head->ycord;
}

/************************************************/
// resets the linked list in order to be used again
void reset (node** head){
    node* tmp = *head;
    node* next;

    while(tmp != NULL){
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    *head = NULL;
}

/******************************************/
//this function reverse the list
void reverseList (node** head){
    node* prev = NULL;
    node* curr = *head;
    node* next = NULL;

    while (curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

/********************************************/
//display the list
void showList(node* head){

    while(head != NULL){
        printf("(%d, %d)", head->xcord, head->ycord);
        head = head->next;
    }
    printf("\n");
}

/*******************************************************/
int main (int argc, char **argv)
{
  FILE *src = NULL;
  maze m1;

  int xpos, ypos;
  int i,j;
  int count = 0;

  int debugMode = 1; // debug mode is set to true initially

  printf("%s %s %s\n\n", argv[0], argv[1], argv[2]);

  /* verify the proper number of command line arguments were given */
  if(argc == 2) { // if the are only two arguments
     debugMode = 0; // debug mode is false
     src = fopen( argv[1], "r" ); // read in file

     //check if th einput file is NULL
     if(src == NULL){
         fprintf (stderr, "Can't open input file: %s\n", argv[1] );
         exit(-1);
     }
  }

  /* Try to open the input file. */
  else if (strncmp(argv[1], "-d", 2) == 0 ){
    debugMode = 1; // debug mode is true
    src = fopen(argv[2], "r"); // read file

    //checj if the input file is NULL
    if(src == NULL){
        fprintf(stderr, "Can't open input file: %s\n", argv[2] );
        exit(-1);
    }
  }

   else if (strncmp(argv[2], "-d", 2) == 0){ // if the third argument is -d
        debugMode = 1; // debug mode is true
        src = fopen(argv[1], "r"); // read in file

        // check to see if the input file is NULL
        if (src == NULL){
            fprintf(stderr, "This file cannot be opened: %s\n", argv[1]);
            exit (-1);
        }
    }

  //checks if there is a proper number of command
  if (argc > 3){
        fprintf(stderr, "Too many files entered.\n");
        exit (-1);
    }


  /* read in the size, starting and ending positions in the maze */
 /**********************************************************/
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  //checks of the input is valid
   while (invalidSize(&m1)){
        fprintf(stderr, "%d %d => Invalid: Maze sizes must be greater than 0.\n", m1.xsize, m1.ysize);
        fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
    }
    /* print them out to verify the input */
    printf ("size: %d, %d\n", m1.xsize, m1.ysize);
    count++; // adds one to count if correct input was given
  /**********************************************************/

  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);

  while (invalidStartingPoint(&m1)){
        fprintf(stderr, "%d %d Invalid: Starting point must be within range.\n", m1.xstart, m1.ystart);
        fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
    }
    /* print them out to verify the input */
    printf ("start: %d, %d\n", m1.xstart, m1.ystart);
    count++; // adds one to count if correct input was given

  /*************************************************************/
  fscanf (src, "%d %d", &m1.xend, &m1.yend);

  while (invalidEndingPoint(&m1)){
        fprintf(stderr, "%d %d Invalid: Ending point must be within range.\n", m1.xend, m1.yend);
        fscanf (src, "%d %d", &m1.xend, &m1.yend);
    }
  /* print them out to verify the input */
  printf ("end: %d, %d\n", m1.xend, m1.yend);
  count++;

  // if there wasn't enough valid input, print error message
    if (count < 3){
        fprintf(stderr, "Not enough valid input. Please try another file.\n");
        return (-1);
    }
    mazeBoard(&m1);

      /* initialize the maze to empty */
      // create an array based on the size
      char arr1[m1.xsize][m1.ysize];
      for (i = 0; i < m1.xsize; i++)
         for (j = 0; j < m1.ysize; j++)
           arr1[i][j] = '.';

      /* mark the borders of the maze with *'s */
      for (i=0; i < m1.xsize; i++)
        {
         arr1[i][0] = '*';
         arr1[i][m1.ysize-1] = '*';
        }
      for (j=0; j < m1.ysize; j++)
        {
         arr1[0][j] = '*';
         arr1[m1.xsize-1][j] = '*';
        }

      /* mark the starting and ending positions in the maze */
      arr1[m1.xstart][m1.ystart] = 's';
      arr1[m1.xend][m1.yend] = 'e';

      /* mark the blocked positions in the maze with *'s */
      while (fscanf (src, "%d %d", &xpos, &ypos) != EOF){

        if(xpos < m1.ysize && ypos < m1.ysize &&
            m1.arr[xpos][ypos] != 's' &&
            m1.arr[xpos][ypos] != 'e'){

                // set the blocked position
            m1.arr[xpos][ypos] = '*';
            arr1[xpos][ypos] = '*';
        }
      }
      /* print out the initial maze */
      for (i = 0; i < m1.xsize+2; i++){
         for (j = 0; j < m1.ysize+2; j++){
           printf ("%c", m1.arr[i][j]);
        }
         printf("\n");
      }
      printf("\n");

      // creates and initialized a node head
    // head of the list is set to NULL
    node* listHead = initList();

    // push the starting position onto the stack
    push(&listHead, m1.xstart, m1.ystart);
    if (debugMode){
        printf("Debugging information: ");
        printf("(%d, %d) was pushed onto the stack\n", m1.xstart, m1.ystart);
    }
    arr1[listHead->xcord][listHead->ycord] = 'V';

    // while the end has not been found and the list isn't empty
    while (arr1[m1.xend][m1.yend] != 'V' && !isEmpty(listHead)){
        int topX = topXcoor(listHead);
        int topY = topYcoor(listHead);

        // break if the end is found
        if (arr1[m1.xend][m1.yend] == 'V'){
            break;
        }
        else{
            // if it can be done, make right move and update visited array
            if (m1.arr[topX][topY+1] != '*' && arr1[topX][topY+1] != 'V'){
                push(&listHead, topX, topY+1);
                topX = topXcoor(listHead);
                topY = topYcoor(listHead);
                if (debugMode == 1){
                    printf("Debugging information: ");
                    printf("(%d, %d) was pushed onto the stack\n", topX, topY);
                }
                arr1[topX][topY] = 'V';
            }

            // otherwise, make down move and update visited array
            else if (m1.arr[topX+1][topY] != '*' && arr1[topX+1][topY] != 'V'){
                push(&listHead, topX+1, topY);
                topX = topXcoor(listHead);
                topY = topYcoor(listHead);
                if (debugMode == 1){
                    printf("Debugging information: ");
                    printf("(%d, %d) was pushed onto the stack\n", topX, topY);
                }
                arr1[topX][topY] = 'V';
            }

            // otherwise, make left move and update visited array
            else if (m1.arr[topX][topY-1] != '*' && arr1[topX][topY-1] != 'V'){
                push(&listHead, topX, topY-1);
                topX = topXcoor(listHead);
                topY = topYcoor(listHead);
                if (debugMode == 1){
                    printf("Debugging information: ");
                    printf("(%d, %d) was pushed onto the stack\n", topX, topY);
                }
                arr1[topX][topY] = 'V';
            }

            // otherwise, make up move and update visited array
            else if (m1.arr[topX-1][topY] != '*' && arr1[topX-1][topY] != 'V'){
                push(&listHead, topX-1, topY);
                topX = topXcoor(listHead);
                topY = topYcoor(listHead);
                if (debugMode == 1){
                    printf("Debugging information: ");
                    printf("(%d, %d) was pushed onto the stack\n", topX, topY);
                }
                arr1[topX][topY] = 'V';
            }

            // if no moves can be made, need to pop and stack
            // and try to make a different move
            else{
                if (debugMode == 1){ // print debugging information if true
                    printf("Debugging information: ");
                    printf("(%d, %d) was popped from the stack\n", topX, topY);
                }
                pop(&listHead);
            }
        }
    }

    // if all of the nodes were popped, and the
    // list is now empty, there is no solution
    if (isEmpty(listHead)){
        printf("The maze has no solution.\n");
    }
    // otherwise, there was a solution
    // list is displayed from the start to end position
    else{
        printf("\nA solution was found:\n");
        reverseList(&listHead);
        showList(listHead);
        printf("\n");
    }

    // resets the list so it can be used again
    reset(&listHead);


}
