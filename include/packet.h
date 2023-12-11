#ifndef PACKET_H_
#define PACKET_H_

#include <cstdint>
#include <vector>

using std::uint16_t;
using std::uint8_t;

class Packet {
   public:
    virtual void bytes(std::vector<uint8_t>& bytes) = 0;

    static uint16_t calculate_checksum(std::vector<uint8_t>& class_data);

    virtual ~Packet(){};

   protected:
    virtual uint8_t get_message_id() = 0;
    virtual uint8_t get_subclass_id() = 0;
    virtual inline constexpr uint16_t payload_length() = 0;

    void serialize(std::vector<uint8_t>& bytes, std::vector<uint8_t>& class_data);

    static const uint8_t SYNC_CHAR_1;
    static const uint8_t SYNC_CHAR_2;
};

class AckPacket : public Packet {
   public:
    void bytes(std::vector<uint8_t>& bytes) override;

    ~AckPacket();

   protected:
    uint8_t get_message_id() override;

    uint8_t get_subclass_id() override;

    inline constexpr uint16_t payload_length() override;

    static const uint8_t MESSAGE_ID;
    static const uint8_t SUBCLASS_ID;
};

class ThrustSetPacket : public Packet {
   public:
    ThrustSetPacket(uint8_t thruster_id, float speed);

    void bytes(std::vector<uint8_t>& bytes) override;

    ~ThrustSetPacket();

   protected:
    uint8_t get_message_id() override;

    uint8_t get_subclass_id() override;

    inline constexpr uint16_t payload_length() override;

    static const uint8_t MESSAGE_ID;
    static const uint8_t SUBCLASS_ID;

   private:
    uint8_t thruster_id;
    float speed;
};

#endif  // PACKET_H_
