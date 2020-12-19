#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NB_DISK_PAGE 5
#define PAGE_SIZE 20
#define NB_MEM_PAGE 4

char Disk[NB_DISK_PAGE][PAGE_SIZE];
int PageTable[NB_DISK_PAGE];
struct memory {
    char content[PAGE_SIZE];
    int date;
    int npage;
    bool isFree;
} Memory[NB_MEM_PAGE];

int Date = 1;

void init();
char *memory_read(int npage);
int memory_alloc();
void page_fault(int npage);
int lru_select();

int main(void)
{
	printf("initialization\n");
	init();

    printf("access pages as in lecture (1,2,3,4,1,2,5,1,2,3,4,5,2,3)\n");
    int serie[14] = { 0, 1, 2, 3, 0, 1, 4, 0, 1, 2, 3, 4, 1, 2 };
    for (int i = 0; i < 14; i++) {
        printf("read access page %d : %s\n", serie[i], memory_read(serie[i]));
    }
    printf("completed\n");

    printf("print memory_state\n");
    for (int i = 0; i < NB_MEM_PAGE; i++) {
        printf("%d ", Memory[i].npage);
    }
    printf("\n");
    printf("completed\n");
    return 0;
}

void init(void)
{
    for (int i = 0; i < NB_DISK_PAGE; i++) {
        sprintf(Disk[i], "page%d", i);
        PageTable[i] = -1;
    }

    for (int i = 0; i < NB_MEM_PAGE; i++) {
        Memory[i].isFree = true;
        Memory[i].npage = -1;
    }
}

char *memory_read(int npage)
{
    int mempage = PageTable[npage];

    if (mempage == -1) {
        page_fault(npage);
    }

    Memory[PageTable[npage]].date = Date++;

    return Memory[PageTable[npage]].content;
}

int memory_alloc(void)
{
    for (int i = 0; i < NB_MEM_PAGE; i++) {
        if (Memory[i].isFree) {
            Memory[i].isFree = false;
            return i;
        }
    }
    return -1;
}

void page_fault(int npage)
{
    int mempage = memory_alloc();
    if (mempage == -1) {
        mempage = lru_select();
        memcpy(Disk[Memory[mempage].npage], Memory[mempage].content, PAGE_SIZE);
        PageTable[Memory[mempage].npage] = -1;
    }
    Memory[mempage].npage = npage;
    memcpy(Memory[mempage].content, Disk[npage], PAGE_SIZE);
    PageTable[npage] = mempage;
}

int lru_select(void)
{
    int minDate = 99999;
    int mempage = -1;
    for (int i = 0; i < NB_MEM_PAGE; i++) {
        if (Memory[i].date < minDate) {
            minDate = Memory[i].date;
            mempage = i;
        }
    }
    return mempage;
}