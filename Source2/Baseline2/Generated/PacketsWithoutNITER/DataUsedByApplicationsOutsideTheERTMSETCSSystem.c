
/* =============================================================================
Formalization of Subset-026-7 (Chapter 7: ERTMS/ETCS language)

- Name: Subset-026-7 / TrainToTrack_DataUsedByApplicationsOutsideTheERTMSETCSSystem
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


#include "DataUsedByApplicationsOutsideTheERTMSETCSSystem.h"
#include "Bit64.h"


int DataUsedByApplicationsOutsideTheERTMSETCSSystem_UpperBitsNotSet(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p)
{
    int status = 1;

    status = status && UpperBitsNotSet64(p->L_PACKET,          13);
    status = status && UpperBitsNotSet64(p->NID_XUSER,         9) ;
    status = status && UpperBitsNotSet64(p->Other_data_depending_on__NID_XUSER, 64);

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int DataUsedByApplicationsOutsideTheERTMSETCSSystem_EncodeBit(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_BITSIZE))
    {
        if (DataUsedByApplicationsOutsideTheERTMSETCSSystem_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 13, p->L_PACKET);
            Bitstream_Write(stream, 9,  p->NID_XUSER);
            Bitstream_Write(stream, 64, p->Other_data_depending_on__NID_XUSER);


            //@ assert L_PACKET:          EqualBits(stream, pos,       pos + 13,  p->L_PACKET);
            //@ assert NID_XUSER:         EqualBits(stream, pos + 13,  pos + 22,  p->NID_XUSER);
            //@ assert Other_data_depending_on__NID_XUSER: EqualBits(stream, pos + 22,  pos + 86,  p->Other_data_depending_on__NID_XUSER);

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

int DataUsedByApplicationsOutsideTheERTMSETCSSystem_DecodeBit(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_BITSIZE))
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
          requires NID_XUSER:      stream->bitpos == pos + 13;
          assigns                  stream->bitpos;
          assigns                  p->NID_XUSER;
          ensures  NID_XUSER:      stream->bitpos == pos + 22;
          ensures  NID_XUSER:      EqualBits(stream, pos + 13, pos + 22, p->NID_XUSER);
          ensures  NID_XUSER:      UpperBitsNotSet(p->NID_XUSER, 9);
        */
        {
            p->NID_XUSER        = Bitstream_Read(stream, 9);
        }

        /*@
          requires Other_data_depending_on__NID_XUSER: stream->bitpos == pos + 22;
          assigns                  stream->bitpos;
          assigns                  p->Other_data_depending_on__NID_XUSER;
          ensures  Other_data_depending_on__NID_XUSER: stream->bitpos == pos + 86;
          ensures  Other_data_depending_on__NID_XUSER: EqualBits(stream, pos + 22, pos + 86, p->Other_data_depending_on__NID_XUSER);
          ensures  Other_data_depending_on__NID_XUSER: UpperBitsNotSet(p->Other_data_depending_on__NID_XUSER, 64);
        */
        {
            p->Other_data_depending_on__NID_XUSER        = Bitstream_Read(stream, 64);
        }

        //@ assert L_PACKET:          EqualBits(stream, pos,       pos + 13,  p->L_PACKET);
        //@ assert NID_XUSER:         EqualBits(stream, pos + 13,  pos + 22,  p->NID_XUSER);
        //@ assert Other_data_depending_on__NID_XUSER: EqualBits(stream, pos + 22,  pos + 86,  p->Other_data_depending_on__NID_XUSER);

        //@ assert L_PACKET:          UpperBitsNotSet(p->L_PACKET,          13);
        //@ assert NID_XUSER:         UpperBitsNotSet(p->NID_XUSER,         9);
        //@ assert Other_data_depending_on__NID_XUSER: UpperBitsNotSet(p->Other_data_depending_on__NID_XUSER, 64);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

#ifndef FRAMAC_IGNORE

int DataUsedByApplicationsOutsideTheERTMSETCSSystem_EncodeInt(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, Metadata* data, kcg_int* stream)
{
    data->nid_packet = 44;
    data->valid = 1;

    kcg_int startAddress = data->startAddress;

    stream[startAddress++] = p->header.NID_PACKET;

    stream[startAddress++] = p->L_PACKET;
    stream[startAddress++] = p->NID_XUSER;
    stream[startAddress++] = p->Other_data_depending_on__NID_XUSER;

    data->endAddress = startAddress-1;

    return 1;
}

int DataUsedByApplicationsOutsideTheERTMSETCSSystem_DecodeInt(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, const Metadata* data, const kcg_int* stream)
{
    if(data->nid_packet != 44)
    {
         return 0;
    }

    kcg_int startAddress = data->startAddress;
    p->header.NID_PACKET = stream[startAddress++];

    p->L_PACKET = stream[startAddress++];
    p->NID_XUSER = stream[startAddress++];
    p->Other_data_depending_on__NID_XUSER = stream[startAddress++];

    if(startAddress-1 != data->endAddress)
    {
         return 0;
    }

    return 1;
}

// number of cells in allocation memory
#define DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryMax		8

// end-of-freelist indicator
#define DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryNil		(-1)

// allocation memory
static DataUsedByApplicationsOutsideTheERTMSETCSSystem DataUsedByApplicationsOutsideTheERTMSETCSSystemMemory[DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryMax];

// lowest unused cell of allocation memory
static uint64_t DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryTop = 0;

// index of first element of freelist
static uint64_t DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList = DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryNil;

DataUsedByApplicationsOutsideTheERTMSETCSSystem* DataUsedByApplicationsOutsideTheERTMSETCSSystem_New(void)
{
    DataUsedByApplicationsOutsideTheERTMSETCSSystem* ptr;

    if (DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList != DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryNil)
    {
        // allocate from freelist
        ptr = &DataUsedByApplicationsOutsideTheERTMSETCSSystemMemory[DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList];
        DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList = DataUsedByApplicationsOutsideTheERTMSETCSSystemMemory[DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList].header.NID_PACKET;
    }
    else if (DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryTop < DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryMax)
    {
        // allocate from top
        ptr = &DataUsedByApplicationsOutsideTheERTMSETCSSystemMemory[DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryTop];
        DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryTop += 1;
    }
    else
    {
        // memory exhausted
        return 0;
    }

    DataUsedByApplicationsOutsideTheERTMSETCSSystem_Init(ptr);

    return ptr;
}


void DataUsedByApplicationsOutsideTheERTMSETCSSystem_Delete(DataUsedByApplicationsOutsideTheERTMSETCSSystem* ptr)
{
    // prepend to freelist
    ptr->header.NID_PACKET = DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList;
    DataUsedByApplicationsOutsideTheERTMSETCSSystemMemoryFreeList = ptr - DataUsedByApplicationsOutsideTheERTMSETCSSystemMemory;
}

#endif // FRAMAC_IGNORE

