#include <chrono>
#include <iostream>
#include <vector>
class ShiftHistory {
    std::vector<int> a; int cap;
public:
    explicit ShiftHistory(int k): cap(k) {}
    void add(int x) { if ((int)a.size() == cap) { for (int i=1;i<cap;++i) a[i-1]=a[i]; a[cap-1]=x; } else a.push_back(x); }
    int latest() const { return a.empty() ? -1 : a.back(); }
};
class CircularHistory {
    std::vector<int> a; int cap, count=0, next=0;
public:
    explicit CircularHistory(int k): a(k), cap(k) {}
    void add(int x) { a[next]=x; next=(next+1)%cap; if(count<cap) ++count; }
    int latest() const { return count==0 ? -1 : a[(next-1+cap)%cap]; }
};
int main() {
    constexpr int K=50, N=200000;
    ShiftHistory s(K); CircularHistory c(K);
    auto t1=std::chrono::steady_clock::now(); for(int i=0;i<N;++i)s.add(i); auto t2=std::chrono::steady_clock::now();
    for(int i=0;i<N;++i) { c.add(i); }
    auto t3=std::chrono::steady_clock::now();
    std::cout << "shift_latest=" << s.latest() << " circular_latest=" << c.latest() << '\n';
    std::cout << "shift_ms=" << std::chrono::duration<double,std::milli>(t2-t1).count() << '\n';
    std::cout << "circular_ms=" << std::chrono::duration<double,std::milli>(t3-t2).count() << '\n';
}