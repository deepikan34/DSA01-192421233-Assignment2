# DSA01-192421233-Assignment2

## Student details
- Name: N.Deepika
- Register number: 192421233
- Course / section: DSA0111 - C++

## Compiler and build
- Compiler used: **g++ 14.2.0 (GNU) on Linux x86_64**
- Language standard: **C++17**
- Common compile command:

```bash
g++ -std=c++17 -Wall -Wextra Task01/q1_prediction.cpp -o Task01/q1_prediction
```

Run the matching executable from the repository root, for example:

```bash
./Task01/q1_prediction
```

Each task folder contains source (`.cpp`), captured terminal output (`*_output.txt`) and an output screenshot (`*_output.png`). `Task02/compiler_warning.txt` contains the intentional warning from the dangling-reference example. Do not execute that undefined-behaviour example.

## Task summaries
| Folder | Topic | Result |
|---|---|---|
| Task01 | Call by value, reference, pointer; reference return; default arguments | Caller fee remains 45000 by value, becomes 40500 by reference, then 36450 by pointer. |
| Task02 | Return by reference, index and pointer; dangling reference | Highest array element can be modified through a reference; local-reference return produces a compiler warning and is unsafe. |
| Task03 | Default arguments and overloading | Integer grams, floating kilograms and Parcel calls resolve without ambiguity. |
| Task04 | Class with fixed transaction array | Circular indexing retains the latest 10 transactions without shifting. |
| Task05 | Static members and object arrays | Three seats issued; fourth ticket is waiting. |
| Task06 | Friend and inline functions | Time difference is 205 minutes; comparison tests pass. Benchmark timings are recorded for `-O0` and `-O2`. |
| Task07 | Diagnose, redesign and validate | Circular history has O(1) insertion and is compared against O(k) shifting. |

## Exact commands
```bash
# Build and run a task (replace file and executable names)
g++ -std=c++17 -Wall -Wextra Task03/q3_overloading.cpp -o Task03/q3_overloading
./Task03/q3_overloading

# Inline benchmark at both optimisation levels
g++ -std=c++17 -Wall -Wextra -O0 Task06/q6_inline_benchmark.cpp -o Task06/benchmark_O0
./Task06/benchmark_O0
g++ -std=c++17 -Wall -Wextra -O2 Task06/q6_inline_benchmark.cpp -o Task06/benchmark_O2
./Task06/benchmark_O2
```

## Verification notes
All runnable task programs were compiled and executed in the prepared environment. The exact outputs are saved beside each source file. Timings are machine- and compiler-dependent; rerun them on the submission machine and replace the recorded values if they differ. The dangling-reference program is compile-only because using the returned reference is undefined behaviour.

## Git history
The repository was committed progressively, with separate commits for Task01 through Task07. Add your own GitHub remote and push after reviewing, personalising, and understanding every task.
