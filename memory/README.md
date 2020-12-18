# Implement a small simulation of virtual memory management

## Given
The labwork includes a template file, [template_mem.c](template_mem.c).

## Compilation
The code was compiled with:
```bash
# gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
gcc -Wall -Wextra -std=c11  virtual_mem.c  -o virtual_mem.out
```

## Remarks
There are small modifications from the template code to implement this task.
1. Merge `Memory` and `MemState` to one struct.
   We find this change makes it easier to keep track of memory content and its state. Also `free` is changed to `isFree`. It sounds confusing and collides itself with a `stdlib` function about a related topic.
```c
// template_mem.c
char Memory[NB_MEM_PAGE][PAGE_SIZE];
struct {
	boolean free;
	int date;
	int npage;
} MemState[NB_MEM_PAGE];

// virtual_mem.c
struct memory {
    char content[PAGE_SIZE];
    int date;
    int npage;
    bool isFree;
} Memory[NB_MEM_PAGE];
```

2. `#include <stdbool.h>`
   It's included in the C standard, so there's no reason to keep it back. Besides, it's dangerous to simply re-define basic data types.
```c
// template_mem.c
#define boolean int
#define true 1
#define false 0

// virtual_mem.c
#include <stdbool.h>
```
Other changes are minors.

## Output
```
./virtual_mem.out 
initialization
access pages as in lecture (1,2,3,4,1,2,5,1,2,3,4,5,2,3)
read access page 0 : page0
read access page 1 : page1
read access page 2 : page2
read access page 3 : page3
read access page 0 : page0
read access page 1 : page1
read access page 4 : page4
read access page 0 : page0
read access page 1 : page1
read access page 2 : page2
read access page 3 : page3
read access page 4 : page4
read access page 1 : page1
read access page 2 : page2
completed
print memory_state
3 4 1 2 
completed
```
