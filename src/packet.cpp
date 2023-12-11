#include "packet.h"

const uint8_t Packet::SYNC_CHAR_1 = 0x37;
const uint8_t Packet::SYNC_CHAR_2 = 0x01;

uint16_t Packet::calculate_checksum(std::vector<uint8_t>& class_data) {
    uint16_t sum1 = 0, sum2 = 0;
    for (uint16_t i = 0; i < class_data.size(); i++) {
        sum1 = (sum1 + class_data[i]) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return (sum2 << 8) | sum1;
}

void Packet::serialize(std::vector<uint8_t>& bytes, std::vector<uint8_t>& class_data) {
    bytes.push_back(SYNC_CHAR_1);
    bytes.push_back(SYNC_CHAR_2);
    bytes.push_back(get_message_id());
    bytes.push_back(get_subclass_id());

    bytes.push_back(payload_length());
    bytes.push_back(payload_length() >> 8);

    bytes.insert(bytes.end(), class_data.begin(), class_data.end());

    uint16_t checksum = calculate_checksum(class_data);
    bytes.push_back(checksum);
    bytes.push_back(checksum >> 8);
}

void AckPacket::bytes(std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> class_data;
    serialize(bytes, class_data);
}

AckPacket::~AckPacket() {}

uint8_t AckPacket::get_message_id() {
    return MESSAGE_ID;
}

uint8_t AckPacket::get_subclass_id() {
    return SUBCLASS_ID;
}

inline constexpr uint16_t AckPacket::payload_length() {
    return 0;
}

const uint8_t AckPacket::MESSAGE_ID = 0x00;
const uint8_t AckPacket::SUBCLASS_ID = 0x01;

ThrustSetPacket::ThrustSetPacket(uint8_t thruster_id, float speed) {
    ThrustSetPacket::thruster_id = thruster_id;
    ThrustSetPacket::speed = speed;
}

void ThrustSetPacket::bytes(std::vector<uint8_t>& bytes) {
    std::vector<uint8_t> class_data;
    class_data.push_back(thruster_id);
    uint8_t* speed_bytes = reinterpret_cast<uint8_t*>(&speed);
    class_data.insert(class_data.end(), speed_bytes, speed_bytes + 4);
    serialize(bytes, class_data);
}

ThrustSetPacket::~ThrustSetPacket() {}

uint8_t ThrustSetPacket::get_message_id() {
    return MESSAGE_ID;
}

uint8_t ThrustSetPacket::get_subclass_id() {
    return SUBCLASS_ID;
}

inline constexpr uint16_t ThrustSetPacket::payload_length() {
    return 5;
}

const uint8_t ThrustSetPacket::MESSAGE_ID = 0x02;
const uint8_t ThrustSetPacket::SUBCLASS_ID = 0x02;
