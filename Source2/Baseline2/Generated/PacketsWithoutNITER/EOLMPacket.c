
/* =============================================================================
Formalization of Subset-026-7 (Chapter 7: ERTMS/ETCS language)

- Name: Subset-026-7 / TrackToTrain_EOLMPacket
- Description: UNISIG SUBSET-026-7, ISSUE : 3.3.0, 3.5 ERTMS/ETCS language) 
- Copyright (c) 

- Licensed under the EUPL V.1.1 ( http://joinup.ec.europa.eu/software/page/eupl/licence-eupl )
- Gist URL: none
- Cryptography: No
- Author(s): Fraunhofer FOKUS

Disclaimer:

The use of this software is limited to NON-vital applications. 
It has NOT been developed for vital operation purposes and MUST NOT be used for applications 
which may cause harm to people, physical accidents or financial loss. 

THEREFORE, NO LIABILITY WILL BE GIVEN FOR SUCH AND ANY OTHER KIND OF USE.       
============================================================================= */


#include "EOLMPacket.h"
#include "Bit64.h"


int EOLMPacket_UpperBitsNotSet(const EOLMPacket* p)
{
    int status = 1;

    status = status && UpperBitsNotSet64(p->Q_DIR,             2) ;
    status = status && UpperBitsNotSet64(p->L_PACKET,          13);
    status = status && UpperBitsNotSet64(p->Q_SCALE,           2) ;
    status = status && UpperBitsNotSet64(p->NID_LOOP,          14);
    status = status && UpperBitsNotSet64(p->D_LOOP,            15);
    status = status && UpperBitsNotSet64(p->L_LOOP,            15);
    status = status && UpperBitsNotSet64(p->Q_LOOPDIR,         1) ;
    status = status && UpperBitsNotSet64(p->Q_SSCODE,          4) ;

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int EOLMPacket_EncodeBit(const EOLMPacket* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, EOLMPACKET_BITSIZE))
    {
        if (EOLMPacket_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 2,  p->Q_DIR);
            Bitstream_Write(stream, 13, p->L_PACKET);
            Bitstream_Write(stream, 2,  p->Q_SCALE);
            Bitstream_Write(stream, 14, p->NID_LOOP);
            Bitstream_Write(stream, 15, p->D_LOOP);
            Bitstream_Write(stream, 15, p->L_LOOP);
            Bitstream_Write(stream, 1,  p->Q_LOOPDIR);
            Bitstream_Write(stream, 4,  p->Q_SSCODE);


            //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
            //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);
            //@ assert Q_SCALE:           EqualBits(stream, pos + 15,  pos + 17,  p->Q_SCALE);
            //@ assert NID_LOOP:          EqualBits(stream, pos + 17,  pos + 31,  p->NID_LOOP);
            //@ assert D_LOOP:            EqualBits(stream, pos + 31,  pos + 46,  p->D_LOOP);
            //@ assert L_LOOP:            EqualBits(stream, pos + 46,  pos + 61,  p->L_LOOP);
            //@ assert Q_LOOPDIR:         EqualBits(stream, pos + 61,  pos + 62,  p->Q_LOOPDIR);
            //@ assert Q_SSCODE:          EqualBits(stream, pos + 62,  pos + 66,  p->Q_SSCODE);

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

int EOLMPacket_DecodeBit(EOLMPacket* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, EOLMPACKET_BITSIZE))
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
          requires Q_SCALE:        stream->bitpos == pos + 15;
          assigns                  stream->bitpos;
          assigns                  p->Q_SCALE;
          ensures  Q_SCALE:        stream->bitpos == pos + 17;
          ensures  Q_SCALE:        EqualBits(stream, pos + 15, pos + 17, p->Q_SCALE);
          ensures  Q_SCALE:        UpperBitsNotSet(p->Q_SCALE, 2);
        */
        {
            p->Q_SCALE        = Bitstream_Read(stream, 2);
        }

        /*@
          requires NID_LOOP:       stream->bitpos == pos + 17;
          assigns                  stream->bitpos;
          assigns                  p->NID_LOOP;
          ensures  NID_LOOP:       stream->bitpos == pos + 31;
          ensures  NID_LOOP:       EqualBits(stream, pos + 17, pos + 31, p->NID_LOOP);
          ensures  NID_LOOP:       UpperBitsNotSet(p->NID_LOOP, 14);
        */
        {
            p->NID_LOOP        = Bitstream_Read(stream, 14);
        }

        /*@
          requires D_LOOP:         stream->bitpos == pos + 31;
          assigns                  stream->bitpos;
          assigns                  p->D_LOOP;
          ensures  D_LOOP:         stream->bitpos == pos + 46;
          ensures  D_LOOP:         EqualBits(stream, pos + 31, pos + 46, p->D_LOOP);
          ensures  D_LOOP:         UpperBitsNotSet(p->D_LOOP, 15);
        */
        {
            p->D_LOOP        = Bitstream_Read(stream, 15);
        }

        /*@
          requires L_LOOP:         stream->bitpos == pos + 46;
          assigns                  stream->bitpos;
          assigns                  p->L_LOOP;
          ensures  L_LOOP:         stream->bitpos == pos + 61;
          ensures  L_LOOP:         EqualBits(stream, pos + 46, pos + 61, p->L_LOOP);
          ensures  L_LOOP:         UpperBitsNotSet(p->L_LOOP, 15);
        */
        {
            p->L_LOOP        = Bitstream_Read(stream, 15);
        }

        /*@
          requires Q_LOOPDIR:      stream->bitpos == pos + 61;
          assigns                  stream->bitpos;
          assigns                  p->Q_LOOPDIR;
          ensures  Q_LOOPDIR:      stream->bitpos == pos + 62;
          ensures  Q_LOOPDIR:      EqualBits(stream, pos + 61, pos + 62, p->Q_LOOPDIR);
          ensures  Q_LOOPDIR:      UpperBitsNotSet(p->Q_LOOPDIR, 1);
        */
        {
            p->Q_LOOPDIR        = Bitstream_Read(stream, 1);
        }

        /*@
          requires Q_SSCODE:       stream->bitpos == pos + 62;
          assigns                  stream->bitpos;
          assigns                  p->Q_SSCODE;
          ensures  Q_SSCODE:       stream->bitpos == pos + 66;
          ensures  Q_SSCODE:       EqualBits(stream, pos + 62, pos + 66, p->Q_SSCODE);
          ensures  Q_SSCODE:       UpperBitsNotSet(p->Q_SSCODE, 4);
        */
        {
            p->Q_SSCODE        = Bitstream_Read(stream, 4);
        }

        //@ assert Q_DIR:             EqualBits(stream, pos,       pos + 2,   p->Q_DIR);
        //@ assert L_PACKET:          EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET);
        //@ assert Q_SCALE:           EqualBits(stream, pos + 15,  pos + 17,  p->Q_SCALE);
        //@ assert NID_LOOP:          EqualBits(stream, pos + 17,  pos + 31,  p->NID_LOOP);
        //@ assert D_LOOP:            EqualBits(stream, pos + 31,  pos + 46,  p->D_LOOP);
        //@ assert L_LOOP:            EqualBits(stream, pos + 46,  pos + 61,  p->L_LOOP);
        //@ assert Q_LOOPDIR:         EqualBits(stream, pos + 61,  pos + 62,  p->Q_LOOPDIR);
        //@ assert Q_SSCODE:          EqualBits(stream, pos + 62,  pos + 66,  p->Q_SSCODE);

        //@ assert Q_DIR:             UpperBitsNotSet(p->Q_DIR,             2);
        //@ assert L_PACKET:          UpperBitsNotSet(p->L_PACKET,          13);
        //@ assert Q_SCALE:           UpperBitsNotSet(p->Q_SCALE,           2);
        //@ assert NID_LOOP:          UpperBitsNotSet(p->NID_LOOP,          14);
        //@ assert D_LOOP:            UpperBitsNotSet(p->D_LOOP,            15);
        //@ assert L_LOOP:            UpperBitsNotSet(p->L_LOOP,            15);
        //@ assert Q_LOOPDIR:         UpperBitsNotSet(p->Q_LOOPDIR,         1);
        //@ assert Q_SSCODE:          UpperBitsNotSet(p->Q_SSCODE,          4);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

