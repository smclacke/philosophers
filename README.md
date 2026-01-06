# Philosophers
*I never thought philosophy would be so deadly*

A multi-threaded solution to the classic Dining Philosophers problem, demonstrating concurrent programming, synchronization mechanisms, and deadlock avoidance using POSIX threads and mutexes.

---

## The Problem

Five philosophers sit at a table with forks between them. Each needs two forks to eat and can only think or eat. The challenge: design an algorithm ensuring no philosopher starves. A naive approach causes deadlock—all philosophers pick up left forks and wait infinitely for right forks.

**Reference:** https://en.wikipedia.org/wiki/Dining_philosophers_problem

---

## Program Usage

```bash
./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional_meals]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers
- `time_to_die`: Max milliseconds without eating before death
- `time_to_eat`: Milliseconds to eat (holding both forks)
- `time_to_sleep`: Milliseconds to sleep after eating
- `optional_meals`: Number of meals each philosopher must eat (optional)

**Examples:**
```bash
./philosophers 5 800 200 200        # Standard case
./philosophers 4 410 200 200 5      # With meal requirement
```

---

## Key Concepts

### Multi-threading & Mutexes
Each philosopher runs as a POSIX thread. A **mutex** (mutual exclusion lock) protects each fork—only one philosopher can hold it at a time. Multiple mutexes coordinate philosopher-specific data (eat count, last meal time) and program state (start/stop).

### Race Conditions
Occur when threads access shared data without synchronization. Mutexes serialize access to prevent unpredictable behavior and crashes.

### Deadlock Prevention
- **Ordered locking**: Philosophers always acquire left fork, then right fork (consistent order prevents circular waits)
- **Active monitoring**: A monitor thread detects starvation
- **Tight synchronization**: Ensures forks are always released for other philosophers

### Learning Objectives
✓ Thread lifecycle and concurrent execution  
✓ Mutex-based synchronization and resource protection  
✓ Deadlock recognition and prevention  
✓ POSIX thread APIs (`pthread_create`, `pthread_mutex_lock`, etc.)  
✓ State management in concurrent systems  
✓ Monitor threads for anomaly detection  

---

## Architecture

```
Main (args, init, lifecycle)
    ↓
Create mutexes → Spawn philosopher threads → Start monitor thread
    ↓
Each Philosopher Thread        Monitor Thread
├─ Think                      ├─ Check for deaths
├─ Grab left fork            ├─ Check meal completion
├─ Grab right fork           └─ Signal termination
├─ Eat (time_to_eat)
├─ Release forks
└─ Sleep (time_to_sleep)
```

---

## Source Files Overview

| File | Purpose |
|------|---------|
| `main.c` | Entry point, argument validation, orchestration |
| `init_input.c` | Parse and validate command-line arguments |
| `init_philos.c` | Create philosopher structures and allocate memory |
| `mutexes.c` | Initialize forks and program state mutexes |
| `routine.c` | Core philosopher logic (think→eat→sleep cycle) |
| `monitor.c` | Monitor thread detecting death and completion |
| `life_cycle.c` | Coordinate mutexes, threads, and cleanup |
| `time.c` | Precision timing functions |
| `utils.c`, `error.c` | Utilities and error handling |

### Data Structures (`structs.h`)

**t_data** (shared simulation state):
- Philosopher count, timing parameters
- Flags: `stop_b`, `died_b`, `yes_start_b`
- Mutex arrays for forks and program state
- Start timestamp for relative timing

**t_philo** (individual philosopher):
- ID, meal count (`x_eaten`), last meal time
- References to left/right fork mutexes
- Mutexes protecting eat count and dinner time

**t_god** (container):
- Pointer to `t_data`
- Array of `t_philo` structures

---

## Compilation & Execution

```bash
make              # Build executable
make clean        # Remove object files
make fclean       # Full cleanup
make re           # Rebuild

# Output format:
# [timestamp] [id] has taken a fork
# [timestamp] [id] is eating
# [timestamp] [id] is sleeping
# [timestamp] [id] is thinking
# [timestamp] [id] died
```

---

## Implementation Highlights

### Deadlock Prevention
1. **Ordered fork acquisition**: Left fork always acquired before right fork
2. **Monitor thread**: Continuously checks philosopher states for starvation
3. **Atomic operations**: Mutexes ensure fork pickup, status checks are indivisible

### Race Condition Prevention
- Fork access: Protected by individual fork mutexes
- Eat counters: Protected by `eat_xamount_m`
- Meal timestamps: Protected by `dinner_time_m`
- Program state: Protected by `prog_m[START]` and `prog_m[STOP]`

### Timing
- `gettimeofday()` for microsecond precision
- All delays relative to program start time
- Accurate starvation detection within millisecond windows

### Thread Synchronization
1. Philosophers wait for START signal before beginning
2. Monitor thread polls states in tight loop
3. All threads regularly check STOP flag for clean exit

---

## Key Takeaways

- **Synchronization is critical**: Unprotected shared data leads to crashes
- **Deadlock is a real threat**: Naive algorithms fail silently under specific timing
- **Concurrent testing is hard**: Race conditions appear inconsistently
- **Monitoring matters**: Active detection prevents silent failures
- **POSIX threads require discipline**: Mutex misuse causes subtle, hard-to-debug bugs
