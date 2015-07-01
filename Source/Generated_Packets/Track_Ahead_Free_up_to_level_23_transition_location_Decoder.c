
#include "Track_Ahead_Free_up_to_level_23_transition_location_Decoder.h"
#include "Bitstream_Read.h"

int Track_Ahead_Free_up_to_level_23_transition_location_Decoder(Bitstream* stream, Track_Ahead_Free_up_to_level_23_transition_location_Core* p)
{
    if (NormalBitstream(stream, TRACK_AHEAD_FREE_UP_TO_LEVEL_23_TRANSITION_LOCATION_CORE_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

	{ p->Q_DIR		= Bitstream_Read(stream, 2); }

	{ p->L_PACKET		= Bitstream_Read(stream, 13); }

	{ p->Q_NEWCOUNTRY		= Bitstream_Read(stream, 1); }

        if (p->Q_NEWCOUNTRY == 1)
        {
	{ p->NID_C		= Bitstream_Read(stream, 10); }
        }

	{ p->NID_BG		= Bitstream_Read(stream, 14); }



	//@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

