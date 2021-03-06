
#ifndef DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_H_INCLUDED
#define DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_H_INCLUDED

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

#include "Bitstream.h"
#include "CompressedPackets.h"
#include "PacketHeader.h"

struct DataUsedByApplicationsOutsideTheERTMSETCSSystem
{
    PacketHeader header;

    // TransmissionMedia=Any
    // Messages between on-board and trackside devices, which contain information used by
    // applications outside the ERTMS/ETCS system.
    // Packet Number = 44

    uint64_t  L_PACKET;         // # 13
    uint64_t  NID_XUSER;        // # 9
    uint64_t  Other_data_depending_on__NID_XUSER;// # 64
};

typedef struct DataUsedByApplicationsOutsideTheERTMSETCSSystem DataUsedByApplicationsOutsideTheERTMSETCSSystem;

#define DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_BITSIZE 86

/*@
    logic integer BitSize{L}(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) = DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_BITSIZE;

    logic integer MaxBitSize{L}(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) = BitSize(p);

    predicate Separated(Bitstream* stream, DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) =
      Invariant(p->L_PACKET)          &&
      Invariant(p->NID_XUSER)         &&
      Invariant(p->Other_data_depending_on__NID_XUSER);

    predicate ZeroInitialized(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) =
      ZeroInitialized(p->L_PACKET)          &&
      ZeroInitialized(p->NID_XUSER)         &&
      ZeroInitialized(p->Other_data_depending_on__NID_XUSER);

    predicate EqualBits(Bitstream* stream, integer pos, DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) =
      EqualBits(stream, pos,       pos + 13,  p->L_PACKET)          &&
      EqualBits(stream, pos + 13,  pos + 22,  p->NID_XUSER)         &&
      EqualBits(stream, pos + 22,  pos + 86,  p->Other_data_depending_on__NID_XUSER);

    predicate UpperBitsNotSet(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p) =
      UpperBitsNotSet(p->L_PACKET,         13)  &&
      UpperBitsNotSet(p->NID_XUSER,        9)   &&
      UpperBitsNotSet(p->Other_data_depending_on__NID_XUSER,64);

*/

/*@
    requires valid:      \valid_read(p);
    requires invariant:  Invariant(p);

    assigns \nothing;

    ensures result:  \result <==> UpperBitsNotSet(p);
*/
int DataUsedByApplicationsOutsideTheERTMSETCSSystem_UpperBitsNotSet(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p);

/*@
    requires valid_stream:      Writeable(stream);
    requires stream_invariant:  Invariant(stream, MaxBitSize(p));
    requires valid_package:     \valid_read(p);
    requires invariant:         Invariant(p);
    requires separation:        Separated(stream, p);

    assigns stream->bitpos;
    assigns stream->addr[0..(stream->size-1)];

    behavior normal_case:
      assumes Normal{Pre}(stream, MaxBitSize(p)) && UpperBitsNotSet{Pre}(p);

      assigns stream->bitpos;
      assigns stream->addr[0..(stream->size-1)];

      ensures result:     \result == 1;
      ensures increment:  stream->bitpos == \old(stream->bitpos) + BitSize(p);
      ensures left:       Unchanged{Here,Old}(stream, 0, \old(stream->bitpos));
      ensures middle:     EqualBits(stream, \old(stream->bitpos), p);
      ensures right:      Unchanged{Here,Old}(stream, stream->bitpos, 8 * stream->size);

    behavior values_too_big:
      assumes Normal{Pre}(stream, MaxBitSize(p)) && !UpperBitsNotSet{Pre}(p);

      assigns \nothing;

      ensures result:        \result == -2;

    behavior invalid_bit_sequence:
      assumes !Normal{Pre}(stream, MaxBitSize(p));

      assigns \nothing;

      ensures result:       \result == -1;

    complete behaviors;
    disjoint behaviors;
*/
int DataUsedByApplicationsOutsideTheERTMSETCSSystem_EncodeBit(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, Bitstream* stream);

/*@
    requires valid_stream:      Readable(stream);
    requires stream_invariant:  Invariant(stream, MaxBitSize(p));
    requires valid_package:     \valid(p);
    requires separation:        Separated(stream, p);

    assigns stream->bitpos;
    assigns *p;

    ensures unchanged:          Unchanged{Here,Old}(stream, 0, 8*stream->size);

    behavior normal_case:
      assumes Normal{Pre}(stream, MaxBitSize(p));

      assigns stream->bitpos;
      assigns *p;

      ensures invariant:  Invariant(p);
      ensures result:     \result == 1;
      ensures increment:  stream->bitpos == \old(stream->bitpos) + BitSize(p);
      ensures equal:      EqualBits(stream, \old(stream->bitpos), p);
      ensures upper:      UpperBitsNotSet(p);

    behavior error_case:
      assumes !Normal{Pre}(stream, MaxBitSize(p));

      assigns \nothing;

      ensures result: \result == 0;

    complete behaviors;
    disjoint behaviors;
*/
int DataUsedByApplicationsOutsideTheERTMSETCSSystem_DecodeBit(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, Bitstream* stream);

#ifndef FRAMAC_IGNORE

DataUsedByApplicationsOutsideTheERTMSETCSSystem*  DataUsedByApplicationsOutsideTheERTMSETCSSystem_New(void);

void   DataUsedByApplicationsOutsideTheERTMSETCSSystem_Delete(DataUsedByApplicationsOutsideTheERTMSETCSSystem*);

static inline void DataUsedByApplicationsOutsideTheERTMSETCSSystem_Init(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p)
{
    p->header.NID_PACKET = 44;
    p->header.list = TRAINTOTRACK;
    p->L_PACKET = 0;
    p->NID_XUSER = 0;
    p->Other_data_depending_on__NID_XUSER = 0;
}

static inline void DataUsedByApplicationsOutsideTheERTMSETCSSystem_Print(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, FILE* stream)
{
    PacketHeader_Print(&p->header, stream);
    fprintf(stream, "(%lu,%lu,%lu)",
            p->L_PACKET,
            p->NID_XUSER,
            p->Other_data_depending_on__NID_XUSER);
}

static inline int DataUsedByApplicationsOutsideTheERTMSETCSSystem_Equal(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* a, const DataUsedByApplicationsOutsideTheERTMSETCSSystem* b)
{
    int status = PacketHeader_Equal(&a->header, &b->header);
    
    status = status && (a->L_PACKET == b->L_PACKET);
    status = status && (a->NID_XUSER == b->NID_XUSER);
    status = status && (a->Other_data_depending_on__NID_XUSER == b->Other_data_depending_on__NID_XUSER);

    return status;
}

static inline uint32_t DataUsedByApplicationsOutsideTheERTMSETCSSystem_Length(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p)
{
    return (uint32_t)(p->L_PACKET);
}

int DataUsedByApplicationsOutsideTheERTMSETCSSystem_EncodeInt(const DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, Metadata* data, kcg_int* stream);

int DataUsedByApplicationsOutsideTheERTMSETCSSystem_DecodeInt(DataUsedByApplicationsOutsideTheERTMSETCSSystem* p, const Metadata* data, const kcg_int* stream);

#endif // FRAMAC_IGNORE

#endif // DATAUSEDBYAPPLICATIONSOUTSIDETHEERTMSETCSSYSTEM_H_INCLUDED


