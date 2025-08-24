#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>

struct myArray
{
    int total_size; // total number of block reserved
    int used_size;// number of used block
    int *ptr; // it points to first element of array
};

void createArray(struct myArray * a, int tSize, int uSize){
    // (*a).total_size = tSize;
    // (*a).used_size = uSize;
    // (*a).ptr = (int *)malloc(tSize * sizeof(int));

    a->total_size = tSize;
    a->used_size = uSize;
    // give contiguous memory of tSize*sizeof(int) byte
    // and ptr point to 1st block/element of memory location
    a->ptr = (int *)malloc(tSize * sizeof(int));
}

void show(struct myArray *a){
    for (int i = 0; i < a->used_size; i++)
    {
        printf("%d\n", (a->ptr)[i]);
    }
}

void setVal(struct myArray *a){
    int n;
    for (int i = 0; i < a->used_size; i++)
    {
        printf("Enter element:%d\n", i);
        scanf("%d", &n);
        (a->ptr)[i] = n;
    }
    
}

int main(){
    struct myArray marks;/*What Happens in Memory
When you declare struct myArray marks;, the compiler allocates memory for the variable marks. Specifically, it allocates enough memory to hold all three members of the structure:

Memory for total_size (an integer)
Memory for used_size (an integer)
Memory for ptr (a pointer to an integer)*/

/*struct myArray defines a new structure type with three members.
struct myArray marks; declares a variable marks of this structure type.
The variable marks can then be used to store and manage an array, including its total size, used size, and a pointer to the array's elements.
*/
    createArray(&marks, 100, 20);
    printf("We are taking input now:\n");
    setVal(&marks);

    printf("We are printing stored information show:\n");
    show(&marks);

    return 0;
}