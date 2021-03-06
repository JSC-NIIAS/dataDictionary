
#ifndef ROUTESUITABILITYDATA_1_H_INCLUDED
#define ROUTESUITABILITYDATA_1_H_INCLUDED

/* =============================================================================
Formalization of Subset-026-7 (Chapter 7: ERTMS/ETCS language)

- Name: Subset-026-7 / TrackToTrain_RouteSuitabilityData
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

struct RouteSuitabilityData_1
{

    uint64_t  D_SUITABILITY;    // # 15
    uint64_t   Q_SUITABILITY;    // # 2
    uint64_t   M_LOADINGGAUGE;   // # 8
    uint64_t   M_AXLELOAD;       // # 7
    uint64_t   M_TRACTION;       // # 8
};

typedef struct RouteSuitabilityData_1 RouteSuitabilityData_1;

#define ROUTESUITABILITYDATA_1_BITSIZE 17

/*@
    logic integer BitSize{L}(RouteSuitabilityData_1* p) = ROUTESUITABILITYDATA_1_BITSIZE;

    logic integer MaxBitSize{L}(RouteSuitabilityData_1* p) = BitSize(p);

    predicate Separated(Bitstream* stream, RouteSuitabilityData_1* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(RouteSuitabilityData_1* p) =
      Invariant(p->D_SUITABILITY)     &&
      Invariant(p->Q_SUITABILITY);

    predicate ZeroInitialized(RouteSuitabilityData_1* p) =
      ZeroInitialized(p->D_SUITABILITY)     &&
      ZeroInitialized(p->Q_SUITABILITY);

    predicate EqualBits(Bitstream* stream, integer pos, RouteSuitabilityData_1* p) =
      EqualBits(stream, pos,       pos + 15,  p->D_SUITABILITY)     &&
      EqualBits(stream, pos + 15,  pos + 17,  p->Q_SUITABILITY);

    predicate UpperBitsNotSet(RouteSuitabilityData_1* p) =
      UpperBitsNotSet(p->D_SUITABILITY,    15)  &&
      UpperBitsNotSet(p->Q_SUITABILITY,    2);

*/

/*@
    requires valid:      \valid_read(p);
    requires invariant:  Invariant(p);

    assigns \nothing;

    ensures result:  \result <==> UpperBitsNotSet(p);
*/
int RouteSuitabilityData_1_UpperBitsNotSet(const RouteSuitabilityData_1* p);

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
int RouteSuitabilityData_1_EncodeBit(const RouteSuitabilityData_1* p, Bitstream* stream);

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

      ensures result: \result == 0; complete behaviors;
    disjoint behaviors;
*/
int RouteSuitabilityData_1_DecodeBit(RouteSuitabilityData_1* p, Bitstream* stream);

#ifndef FRAMAC_IGNORE

static inline void RouteSuitabilityData_1_Init(RouteSuitabilityData_1* p)
{
    p->D_SUITABILITY = 0;
    p->Q_SUITABILITY = 0;
    p->M_LOADINGGAUGE = 0;
    p->M_AXLELOAD = 0;
    p->M_TRACTION = 0;
}

static inline void RouteSuitabilityData_1_Print(const RouteSuitabilityData_1* p, FILE* stream)
{
    fprintf(stream, "(%lu,%lu,%lu,%lu,%lu)",
            p->D_SUITABILITY,
            p->Q_SUITABILITY,
            p->M_LOADINGGAUGE,
            p->M_AXLELOAD,
            p->M_TRACTION);
}

static inline int RouteSuitabilityData_1_Equal(const RouteSuitabilityData_1* a, const RouteSuitabilityData_1* b)
{
    int status = 1;

    status = status && (a->D_SUITABILITY == b->D_SUITABILITY);
    status = status && (a->Q_SUITABILITY == b->Q_SUITABILITY);

    if (a->Q_SUITABILITY == 0)
    {
        status = status && (a->M_LOADINGGAUGE == b->M_LOADINGGAUGE);
    }

    if (a->Q_SUITABILITY == 1)
    {
        status = status && (a->M_AXLELOAD == b->M_AXLELOAD);
    }

    if (a->Q_SUITABILITY == 2)
    {
        status = status && (a->M_TRACTION == b->M_TRACTION);
    }

    return status;
}

int RouteSuitabilityData_1_EncodeInt(const RouteSuitabilityData_1* p, kcg_int* startAddress, kcg_int* stream);

int RouteSuitabilityData_1_DecodeInt(RouteSuitabilityData_1* p, kcg_int* startAddress, const kcg_int* stream);

#endif // FRAMAC_IGNORE

#endif // ROUTESUITABILITYDATA_1_H_INCLUDED

