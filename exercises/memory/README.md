# Memory exercises

## Solutions

### Exercise 1
* Main: See below
* Supporting files: None
* How to run: not run-able because these functions (listed below) are assumed to have their implementations available.
```c
mem_addr_t PageTable[NB_PAGE];
disk_addr_t SwapTable[NB_PAGE];

// have to be called when a memory error is detected (??)
void memory_error();
// returns the address of the page in memory, null if memory is full
mem_addr_t memory_alloc();
// return the page number in PageTable, the address of the page is in memory
int lru_select();
// allocate a page in the swap, return the address of page on disk
disk_addr_t swap_alloc();
// free a page from swap
void swap_free(disk_addr_t disk_page);
// load a page from swap to a page in memory
void load_page(mem_addr_t mem_page, disk_addr_t disk_page);
// store a page from memory into a page in swap
void store_page(mem_addr_t mem_page, disk_addr_t disk_page);

// to be implemented, invoked whenever PageTable[npage] == NULL
void page_fault(int npage)
{
    if (SwapTable[npage]) {
        memory_error();
    }

    mem_addr_t mem_page = memory_alloc();

    if (mem_page == NULL) {
        int repl_npage = lru_select();
        mem_page = PageTable[repl_npage];
        disk_addr_t swap_page = swap_alloc();
        store_page(mem_page, swap_page);
        SwapTable[repl_npage] = swap_page;
        PageTable[repl_npage] = NULL;
    }

    load_page(mem_page, SwapTable[npage]);
    swap_free(SwapTable[npage]);
    SwapTable[npage] = NULL;
    PageTable[npage] = mem_page;
}
```

### Exercise 2
* Main file: See below
* Supporting files: None
* Explanation: Each numeric header represents the page accessed, and each column excluded that represents the state of the memory after the access on the header. Pages are default to empty at t = 0. Replacement algorithm only used where a page to access is invalid (not in the column). The *first example* of all 3 tables below *starts at the __7th__ column* (access to __page 5__).
* How to run: Just filling in the tables (about replacement algorithms).
  * FIFO (First In, First Out: what used first will be swapped out first)
    | Access to page | 1 | 2 | 3 | 4 | 1 | 2 | 5 | 1 | 2 | 3 | 4 | 5 | 2 | 3 |
    | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
    | **Page 1** | 1 | 1 | 1 | 1 | 1 | 1 | 5 | 5 | 5 | 5 | 4 | 4 | 4 | 4 |
    | **Page 2** | NULL | 2 | 2 | 2 | 2 | 2 | 2 | 1 | 1 | 1 | 1 | 5 | 5 | 5 |
    | **Page 3** | NULL | NULL | 3 | 3 | 3 | 3 | 3 | 3 | 2 | 2 | 2 | 2 | 2 | 2 |
    | **Page 4** | NULL | NULL | NULL | 4 | 4 | 4 | 4 | 4 | 4 | 3 | 3 | 3 | 3 | 3 |
  * LRU (Least Recently Used: what accessed the least will be swapped out first)
    | Access to page | 1 | 2 | 3 | 4 | 1 | 2 | 5 | 1 | 2 | 3 | 4 | 5 | 2 | 3 |
    | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
    | **Page 1** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 5 | 5 | 5 |
    | **Page 2** | NULL | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 |
    | **Page 3** | NULL | NULL | 3 | 3 | 3 | 3 | 5 | 5 | 5 | 5 | 4 | 4 | 4 | 4 |
    | **Page 4** | NULL | NULL | NULL | 4 | 4 | 4 | 4 | 4 | 4 | 3 | 3 | 3 | 3 | 3 |
  * Optimal (what will not be used in longest time will be swapped out first) (can't be implemented IRL)
    | Access to page | 1 | 2 | 3 | 4 | 1 | 2 | 5 | 1 | 2 | 3 | 4 | 5 | 2 | 3 |
    | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
    | **Page 1** | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 | 4 | 4 | 4 | 4 |
    | **Page 2** | NULL | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 | 2 |
    | **Page 3** | NULL | NULL | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 3 | 3 |
    | **Page 4** | NULL | NULL | NULL | 4 | 4 | 4 | 5 | 5 | 5 | 5 | 5 | 5 | 5 | 5 |
