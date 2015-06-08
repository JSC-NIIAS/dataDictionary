
#include "Inhibition_of_balise_group_message_consistency_reaction_Decoder.h"
#include "Bitwalker_Peek_Normal.h"

int Inhibition_of_balise_group_message_consistency_reaction_Decoder(Bitstream* stream, Inhibition_of_balise_group_message_consistency_reaction* p)
{
    if (NormalBitstream(stream, INHIBITION_OF_BALISE_GROUP_MESSAGE_CONSISTENCY_REACTION_BITSIZE))
    {
        uint8_t* addr = stream->addr;
        const uint32_t size = stream->size;
        const uint32_t pos = stream->bitpos;

        p->Q_DIR              = Bitwalker_Peek_Normal(addr, size, pos,       2);
        p->L_PACKET           = Bitwalker_Peek_Normal(addr, size, pos + 2,   13);

        stream->bitpos += INHIBITION_OF_BALISE_GROUP_MESSAGE_CONSISTENCY_REACTION_BITSIZE;

        //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
        //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);

        //@ assert Q_DIR:             UpperBitsNotSet(p->Q_DIR,             2);
        //@ assert L_PACKET:          UpperBitsNotSet(p->L_PACKET,          13);

        return 1;
    }
    else
    {
        return 0;
    }
}

