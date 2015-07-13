
#include "Track_Condition_Station_Platforms_Core_1.h"
#include "UpperBitsNotSet.h"
#include "Bitstream_Write.h"
#include "Bitstream_Read.h"

int Track_Condition_Station_Platforms_Core_1_UpperBitsNotSet(const Track_Condition_Station_Platforms_Core_1* p)
{
    bool status = true;

    status = status && UpperBitsNotSet64(p->D_TRACKCOND_k,     15);
    status = status && UpperBitsNotSet64(p->L_TRACKCOND_k,     15);
    status = status && UpperBitsNotSet64(p->M_PLATFORM_k,      4) ;
    status = status && UpperBitsNotSet64(p->Q_PLATFORM_k,      2) ;

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Track_Condition_Station_Platforms_Core_1_Encoder(Bitstream* stream, const Track_Condition_Station_Platforms_Core_1* p)
{
    if (NormalBitstream(stream, TRACK_CONDITION_STATION_PLATFORMS_CORE_1_CORE_BITSIZE))
    {
        if (Track_Condition_Station_Platforms_Core_1_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 15, p->D_TRACKCOND_k);
            Bitstream_Write(stream, 15, p->L_TRACKCOND_k);
            Bitstream_Write(stream, 4,  p->M_PLATFORM_k);
            Bitstream_Write(stream, 2,  p->Q_PLATFORM_k);


            //@ assert D_TRACKCOND_k:     EqualBits(stream, pos,       pos + 15,  p->D_TRACKCOND_k);
            //@ assert L_TRACKCOND_k:     EqualBits(stream, pos + 15,  pos + 30,  p->L_TRACKCOND_k);
            //@ assert M_PLATFORM_k:      EqualBits(stream, pos + 30,  pos + 34,  p->M_PLATFORM_k);
            //@ assert Q_PLATFORM_k:      EqualBits(stream, pos + 34,  pos + 36,  p->Q_PLATFORM_k);

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

int Track_Condition_Station_Platforms_Core_1_Decoder(Bitstream* stream, Track_Condition_Station_Platforms_Core_1* p)
{
    if (NormalBitstream(stream, TRACK_CONDITION_STATION_PLATFORMS_CORE_1_CORE_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

	/*@
	  requires D_TRACKCOND_k:  stream->bitpos == pos + 0;
	  assigns        	   stream->bitpos;
	  assigns		   p->D_TRACKCOND_k;
	  ensures  D_TRACKCOND_k:  stream->bitpos == pos + 15;
	  ensures  D_TRACKCOND_k:  EqualBits(stream, pos + 0, pos + 15, p->D_TRACKCOND_k);
	  ensures  D_TRACKCOND_k:  UpperBitsNotSet(p->D_TRACKCOND_k, 15);
	*/
	{ p->D_TRACKCOND_k		= Bitstream_Read(stream, 15); }

	/*@
	  requires L_TRACKCOND_k:  stream->bitpos == pos + 15;
	  assigns        	   stream->bitpos;
	  assigns		   p->L_TRACKCOND_k;
	  ensures  L_TRACKCOND_k:  stream->bitpos == pos + 30;
	  ensures  L_TRACKCOND_k:  EqualBits(stream, pos + 15, pos + 30, p->L_TRACKCOND_k);
	  ensures  L_TRACKCOND_k:  UpperBitsNotSet(p->L_TRACKCOND_k, 15);
	*/
	{ p->L_TRACKCOND_k		= Bitstream_Read(stream, 15); }

	/*@
	  requires M_PLATFORM_k:   stream->bitpos == pos + 30;
	  assigns        	   stream->bitpos;
	  assigns		   p->M_PLATFORM_k;
	  ensures  M_PLATFORM_k:   stream->bitpos == pos + 34;
	  ensures  M_PLATFORM_k:   EqualBits(stream, pos + 30, pos + 34, p->M_PLATFORM_k);
	  ensures  M_PLATFORM_k:   UpperBitsNotSet(p->M_PLATFORM_k, 4);
	*/
	{ p->M_PLATFORM_k		= Bitstream_Read(stream, 4); }

	/*@
	  requires Q_PLATFORM_k:   stream->bitpos == pos + 34;
	  assigns        	   stream->bitpos;
	  assigns		   p->Q_PLATFORM_k;
	  ensures  Q_PLATFORM_k:   stream->bitpos == pos + 36;
	  ensures  Q_PLATFORM_k:   EqualBits(stream, pos + 34, pos + 36, p->Q_PLATFORM_k);
	  ensures  Q_PLATFORM_k:   UpperBitsNotSet(p->Q_PLATFORM_k, 2);
	*/
	{ p->Q_PLATFORM_k		= Bitstream_Read(stream, 2); }

        //@ assert D_TRACKCOND_k:     EqualBits(stream, pos,       pos + 15,  p->D_TRACKCOND_k);
        //@ assert L_TRACKCOND_k:     EqualBits(stream, pos + 15,  pos + 30,  p->L_TRACKCOND_k);
        //@ assert M_PLATFORM_k:      EqualBits(stream, pos + 30,  pos + 34,  p->M_PLATFORM_k);
        //@ assert Q_PLATFORM_k:      EqualBits(stream, pos + 34,  pos + 36,  p->Q_PLATFORM_k);

        //@ assert D_TRACKCOND_k:     UpperBitsNotSet(p->D_TRACKCOND_k,     15);
        //@ assert L_TRACKCOND_k:     UpperBitsNotSet(p->L_TRACKCOND_k,     15);
        //@ assert M_PLATFORM_k:      UpperBitsNotSet(p->M_PLATFORM_k,      4);
        //@ assert Q_PLATFORM_k:      UpperBitsNotSet(p->Q_PLATFORM_k,      2);

	//@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

