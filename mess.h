#ifndef __CAR_MESSAGE_H
#define __CAR_MESSAGE_H

struct RadioPacket // Any packet up to 32 bytes can be sent.
{
    bool upGear;
	bool downGear;
	bool brake;
    uint16_t x;
    uint16_t y;
};

#endif