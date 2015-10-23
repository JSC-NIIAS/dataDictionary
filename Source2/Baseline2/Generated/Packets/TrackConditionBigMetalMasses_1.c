
#include "TrackConditionBigMetalMasses_1.h"
#include "Bit64.h"

TrackConditionBigMetalMasses_1* TrackConditionBigMetalMasses_1_New(void)
{
    void* raw = malloc(sizeof(TrackConditionBigMetalMasses_1));
    TrackConditionBigMetalMasses_1* ptr = (TrackConditionBigMetalMasses_1*)raw;
    TrackConditionBigMetalMasses_1_Init(ptr);
    return ptr;
}


void TrackConditionBigMetalMasses_1_Delete(TrackConditionBigMetalMasses_1* ptr)
{
    free(ptr);
}


int TrackConditionBigMetalMasses_1_UpperBitsNotSet(const TrackConditionBigMetalMasses_1* p)
{
    int status = 1;

    status = status && UpperBitsNotSet64(p->D_TRACKCOND,       15);
    status = status && UpperBitsNotSet64(p->L_TRACKCOND,       15);

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int TrackConditionBigMetalMasses_1_EncodeBit(const TrackConditionBigMetalMasses_1* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, TRACKCONDITIONBIGMETALMASSES_1_BITSIZE))
    {
        if (TrackConditionBigMetalMasses_1_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 15, p->D_TRACKCOND);
            Bitstream_Write(stream, 15, p->L_TRACKCOND);


            //@ assert D_TRACKCOND:       EqualBits(stream, pos,       pos + 15,  p->D_TRACKCOND);
            //@ assert L_TRACKCOND:       EqualBits(stream, pos + 15,  pos + 30,  p->L_TRACKCOND);

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

int TrackConditionBigMetalMasses_1_DecodeBit(TrackConditionBigMetalMasses_1* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, TRACKCONDITIONBIGMETALMASSES_1_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

        /*@
          requires D_TRACKCOND:    stream->bitpos == pos + 0;
          assigns                  stream->bitpos;
          assigns                  p->D_TRACKCOND;
          ensures  D_TRACKCOND:    stream->bitpos == pos + 15;
          ensures  D_TRACKCOND:    EqualBits(stream, pos + 0, pos + 15, p->D_TRACKCOND);
          ensures  D_TRACKCOND:    UpperBitsNotSet(p->D_TRACKCOND, 15);
        */
        {
            p->D_TRACKCOND        = Bitstream_Read(stream, 15);
        }

        /*@
          requires L_TRACKCOND:    stream->bitpos == pos + 15;
          assigns                  stream->bitpos;
          assigns                  p->L_TRACKCOND;
          ensures  L_TRACKCOND:    stream->bitpos == pos + 30;
          ensures  L_TRACKCOND:    EqualBits(stream, pos + 15, pos + 30, p->L_TRACKCOND);
          ensures  L_TRACKCOND:    UpperBitsNotSet(p->L_TRACKCOND, 15);
        */
        {
            p->L_TRACKCOND        = Bitstream_Read(stream, 15);
        }

        //@ assert D_TRACKCOND:       EqualBits(stream, pos,       pos + 15,  p->D_TRACKCOND);
        //@ assert L_TRACKCOND:       EqualBits(stream, pos + 15,  pos + 30,  p->L_TRACKCOND);

        //@ assert D_TRACKCOND:       UpperBitsNotSet(p->D_TRACKCOND,       15);
        //@ assert L_TRACKCOND:       UpperBitsNotSet(p->L_TRACKCOND,       15);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

int TrackConditionBigMetalMasses_1_EncodeInt(const TrackConditionBigMetalMasses_1* p, PacketInfo* data, kcg_int* stream)
{
    return 0;
}

int TrackConditionBigMetalMasses_1_DecodeInt(TrackConditionBigMetalMasses_1* p, PacketInfo* data, kcg_int* stream)
{
    return 0;
}

