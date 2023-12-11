#include <cstring>
#include <iostream>
#include "interface.h"
#include "packet.h"
#include "packet_factory.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

void show(std::vector<uint8_t>& data) {
    for (auto a : data) {
        std::cout << std::hex << (uint16_t)a << " ";
    }
    std::cout << std::endl;
}

TEST_CASE("Test AckPacket") {
    AckPacket packet;
    std::vector<uint8_t> bytes;
    packet.bytes(bytes);
    std::vector<uint8_t> correct = {0x37, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
    CHECK(bytes == correct);
}

TEST_CASE("Test ThrustSetPacket") {
    float thrust = 1.0;
    uint8_t id = 0;
    ThrustSetPacket packet(0, thrust);

    std::vector<uint8_t> bytes;
    packet.bytes(bytes);

    std::vector<uint8_t> correct = {0x37, 0x01, 0x02, 0x02, 0x05, 0x00};

    std::vector<uint8_t> class_data;
    class_data.push_back(id);

    uint8_t* data = reinterpret_cast<uint8_t*>(&thrust);
    class_data.insert(class_data.end(), data, data + 4);

    uint16_t checksum = Packet::calculate_checksum(class_data);

    correct.insert(correct.end(), class_data.begin(), class_data.end());
    correct.push_back(checksum);
    correct.push_back(checksum >> 8);
    show(correct);

    CHECK(bytes == correct);
}

TEST_CASE("Test Send ThrustSetPacket") {
    float thrust = 1.0;
    uint8_t id = 0;

    PacketFactory factory;

    Packet* thrustPacket = factory.createThrustSetPacket(id, thrust);
    Packet* ack = factory.createAckPacket();

    class TestSerial : public SerialInterface {
       public:
        TestSerial(Packet* packet, Packet* ack) {
            this->packet = packet;
            this->ack = ack;
        }

        void write(const unsigned char* s, std::size_t size) override {
            std::vector<uint8_t> data(s, s + size);
            std::vector<uint8_t> bytes;
            packet->bytes(bytes);
            CHECK(data == bytes);
        }

        void read(const unsigned char* s, std::size_t bytes) override {
            std::vector<uint8_t> data;
            ack->bytes(data);
            std::memcpy((void*)s, data.data(), bytes);
        }

        uint16_t bytes_available() override {
            std::vector<uint8_t> data;
            ack->bytes(data);
            return data.size();
        }

       private:
        Packet* packet;
        Packet* ack;
    };

    class TestCAN : public CANInterface {
       public:
        void on_data(Packet& data) override {
            received_count++;
            std::vector<uint8_t> bytes;
            data.bytes(bytes);
            if (received_count == 1) {
                CHECK(bytes[2] == 0);
                CHECK(bytes[3] == 1);
            } else {
                REQUIRE(false);
            }
        }

       private:
        int received_count = 0;
    };

    TestCAN can;
    TestSerial serial(thrustPacket, ack);

    USBToCANDriver driver(serial, can);
    driver.send_packet(*thrustPacket);
    driver.read_packet();

    delete ack;
    delete thrustPacket;
}
