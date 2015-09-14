
#ifndef DATA_USED_BY_APPLICATIONS_OUTSIDE_THE_ERTMS_OR_ETCS_SYSTEM_H_INCLUDED
#define DATA_USED_BY_APPLICATIONS_OUTSIDE_THE_ERTMS_OR_ETCS_SYSTEM_H_INCLUDED

#include "Bitstream.h"
#include "Data_used_by_applications_outside_the_ERTMS_or_ETCS_system_Core.h"
#include "BasePacket.h"

struct Data_used_by_applications_outside_the_ERTMS_or_ETCS_system : public BasePacket
{
    Data_used_by_applications_outside_the_ERTMS_or_ETCS_system_Core core;

    Data_used_by_applications_outside_the_ERTMS_or_ETCS_system() : BasePacket(44) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const Data_used_by_applications_outside_the_ERTMS_or_ETCS_system*>(&p))
        {
            return header == q->header && core == q->core;
        }

        return false;
    }

    uint16_t length() const override
    {
        return  core.L_PACKET;
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
        data.nid_packet = 44;
	
	data.valid = core.VALID;
	data.startAddress = startAddress;

	return ::encode(data, stream, startAddress, core);
    }

    int decode(const Packet_Info& data, const kcg_int* stream) override
    {
        if(data.nid_packet != 44)
	{
	    return 0;
	}

	return ::decode(data, stream, core);
    }

};

typedef std::shared_ptr<Data_used_by_applications_outside_the_ERTMS_or_ETCS_system> Data_used_by_applications_outside_the_ERTMS_or_ETCS_systemPtr;

#endif // DATA_USED_BY_APPLICATIONS_OUTSIDE_THE_ERTMS_OR_ETCS_SYSTEM_H_INCLUDED

