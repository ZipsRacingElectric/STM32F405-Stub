# Introdution to the CAN-Bus Communication Protocol - Zips Racing
CAN-Bus (or more specifically, CAN 2.0a) is a communication protocol used for connecting multiple control units spread over a large area. Due to its flexibility and reliability, CAN-Bus is a common choice for connecting the various subsystems of a vehicle.

[CSS-Electronics - CAN-Bus Explained - A Simple Intro (https://www.youtube.com/watch?v=oYps7vT708E)](https://www.youtube.com/watch?v=oYps7vT708E)

## ChibiOS Interface
In ChibiOS, I2C is exposed through the CAN driver. The comprehensive driver documentation can be found at the below URL, however it is quite technical.

[common/doc/chibios/ChibiOS HAL Reference Manual.pdf](common/doc/chibios/ChibiOS&#32;HAL&#32;Reference&#32;Manual.pdf), page 83.

An excerpt of the most useful functionality is provided here.

### Configuration
TODO(Barach): Do I even want to talk about this?

Before a bus can be used, it must first be configured and initialized. The `CANConfig` structure defines configuration options.

```
struct CANConfig
{
	// CAN MCR register initialization data. Note some bits in this register
	// are enforced by the driver regardless their status in this field.
	// Documentation for this
	uint32_t mcr;

	// CAN BTR register initialization data. Note some bits in this register
	// are enforced by the driver regardless their status in this field.
	uint32_t btr;
}
```

### Transmit Frame
```
struct CANTxFrame
{
	// The data length code of the message (number of used bytes in the
	// payload).
	uint8_t DLC:4;

	// The RTR (remote transmit request) bit of the frame.
	uint8_t RTR:1;

	// The IDE (extended identifier) bit of the frame. If set to CAN_IDE_STD,
	// the SID is used, if set to CAN_IDE_EXT, the EID is used. (See below for
	// what these mean).
	uint8_t IDE:1;

	union
	{
		// The 11-bit standard identifier of the message (only used if
		// IDE = CAN_IDE_STD).
		uint32_t SID:11;

		// The 29-bit extended identifier of the message (only used if
		// IDE = CAN_IDE_EXT).
		uint32_t EID:29;
	};

	union
	{
		// The payload of the message, accessed as an array of 8 8-bit integers.
		uint8_t data8[8];

		// The payload of the message, accessed as an array of 4 16-bit integers.
		uint16_t data16[4];

		// The payload of the message, accessed as an array of 2 32-bit integers.
		uint32_t data32[2];

		// The payload of the message, accessed as an array of 1 64-bit integer.
		uint64_t data64[1];
	};
}
```

### Transmitting Messages
The specified frame is queued for transmission, if the hardware queue is full then the invoking thread is queued. Trying to transmit while in sleep mode simply enqueues the thread.
```
msg_t canTransmitTimeout(CANDriver* canp, canmbx_t mailbox, const CANTxFrame* ctfp, sysinterval_t timeout)
```
Parameters:
- `canp`	- A pointer to the `CANDriver` object.
- `mailbox`	- The number of the mailbox(s) to use. Use `CAN_ANY_MAILBOX` for the first available mailbox.
- `ctfp`	- A pointer to the `CANTxFrame` to be transmitted.
- `timeout`	- The number of ticks before the operation times out. The following special values are allowed:
	- `TIME_IMMEDIATE` - Timeout immediately.
	- `TIME_INFINITE` - No timeout.

Return Value:
- `MSG_OK`		- The frame was transmitted successfully.
- `MSG_TIMEOUT`	- The operation has timed out.
- `MSG_RESET`	- The driver has been stopped while waiting.

### Receive Frame
```
struct CANRxFrame
{
	// The data length code of the received message (number of bytes written
	// into the payload).
	uint8_t DLC:4;

	// The RTR (remote transmit request) bit of the frame.
	uint8_t RTR:1;

	// The IDE (extended identifier) bit of the frame. If set to CAN_IDE_STD,
	// the SID is used, if set to CAN_IDE_EXT, the EID is used. (See below for
	// what these mean).
	uint8_t IDE:1;

	union
	{
		// The 11-bit standard identifier of the message (only used if
		// IDE = CAN_IDE_STD).
		uint32_t SID:11;

		// The 29-bit extended identifier of the message (only used if
		// IDE = CAN_IDE_EXT).
		uint32_t EID:29;
	};

	union
	{
		// The payload of the message, accessed as an array of 8 8-bit integers.
		uint8_t data8[8];

		// The payload of the message, accessed as an array of 4 16-bit integers.
		uint16_t data16[4];

		// The payload of the message, accessed as an array of 2 32-bit integers.
		uint32_t data32[2];

		// The payload of the message, accessed as an array of 1 64-bit integer.
		uint64_t data64[1];
	};
};
```

### Receiving Messages
The function waits until a frame is received. Note Trying to receive while in sleep mode simply enqueues the thread.
```
msg_t canReceiveTimeout(CANDriver* canp, canmbx_t mailbox, CANRxFrame* crfp, sysinterval_t timeout)
```
Parameters:
- `canp`	- A pointer to the `CANDriver` object.
- `mailbox`	- The number of the mailbox(s) to use. Use `CAN_ANY_MAILBOX` for the first available mailbox.
- `crfp`	- A pointer to the buffer where the `CANRxFrame` is to be copied.
- `timeout`	- The number of ticks before the operation times out. The following special values are allowed:
	- `TIME_IMMEDIATE`	- Timeout immediately, this is useful in an event driven scenario where a thread never blocks for I/O.
    - `TIME_INFINITE`	- No timeout.

Return Value:
- `MSG_OK`		- A frame has been received and placed in the buffer.
- `MSG_TIMEOUT`	- The operation has timed out.
- `MSG_RESET`	- The driver has been stopped while waiting.