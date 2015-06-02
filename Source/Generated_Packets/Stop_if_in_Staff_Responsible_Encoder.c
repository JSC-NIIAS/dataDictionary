
#include "Stop_if_in_Staff_Responsible_Encoder.h"
#include "Stop_if_in_Staff_Responsible_UpperBitsNotSet.h"
#include "Bitstream_Write.h"

int Stop_if_in_Staff_Responsible_Encoder(Bitstream* stream, const Stop_if_in_Staff_Responsible_Core* p)
{
    if (NormalBitstream(stream, STOP_IF_IN_STAFF_RESPONSIBLE_CORE_BITSIZE))
    {
        if (Stop_if_in_Staff_Responsible_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 2,  p->Q_DIR);
            Bitstream_Write(stream, 13, p->L_PACKET);
            Bitstream_Write(stream, 1,  p->Q_SRSTOP);


            //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
            //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);
            //@ assert Q_SRSTOP:          EqualBits(stream, pos + 15,  pos + 16,  p->Q_SRSTOP);

            return 1;
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -1;
    }
}

