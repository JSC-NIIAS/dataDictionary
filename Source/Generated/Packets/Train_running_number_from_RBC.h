
#ifndef TRAIN_RUNNING_NUMBER_FROM_RBC_H_INCLUDED
#define TRAIN_RUNNING_NUMBER_FROM_RBC_H_INCLUDED

#include "Bitstream.h"
#include "Train_running_number_from_RBC_Core.h"
#include "BasePacket.h"

struct Train_running_number_from_RBC : public BasePacket
{
    Train_running_number_from_RBC_Core core;

    Train_running_number_from_RBC() : BasePacket(140) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const Train_running_number_from_RBC*>(&p))
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
        data.nid_packet = 140;
	data.q_dir = core.Q_DIR;
	data.valid = core.VALID;
	data.startAddress = startAddress;

	return ::encode(data, stream, startAddress, core);
    }

    int decode(const Packet_Info& data, const kcg_int* stream) override
    {
        if(data.nid_packet != 140)
	{
	    return 0;
	}

	return ::decode(data, stream, core);
    }

};

typedef std::shared_ptr<Train_running_number_from_RBC> Train_running_number_from_RBCPtr;

#endif // TRAIN_RUNNING_NUMBER_FROM_RBC_H_INCLUDED

