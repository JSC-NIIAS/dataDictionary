
#ifndef POSITION_REPORT_PARAMETERS_CORE_1_CORE_H_INCLUDED
#define POSITION_REPORT_PARAMETERS_CORE_1_CORE_H_INCLUDED

#include "Bitstream.h"
#include "CompressedPackets.h"

struct Position_Report_Parameters_Core_1
{

    uint64_t  D_LOC;            // # 15
    uint64_t   Q_LGTLOC;         // # 1
};

typedef struct Position_Report_Parameters_Core_1 Position_Report_Parameters_Core_1;

#define POSITION_REPORT_PARAMETERS_CORE_1_CORE_BITSIZE 16

/*@
    logic integer BitSize{L}(Position_Report_Parameters_Core_1* p) = POSITION_REPORT_PARAMETERS_CORE_1_CORE_BITSIZE;

    logic integer MaxBitSize{L}(Position_Report_Parameters_Core_1* p) = BitSize(p);

    predicate Separated(Bitstream* stream, Position_Report_Parameters_Core_1* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(Position_Report_Parameters_Core_1* p) =
      Invariant(p->D_LOC)             &&
      Invariant(p->Q_LGTLOC);

    predicate ZeroInitialized(Position_Report_Parameters_Core_1* p) =
      ZeroInitialized(p->D_LOC)             &&
      ZeroInitialized(p->Q_LGTLOC);

    predicate EqualBits(Bitstream* stream, integer pos, Position_Report_Parameters_Core_1* p) =
      EqualBits(stream, pos,       pos + 15,  p->D_LOC)             &&
      EqualBits(stream, pos + 15,  pos + 16,  p->Q_LGTLOC);

    predicate UpperBitsNotSet(Position_Report_Parameters_Core_1* p) =
      UpperBitsNotSet(p->D_LOC,            15)  &&
      UpperBitsNotSet(p->Q_LGTLOC,         1);

*/

/*@
    requires valid:      \valid_read(p);
    requires invariant:  Invariant(p);

    assigns \nothing;

    ensures result:  \result <==> UpperBitsNotSet(p);
*/
int Position_Report_Parameters_Core_1_UpperBitsNotSet(const Position_Report_Parameters_Core_1* p);

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
int Position_Report_Parameters_Core_1_Encode_Bit(Bitstream* stream, const Position_Report_Parameters_Core_1* p);

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
int Position_Report_Parameters_Core_1_Decode_Bit(Bitstream* stream, Position_Report_Parameters_Core_1* p);

int Position_Report_Parameters_Core_1_Encode_Int(PacketInfo* data, kcg_int* stream, const Position_Report_Parameters_Core_1* p);

int Position_Report_Parameters_Core_1_Decode_Int(PacketInfo* data, const kcg_int* stream, Position_Report_Parameters_Core_1* p);

#ifdef __cplusplus

#include <iostream>

inline std::ostream& operator<<(std::ostream& stream, const Position_Report_Parameters_Core_1& p)
{
    stream
            << +p.D_LOC << ','
            << +p.Q_LGTLOC;

    return stream;
}

inline bool operator==(const Position_Report_Parameters_Core_1& a, const Position_Report_Parameters_Core_1& b)
{
    bool status = true;

    status = status && (a.D_LOC == b.D_LOC);
    status = status && (a.Q_LGTLOC == b.Q_LGTLOC);

    return status;
}

inline bool operator!=(const Position_Report_Parameters_Core_1& a, const Position_Report_Parameters_Core_1& b)
{
    return !(a == b);
}

inline int encode(Bitstream& stream, const Position_Report_Parameters_Core_1& p)
{
    return Position_Report_Parameters_Core_1_Encode_Bit(&stream, &p);
}

inline int decode(Bitstream& stream, Position_Report_Parameters_Core_1& p)
{
    return Position_Report_Parameters_Core_1_Decode_Bit(&stream, &p);
}

inline int encode(PacketInfo& data, kcg_int* stream, const Position_Report_Parameters_Core_1& p)
{
    std::cerr << "encode int function not implemented for packet 58 yet." << std::endl;

    return Position_Report_Parameters_Core_1_Encode_Int(&data, stream, &p);
}

inline int decode(PacketInfo& data, const kcg_int* stream, Position_Report_Parameters_Core_1& p)
{
    std::cerr << "decode int function not implemented for packet 58 yet." << std::endl;

    return Position_Report_Parameters_Core_1_Decode_Int(&data, stream, &p);
}

#endif // __cplusplus

#endif // POSITION_REPORT_PARAMETERS_CORE_1_CORE_H_INCLUDED

