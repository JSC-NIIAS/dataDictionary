
#include "Validated_Train_Data_Message.h"
#include "Packet_Header_Decoder.h"
#include "Packet_Header_Encoder.h"
#include "Decoder_Branch.h"
#include "Encoder_Branch.h"
#include "Bitstream_Write.h"
#include "Bitstream_Read.h"

#include "Bitwalker_Peek_Normal.h"
#include <iostream>
#include <cassert>

bool Validated_Train_Data_Message::decode(Bitstream& stream)
{
    NID_MESSAGE = Bitstream_Read(&stream, 8);
    L_MESSAGE = Bitstream_Read(&stream, 10);
    T_TRAIN = Bitstream_Read(&stream, 32);
    NID_ENGINE = Bitstream_Read(&stream, 24);

    Packet_Header packetID;
    Packet_Header_Decoder(&stream, &packetID);

    packet_0_1 = Decoder_Branch_TrainToTrack(stream, packetID);
    if (!packet_0_1)
    {
        return false;
    }

    Packet_Header_Decoder(&stream, &packetID);
    packet_11 = Decoder_Branch_TrainToTrack(stream, packetID);
    if (!packet_11)
    {
        return false;
    }

    return true;
}

bool Validated_Train_Data_Message::encode(Bitstream& stream) const
{
    Bitstream_Write(&stream, 8, NID_MESSAGE);
    Bitstream_Write(&stream, 10, L_MESSAGE);
    Bitstream_Write(&stream, 32, T_TRAIN);
    Bitstream_Write(&stream, 24, NID_ENGINE);

    Packet_Header packetID;
    packetID.NID_PACKET = packet_0_1->id;

    if (Packet_Header_Encoder(&stream, &packetID) != 1)
    {
        return false;
    }
    if (Encoder_Branch_TrainToTrack(stream, packet_0_1) != 1)
    {
        return false;
    }

    packetID.NID_PACKET = packet_11->id;

    if (Packet_Header_Encoder(&stream, &packetID) != 1)
    {
        return false;
    }
    if (Encoder_Branch_TrainToTrack(stream, packet_11) != 1)
    {
        return false;
    }

    return true;
} 
