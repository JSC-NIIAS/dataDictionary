
#ifndef TRACK_CONDITION_STATION_PLATFORMS_H_INCLUDED
#define TRACK_CONDITION_STATION_PLATFORMS_H_INCLUDED

#include "Bitstream.h"
#include "Track_Condition_Station_Platforms_Core.h"
#include "BasePacket.h"

struct Track_Condition_Station_Platforms : public BasePacket
{
    Track_Condition_Station_Platforms_Core core;

    Track_Condition_Station_Platforms() : BasePacket(69) {}

    void print(std::ostream& stream) const override
    {
        stream << '(' << header << ',' << core << ')';
    }

    bool equals(const BasePacket& p) const override
    {
        if (auto q = dynamic_cast<const Track_Condition_Station_Platforms*>(&p))
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
        data.nid_packet = 69;
	data.q_dir = core.Q_DIR;
	data.valid = core.VALID;
	data.startAddress = startAddress;

	return ::encode(data, stream, startAddress, core);
    }

    int decode(const Packet_Info& data, const kcg_int* stream) override
    {
        if(data.nid_packet != 69)
	{
	    return 0;
	}

	return ::decode(data, stream, core);
    }

};

typedef std::shared_ptr<Track_Condition_Station_Platforms> Track_Condition_Station_PlatformsPtr;

#endif // TRACK_CONDITION_STATION_PLATFORMS_H_INCLUDED

