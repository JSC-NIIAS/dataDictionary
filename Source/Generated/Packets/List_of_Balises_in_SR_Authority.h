
#ifndef LIST_OF_BALISES_IN_SR_AUTHORITY_H_INCLUDED
#define LIST_OF_BALISES_IN_SR_AUTHORITY_H_INCLUDED

#include "Bitstream.h"
#include "List_of_Balises_in_SR_Authority_Core.h"
#include "BasePacket.h"

struct List_of_Balises_in_SR_Authority : public BasePacket
{
    List_of_Balises_in_SR_Authority_Core core;

    List_of_Balises_in_SR_Authority() : BasePacket(63) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const List_of_Balises_in_SR_Authority*>(&p))
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
        data.nid_packet = 63;
	data.q_dir = core.Q_DIR;
	data.valid = core.VALID;
	data.startAddress = startAddress;

	return ::encode(data, stream, startAddress, core);
    }

    int decode(const Packet_Info& data, const kcg_int* stream) override
    {
        if(data.nid_packet != 63)
	{
	    return 0;
	}

	return ::decode(data, stream, core);
    }

};

typedef std::shared_ptr<List_of_Balises_in_SR_Authority> List_of_Balises_in_SR_AuthorityPtr;

#endif // LIST_OF_BALISES_IN_SR_AUTHORITY_H_INCLUDED

