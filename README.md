# CommProtocol

# CommProtocol
A simple command based protocol to exchange data between two participants. The protocol uses a frame with default header and trailer fields. Two frames are used for sending and receiving data respectively.

|------------------------------------------------------------------------------------------|
| Preamble | Dest Addr | Source Addr | Sequence Num | Command | Length | Payload | Trailer |
|------------------------------------------------------------------------------------------|

Frame protocol:

Preamble consists of 5 bytes: 	0xf1, 0xf2, 0xf3, 0xf4, 0xf5.
Source Addr: 					The address of the sender is a 16-bit integer value.
Destination Addr: 				The address of the recipient is a 16-bit integer value.
Sequence Number: 				A consecutive number with a 32-bit integer value.
Command: 						An 8-bit integer value that specifies the command.
Length: 							An 8-bit integer value that specifies the length of the payload in bytes.
Payload: 						command-specific information with variable length
Trailer: 						consists of 3 bytes: 0xff, 0xfe, 0xfd

The protocol defines the following commands:

GetDevice Info:
1. Command: 0x01
2. Payload Length: 0x03
3. Payload:

 Timestamp: 16-bit integer value

 Signal: 8 bit integer value

 SetInterval:
1. Command: 0x02
2. Payload Length: 0x02
3. Payload:

Interval: 16bit integer value.
SetDeviceName:
1. Command: 0x03
2. Payload Length: 0x16
3. Payload:
Name: String with a maximum length of 0x16 bytes.
