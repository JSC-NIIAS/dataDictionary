
#ifndef MA_WITH_SHIFTED_LOCATION_REFERENCE_Message_H_INCLUDED
#define MA_WITH_SHIFTED_LOCATION_REFERENCE_Message_H_INCLUDED

#include "Euroradio_Message.h"
#include "Bitstream.h"
#include <iostream>

struct MA_with_Shifted_Location_Reference_Message : public Euroradio_Message
{
    uint16_t  L_MESSAGE        ;  // # 10
    uint32_t  T_TRAIN          ;  // # 32
    uint8_t  M_ACK             ;  // # 1
    uint32_t  NID_LRBG         ;  // # 24
    uint8_t  Q_SCALE           ;  // # 2
    uint16_t  D_REF            ;  // # 16


    Packet_Header packetID;
    BasePacketPtr  packet_15;
    PacketSequence  optional_packets;

    MA_with_Shifted_Location_Reference_Message() : Euroradio_Message(33) {}

    void print(std::ostream& stream) const override
    {
        stream << '('
               << +header.NID_MESSAGE  << ","
               << +L_MESSAGE << ","
               << +T_TRAIN << ","
               << +M_ACK << ","
               << +NID_LRBG << ","
               << +Q_SCALE << ","
               << +D_REF << ","
               << *(packet_15);

        for (auto i = optional_packets.begin(); i != optional_packets.end(); ++i)
        {
            if (i == optional_packets.begin())
            {
                stream << ',';
            }
            stream << *(*i);
        }

        stream << ")";
    }

    bool equals(const Euroradio_Message& p) const override
    {
	if (auto q = dynamic_cast<const MA_with_Shifted_Location_Reference_Message*>(&p))
	{
            bool status = true;
    
            status = status && (header.NID_MESSAGE == q->header.NID_MESSAGE);
            status = status && (L_MESSAGE == q->L_MESSAGE);
            status = status && (T_TRAIN == q->T_TRAIN);
            status = status && (M_ACK == q->M_ACK);
            status = status && (NID_LRBG == q->NID_LRBG);
            status = status && (Q_SCALE == q->Q_SCALE);
            status = status && (D_REF == q->D_REF);
            status = status && (*packet_15 == *(q->packet_15));

            if (optional_packets.size() == q->optional_packets.size())
            {
                for (size_t i = 0; i < optional_packets.size(); ++i)
                {
                    status = status && (*(optional_packets[i]) == *(q->optional_packets[i]));
                }
            }
            else
            {
                return false;
            }

            return status;
        }
	return false;
    }

    bool decode(Bitstream& stream);

    bool encode(Bitstream& stream) const;
};

typedef std::shared_ptr<MA_with_Shifted_Location_Reference_Message> MA_with_Shifted_Location_Reference_MessagePtr;

#endif // MA_WITH_SHIFTED_LOCATION_REFERENCE_Message_H_INCLUDED

