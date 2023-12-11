#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <cstddef>
#include <cstdint>
#include <vector>

#include "packet.h"

class serial_interface {
   public:
    virtual void write(const char* s, std::size_t size) = 0;

    virtual void read(const char* buffer, std::size_t bytes) = 0;

    virtual bool has_bytes() = 0;
};

class can_interface {
   public:
    virtual void on_data(Packet& data) = 0;

    virtual void send_data(Packet& data) = 0;
};

#endif  // INTERFACE_H_
