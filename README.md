##################################################
# Machine Intelligence Laboratory
# University of Florida, Gainesville, FL
##################################################
# Spring 2024 Software Team Application
##################################################



##################################################
# Challenge Objective
##################################################

For your assessment, you will be implementing a simple simulated serial driver that processes
incoming packets and delivers return response packets according to the packet received.

You can use either Python or C++ to complete this challenge, and can complete the
specifications according to any code structure you prefer. You do not need any external
libraries to complete this challenge. However, if you do use external libraries, please
include a requirements.txt file or a list of dependencies in your README.

You will be assessed on the following criteria:
- Correctness of implementation
- Code quality
- Documentation (only simple documentation needed)
- Testing

You do not need to submit a complete solution to be considered for admission. However,
the more complete your solution, the better your chances of being accepted. Each
solution will be hollistically reviewed by a member of the Software Team.

##################################################
# Serial Driver Outline
##################################################

Each packet will begin with a 1 byte identifier. This identifier will be used to
determine the layout of the rest of the packet and how to handle the packet.

| Identifier | Message            |
|------------|--------------------|
| 0x00       | Kill               |
| 0x01       | Unkill             |
| 0x02       | Get Kill Status    |
| 0x03       | Return Kill Status |
| 0x04       | Heart Beat         |
| 0x05       | ACK                |
| 0x06       | Set Thrust         |
| 0x07       | ACK Thrust         |

At the end of every packet is a 1 byte checksum of all the data in the packet
to verify packet integrity. It is calculated as just the XOR operation applied
to every byte in the packet.

After the packet identifier, the contents of the packet become specific to the 
message type sent. Below is a chart

## Kill, Unkill, Get Kill Status, Heart Beat, and ACK

No bytes following identifier besides the checksum at the end. An example packet
would be:

Kill:
Byte 0: 0x00
Byte 1: 0x00

Unkill:
Byte 0: 0x01
Byte 1: 0x01

Get Kill Status:
Byte 0: 0x02
Byte 1: 0x02

Heart Beat:
Byte 0: 0x04
Byte 1: 0x04

ACK:
Byte 0: 0x05
Byte 1: 0x05

## Return Kill Status

One byte following the identifier. The byte is 0x00 if kill is enabled and 0x01 if kill
is disabled. Example packets would be:

Kill is disabled:
Byte 0: 0x03
Byte 1: 0x01
Byte 2: 0x02

Kill is enabled:
Byte 0: 0x03
Byte 1: 0x00
Byte 2: 0x03

## Set Thrust

One byte of the ID of the thruster to set the values of and then 4 bytes of the 
float thrust value in little endian form. The thrust IDs are 0-7.

## ACK Thrust

Exact same format as the Set Thrust message but with the ACK Thrust identifier.

## Packet order

If Kill or Unkill is sent to the serial driver, it sends back the packet as an ACK.

If Get Kill Status packet is sent, return a Return Kill Status packet.

If a Heart Beat packet is sent, return an ACK packet.

If a Set Thrust packet is sent, return an ACK Thrust packet.
