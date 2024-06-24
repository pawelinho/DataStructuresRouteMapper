#include <cassert>
#include "address.h"

void testAddressEquality() {
    Address a1("Location A", 10, 20);
    Address a2("Location A", 10, 20);
    Address a3("Location B", 30, 40);

    assert(a1 == a2);
    assert(!(a1 == a3));
}

int main() {
    testAddressEquality();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
