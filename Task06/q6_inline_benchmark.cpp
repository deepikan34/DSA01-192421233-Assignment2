#include <chrono>
#include <iostream>
volatile long long sink = 0;
inline int inlineMinutes(int h, int m) { return h * 60 + m; }
#if defined(__GNUC__)
__attribute__((noinline))
#endif
int ordinaryMinutes(int h, int m) { return h * 60 + m; }
int main() {
    constexpr int N = 10000000;
    auto t1 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink += inlineMinutes(i % 24, i % 60);
    auto t2 = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) sink += ordinaryMinutes(i % 24, i % 60);
    auto t3 = std::chrono::steady_clock::now();
    std::cout << "inline_ms=" << std::chrono::duration<double, std::milli>(t2-t1).count() << '\n';
    std::cout << "ordinary_ms=" << std::chrono::duration<double, std::milli>(t3-t2).count() << '\n';
    std::cout << "sink=" << sink << '\n';
}