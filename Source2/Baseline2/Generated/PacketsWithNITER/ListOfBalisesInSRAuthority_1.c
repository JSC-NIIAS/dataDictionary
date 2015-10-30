
#include "ListOfBalisesInSRAuthority_1.h"
#include "Bit64.h"

int ListOfBalisesInSRAuthority_1_UpperBitsNotSet(const ListOfBalisesInSRAuthority_1* p)
{
    int status = 1;

    status = status && UpperBitsNotSet64(p->Q_NEWCOUNTRY,      1) ;
    if (p->Q_NEWCOUNTRY == 1)
    {
        status = status && UpperBitsNotSet64(p->NID_C,             10);
    }
    status = status && UpperBitsNotSet64(p->NID_BG,            14);

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ListOfBalisesInSRAuthority_1_EncodeBit(const ListOfBalisesInSRAuthority_1* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, LISTOFBALISESINSRAUTHORITY_1_BITSIZE))
    {
        if (ListOfBalisesInSRAuthority_1_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 1,  p->Q_NEWCOUNTRY);
            if (p->Q_NEWCOUNTRY == 1)
            {
                Bitstream_Write(stream, 10, p->NID_C);
            }

            Bitstream_Write(stream, 14, p->NID_BG);


            //@ assert Q_NEWCOUNTRY:      EqualBits(stream, pos,       pos + 1,   p->Q_NEWCOUNTRY);

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

int ListOfBalisesInSRAuthority_1_DecodeBit(ListOfBalisesInSRAuthority_1* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, LISTOFBALISESINSRAUTHORITY_1_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

        /*@
          requires Q_NEWCOUNTRY:   stream->bitpos == pos + 0;
          assigns                  stream->bitpos;
          assigns                  p->Q_NEWCOUNTRY;
          ensures  Q_NEWCOUNTRY:   stream->bitpos == pos + 1;
          ensures  Q_NEWCOUNTRY:   EqualBits(stream, pos + 0, pos + 1, p->Q_NEWCOUNTRY);
          ensures  Q_NEWCOUNTRY:   UpperBitsNotSet(p->Q_NEWCOUNTRY, 1);
        */
        {
            p->Q_NEWCOUNTRY        = Bitstream_Read(stream, 1);
        }

        if (p->Q_NEWCOUNTRY == 1)
        {
            {
                p->NID_C        = Bitstream_Read(stream, 10);
            }

        }

        {
            p->NID_BG        = Bitstream_Read(stream, 14);
        }

        //@ assert Q_NEWCOUNTRY:      EqualBits(stream, pos,       pos + 1,   p->Q_NEWCOUNTRY);

        //@ assert Q_NEWCOUNTRY:      UpperBitsNotSet(p->Q_NEWCOUNTRY,      1);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

int ListOfBalisesInSRAuthority_1_EncodeInt(const ListOfBalisesInSRAuthority_1* p, kcg_int* startAddress, kcg_int* stream)
{
    stream[(*startAddress)++] = p->Q_NEWCOUNTRY;
    stream[(*startAddress)++] = p->NID_C;
    stream[(*startAddress)++] = p->NID_BG;

    return 1;
}

int ListOfBalisesInSRAuthority_1_DecodeInt(ListOfBalisesInSRAuthority_1* p, kcg_int* startAddress, const kcg_int* stream)
{
    p->Q_NEWCOUNTRY = stream[(*startAddress)++];
    p->NID_C = stream[(*startAddress)++];
    p->NID_BG = stream[(*startAddress)++];

    return 1;
}

