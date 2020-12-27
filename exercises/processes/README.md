# Processes exercises

## Solutions

### Exercise 1
* Main: [main.c](Ex1/main.c)
* Supporting files: [gendoc](Ex1/gendoc), [Print](Ex1/Print), [install.sh](Ex1/install.sh)
* How to run:
```bash
# While in Ex1/
chmod +x install.sh
./install.sh
gcc -Wall -Wextra -std=c11 -o Ex1 main.c
./Ex1
```

### Exercise 2
* Main: [main.c](Ex2/main.c)
* Supporting files: [a.c](Ex2/a.c), [b.c](Ex2/b.c)
* How to run: Impossible to run at the moment (will be stuck at scanf() phase of A and B processes)
```bash
# While in Ex2/
gcc -Wall -Wextra -std=c11 -o a.out a.c
gcc -Wall -Wextra -std=c11 -o b.out b.c
gcc -Wall -Wextra -std=c11 -o Ex2 main.c
./Ex2
```

### Exercise 3
* Main: [main.c](Ex3/main.c)
* Supporting files: None
* How to run:
```bash
# While in Ex3/
gcc -Wall -Wextra -std=c11 -o Ex3 main.c
./Ex3
```
