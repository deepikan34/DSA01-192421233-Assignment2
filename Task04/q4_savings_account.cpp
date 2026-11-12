#include <iostream>
#include <string>
class SavingsAccount {
    long long accountNumber;
    double balance;
    double transactions[10]{};
    int count = 0;
    int next = 0; // next position to overwrite (circular buffer)
public:
    SavingsAccount(long long number, double opening) : accountNumber(number), balance(opening) {}
    void deposit(double amount) { if (amount <= 0) return; balance += amount; record(amount); }
    bool withdraw(double amount) { if (amount <= 0 || amount > balance) return false; balance -= amount; record(-amount); return true; }
    void miniStatement() const;
private:
    void record(double amount) { transactions[next] = amount; next = (next + 1) % 10; if (count < 10) ++count; }
};
void SavingsAccount::miniStatement() const {
    std::cout << "Account: " << accountNumber << " Balance: " << balance << '\n';
    std::cout << "Recent transactions (oldest to newest):\n";
    int start = (count == 10) ? next : 0;
    for (int i = 0; i < count; ++i) std::cout << transactions[(start + i) % 10] << '\n';
}
int main() {
    SavingsAccount a(100234, 1000);
    for (int i = 1; i <= 11; ++i) a.deposit(i * 10);
    a.withdraw(25);
    a.miniStatement();
}