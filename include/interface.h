#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <cstddef>
#include <cstdint>
#include <vector>

#include "packet.h"

class SerialInterface {
   public:
    virtual void write(const unsigned char* s, std::size_t size) = 0;

    virtual void read(const unsigned char* buffer, std::size_t bytes) = 0;

    virtual uint16_t bytes_available() = 0;
};

class CANInterface {
   public:
    virtual void on_data(Packet& data) = 0;
};

class USBToCANDriver {
   public:
    USBToCANDriver(SerialInterface& stream, CANInterface& interface);

    void read_packet();

    void send_packet(Packet& packet);

   private:
    SerialInterface& stream;

    CANInterface& interface;
};

#endif  // INTERFACE_H_
