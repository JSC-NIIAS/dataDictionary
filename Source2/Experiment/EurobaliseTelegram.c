
#include "EurobaliseTelegram.h"
#include "PacketFactory.h"
#include "Packet_DecodeBit.h"
#include "Packet_EncodeBit.h"
#include "Packet_Length.h"

void EurobaliseTelegram_Print(const EurobaliseTelegram* t, FILE* stream)
{
    TelegramHeader_Print(&t->header, stream);
    PacketSequence_Print(&t->packets, stream);
}

void EurobaliseTelegram_Clear(EurobaliseTelegram* t)
{
    TelegramHeader_Init(&t->header);
    PacketSequence_Clear(&t->packets);
}

int EurobaliseTelegram_Equal(const EurobaliseTelegram* a, const EurobaliseTelegram* b)
{
    return TelegramHeader_Equal(&a->header,  &b->header) &&
           PacketSequence_Equal(&a->packets, &b->packets);
}


int EurobaliseTelegram_DecodeBit(EurobaliseTelegram* t, Bitstream* stream)
{
    //printf("EurobaliseTelegram_DecodeBit::enter\n");

    if (TelegramHeader_DecodeBit(stream, &t->header) != 1)
    {
        return 0;
    }

    //printf("EurobaliseTelegram_DecodeBit::t->header.Q_UPDOWN = %"PRIu64"\n", t->header.Q_UPDOWN);

    //std::cout << stream->bitpos << std::endl;

    const uint32_t old_pos = stream->bitpos;
    uint32_t current_pos = stream->bitpos;

    while (stream->bitpos <= 1023 + old_pos)
    {
        if (current_pos != stream->bitpos)
        {
            //printf("problem here %lu is not %lu\n", current_pos, stream->bitpos);
            //std::cerr << stream->bitpos << " != " << current_pos << std::endl;
            return 0;
        }

        PacketHeader packet_header = {0, 0};
        PacketHeader_DecodeBit(&packet_header, stream);
        //printf("EurobaliseTelegram_DecodeBit::packet_header = %d\n", packet_header.NID_PACKET);

        PacketHeader* ptr = 0;

        if (packet_header.NID_PACKET == 255)
        {
            ptr = PacketFactory_BothWays(packet_header);
            assert(ptr);

            // beware: no need to decode further fields
            EurobaliseTelegram_Add(t, ptr);
            //printf("EurobaliseTelegram_DecodeBit size after add = %d\n", EurobaliseTelegram_Size(t));
            break;
        }

        if (t->header.Q_UPDOWN == 1)
        {

            ptr = PacketFactory_TrackToTrain(packet_header);

            if (ptr)
            {
                EurobaliseTelegram_Add(t, ptr);
                //printf("EurobaliseTelegram_DecodeBit size after add = %d\n", EurobaliseTelegram_Size(t));
            }
            else
            {
                return 0;
            }
        }
        else
        {
            assert(t->header.Q_UPDOWN == 0);
            ptr = PacketFactory_TrainToTrack(packet_header);

            if (ptr)
            {
                EurobaliseTelegram_Add(t, ptr);
                //printf("EurobaliseTelegram_DecodeBit size after add = %d\n", EurobaliseTelegram_Size(t));
            }
            else
            {
                return 0;
            }
        }

        if (ptr)
        {
            Packet_DecodeBit(ptr, stream);
            current_pos += Packet_Length(ptr);
        }
    }

    return 1;
}

int EurobaliseTelegram_EncodeBit(const EurobaliseTelegram* t, Bitstream* stream)
{
    if (TelegramHeader_EncodeBit(&t->header, stream) != 1)
    {
        return 0;
    }

    uint32_t old_pos = stream->bitpos;

    // check that last packet denotes end of message
    assert(PacketSequence_Back(&t->packets)->NID_PACKET == 255);

    for (uint32_t i = 0; i < EurobaliseTelegram_Size(t); ++i)
    {
        if (stream->bitpos > 1023 + old_pos)
        {
            return 0;
        }

        if (PacketHeader_EncodeBit(EurobaliseTelegram_Get(t, i), stream) != 1)
        {
            return 0;
        }

        if (Packet_EncodeBit(EurobaliseTelegram_Get(t, i), stream) != 1)
        {
            return 0;
        }

    }

    return 1;
}

/*
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

*/

