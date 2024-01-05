#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <cstddef>
#include <cstdint>
#include <vector>

class SerialDriverInterface {
   public:
    virtual void send(const unsigned char* s, std::size_t size) = 0;

    virtual void receive(const unsigned char* buffer, std::size_t bytes) = 0;

    virtual uint16_t bytes_available() = 0;
};

class SerialDriverFactory {
   public:
    static SerialDriverInterface* createSerialDriver() { return nullptr; }
};

#endif  // INTERFACE_H_
