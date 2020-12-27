# Memory exercises

## Solutions

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
