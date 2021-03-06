
#include "EurobaliseTelegram.h"
#include "TelegramHeader.h"
#include "PacketFactory.h"
#include <iostream>
#include <cassert>

std::ostream& operator<< (std::ostream& stream, const EurobaliseTelegram& telegram)
{
    stream << '(' << telegram.header() << ",";

    for (size_t i = 0; i != telegram.numberPackets(); ++i)
    {
        stream << *telegram.packet(i);

        if (i + 1 != telegram.numberPackets())
        {
            stream << ',';
        }
        else
        {
            stream << ')';
        }

    }

    return stream;
}

bool operator==(const EurobaliseTelegram& a, const EurobaliseTelegram& b)
{
    if (a.header() == b.header())
    {
        if (a.numberPackets() == b.numberPackets())
        {
            bool result = true;

            for (size_t i = 0; i < a.numberPackets(); ++i)
            {
                result = result && (*(a.packet(i)) == *(b.packet(i)));
            }

            return result;
        }
    }

    return false;
}

bool operator!=(const EurobaliseTelegram& a, const EurobaliseTelegram& b)
{
    return !(a == b);
}

bool EurobaliseTelegram::decode(Bitstream& stream)
{
    if (TelegramHeader_Decoder(&stream, &m_header) != 1)
    {
        return false;
    }

    //std::cout << stream->bitpos << std::endl;

    const uint32_t old_pos = stream.bitpos;
    uint32_t current_pos = stream.bitpos;

    while (stream.bitpos <= 1023 + old_pos)
    {
        if (current_pos != stream.bitpos)
        {
            std::cerr << stream.bitpos << " != " << current_pos << std::endl;
            return false;
        }

        PacketHeader packet_header{0};
        ::decode(stream, packet_header);
	
	BasePacketPtr ptr;

        if (header().Q_UPDOWN == 1)
	{
            ptr = PacketFactory_TrackToTrain(packet_header.NID_PACKET);
	}
	else
	{
	    assert(header().Q_UPDOWN == 0);
            ptr = PacketFactory_TrainToTrack(packet_header.NID_PACKET);
        }

        if (ptr)
	{
            if (ptr->decode(stream) != 1)
	    {
	        return false;
	    }
	    
	    m_packets.push_back(ptr);

            if (ptr->header.NID_PACKET == 255)
            {
                break;
            }
	}
        else
        {
            return false;
        }

        current_pos += ptr->length();
    }

    return true;
}

bool EurobaliseTelegram::encode(Bitstream& stream) const
{
    if (::encode(stream, header()) != 1)
    {
        return false;
    }

    uint32_t old_pos = stream.bitpos;

    // check that last packet denotes end of message
    assert(m_packets.back()->header.NID_PACKET == 255);

    for (auto p = m_packets.begin(); p != m_packets.end(); ++p)
    {
        if (stream.bitpos > 1023 + old_pos)
        {
            return false;
        }

        if (::encode(stream, (*p)->header) != 1)
        {
            return false;
        }

        if ((*p)->encode(stream) != 1)
	{
	    return false;
	}

    }

    return true;
}

bool EurobaliseTelegram::encode(FlatPackets& packetStruct) const
{
    kcg_int startAddress = 0;
    unsigned int i;

    for (i = 0; i < m_packets.size(); ++i)
    {
        packetStruct.PacketHeaders[i].startAddress = startAddress;
        m_packets[i]->encode(packetStruct.PacketHeaders[i], packetStruct.PacketData);
        startAddress = packetStruct.PacketHeaders[i].endAddress + 1;
    }

    if (packetStruct.PacketHeaders[i - 1].nid_packet != 255)
    {
        return false;
    }

    return true;
}

bool EurobaliseTelegram::decode(FlatPackets& packetStruct)
{
    for (unsigned int i = 0; i < 50; ++i)
    {
        if (packetStruct.PacketHeaders[i].valid == 1)
        {
            BasePacketPtr ptr;

            if (m_header.Q_UPDOWN == 0)
            {
                ptr = PacketFactory_TrainToTrack(packetStruct.PacketHeaders[i].nid_packet);
	    }
	    else if (m_header.Q_UPDOWN == 1)
	    {
	        ptr = PacketFactory_TrackToTrain(packetStruct.PacketHeaders[i].nid_packet);
	    }
	    else
	    {
	        std::cout << "wrong q_updown" << std::endl;
	        return false;
	    }

            if (ptr)
            {
                ptr->decode(packetStruct.PacketHeaders[i], packetStruct.PacketData);
    
                m_packets.push_back(ptr);
            }
            else
            {
                return false;
            }
    
            if (ptr->header.NID_PACKET == 255)
            {
                break;
            }
        }
    }

    return true;
}

