# Implement a small simulation of virtual memory management

## Summary
Template file: [template_mem.c](template_mem.c)
Solution: [virtual_mem.c](virtual_mem.c) (This README is about this file)

## Compilation
The code was compiled with:
```bash
# gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
gcc -Wall -Wextra -std=c11  virtual_mem.c  -o virtual_mem.out
```

## Remarks
There are small modifications from the template code to implement this task.
1. Merge `Memory` and `MemState` to one struct.
   * This change makes it easier to keep track of memory content and its state. 
   * `free` is also changed to `isFree`, because `free` sounds confusing and collides itself with a `stdlib` function about a related topic.
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
    * It's included in the C standard, so there's no reason to keep it back.
    * It's also dangerous to simply re-define basic data types.
```c
// template_mem.c
#define boolean int
#define true 1
#define false 0

// virtual_mem.c
#include <stdbool.h>
```

3. Make `page_fault()` returns the `mempage` it requests (commit [e2261a37186af0e793eb0832567a97342414a298](https://github.com/zer0warm/OS2020/commit/e2261a37186af0e793eb0832567a97342414a298)).
```c
// template_mem.c
void page_fault(int npage);

// virtual_mem.c
int page_fault(int npage);
```

Other changes are minors.

## Output
```
./virtual_mem.out
initialization
access pages as in lecture (1,2,3,4,1,2,5,1,2,3,4,5,2,3)
read access page 0:
-- page_fault: 0
-- memory_alloc: 0
-- content: page0
read access page 1:
-- page_fault: 1
-- memory_alloc: 1
-- content: page1
read access page 2:
-- page_fault: 2
-- memory_alloc: 2
-- content: page2
read access page 3:
-- page_fault: 3
-- memory_alloc: 3
-- content: page3
read access page 0:
-- content: page0
read access page 1:
-- content: page1
read access page 4:
-- page_fault: 4
-- memory_alloc: -1
-- lru_select: 2
-- content: page4
read access page 0:
-- content: page0
read access page 1:
-- content: page1
read access page 2:
-- page_fault: 2
-- memory_alloc: -1
-- lru_select: 3
-- content: page2
read access page 3:
-- page_fault: 3
-- memory_alloc: -1
-- lru_select: 2
-- content: page3
read access page 4:
-- page_fault: 4
-- memory_alloc: -1
-- lru_select: 0
-- content: page4
read access page 1:
-- content: page1
read access page 2:
-- content: page2
completed
print memory_state
4 1 3 2 
completed
```
