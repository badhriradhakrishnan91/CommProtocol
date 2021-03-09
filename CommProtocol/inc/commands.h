#ifndef INC_COMMANDS_H_
#define INC_COMMANDS_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#include <iostream>
#include <string>
#include <cstring>

#include <stdint.h>

using namespace std;

/* Exported defines ----------------------------------------------------------*/
#define DEVICEINFO_LEN      0x03

#define SOURCE_ADDR         0x4892
#define DEST_ADDR           0xA96F

/* Exported types ------------------------------------------------------------*/

extern uint8_t sendFrame[500];      //!< Buffer for send frame
extern uint8_t receiveFrame[500];   //!< Buffer for receive frame
extern uint32_t seqNum;             //!< Sequence number
extern uint8_t preamble[5];         //!< Header preamble
extern uint8_t trailer[3];          //!< Trailer bytes

/**
 * @brief Structure for payload frame data.
 */
typedef struct{
	uint8_t command;                //!< Command code for operations
	uint8_t payloadLen;             //!< Payload length
}frame_t;

/* Class definitions ---------------------------------------------------------*/
/**
 * @brief Frame info for various commands.
 */
class FrameInfo {
public:
	FrameInfo()
{
		memset(sendFrame, 0x00, sizeof(sendFrame));
		memset(receiveFrame, 0x00, sizeof(receiveFrame));
}

	void setPreamble();
	void setDestAddr(uint16_t destAddr);
	void setSourceAddr(uint16_t sourceAddr);
	void setCommand(uint8_t command);
	void setSeqNum(uint32_t seqNum);
};

/**
 * @brief Get device info commands and payload length.
 */
class GetDeviceInfo{
private:
	frame_t getdeviceInfo = {
			.command = 0x01,
			.payloadLen = 0x03,
	};

public:
	void getPayload(uint16_t timeStamp, uint8_t signal);
};

/**
 * @brief Set interval commands and payload length.
 */
class SetInterval{
private:
	frame_t setInterval = {
			.command = 0x02,
			.payloadLen = 0x02,
	};

public:
	void setPayload(uint16_t payload);
};

/**
 * @brief Set device name commands and payload length.
 */
class SetDeviceName{
private:
	frame_t setDeviceName = {
			.command = 0x03,
	};

public:
	void setPayload(string payload, uint8_t payloadLen);
};

/* Exported functions --------------------------------------------------------*/
void init();
uint8_t readDeviceInfo(uint16_t timeStamp, uint8_t signal);
void changeInterval(uint16_t intervalVal);
void changeDeviceName(string deviceName, uint16_t deviceNameLen);
void updateSequenceNumber(uint32_t seqNum);
void setTrailer(uint8_t len);
void printFrame(uint16_t len);


#endif /* INC_COMMANDS_H_ */
