
#include "Position_Report_based_on_two_balise_groups_Decoder.h"
#include "Bitstream_Read.h"

int Position_Report_based_on_two_balise_groups_Decoder(Bitstream* stream, Position_Report_based_on_two_balise_groups_Core* p)
{
    if (NormalBitstream(stream, POSITION_REPORT_BASED_ON_TWO_BALISE_GROUPS_CORE_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

	/*@
	  requires L_PACKET:       stream->bitpos == pos + 0;
	  assigns        	   stream->bitpos;
	  assigns		   p->L_PACKET;
	  ensures  L_PACKET:       stream->bitpos == pos + 13;
	  ensures  L_PACKET:       EqualBits(stream, pos + 0, pos + 13, p->L_PACKET);
	  ensures  L_PACKET:       UpperBitsNotSet(p->L_PACKET, 13);
	*/
	{ p->L_PACKET		= Bitstream_Read(stream, 13); }

	/*@
	  requires Q_SCALE:        stream->bitpos == pos + 13;
	  assigns        	   stream->bitpos;
	  assigns		   p->Q_SCALE;
	  ensures  Q_SCALE:        stream->bitpos == pos + 15;
	  ensures  Q_SCALE:        EqualBits(stream, pos + 13, pos + 15, p->Q_SCALE);
	  ensures  Q_SCALE:        UpperBitsNotSet(p->Q_SCALE, 2);
	*/
	{ p->Q_SCALE		= Bitstream_Read(stream, 2); }

	/*@
	  requires NID_LRBG:       stream->bitpos == pos + 15;
	  assigns        	   stream->bitpos;
	  assigns		   p->NID_LRBG;
	  ensures  NID_LRBG:       stream->bitpos == pos + 39;
	  ensures  NID_LRBG:       EqualBits(stream, pos + 15, pos + 39, p->NID_LRBG);
	  ensures  NID_LRBG:       UpperBitsNotSet(p->NID_LRBG, 24);
	*/
	{ p->NID_LRBG		= Bitstream_Read(stream, 24); }

	/*@
	  requires NID_PRVLRBG:    stream->bitpos == pos + 39;
	  assigns        	   stream->bitpos;
	  assigns		   p->NID_PRVLRBG;
	  ensures  NID_PRVLRBG:    stream->bitpos == pos + 63;
	  ensures  NID_PRVLRBG:    EqualBits(stream, pos + 39, pos + 63, p->NID_PRVLRBG);
	  ensures  NID_PRVLRBG:    UpperBitsNotSet(p->NID_PRVLRBG, 24);
	*/
	{ p->NID_PRVLRBG		= Bitstream_Read(stream, 24); }

	/*@
	  requires D_LRBG:         stream->bitpos == pos + 63;
	  assigns        	   stream->bitpos;
	  assigns		   p->D_LRBG;
	  ensures  D_LRBG:         stream->bitpos == pos + 78;
	  ensures  D_LRBG:         EqualBits(stream, pos + 63, pos + 78, p->D_LRBG);
	  ensures  D_LRBG:         UpperBitsNotSet(p->D_LRBG, 15);
	*/
	{ p->D_LRBG		= Bitstream_Read(stream, 15); }

	/*@
	  requires Q_DIRLRBG:      stream->bitpos == pos + 78;
	  assigns        	   stream->bitpos;
	  assigns		   p->Q_DIRLRBG;
	  ensures  Q_DIRLRBG:      stream->bitpos == pos + 80;
	  ensures  Q_DIRLRBG:      EqualBits(stream, pos + 78, pos + 80, p->Q_DIRLRBG);
	  ensures  Q_DIRLRBG:      UpperBitsNotSet(p->Q_DIRLRBG, 2);
	*/
	{ p->Q_DIRLRBG		= Bitstream_Read(stream, 2); }

	/*@
	  requires Q_DLRBG:        stream->bitpos == pos + 80;
	  assigns        	   stream->bitpos;
	  assigns		   p->Q_DLRBG;
	  ensures  Q_DLRBG:        stream->bitpos == pos + 82;
	  ensures  Q_DLRBG:        EqualBits(stream, pos + 80, pos + 82, p->Q_DLRBG);
	  ensures  Q_DLRBG:        UpperBitsNotSet(p->Q_DLRBG, 2);
	*/
	{ p->Q_DLRBG		= Bitstream_Read(stream, 2); }

	/*@
	  requires L_DOUBTOVER:    stream->bitpos == pos + 82;
	  assigns        	   stream->bitpos;
	  assigns		   p->L_DOUBTOVER;
	  ensures  L_DOUBTOVER:    stream->bitpos == pos + 97;
	  ensures  L_DOUBTOVER:    EqualBits(stream, pos + 82, pos + 97, p->L_DOUBTOVER);
	  ensures  L_DOUBTOVER:    UpperBitsNotSet(p->L_DOUBTOVER, 15);
	*/
	{ p->L_DOUBTOVER		= Bitstream_Read(stream, 15); }

	/*@
	  requires L_DOUBTUNDER:   stream->bitpos == pos + 97;
	  assigns        	   stream->bitpos;
	  assigns		   p->L_DOUBTUNDER;
	  ensures  L_DOUBTUNDER:   stream->bitpos == pos + 112;
	  ensures  L_DOUBTUNDER:   EqualBits(stream, pos + 97, pos + 112, p->L_DOUBTUNDER);
	  ensures  L_DOUBTUNDER:   UpperBitsNotSet(p->L_DOUBTUNDER, 15);
	*/
	{ p->L_DOUBTUNDER		= Bitstream_Read(stream, 15); }

	/*@
	  requires Q_LENGTH:       stream->bitpos == pos + 112;
	  assigns        	   stream->bitpos;
	  assigns		   p->Q_LENGTH;
	  ensures  Q_LENGTH:       stream->bitpos == pos + 114;
	  ensures  Q_LENGTH:       EqualBits(stream, pos + 112, pos + 114, p->Q_LENGTH);
	  ensures  Q_LENGTH:       UpperBitsNotSet(p->Q_LENGTH, 2);
	*/
	{ p->Q_LENGTH		= Bitstream_Read(stream, 2); }

        if ((p->Q_LENGTH == 1) || (p->Q_LENGTH == 2))
        {
	{ p->L_TRAININT		= Bitstream_Read(stream, 15); }
        }

	/*@
	  requires V_TRAIN:        stream->bitpos == pos + 129;
	  assigns        	   stream->bitpos;
	  assigns		   p->V_TRAIN;
	  ensures  V_TRAIN:        stream->bitpos == pos + 136;
	  ensures  V_TRAIN:        EqualBits(stream, pos + 129, pos + 136, p->V_TRAIN);
	  ensures  V_TRAIN:        UpperBitsNotSet(p->V_TRAIN, 7);
	*/
	{ p->V_TRAIN		= Bitstream_Read(stream, 7); }

	/*@
	  requires Q_DIRTRAIN:     stream->bitpos == pos + 136;
	  assigns        	   stream->bitpos;
	  assigns		   p->Q_DIRTRAIN;
	  ensures  Q_DIRTRAIN:     stream->bitpos == pos + 138;
	  ensures  Q_DIRTRAIN:     EqualBits(stream, pos + 136, pos + 138, p->Q_DIRTRAIN);
	  ensures  Q_DIRTRAIN:     UpperBitsNotSet(p->Q_DIRTRAIN, 2);
	*/
	{ p->Q_DIRTRAIN		= Bitstream_Read(stream, 2); }

	/*@
	  requires M_MODE:         stream->bitpos == pos + 138;
	  assigns        	   stream->bitpos;
	  assigns		   p->M_MODE;
	  ensures  M_MODE:         stream->bitpos == pos + 142;
	  ensures  M_MODE:         EqualBits(stream, pos + 138, pos + 142, p->M_MODE);
	  ensures  M_MODE:         UpperBitsNotSet(p->M_MODE, 4);
	*/
	{ p->M_MODE		= Bitstream_Read(stream, 4); }

	/*@
	  requires M_LEVEL:        stream->bitpos == pos + 142;
	  assigns        	   stream->bitpos;
	  assigns		   p->M_LEVEL;
	  ensures  M_LEVEL:        stream->bitpos == pos + 145;
	  ensures  M_LEVEL:        EqualBits(stream, pos + 142, pos + 145, p->M_LEVEL);
	  ensures  M_LEVEL:        UpperBitsNotSet(p->M_LEVEL, 3);
	*/
	{ p->M_LEVEL		= Bitstream_Read(stream, 3); }

        if (p->M_LEVEL == 1)
        {
	{ p->NID_NTC		= Bitstream_Read(stream, 8); }
        }

        //@ assert L_PACKET:          EqualBits(stream, pos,       pos + 13,  p->L_PACKET);
        //@ assert Q_SCALE:           EqualBits(stream, pos + 13,  pos + 15,  p->Q_SCALE);
        //@ assert NID_LRBG:          EqualBits(stream, pos + 15,  pos + 39,  p->NID_LRBG);
        //@ assert NID_PRVLRBG:       EqualBits(stream, pos + 39,  pos + 63,  p->NID_PRVLRBG);
        //@ assert D_LRBG:            EqualBits(stream, pos + 63,  pos + 78,  p->D_LRBG);
        //@ assert Q_DIRLRBG:         EqualBits(stream, pos + 78,  pos + 80,  p->Q_DIRLRBG);
        //@ assert Q_DLRBG:           EqualBits(stream, pos + 80,  pos + 82,  p->Q_DLRBG);
        //@ assert L_DOUBTOVER:       EqualBits(stream, pos + 82,  pos + 97,  p->L_DOUBTOVER);
        //@ assert L_DOUBTUNDER:      EqualBits(stream, pos + 97,  pos + 112, p->L_DOUBTUNDER);
        //@ assert Q_LENGTH:          EqualBits(stream, pos + 112, pos + 114, p->Q_LENGTH);
        //@ assert V_TRAIN:           EqualBits(stream, pos + 129, pos + 136, p->V_TRAIN);
        //@ assert Q_DIRTRAIN:        EqualBits(stream, pos + 136, pos + 138, p->Q_DIRTRAIN);
        //@ assert M_MODE:            EqualBits(stream, pos + 138, pos + 142, p->M_MODE);
        //@ assert M_LEVEL:           EqualBits(stream, pos + 142, pos + 145, p->M_LEVEL);

        //@ assert L_PACKET:          UpperBitsNotSet(p->L_PACKET,          13);
        //@ assert Q_SCALE:           UpperBitsNotSet(p->Q_SCALE,           2);
        //@ assert NID_LRBG:          UpperBitsNotSet(p->NID_LRBG,          24);
        //@ assert NID_PRVLRBG:       UpperBitsNotSet(p->NID_PRVLRBG,       24);
        //@ assert D_LRBG:            UpperBitsNotSet(p->D_LRBG,            15);
        //@ assert Q_DIRLRBG:         UpperBitsNotSet(p->Q_DIRLRBG,         2);
        //@ assert Q_DLRBG:           UpperBitsNotSet(p->Q_DLRBG,           2);
        //@ assert L_DOUBTOVER:       UpperBitsNotSet(p->L_DOUBTOVER,       15);
        //@ assert L_DOUBTUNDER:      UpperBitsNotSet(p->L_DOUBTUNDER,      15);
        //@ assert Q_LENGTH:          UpperBitsNotSet(p->Q_LENGTH,          2);
        //@ assert V_TRAIN:           UpperBitsNotSet(p->V_TRAIN,           7);
        //@ assert Q_DIRTRAIN:        UpperBitsNotSet(p->Q_DIRTRAIN,        2);
        //@ assert M_MODE:            UpperBitsNotSet(p->M_MODE,            4);
        //@ assert M_LEVEL:           UpperBitsNotSet(p->M_LEVEL,           3);

	//@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}
