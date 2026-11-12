#include <iostream>
int& highestRef(int a[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (a[i] > a[best]) best = i;
    return a[best];
}
int highestIndex(const int a[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (a[i] > a[best]) best = i;
    return best;
}
int* highestPointer(int a[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (a[i] > a[best]) best = i;
    return &a[best];
}
// Deliberately unsafe example is kept commented: never call a function returning
// a reference to its local variable (the local object dies at function exit).
// int& dangling() { int local = 10; return local; }
int main() {
    int marks[] = {72, 91, 84, 88};
    highestRef(marks, 4) += 2;
    std::cout << "After reference moderation: " << marks[1] << '\n';
    int idx = highestIndex(marks, 4); marks[idx] += 2;
    std::cout << "After index moderation: " << marks[idx] << '\n';
    int* p = highestPointer(marks, 4); *p += 2;
    std::cout << "After pointer moderation: " << *p << '\n';
}