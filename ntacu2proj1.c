#include <stdio.h>
#include <stdlib.h>

//---------function prototypes---------------
void arrayCopy (int fromArray[], int toArray[], int size);
void myFavorateSort (int arr[], int size);
int linSearch (int arr[], int size, int target, int* numComparisons);
int binary (int arr[], int size, int target, int* numComparisons);
//--------------------------------------------
 int main()
{
    int *ptr;// pointer will hold my first array
    int *ptr2;// second array
    int size =2;
    ptr = (int *) malloc (size * sizeof(int) );
    printf("Enter values, enter -999 to terminate\n" );
    int val;
    scanf("%d",&val);
    int i=0;  //counter value keeps track of number of elements in array
    while(val!=-999){
        if(i<size){;}//its safe to keep adding to the array
        else{
             int *temp;//make the array bigger
            temp = (int *) malloc ( size * 2 * sizeof(int) );
            int z;
            for ( z = 0 ; z < size ; z++)
            temp[z] = ptr[z];
            free (ptr);
            ptr = temp;
            size = size * 2;
        }
        ptr[i] =val;// store the numbers
        i++;//ads one number to the array
        scanf("%d",&val);//inputs new number if -999 while loop will not run
    }
    ptr2 = (int *) malloc (size * sizeof(int) );// holds the second array to store copy
    printf("Inputed numbers are: ");
    int j;
    for(j = 0; j < i; j++) {
        printf("  %d", ptr[j]);
    }
    arrayCopy(ptr, ptr2,i); // sends inputed numbers to be copied
    printf("\n   Copy numbers are: ");
    for( j = 0; j < i; j++) {
        printf("  %d", ptr2[j]);
    }
    myFavorateSort(ptr2,i);//  sorts the numbers in assending order
    printf("\n Sorted numbers are: ");
    for( j = 0; j < i; j++) {
        printf("  %d", ptr2[j]);
    }
    int numberOfComparisons=0;//counter for comparisons  for linear search
       int numberOfComparisons2=0; //counter for binary comparisons

    int target;// number to be searched
    while(1){
    printf("\nEnter a target value or -999 to exit program:" );
    scanf("%d", &target);
    if (target ==-999){
        printf("Exiting program");
        return 0;
    }
    int index = linSearch(ptr, i,target, &numberOfComparisons );// recceives the index positin of the unsorted array targer number
    if(index ==-1){
            printf("Hola");
        printf("The number was not found. The number of linear comparisons: %d\n",numberOfComparisons);
    }
    else{
        printf("\n the linear search of the unsorted array comparison is: %d\n",numberOfComparisons  );
        printf("\n the linear search of the unsorted array index position is: %d \n",index  );
    }
    int index2 = binary( ptr2,  i, target, &numberOfComparisons2);// will receive the index of the sorted target number
    if(index2 ==-1){
        printf("The number was not found. The number of binary comparisons: %d\n",numberOfComparisons2);
    }
    else{
        printf("\n the binary search of the sorted array comparisons is: %d \n",numberOfComparisons2  );
        printf("\n the binary search of the sorted array index position is: %d \n",index2  );
    }
    numberOfComparisons2 =0;// set my counters back to 0 for the next loop
    numberOfComparisons =0;
    index=0;
    index2 =0;

    }
    return 0;
}
//------------------------------------------------
 void arrayCopy(int fromArray[], int toArray[], int size){//copies array to second array
 	int i;
   for(  i =0;i<size;i++){
    toArray[i]=fromArray[i];
   }
 }//bubble sort
 //--------------------------------------------
 void myFavorateSort (int ptr2[], int size){//receives the array and sorts it in ascending order
    int i,j;
    int swap;
    for(i=0;i<size;i++){
        for(j=i;j<size;j++){
            if(ptr2[j]<ptr2[i]){
                swap = ptr2[i];
                ptr2[i] = ptr2[j];
                ptr2[j] = swap;
            }
        }
    }
 }
 //---------------------------------------------------------------
 //linear search on unsorted array
 int linSearch (int ptr[], int size, int target, int* numComparisons){
    int i=0;
    for(i;i<size;i++){
        (*numComparisons)++;  //hold current numComparisons and update returning it to main
        if(target==ptr[i]){
            break;  //break out of for loop will be one less than coparisons which is the index of the target value
        }
    }
    if(i ==size){
        return -1; //all elements were crossed and target number  was not found
    }
    else{
        return i; // this will hold the index position of the target number
    }
 }
 //----------------------------------------------------------------
 // binary search on the sorted array
 int binary(int ptr2[], int size, int target, int* numComparisons){
	int     low = 0;
    int high = size - 1;
    while (low <= high) {
      int mid = low + ((high - low) / 2);
       if (ptr2[mid] > target){
           high = mid - 1;
       }
       else if (ptr2[mid] < target){
           low = mid + 1;
       }
       else{
        (*numComparisons)++;
           return mid; // found
   }
    (*numComparisons)++;
   }
 return -1;
  }
