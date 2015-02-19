
#include "Reversing_supervision_information_Data_Encoder.h"
#include "Reversing_supervision_information_Data_UpperBitsNotSet.h"
#include "Bitwalker_Poke_Normal.h"

int Reversing_supervision_information_Data_Encoder(Bitstream* stream, const Reversing_supervision_information_Data* p)
{
    if (NormalBitstream(stream, REVERSING_SUPERVISION_INFORMATION_DATA_BITSIZE))
    {
        if (Reversing_supervision_information_Data_UpperBitsNotSet(p))
        {
            uint8_t* addr = stream->addr;
            const uint32_t size = stream->size;
            const uint32_t pos = stream->bitpos;

            Bitwalker_Poke_Normal(addr, size, pos,       2,  p->Q_DIR);
            Bitwalker_Poke_Normal(addr, size, pos + 15,  2,  p->Q_SCALE);
            Bitwalker_Poke_Normal(addr, size, pos + 17,  15, p->D_REVERSE);
            Bitwalker_Poke_Normal(addr, size, pos + 32,  7,  p->V_REVERSE);

            stream->bitpos += REVERSING_SUPERVISION_INFORMATION_DATA_BITSIZE;

            //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
            //@ assert Q_SCALE:           EqualBits(stream, pos + 15,  pos + 17,  p->Q_SCALE);
            //@ assert D_REVERSE:         EqualBits(stream, pos + 17,  pos + 32,  p->D_REVERSE);
            //@ assert V_REVERSE:         EqualBits(stream, pos + 32,  pos + 39,  p->V_REVERSE);

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

