#include <iostream>
#include <string>
struct Parcel { double kg; bool express; bool insured; };
double charge(int grams, bool express = false, bool insured = false) {
    double base = grams * 0.02;
    return base + (express ? 50 : 0) + (insured ? 20 : 0);
}
double charge(double kg, bool express = false, bool insured = false) {
    double base = kg * 20.0;
    return base + (express ? 50 : 0) + (insured ? 20 : 0);
}
double charge(const Parcel& p) { return charge(p.kg, p.express, p.insured); }
int main() {
    Parcel p{2.5, true, true};
    std::cout << "charge(2) = " << charge(2) << " [int grams]\n";
    std::cout << "charge(2.0f) = " << charge(2.0f) << " [double kg via promotion]\n";
    std::cout << "charge(500, true) = " << charge(500, true) << " [int grams]\n";
    std::cout << "charge(1.5, false, true) = " << charge(1.5, false, true) << " [double kg]\n";
    std::cout << "charge(p) = " << charge(p) << " [Parcel]\n";
    std::cout << "charge(750) = " << charge(750) << " [int grams]\n";
}