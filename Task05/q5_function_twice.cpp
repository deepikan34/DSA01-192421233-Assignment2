#include <iostream>
#include <string>
class TicketOfficeDemo {
public:
    static int issued;
    static const int capacity = 3;
};
int TicketOfficeDemo::issued = 0;
void bookBatch(const std::string& batchName) {
    for (int i = 1; i <= 2; ++i) {
        if (TicketOfficeDemo::issued < TicketOfficeDemo::capacity) {
            ++TicketOfficeDemo::issued;
            std::cout << batchName << " ticket " << i << ": Seat " << TicketOfficeDemo::issued << '\n';
        } else {
            std::cout << batchName << " ticket " << i << ": Waiting\n";
        }
    }
    std::cout << "Shared count: " << TicketOfficeDemo::issued << '\n';
}
int main() { bookBatch("First call"); bookBatch("Second call"); }
