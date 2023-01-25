#include <stdlib.h>
struct mystruct{
  int number;
  struct mystruct *nextstruct;
};
int main(){
  struct mystruct *firststruct;
  firststruct = malloc(sizeof(struct mystruct));
  firststruct->number = 1;
  firststruct->nextstruct = malloc(sizeof(struct mystruct));
  firststruct->nextstruct->number = 2;
  firststruct->nextstruct->nextstruct = NULL;
}

// In the code, I have two pointer variables. The first pointer is
// firststruct which is the pointer to the struct mystruct. This pointer has been
// declared in line 7 is statistically allocated. Therefore, it comes from the stack
// portion of the memory. Therefore, once you compile your code, it knows
// that it needs to allocate 4bytes of memory to hold the address, the pointer
// variable.

// After that, from line 9 onwards, everything is being
// dynamically created. Where the function pass firststruct=malloc
// (sizeof(struct mystruct)), it request enough memory from the heap to store
// that structure. Once malloc returns with the address in the heap, it is stored
// in the firststruct pointer variable and creates the first link. As you can see in
// the diagram, the firststruct is at #1000, and that value 1000 gets stored into
// the firststruct pointer variable.

// Now we need to connect the first dynamically allocated struct
// to the second structure. To do so, we need to call malloc function again
// using the pointer variable inside the firststruct. Once the malloc returns with
// the address to the nextstruct which is #1010. Then, we will pass that value
// to the nextstruct pointer variable which is inside firststruct.
// So basically, we can keep adding new structs. The basic idea
// here is that we can access every struct because they are all linked together
// by this chain of pointers. And that's a fundamental idea behind a linked list.
