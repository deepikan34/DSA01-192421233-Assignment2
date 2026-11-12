# Assignment 2 – CO2: C++ Functions and Object-Oriented Concepts

**Student:** [Enter name]  
**Register number:** [Enter register number]  
**Repository:** `https://github.com/<your-username>/DSA01-<register-number>-Assignment2`  
**Compiler:** g++ 14.2.0, C++17, `-Wall -Wextra`

> The attached assignment PDF contains seven numbered questions (Q1–Q7). The generic request mentioned 12 tasks, but no Q8–Q12 appear in the supplied PDF. This report covers every numbered question in the PDF.

## Q1 – Call by value, reference and pointer

### Prediction before execution
For the supplied `change` program, the predicted output is:
```text
1 12 13
1 100
16 13 6
```
The first parameter is a copy, while the second is an alias and the third points to the caller's variable. Therefore only `b` and `c` change in `change`. `bigger(a,c)` returns a reference to the larger object; since `c` is larger, assigning 100 changes `c`. `show(1)` uses y=5,z=10; `show(1,2)` uses z=10; `show(1,2,3)` uses all explicit values.

### Observed result
The program output matched the prediction. The `show` results are 16, 13 and 6 respectively.

### Complete-the-code result
`applyConcession(long long& fee, int percent)` updates the caller's fee with `fee -= fee * percent / 100`. The by-value function changes only its local copy. Observed output:
```text
after call by value   : 45000
after call by reference: 40500
after call by pointer : 36450
```
The pointer call applies a further 10% to 40500. A `const T&` is appropriate when a large object must be read without copying but must not be modified.

### Design decision
For a chain of concessions, returning a new fee makes each calculation explicit and avoids hidden side effects: `fee = applyConcession(fee, percent)`. If the function is specifically an updater in a controlled account object, a non-const reference is also reasonable. This implementation demonstrates both reference and pointer updates.

### Alternative and complexity
All three scalar approaches take O(1) time. A `long long` value parameter copies one scalar (O(1) space); reference, pointer and const-reference parameters pass an address-like reference (O(1) extra space). Passing a large Student object by value copies the whole object (O(S) time/space for object size S), while reference/const-reference avoid that copy. A return-value design is `long long applyConcession(long long fee,int p){ return fee-fee*p/100; }`.

## Q2 – Return by reference and its dangers

`highestRef` finds the maximum array element and returns `int&`; the caller can write `highestRef(marks,4) += 2`. The index alternative returns an integer position and the caller updates `marks[index]`. The pointer alternative returns the address of the selected array element and the caller updates `*ptr`.

Observed test output:
```text
After reference moderation: 93
After index moderation: 95
After pointer moderation: 97
```
The search is O(n) time and O(1) auxiliary space for all three approaches. A reference or pointer to an array element is valid while that element remains alive and at the same storage location. A `std::vector` growth operation may reallocate storage and invalidate references, pointers and iterators. An index remains a position, but its meaning can change if elements are inserted/erased before it.

Returning `const int&` prevents modification through that reference; returning `int` returns a copy and is safest when the caller only needs a value. Returning a reference to a local variable is invalid because the local object is destroyed at function exit. The compiler warning is captured in `Task02/compiler_warning.txt`; the example is intentionally not run because using the dangling reference is undefined behaviour.

## Q3 – Default arguments and function overloading

The original three declarations make `charge(2)` ambiguous because both `charge(double)` and overloads with defaulted trailing parameters can be viable. The redesign uses `charge(int grams, bool express=false, bool insured=false)`, `charge(double kg, bool express=false, bool insured=false)`, and `charge(const Parcel&)`. The first two differ by the weight type; the Parcel overload handles structured input.

### Predictions before execution
- `charge(2)` → integer-grams overload (exact match).
- `charge(2.0f)` → double-kilograms overload (float-to-double promotion beats conversion to int).
- `charge(500,true)` → integer-grams overload.
- `charge(1.5,false,true)` → double-kilograms overload.
- `charge(p)` → Parcel overload.
- `charge(750)` → integer-grams overload.

### Observed output
```text
charge(2) = 0.04 [int grams]
charge(2.0f) = 40 [double kg via promotion]
charge(500, true) = 60 [int grams]
charge(1.5, false, true) = 50 [double kg]
charge(p) = 120 [Parcel]
charge(750) = 15 [int grams]
```
Overload ranking prefers exact match, then promotion, then standard conversion. Default arguments must be supplied from the right because trailing parameters are the ones that can be omitted. Overload resolution occurs at compile time and has no runtime dispatch cost. A Parcel structure centralises optional fields and makes adding a new option easier, but call sites become more verbose; a template can generalise types but needs constraints to avoid accidental matches. Each design has O(1) calculation time here; passing Parcel by const reference avoids copying it.

## Q4 – Class with an array inside it

`SavingsAccount` keeps account number, balance, a private array of 10 transactions, count and a circular `next` index. `deposit`, `withdraw` and the private recording helper are defined inside the class; `miniStatement` is defined outside using `SavingsAccount::miniStatement`.

