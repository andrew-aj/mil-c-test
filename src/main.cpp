#include <cstring>
#include <iostream>
#include <vector>
#include "interface.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

void show(std::vector<uint8_t>& data) {
    for (auto a : data) {
        std::cout << std::hex << (uint16_t)a << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("Test set killed packet") {
    SerialDriverInterface* interface = SerialDriverFactory::createSerialDriver();
    std::vector<unsigned char> packet;
    packet.push_back(0x00);
    packet.push_back(0x00);

    interface->send(packet.data(), 2);

    std::vector<unsigned char> received;
    received.reserve(2);

    interface->receive(received.data(), 2);

    CHECK_EQ(received, packet);
}
