
#include "Temporary_Speed_Restriction_Revocation_Core.h"
#include "Bit64.h"

int Temporary_Speed_Restriction_Revocation_UpperBitsNotSet(const Temporary_Speed_Restriction_Revocation_Core* p)
{
    bool status = true;

    status = status && UpperBitsNotSet64(p->Q_DIR,             2) ;
    status = status && UpperBitsNotSet64(p->L_PACKET,          13);
    status = status && UpperBitsNotSet64(p->NID_TSR,           8) ;

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Temporary_Speed_Restriction_Revocation_Encode_Bit(Bitstream* stream, const Temporary_Speed_Restriction_Revocation_Core* p)
{
    if (Bitstream_Normal(stream, TEMPORARY_SPEED_RESTRICTION_REVOCATION_CORE_BITSIZE))
    {
        if (Temporary_Speed_Restriction_Revocation_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 2,  p->Q_DIR);
            Bitstream_Write(stream, 13, p->L_PACKET);
            Bitstream_Write(stream, 8,  p->NID_TSR);


            //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
            //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);
            //@ assert NID_TSR:           EqualBits(stream, pos + 15,  pos + 23,  p->NID_TSR);

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

int Temporary_Speed_Restriction_Revocation_Decode_Bit(Bitstream* stream, Temporary_Speed_Restriction_Revocation_Core* p)
{
    if (Bitstream_Normal(stream, TEMPORARY_SPEED_RESTRICTION_REVOCATION_CORE_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

        /*@
          requires Q_DIR:          stream->bitpos == pos + 0;
          assigns                  stream->bitpos;
          assigns                  p->Q_DIR;
          ensures  Q_DIR:          stream->bitpos == pos + 2;
          ensures  Q_DIR:          EqualBits(stream, pos + 0, pos + 2, p->Q_DIR);
          ensures  Q_DIR:          UpperBitsNotSet(p->Q_DIR, 2);
        */
        {
            p->Q_DIR        = Bitstream_Read(stream, 2);
        }

        /*@
          requires L_PACKET:       stream->bitpos == pos + 2;
          assigns                  stream->bitpos;
          assigns                  p->L_PACKET;
          ensures  L_PACKET:       stream->bitpos == pos + 15;
          ensures  L_PACKET:       EqualBits(stream, pos + 2, pos + 15, p->L_PACKET);
          ensures  L_PACKET:       UpperBitsNotSet(p->L_PACKET, 13);
        */
        {
            p->L_PACKET        = Bitstream_Read(stream, 13);
        }

        /*@
          requires NID_TSR:        stream->bitpos == pos + 15;
          assigns                  stream->bitpos;
          assigns                  p->NID_TSR;
          ensures  NID_TSR:        stream->bitpos == pos + 23;
          ensures  NID_TSR:        EqualBits(stream, pos + 15, pos + 23, p->NID_TSR);
          ensures  NID_TSR:        UpperBitsNotSet(p->NID_TSR, 8);
        */
        {
            p->NID_TSR        = Bitstream_Read(stream, 8);
        }

        //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
        //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);
        //@ assert NID_TSR:           EqualBits(stream, pos + 15,  pos + 23,  p->NID_TSR);

        //@ assert Q_DIR:             UpperBitsNotSet(p->Q_DIR,             2);
        //@ assert L_PACKET:          UpperBitsNotSet(p->L_PACKET,          13);
        //@ assert NID_TSR:           UpperBitsNotSet(p->NID_TSR,           8);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

int Temporary_Speed_Restriction_Revocation_Encode_Int(PacketInfo* data, kcg_int* stream, const Temporary_Speed_Restriction_Revocation_Core* p)
{
    stream[data->startAddress++] = p->Q_DIR;
    stream[data->startAddress++] = p->L_PACKET;
    stream[data->startAddress++] = p->NID_TSR;

    return 1;
}

int Temporary_Speed_Restriction_Revocation_Decode_Int(PacketInfo* data, const kcg_int* stream, Temporary_Speed_Restriction_Revocation_Core* p)
{
    p->Q_DIR = stream[data->startAddress++];
    p->L_PACKET = stream[data->startAddress++];
    p->NID_TSR = stream[data->startAddress++];

    return 1;
}

