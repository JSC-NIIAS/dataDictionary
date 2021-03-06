
#ifndef REQUEST_TO_SHORTEN_MA_Message_H_INCLUDED
#define REQUEST_TO_SHORTEN_MA_Message_H_INCLUDED

#include "EuroradioMessage.h"
#include "Bitstream.h"
#include <iostream>

struct Request_to_Shorten_MA_Message : public EuroradioMessage
{
    uint16_t  L_MESSAGE        ;  // # 10
    uint32_t  T_TRAIN          ;  // # 32
    uint8_t  M_ACK             ;  // # 1
    uint32_t  NID_LRBG         ;  // # 24

    BasePacketPtr  packet_15;
    BasePacketPtr  packet_80;

    Request_to_Shorten_MA_Message() : EuroradioMessage(9) {}

    void print(std::ostream& stream) const override
    {
        stream << '('
               << +header.NID_MESSAGE  << ","
               << +L_MESSAGE << ","
               << +T_TRAIN << ","
               << +M_ACK << ","
               << +NID_LRBG << ","
               << *(packet_15) << ","
               << *(packet_80) << ")";
    }

    bool equals(const EuroradioMessage& p) const override
    {
	if (auto q = dynamic_cast<const Request_to_Shorten_MA_Message*>(&p))
	{
            bool status = true;
    
            status = status && (header.NID_MESSAGE == q->header.NID_MESSAGE);
            status = status && (L_MESSAGE == q->L_MESSAGE);
            status = status && (T_TRAIN == q->T_TRAIN);
            status = status && (M_ACK == q->M_ACK);
            status = status && (NID_LRBG == q->NID_LRBG);
            status = status && (*packet_15 == *(q->packet_15));
            status = status && (*packet_80 == *(q->packet_80));

            return status;
        }
	return false;
    }

    bool decode(Bitstream& stream);

    bool encode(Bitstream& stream) const;
};

typedef std::shared_ptr<Request_to_Shorten_MA_Message> Request_to_Shorten_MA_MessagePtr;

#endif // REQUEST_TO_SHORTEN_MA_Message_H_INCLUDED

