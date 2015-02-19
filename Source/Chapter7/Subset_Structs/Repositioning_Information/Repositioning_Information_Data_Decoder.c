
#include "Repositioning_Information_Data_Decoder.h"
#include "Bitwalker_Peek_Normal.h"

int Repositioning_Information_Data_Decoder(Bitstream* stream, Repositioning_Information_Data* p)
{
    if (NormalBitstream(stream, REPOSITIONING_INFORMATION_DATA_BITSIZE))
    {
        uint8_t* addr = stream->addr;
        const uint32_t size = stream->size;
        const uint32_t pos = stream->bitpos;

        p->Q_DIR              = Bitwalker_Peek_Normal(addr, size, pos,       2);
        p->Q_SCALE            = Bitwalker_Peek_Normal(addr, size, pos + 15,  2);
        p->L_SECTION          = Bitwalker_Peek_Normal(addr, size, pos + 17,  15);

        stream->bitpos += REPOSITIONING_INFORMATION_DATA_BITSIZE;

        //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
        //@ assert Q_SCALE:           EqualBits(stream, pos + 15,  pos + 17,  p->Q_SCALE);
        //@ assert L_SECTION:         EqualBits(stream, pos + 17,  pos + 32,  p->L_SECTION);

        //@ assert Q_DIR:             UpperBitsNotSet(p->Q_DIR,             2);
        //@ assert Q_SCALE:           UpperBitsNotSet(p->Q_SCALE,           2);
        //@ assert L_SECTION:         UpperBitsNotSet(p->L_SECTION,         15);

        return 1;
    }
    else
    {
        return 0;
    }
}

