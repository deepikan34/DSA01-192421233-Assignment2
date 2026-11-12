// Compile only to inspect the diagnostic. Do not execute this program.
int& badReference() {
    int local = 10;
    return local; // warning: reference to local variable returned
}
int main() { int& r = badReference(); return r; }