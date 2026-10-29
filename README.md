# Philosophers

[![C](https://img.shields.io/badge/language-C-555?style=flat-square&logo=c)](https://www.gnu.org/software/gnu-c-manual/)
![License](https://img.shields.io/badge/license-Educational-lightgrey?style=flat-square)

The dining philosophers problem in C, focusing on concurrency, synchronization and timing.

This project solves the same problem twice: with **threads and mutexes** (`philo/`), and with **processes and semaphores** (`philo_bonus/`), with no data races and no deadlock.

---

## Build & Run

### Requirements
- Linux (POSIX threads and semaphores)
- `gcc` or `clang`, `make`

> Note: Philosophers has been tested on **Fedora Linux 44** and **Ubuntu 24.04**, with gcc 13, gcc 14 (including `-std=gnu23`, the gcc 15 default) and clang 18.

### Compilation
`make -C philo`  
`make -C philo_bonus`

### Run
`./philo/philo <philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [meals] [-s]`  
ex : `./philo/philo 5 800 200 200 7`

`./philo_bonus/philo_bonus` takes the same arguments.

---

## Arguments

- **philosophers** : Number of philosophers (and forks)
- **time_to_die** : Time in ms a philosopher can go without starting a meal
- **time_to_eat** : Time in ms spent eating
- **time_to_sleep** : Time in ms spent sleeping
- **meals** (optional) : The simulation stops once every philosopher has eaten this many times
- **-s** (optional, after `meals`) : Shows the meal counter on each "is eating" line
- **--usage** : Prints the help

All values are integers between 1 and `INT_MAX`.

### Examples

- `./philo/philo 5 800 200 200 7` : Nobody dies, everyone eats 7 times
- `./philo/philo 4 410 200 200` : Runs until stopped (Ctrl+C)
- `./philo/philo 4 310 200 100` : A philosopher dies at ~310 ms

Each philosopher's lines are printed in their own colour:

```
0 1 has taken a fork
0 5 has taken a fork
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
...
```

---

## Technical Overview

### The Problem

N philosophers sit around a table with one fork between each pair. To eat, a philosopher needs both forks next to them. Each one loops through eating, sleeping and thinking, and dies if they go `time_to_die` ms without starting a meal. The program must:

- Never let two philosophers hold the same fork
- Never deadlock
- Announce a death within 10 ms, and print nothing after it
- Avoid data races, with no global variables

### Features

- Mandatory part, `philo/`: threads and mutexes
  - One thread per philosopher, no monitor thread: each philosopher checks its own death time on every iteration
  - Non-blocking forks: each fork has a state flag protected by its own mutex, locked only long enough to test and claim the fork. No thread ever waits while holding a mutex, so a deadlock cannot happen
  - Fairness: even and odd philosophers pick up their forks in opposite order, and even-numbered ones wait one meal before starting, so neighbours alternate instead of competing
  - A single print mutex, which also holds the "simulation running" flag: once a death is printed, nothing else is
- Bonus part, `philo_bonus/`: processes and semaphores
  - One process per philosopher, created with `fork()`
  - The forks are a single counting semaphore in the middle of the table
  - A second semaphore guards printing, and a third one releases all processes at the same time
  - When a philosopher dies, its process exits with a dedicated status; the parent then kills the others and removes the named semaphores

### Architecture

Each philosopher is a small state machine: **thinking → taking forks → eating → sleeping**, with a death check between steps.

- **Parsing** : `parsing.c`
  - Validates the arguments (digits only, 1 to `INT_MAX`)
  - `--usage` help and `-s` option
- **Setup** : `tab.c`, `tab_bis.c` (`init_bonus.c` in the bonus)
  - Allocates philosophers, forks and mutexes (semaphores in the bonus)
- **Simulation** : `thread.c`, `routine.c`, `state.c`, `state_bis.c` (`process_bonus.c`, `state_bonus.c`, `state_bis_bonus.c` in the bonus)
  - Thread (or process) creation and synchronized start
  - State machine and death check
  - Fork handling and output
- **Utilities** : `time.c`, `color.c`, `failure.c`, `utils.c`
  - Time in milliseconds
  - One colour per philosopher
  - Error handling and cleanup

---

### Checking for Data Races

```bash
make -C philo re CFLAGS="-Wall -Wextra -Werror -g -fsanitize=thread"
./philo/philo 5 800 200 200 7

make -C philo re
valgrind --tool=helgrind ./philo/philo 4 800 200 200 3
```

- ThreadSanitizer (from 1 to 200 philosophers), Helgrind and DRD report no data race
- Valgrind reports no memory leak

---

## More

### Educational Context

This project was developed as part of a programming curriculum (42 Paris) and aims to demonstrate:

- Multithreading with POSIX threads and mutexes
- Multiprocessing with `fork()` and POSIX semaphores
- Deadlock-free resource sharing
- Precise timing and clean resource management

> Note: This project is for educational purposes, as a hands-on learning experience for concurrent programming.

### AI Usage

This README was written with the help of Claude (Anthropic). The code itself was written without any LLM, as the project was part of a learning curriculum.
