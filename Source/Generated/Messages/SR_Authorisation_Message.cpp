
#include "SR_Authorisation_Message.h"
#include "Packet_Header.h"
#include "Decoder_Branch.h"
#include "Encoder_Branch.h"
#include "Bitstream_Write.h"
#include "Bitstream_Read.h"


#include <iostream>
#include <cassert>

bool SR_Authorisation_Message::decode(Bitstream& stream)
{
    uint32_t old_pos = stream.bitpos;

    L_MESSAGE = Bitstream_Read(&stream, 10);
    T_TRAIN = Bitstream_Read(&stream, 32);
    M_ACK = Bitstream_Read(&stream, 1);
    NID_LRBG = Bitstream_Read(&stream, 24);
    Q_SCALE = Bitstream_Read(&stream, 2);
    D_SR = Bitstream_Read(&stream, 15);

    Packet_Header packetID;

    while (old_pos + (8 * L_MESSAGE) > stream.bitpos + 8 + 7)
    {
        BasePacketPtr packet;

        Packet_Header_Decoder(&stream, &packetID);

        packet = Decoder_Branch_TrackToTrain(stream, packetID);
        if (packet)
        {
            if (packet->header.NID_PACKET != 63)
            {
                return false;
            }
            optional_packets.push_back(packet);
        }
        else
        {
            return false;
        }
    }

    if (stream.bitpos > old_pos + (8 * L_MESSAGE))
    {
        return false;
    }

    stream.bitpos = old_pos + (8 * L_MESSAGE);

    return true;
}

bool SR_Authorisation_Message::encode(Bitstream& stream) const
{
    uint32_t old_pos = stream.bitpos;

    Bitstream_Write(&stream, 10, L_MESSAGE);
    Bitstream_Write(&stream, 32, T_TRAIN);
    Bitstream_Write(&stream, 1, M_ACK);
    Bitstream_Write(&stream, 24, NID_LRBG);
    Bitstream_Write(&stream, 2, Q_SCALE);
    Bitstream_Write(&stream, 15, D_SR);


    for (auto p = optional_packets.begin(); p != optional_packets.end(); ++p)
    {

        if (Packet_Header_Encoder(&stream, &((*p)->header)) != 1)
        {
            return false;
        }

        if (Encoder_Branch_TrackToTrain(stream, *p) != 1)
        {
            return false;
        }
    }

    if (stream.bitpos > old_pos + (8 * L_MESSAGE))
    {
        return false;
    }

    stream.bitpos = old_pos + (8 * L_MESSAGE);

    return true;
} 
