
#include "Packet_for_sending_fixed_text_messages_Encoder.h"
#include "Packet_for_sending_fixed_text_messages_UpperBitsNotSet.h"
#include "Bitstream_Write.h"

int Packet_for_sending_fixed_text_messages_Encoder(Bitstream* stream, const Packet_for_sending_fixed_text_messages_Core* p)
{
    if (NormalBitstream(stream, PACKET_FOR_SENDING_FIXED_TEXT_MESSAGES_CORE_BITSIZE))
    {
        if (Packet_for_sending_fixed_text_messages_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 2,  p->Q_DIR);
            Bitstream_Write(stream, 13, p->L_PACKET);
            Bitstream_Write(stream, 2,  p->Q_SCALE);
            Bitstream_Write(stream, 2,  p->Q_TEXTCLASS);
            Bitstream_Write(stream, 1,  p->Q_TEXTDISPLAY);
            Bitstream_Write(stream, 15, p->D_TEXTDISPLAY);
            Bitstream_Write(stream, 4,  p->M_MODETEXTDISPLAY0);
            Bitstream_Write(stream, 3,  p->M_LEVELTEXTDISPLAY0);
            if (p->M_LEVELTEXTDISPLAY0 == 1)
            {
            Bitstream_Write(stream, 8,  p->NID_NTC0);
            }

            Bitstream_Write(stream, 15, p->L_TEXTDISPLAY);
            Bitstream_Write(stream, 10, p->T_TEXTDISPLAY);
            Bitstream_Write(stream, 4,  p->M_MODETEXTDISPLAY1);
            Bitstream_Write(stream, 3,  p->M_LEVELTEXTDISPLAY1);
            if (p->M_LEVELTEXTDISPLAY1 == 1)
            {
            Bitstream_Write(stream, 8,  p->NID_NTC1);
            }

            Bitstream_Write(stream, 2,  p->Q_TEXTCONFIRM);
            if (p->Q_TEXTCONFIRM != 0)
            {
            Bitstream_Write(stream, 1,  p->Q_CONFTEXTDISPLAY);
            Bitstream_Write(stream, 1,  p->Q_TEXTREPORT);
            }

            if ((p->|| (p->))
            {
            Bitstream_Write(stream, 8,  p->NID_TEXTMESSAGE);
            Bitstream_Write(stream, 10, p->NID_C);
            Bitstream_Write(stream, 14, p->NID_RBC);
            }

            Bitstream_Write(stream, 8,  p->Q_TEXT);


            //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
            //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);
            //@ assert Q_SCALE:           EqualBits(stream, pos + 15,  pos + 17,  p->Q_SCALE);
            //@ assert Q_TEXTCLASS:       EqualBits(stream, pos + 17,  pos + 19,  p->Q_TEXTCLASS);
            //@ assert Q_TEXTDISPLAY:     EqualBits(stream, pos + 19,  pos + 20,  p->Q_TEXTDISPLAY);
            //@ assert D_TEXTDISPLAY:     EqualBits(stream, pos + 20,  pos + 35,  p->D_TEXTDISPLAY);
            //@ assert M_MODETEXTDISPLAY0: EqualBits(stream, pos + 35,  pos + 39,  p->M_MODETEXTDISPLAY0);
            //@ assert M_LEVELTEXTDISPLAY0: EqualBits(stream, pos + 39,  pos + 42,  p->M_LEVELTEXTDISPLAY0);

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

