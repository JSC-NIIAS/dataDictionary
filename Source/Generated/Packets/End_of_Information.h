
#ifndef END_OF_INFORMATION_H_INCLUDED
#define END_OF_INFORMATION_H_INCLUDED

#include "Bitstream.h"
#include "End_of_Information_Core.h"
#include "BasePacket.h"

struct End_of_Information : public BasePacket
{
    End_of_Information_Core core;

    End_of_Information() : BasePacket(255) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const End_of_Information*>(&p))
        {
            return header == q->header && core == q->core;
        }

        return false;
    }

    uint16_t length() const override
    {
        return  8;
    }

    int encode(Bitstream& stream) const override
    {
        return ::encode(stream, core);
    }

    int decode(Bitstream& stream) override
    {
        return ::decode(stream, core);
    }

    int encode(Packet_Info& data, kcg_int* stream, kcg_int startAddress) const override
    {
        data.nid_packet = 255;
	
	data.valid = core.VALID;
	data.startAddress = startAddress;

	return ::encode(data, stream, startAddress, core);
    }

    int decode(const Packet_Info& data, const kcg_int* stream) override
    {
        if(data.nid_packet != 255)
	{
	    return 0;
	}

	return ::decode(data, stream, core);
    }

};

typedef std::shared_ptr<End_of_Information> End_of_InformationPtr;

#endif // END_OF_INFORMATION_H_INCLUDED