#ifndef FRAMAC_IGNORE

int EOLMPacket_EncodeInt(const EOLMPacket* p, Metadata* data, kcg_int* stream)
{
    data->nid_packet = 134;
    data->q_dir = p->Q_DIR;
    data->valid = 1;

    kcg_int startAddress = data->startAddress;

    stream[startAddress++] = p->header.NID_PACKET;

    stream[startAddress++] = p->Q_DIR;
    stream[startAddress++] = p->L_PACKET;
    stream[startAddress++] = p->Q_SCALE;
    stream[startAddress++] = p->NID_LOOP;
    stream[startAddress++] = p->D_LOOP;
    stream[startAddress++] = p->L_LOOP;
    stream[startAddress++] = p->Q_LOOPDIR;
    stream[startAddress++] = p->Q_SSCODE;

    data->endAddress = startAddress-1;

    return 1;
}

int EOLMPacket_DecodeInt(EOLMPacket* p, const Metadata* data, const kcg_int* stream)
{
    if(data->nid_packet != 134)
    {
         return 0;
    }

    kcg_int startAddress = data->startAddress;
    p->header.NID_PACKET = stream[startAddress++];

    p->Q_DIR = stream[startAddress++];
    p->L_PACKET = stream[startAddress++];
    p->Q_SCALE = stream[startAddress++];
    p->NID_LOOP = stream[startAddress++];
    p->D_LOOP = stream[startAddress++];
    p->L_LOOP = stream[startAddress++];
    p->Q_LOOPDIR = stream[startAddress++];
    p->Q_SSCODE = stream[startAddress++];

    if(startAddress-1 != data->endAddress)
    {
         return 0;
    }

    return 1;
}

