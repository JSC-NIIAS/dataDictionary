
#include "Adhesion_Factor_Decoder.h"
#include "Bitwalker_Peek_Normal.h"

int Adhesion_Factor_Decoder(Bitstream* stream, Adhesion_Factor* p)
{
    if (NormalBitstream(stream, ADHESION_FACTOR_BITSIZE))
    {
        uint8_t* addr = stream->addr;
        const uint32_t size = stream->size;
        const uint32_t pos = stream->bitpos;

        p->Header.NID_PACKET         = Bitwalker_Peek_Normal(addr, size, pos,       8);
        p->Header.Q_DIR              = Bitwalker_Peek_Normal(addr, size, pos + 8,   2);
        p->Header.L_PACKET           = Bitwalker_Peek_Normal(addr, size, pos + 10,  13);
        p->Data.Q_SCALE            = Bitwalker_Peek_Normal(addr, size, pos + 23,  2);
        p->Data.D_ADHESION         = Bitwalker_Peek_Normal(addr, size, pos + 25,  15);
        p->Data.L_ADHESION         = Bitwalker_Peek_Normal(addr, size, pos + 40,  15);
        p->Data.M_ADHESION         = Bitwalker_Peek_Normal(addr, size, pos + 55,  1);

        stream->bitpos += ADHESION_FACTOR_BITSIZE;

        //@ assert NID_PACKET:        EqualBits(stream, pos,       pos + 8,   p->Header.NID_PACKET);
        //@ assert Q_DIR:             EqualBits(stream, pos + 8,   pos + 10,  p->Header.Q_DIR);
        //@ assert L_PACKET:          EqualBits(stream, pos + 10,  pos + 23,  p->Header.L_PACKET);
        //@ assert Q_SCALE:           EqualBits(stream, pos + 23,  pos + 25,  p->Data.Q_SCALE);
        //@ assert D_ADHESION:        EqualBits(stream, pos + 25,  pos + 40,  p->Data.D_ADHESION);
        //@ assert L_ADHESION:        EqualBits(stream, pos + 40,  pos + 55,  p->Data.L_ADHESION);
        //@ assert M_ADHESION:        EqualBits(stream, pos + 55,  pos + 56,  p->Data.M_ADHESION);

        return 1;
    }
    else
    {
        return 0;
    }
}

