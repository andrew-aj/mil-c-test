#ifndef PACKET_FACTORY_H_
#define PACKET_FACTORY_H_

#include "packet.h"

class PacketFactory {
   public:
    Packet* createAckPacket() { return new AckPacket(); }

    Packet* createNakPacket() { return nullptr; }

    Packet* createThrustSetPacket(uint8_t thruster_id, float speed) { return new ThrustSetPacket(thruster_id, speed); }

    Packet* createKillSetPacket(uint8_t kill_set) { return nullptr; }

    Packet* createKillReceivePacket(uint8_t kill_status) { return nullptr; }

    Packet* createBatteryPollRequestPacket() { return nullptr; }

    Packet* createBatteryPollResponsePacket(float one, float two, float three, float four) { return nullptr; }
};
#endif  // PACKET_FACTORY_H_
