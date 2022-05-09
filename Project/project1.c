#include <stdio.h>
#include <stdlib.h>

void makeArrayCopy (int fromArray[], int toArray[], int size)
{
    for(int i = 0; i < size; i++)
        {
            toArray[i] = fromArray[i];
        }
}

void swap(int *p1, int *p2) 
{ 
    int temp = *p1; 
    *p1 = *p2; 
    *p2 = temp; 
}

void myFavoriteSort (int arr[], int size)
{
    int i, j, min;
    for (i = 0; i < size; i++) 
     {
        min = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min]){
                min = j;
            }
        }
        swap(&arr[min], &arr[i]);
    }
}

void indexComparison (int unsortedArray[],int sortedArray[] ,int size, int *counter)
{
    for(int i = 0; i < size; i++)
    {
        if(unsortedArray[i] == sortedArray[i])
            (*counter)++;
    }
}

int targetSum (int arr[], int size, int target, int* index1, int* index2)
{
    while(*index1 != *index2)
    {
        if (arr[*index1] + arr[*index2] == target)
        {
            return 1;
        }
        else if (arr[*index1] + arr[*index2] <= target)
        {
            *index1 += 1;
        }
        else if(arr[*index1] + arr[*index2] >= target)
        {
            *index2 -= 1;
        }
        if(arr[*index1] == arr[*index2])
        {
            return -1;
        }
    }
}

int main (int argc, char** argv)
{
 int val; 
 int *userInput; 
 int size = 1;
 userInput = (int*)malloc(sizeof(int)*1);

 /* prompt the user for input */
 printf ("Enter in a list of numbers to be stored in a dynamic array.\n");
 printf ("End the list with the terminal value of -999\n");

 int indices = 0;
 
 /* loop until the user enters -999 */
 scanf ("%d", &val);
 while (val != -999)
   {
    /* store the value into an array */
    if(indices >= size)
    {
        int *temp;
        temp = userInput;
        userInput = (int*)malloc(sizeof(int)*size*2);
        
        for(int j = 0; j < size; j++)
        {
            userInput[j] = temp[j];
        }

        free(temp);

        size *= 2;
    }

    userInput[indices] = val;
    indices++;

    /* get next value */
    scanf("%d", &val);
   }

 /* call function to make a copy of the array of values */
  int *copy = (int*)malloc(sizeof(int)*indices);
  makeArrayCopy(userInput, copy, indices);

 /* call function to sort one of the arrays */ 
  myFavoriteSort(copy, indices);

 /* Prompt user to enter a value to pick a task */
 printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n"); 
 int choice;
 scanf("%d", &choice);
 while(choice != 1 && choice != 2)
 {
     printf("Invalid input. Enter 1 or 2.\n");
     scanf("%d", &choice);
 }
 
 /* If user input is 1, perform index comparison */
 int counter = 0;
 if(choice == 1)
 {
     indexComparison(userInput, copy, indices, &counter);
     if(counter == 0)
    {
        printf("All elements change location in the sorted array.\n");
    }
    else
    {
        printf("%d values are in the same location in both arrays\n", counter);
    }
 }
 
  /* If user input is 2, perform target sum */
 if(choice == 2)
 {
    /* loop until the user enters -999 */
    printf ("Enter in a list of numbers to use for searching.  \n");
    printf ("End the list with a terminal value of -999\n");
    scanf ("%d", &val);
    while (val != -999)
    {
        /* call function to perform target sum operation */
        int index1 = 0;
        int index2 = indices - 1;
        int result = targetSum(copy, indices, val, &index1, &index2);
        /* print out info about the target sum results  */
        if(result == -1)
        {
            printf("Target sum failed!\n");
        }
        else if(result == 1)
        {
            printf("Success! Elements at indices %d and %d add up to %d\n", index1, index2, val);
        }
        /* get next value */
        scanf("%d", &val);
    }
  }

 printf ("Good bye\n");
 return 0;
} 