
/* =============================================================================
Formalization of Subset-026-7 (Chapter 7: ERTMS/ETCS language)

- Name: Subset-026-7 / TrainToTrack_Level23TransitionInformation
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


#include "Level23TransitionInformation.h"
#include "Bit64.h"


int Level23TransitionInformation_UpperBitsNotSet(const Level23TransitionInformation* p)
{
    int status = 1;

    status = status && UpperBitsNotSet64(p->L_PACKET,          13);
    status = status && UpperBitsNotSet64(p->NID_LTRBG,         24);

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Level23TransitionInformation_EncodeBit(const Level23TransitionInformation* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, LEVEL23TRANSITIONINFORMATION_BITSIZE))
    {
        if (Level23TransitionInformation_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 13, p->L_PACKET);
            Bitstream_Write(stream, 24, p->NID_LTRBG);


            //@ assert L_PACKET:          EqualBits(stream, pos,       pos + 13,  p->L_PACKET);
            //@ assert NID_LTRBG:         EqualBits(stream, pos + 13,  pos + 37,  p->NID_LTRBG);

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

int Level23TransitionInformation_DecodeBit(Level23TransitionInformation* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, LEVEL23TRANSITIONINFORMATION_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

        /*@
          requires L_PACKET:       stream->bitpos == pos + 0;
          assigns                  stream->bitpos;
          assigns                  p->L_PACKET;
          ensures  L_PACKET:       stream->bitpos == pos + 13;
          ensures  L_PACKET:       EqualBits(stream, pos + 0, pos + 13, p->L_PACKET);
          ensures  L_PACKET:       UpperBitsNotSet(p->L_PACKET, 13);
        */
        {
            p->L_PACKET        = Bitstream_Read(stream, 13);
        }

        /*@
          requires NID_LTRBG:      stream->bitpos == pos + 13;
          assigns                  stream->bitpos;
          assigns                  p->NID_LTRBG;
          ensures  NID_LTRBG:      stream->bitpos == pos + 37;
          ensures  NID_LTRBG:      EqualBits(stream, pos + 13, pos + 37, p->NID_LTRBG);
          ensures  NID_LTRBG:      UpperBitsNotSet(p->NID_LTRBG, 24);
        */
        {
            p->NID_LTRBG        = Bitstream_Read(stream, 24);
        }

        //@ assert L_PACKET:          EqualBits(stream, pos,       pos + 13,  p->L_PACKET);
        //@ assert NID_LTRBG:         EqualBits(stream, pos + 13,  pos + 37,  p->NID_LTRBG);

        //@ assert L_PACKET:          UpperBitsNotSet(p->L_PACKET,          13);
        //@ assert NID_LTRBG:         UpperBitsNotSet(p->NID_LTRBG,         24);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

#ifndef FRAMAC_IGNORE

int Level23TransitionInformation_EncodeInt(const Level23TransitionInformation* p, Metadata* data, kcg_int* stream)
{
    data->nid_packet = 9;
    data->valid = 1;

    kcg_int startAddress = data->startAddress;

    stream[startAddress++] = p->header.NID_PACKET;

    stream[startAddress++] = p->L_PACKET;
    stream[startAddress++] = p->NID_LTRBG;

    data->endAddress = startAddress-1;

    return 1;
}

int Level23TransitionInformation_DecodeInt(Level23TransitionInformation* p, const Metadata* data, const kcg_int* stream)
{
    if(data->nid_packet != 9)
    {
         return 0;
    }

    kcg_int startAddress = data->startAddress;
    p->header.NID_PACKET = stream[startAddress++];

    p->L_PACKET = stream[startAddress++];
    p->NID_LTRBG = stream[startAddress++];

    if(startAddress-1 != data->endAddress)
    {
         return 0;
    }

    return 1;
}

// number of cells in allocation memory
#define Level23TransitionInformationMemoryMax		8

// end-of-freelist indicator
#define Level23TransitionInformationMemoryNil		(-1)

// allocation memory
static Level23TransitionInformation Level23TransitionInformationMemory[Level23TransitionInformationMemoryMax];

// lowest unused cell of allocation memory
static uint64_t Level23TransitionInformationMemoryTop = 0;

// index of first element of freelist
static uint64_t Level23TransitionInformationMemoryFreeList = Level23TransitionInformationMemoryNil;

Level23TransitionInformation* Level23TransitionInformation_New(void)
{
    Level23TransitionInformation* ptr;

    if (Level23TransitionInformationMemoryFreeList != Level23TransitionInformationMemoryNil)
    {
        // allocate from freelist
        ptr = &Level23TransitionInformationMemory[Level23TransitionInformationMemoryFreeList];
        Level23TransitionInformationMemoryFreeList = Level23TransitionInformationMemory[Level23TransitionInformationMemoryFreeList].header.NID_PACKET;
    }
    else if (Level23TransitionInformationMemoryTop < Level23TransitionInformationMemoryMax)
    {
        // allocate from top
        ptr = &Level23TransitionInformationMemory[Level23TransitionInformationMemoryTop];
        Level23TransitionInformationMemoryTop += 1;
    }
    else
    {
        // memory exhausted
        return 0;
    }

    Level23TransitionInformation_Init(ptr);

    return ptr;
}


void Level23TransitionInformation_Delete(Level23TransitionInformation* ptr)
{
    // prepend to freelist
    ptr->header.NID_PACKET = Level23TransitionInformationMemoryFreeList;
    Level23TransitionInformationMemoryFreeList = ptr - Level23TransitionInformationMemory;
}

#endif // FRAMAC_IGNORE