Observed test: 11 deposits of 10 through 110 followed by a withdrawal of 25. The statement contains the newest ten entries in order:
```text
Account: 100234 Balance: 1635
Recent transactions (oldest to newest):
30
40
50
60
70
80
90
100
110
-25
```
The array is private to protect balance/history invariants. Shifting a full array costs O(k) per new transaction (k retained entries); a circular index overwrites the oldest slot in O(1). Both use O(k) storage. Increasing capacity from 10 to 50 changes the capacity constant and storage size; the circular design still needs no shifting. `std::deque` also supports push_back/pop_front in amortised O(1), but has container overhead and dynamic allocation.

## Q5 – Static members and arrays of objects

`issued` and `CAPACITY` are static because they belong to the BusTicket class, not to each ticket. The static data member is defined once outside the class (`int BusTicket::issued = 0`). `count()` is static and therefore has no `this` pointer; it cannot directly access a particular object's non-static `seat` or `name`. An array of four objects is initialised with four constructor calls.

### Prediction before execution
For `Token counter[3]`, constructors assign IDs 101, 102 and 103. `extra` receives 104; `issued()` returns four. Predicted output: `101 103 104 4`.

### Observed outputs
```text
101 103 104 4
```
The BusTicket program prints:
```text
Asha: Seat 1
Bala: Seat 2
Chitra: Seat 3
Dev: Waiting
Issued: 3
```
The static counter starts at 0 for BusTicket and persists across function calls. If a function is called twice and creates tickets each time, the shared count is not reset; the second call continues issuing remaining seats and then marks later tickets waiting. If each bus needs an independent capacity, a TicketOffice object passed to each ticket is more flexible than one class-wide static counter. A global counter also uses one integer but weakens encapsulation. All counter updates are O(1) and storage is O(1) shared state.

## Q6 – Friend functions and inline functions

`minutesBetween` and `earlier` are friend functions because they compare two Time objects symmetrically and need access to private hour/minute values. They are called as ordinary functions, unlike member functions (`a.isEarlier(b)`). A friend is not a member, but the class grants it private access. Keeping data private preserves invariants; making it public would allow uncontrolled changes.

Observed output:
```text
205 false
0 true
```
The first case is 09:45 to 13:10 (3 hours 25 minutes = 205 minutes). The second compares noon with itself (0) and 11:50 with noon (true). Inline requests that the compiler consider substituting a function body at the call site; it is not a guarantee. Tiny functions may benefit, but modern optimisation may inline or optimise ordinary functions too.

### Benchmark evidence
`Task06/q6_inline_benchmark.cpp` runs 10,000,000 calls for both an inline candidate and a noinline ordinary function. Example recorded run (milliseconds; hardware/compiler dependent):
- `-O0`: inline 35.7385 ms; ordinary 35.7060 ms.
- `-O2`: inline 18.3593 ms; ordinary 19.1124 ms.

The near-equal `-O0` result shows the keyword alone does not guarantee a speedup. At `-O2`, the inline candidate was modestly faster in this run. Repeat on the target machine and report its measurements. Both functions are O(1) per call; the loop is O(N). Member functions with getters can preserve encapsulation, while friend functions avoid exposing getters solely for comparison. The symmetric friend design is retained because both operands have equal status and access is limited to two named functions.

## Q7 – Diagnose, redesign and validate

### A. Diagnosis
The fixed-size history implemented by shifting all retained entries when full takes O(k) work for every new transaction. This becomes increasingly expensive as the required history capacity grows.

### B. Objective
Keep the most recent 50 values while making insertion O(1), retaining O(k) bounded memory and returning the latest item correctly.

### C. Revised design
Use a circular buffer with a fixed vector, `next` index and `count`. Insert at `next`, advance it modulo capacity, and increase count until full. This uses one additional index and avoids shifting. Pseudocode:
```text
add(value):
    data[next] = value
    next = (next + 1) mod capacity
    count = min(count + 1, capacity)
```
Trade-off: retrieving values in chronological order requires index arithmetic; a shifting array keeps chronological order physically but costs more per insertion.

### D. Prediction
For the same capacity and number of insertions, both designs should retain the same latest value; circular insertion should take less time once the buffer is full.

### E. Validation
The benchmark inserts 200,000 integers into capacity-50 histories. Both versions report latest value 199999. Example recorded timings are in `Task07/q7_circular_buffer_comparison_output.txt`; timings vary by machine. The original shifting design is O(k) per insertion after filling; circular insertion is O(1). Both use O(k) space.

### F. Final evaluation
The circular design meets the objective: same retained latest value with constant-time insertion and bounded memory. It is preferable for frequent updates and larger capacities. A shifting array can still be simpler when capacity is tiny and chronological iteration is more important than insertion cost. The timing result is empirical, not a universal guarantee.

## Submission checklist
- [x] Q1–Q7 source programs
- [x] Compile/run output text and output screenshots
- [x] Compiler warning evidence for dangling reference
- [x] Predictions documented before observed outputs
- [x] Complexity and alternative-design analysis
- [x] README and progressive local commits
- [ ] Replace student placeholders and repository name with the exact register number
- [ ] Create GitHub repository, add remote, push commits, verify public/faculty access
- [ ] Upload report and GitHub URL through Google Classroom

**Important:** The local repository and report are prepared, but no GitHub account was connected in this session. Therefore no live GitHub URL has been created or pushed. You must create the remote repository and push this work yourself.