// number of cells in allocation memory
#define EOLMPacketMemoryMax		8

// end-of-freelist indicator
#define EOLMPacketMemoryNil		(-1)

// allocation memory
static EOLMPacket EOLMPacketMemory[EOLMPacketMemoryMax];

// lowest unused cell of allocation memory
static uint64_t EOLMPacketMemoryTop = 0;

// index of first element of freelist
static uint64_t EOLMPacketMemoryFreeList = EOLMPacketMemoryNil;

EOLMPacket* EOLMPacket_New(void)
{
    EOLMPacket* ptr;

    if (EOLMPacketMemoryFreeList != EOLMPacketMemoryNil)
    {
        // allocate from freelist
        ptr = &EOLMPacketMemory[EOLMPacketMemoryFreeList];
        EOLMPacketMemoryFreeList = EOLMPacketMemory[EOLMPacketMemoryFreeList].header.NID_PACKET;
    }
    else if (EOLMPacketMemoryTop < EOLMPacketMemoryMax)
    {
        // allocate from top
        ptr = &EOLMPacketMemory[EOLMPacketMemoryTop];
        EOLMPacketMemoryTop += 1;
    }
    else
    {
        // memory exhausted
        return 0;
    }

    EOLMPacket_Init(ptr);

    return ptr;
}


void EOLMPacket_Delete(EOLMPacket* ptr)
{
    // prepend to freelist
    ptr->header.NID_PACKET = EOLMPacketMemoryFreeList;
    EOLMPacketMemoryFreeList = ptr - EOLMPacketMemory;
}

#endif // FRAMAC_IGNORE

