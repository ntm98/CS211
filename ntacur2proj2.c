#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
//structures with typedef
/*--------------------------------------------------*/
typedef struct{

    char *stack_1; //pointer a dynamic array
    int size;
    int top;
} stack;

/*--------------------------------------------------*/
typedef stack * Stackk;
    void push(stack* s, char val);
    char pop(stack * s);
    int is_empty(stack * s);
    stack *init (int n);
    void clear(stack *stak);
    int debug = FALSE;
    int balance_fn (char *value, int *error_at)
/*-------------------------------------------------*/
 {
    char punct_marks = '\0';
    char tmp; // a temporary
    int error = FALSE;
    int i = 0;
    stack *stck;
    stck = init(301);
    while (value[i] != '\0'){
        punct_marks = value[i];
        // if- statement checking every symbol
        if (punct_marks == '(' || punct_marks == '{' || punct_marks == '[' || punct_marks == '<')
            push(stck, punct_marks); // function push it will s
        else if (punct_marks == ')' || punct_marks == '}' || punct_marks == ']'|| punct_marks == '>'){
            if (is_empty (stck)){
                error = TRUE;
                break;
            }
        tmp = pop(stck);
        if (!((tmp == '(' && punct_marks == ')') || (tmp == '{' && punct_marks == '}')
            ||(tmp == '[' && punct_marks == ']')||(tmp == '<' && punct_marks == '>'))){
                error = TRUE;
                break;
            }
        }
            i++;
    }
    if (!is_empty (stck))
            error = TRUE;
        if ((error == TRUE) && (error_at != NULL))
            *error_at = i + 1;
        clear(stck);
            return error;
}
/*-----------------------------------------------------------------------*/
// Push function works when a symbol is encountered,
// a symbol is pushed onto the stack
void push(Stackk stck, char val_par){

    if (stck->top >= 301){

        printf ("\nStack FULL creating new stack");

        char *tmp = (char *)malloc( sizeof(char) * (stck->size + 2) );
        free(stck->stack_1);
        stck->stack_1 = tmp;
        stck->stack_1 += 2;
    }
        stck->stack_1[++(stck->top)] = val_par;
    }
/*--------- function pop  --------------------------------------------------*/
//
char pop(stack * stck)
    {
        if (stck->top <= -1)
        return '\0';
        return stck->stack_1[(stck->top)--];
}
/*----------------function is_empty ---------------------------------------*/
// if the stack is empty, the expression is not balanced
int is_empty (stack * stck){

    if (stck->top <= -1) // checking if the stack is empty
        return TRUE;  // if is balanced
        return FALSE; // is not balanced
}
/*-----------------------------------------------------------------------*/
stack *init(int n){
        stack *tmp;
        tmp = malloc (sizeof (stack)+2);
    if (tmp == NULL){
        printf ("Terminating\n");
        exit (1);
    }
    tmp->stack_1 = malloc (sizeof (char) * n + 2);
    if (tmp->stack_1 == NULL){
        printf("Terminating\n");
        exit (1);
    }
        tmp->top = -1;
        return tmp;
}
/*-----------------------------------------------------------------------*/
void clear (stack *stck){
    if (stck != NULL){  //checking if the stack is empty
        if (stck->stack_1) // we are giving back the memory with free
            free (stck->stack_1);
            free (stck);
        }
}
/*-----------------------------------------------------------------------*/
int main (int argc, char** argv)
{
 char input[301];
 debug = FALSE;
 int values;
 int error_at;
 if( argc > 2 )
    {
    printf("Please use: %s[-d]\n", argv[0]);
    exit(0);
    }
    if( argc == 2 && argv[1][0] == '-' && argv[1][1] == 'd' )
    {
    printf("\nDebuging information\n");
    debug = TRUE;
}
 /* set up an infinite loop */
 while (1)
 {
   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;

   printf ("%s\n", input);

   /* run the algorithm to determine is input is balanced */
    values = balance_fn(input, &error_at);
    if(values == FALSE)
    {
        printf ("\nExpression are balance:\n");
    }
     else{

        printf ("\nExpression is not balance:\n");
        printf ("\n%s\n",input);
        printf("Missing a Symbol %d\n",error_at);
    }
 }

 printf ("\nGoodbye\n");
 return 0;
}
