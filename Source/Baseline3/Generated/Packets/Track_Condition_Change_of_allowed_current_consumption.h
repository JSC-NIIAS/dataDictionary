
#ifndef TRACK_CONDITION_CHANGE_OF_ALLOWED_CURRENT_CONSUMPTION_H_INCLUDED
#define TRACK_CONDITION_CHANGE_OF_ALLOWED_CURRENT_CONSUMPTION_H_INCLUDED

#include "Bitstream.h"
#include "Track_Condition_Change_of_allowed_current_consumption_Core.h"
#include "BasePacket.h"

struct Track_Condition_Change_of_allowed_current_consumption : public BasePacket
{
    Track_Condition_Change_of_allowed_current_consumption_Core core;

    Track_Condition_Change_of_allowed_current_consumption() : BasePacket(40) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const Track_Condition_Change_of_allowed_current_consumption*>(&p))
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

    int encode(PacketInfo& data, kcg_int* stream) const override
    {
        data.nid_packet = 40;
        data.q_dir = core.Q_DIR;
        data.valid = 1;

        PacketInfo q = data;

        stream[q.startAddress++] = header.NID_PACKET;

        int ret = ::encode(q, stream, core);

        data.endAddress = q.startAddress - 1;

        return ret;
    }

    int decode(const PacketInfo& data, const kcg_int* stream) override
    {
        if (data.nid_packet != 40)
        {
            return 0;
        }

        PacketInfo q = data;

        header.NID_PACKET = stream[q.startAddress++];

        int ret = ::decode(q, stream, core);

        if (q.startAddress - 1 != data.endAddress)
        {
            return 0;
        }

        return ret;
    }

};

typedef std::shared_ptr<Track_Condition_Change_of_allowed_current_consumption> Track_Condition_Change_of_allowed_current_consumptionPtr;

#endif // TRACK_CONDITION_CHANGE_OF_ALLOWED_CURRENT_CONSUMPTION_H_INCLUDED

