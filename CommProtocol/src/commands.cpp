
/* Includes ------------------------------------------------------------------*/
#include "commands.h"
#include <iostream>

using namespace std;

/* Internal Defines ----------------------------------------------------------*/
#define DEBUG 1

/* Global Variables ----------------------------------------------------------*/
uint8_t sendFrame[500] = {0};                               //!< Buffer for send frame
uint8_t receiveFrame[500] = {0};                            //!< Buffer for receive frame
uint32_t seqNum = 0x00000000;                               //!< Sequence number
uint8_t preamble[5] = {0xF1, 0xF2, 0xF3, 0xF4, 0xF5};       //!< Header preamble
uint8_t trailer[3] = {0xFF, 0xFE, 0xFD};                    //!< Trailer bytes

/* Exported functions --------------------------------------------------------*/
#if DEBUG
/**
 * @brief Frame debug function.
 */
void printFrame(uint16_t len)
{
	for(uint16_t i=0; i<len; i++)
	{
		cout << hex << "\n" << unsigned(sendFrame[i]);
	}
}
#endif // DEBUG

/**
 * @brief Function to set header preamble.
 */
void FrameInfo::setPreamble()
{
	for(uint8_t i=0; i<5; i++)
	{
		sendFrame[i] = preamble[i];
	}
}

/**
 * @brief Function to set Destination address.
 */
void FrameInfo::setDestAddr(uint16_t destAddr)
{
	sendFrame[5] = (uint8_t)((destAddr >> 8) & 0xFF);
	sendFrame[6] = (uint8_t)((destAddr >> 0) & 0xFF);
}

/**
 * @brief Function to set Source address.
 */
void FrameInfo::setSourceAddr(uint16_t sourceAddr)
{
	sendFrame[7] = (uint8_t)((sourceAddr >> 8) & 0xFF);
	sendFrame[8] = (uint8_t)((sourceAddr >> 0) & 0xFF);
}

/**
 * @brief Function to set Sequence number.
 */
void FrameInfo::setSeqNum(uint32_t seqNum)
{
	sendFrame[9] = (uint8_t)((seqNum & 0xFF000000) >> 24);
	sendFrame[10] = (uint8_t)((seqNum & 0x00FF0000) >> 16);
	sendFrame[11] = (uint8_t)((seqNum & 0x0000FF00) >> 8);
	sendFrame[12] = (uint8_t)(seqNum & 0x000000FF);
}

/**
 * @brief Function to get device info.
 */
void GetDeviceInfo::getPayload(uint16_t timeStamp, uint8_t signal)
{
	uint8_t msb = receiveFrame[15];
	uint8_t lsb = receiveFrame[16];
	timeStamp = (msb << 8 ) | (lsb & 0xff);
	signal = receiveFrame[17];
}

/**
 * @brief Function to set device interval.
 */
void SetInterval::setPayload(uint16_t payload)
{
	sendFrame[13] = setInterval.command;
	sendFrame[14] = setInterval.payloadLen;
	sendFrame[15] = (uint8_t)((payload >> 8) & 0xFF);
	sendFrame[16] = (uint8_t)((payload >> 0) & 0xFF);
}

/**
 * @brief Function to set device name.
 */
void SetDeviceName::setPayload(string payload, uint8_t payloadLen)
{
	sendFrame[13] = setDeviceName.command;
	sendFrame[14] = payloadLen;
	for(uint8_t i=0; i<payloadLen; i++)
	{
		sendFrame[15 + i] = payload[i];
	}
}

/**
 * @brief Function to initialize communication.
 */
void init()
{
	FrameInfo frameObj;
	frameObj.setPreamble();
	frameObj.setDestAddr(DEST_ADDR);
	frameObj.setSourceAddr(SOURCE_ADDR);
	frameObj.setSeqNum(seqNum);

	//Code for transmit/receive frame data
}

/**
 * @brief Function to read the device info with time stamp and signal.
 */
uint8_t readDeviceInfo(uint16_t timeStamp, uint8_t signal)
{

	//Code for receiving data into receive frame

	//Check if the payload length is valid and non-zero in
	//the received frame
	//If payload length is zero then no payload data to get
	if(receiveFrame[14] != 0)
	{
		GetDeviceInfo getObj;
		getObj.getPayload(timeStamp, signal);
	}
	else
	{
		return 0;
	}
	return 1;
}

/**
 * @brief Function to change interval for device communication.
 */
void changeInterval(uint16_t intervalVal)
{
	SetInterval intervalObj;
	intervalObj.setPayload(intervalVal);
	setTrailer(2);

	//Code for transmit/receive frame data
}

/**
 * @brief Function to set user defined device name.
 */
void changeDeviceName(string deviceName, uint16_t deviceNameLen)
{
	SetDeviceName deviceNameObj;
	bool isChained = false;

	//check if chained transmission is required
	if(deviceNameLen > 0xFF)
	{
		isChained = true;
	}
	if(isChained)
	{
		//Code for sending payload in chunks since
		//the payload size is greater than 0xFF.
		//Sequence number is used to determine the
		//order of frame data to be sent in chunks.
		//Example: seqNum = 0x00000000 for 1st frame
		//         seqNum = 0x00000001 for 2nd frame
		//         seqNum = 0x00000002 for 3nd frame
		//         and so on...

		updateSequenceNumber(seqNum);
		setTrailer(deviceNameLen);
	}
	else
	{
		//Unchained transmission of payload

		deviceNameObj.setPayload(deviceName, (uint8_t)deviceNameLen);
		setTrailer((uint8_t)deviceNameLen);
	}

	//Code for transmit/receive frame data
}

/**
 * @brief Function to set trailer bytes for the frame.
 */
void setTrailer(uint8_t len)
{
	for(uint8_t i=0; i<sizeof(trailer); i++)
	{
		sendFrame[15 + len + i] = trailer[i];
	}

}

/**
 * @brief Function to update sequence number for chained transmission.
 */
void updateSequenceNumber(uint32_t seqNum)
{
	//Code for updating the sequence number based on number of
	//frames required to transmit the payload

	return;
}
