
#ifndef SESSION_MANAGEMENT_CORE_H_INCLUDED
#define SESSION_MANAGEMENT_CORE_H_INCLUDED

#include "Bitstream.h"
#include "CompressedPackets.h"

struct Session_Management_Core
{
    // TransmissionMedia=Any
    // Packet to give the identity and telephone number of the RBC
    // with which a session shall be established or terminated.
    // Packet Number = 42

    uint64_t   Q_DIR;            // # 2
    uint64_t  L_PACKET;         // # 13
    uint64_t   Q_RBC;            // # 1
    uint64_t  NID_C;            // # 10
    uint64_t  NID_RBC;          // # 14
    uint64_t  NID_RADIO;        // # 64
    uint64_t   Q_SLEEPSESSION;   // # 1
};

typedef struct Session_Management_Core Session_Management_Core;

#define SESSION_MANAGEMENT_CORE_BITSIZE 31

/*@
    logic integer BitSize{L}(Session_Management_Core* p) = SESSION_MANAGEMENT_CORE_BITSIZE;

    logic integer MaxBitSize{L}(Session_Management_Core* p) = BitSize(p);

    predicate Separated(Bitstream* stream, Session_Management_Core* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(Session_Management_Core* p) =
      Invariant(p->Q_DIR)             &&
      Invariant(p->L_PACKET)          &&
      Invariant(p->Q_RBC);

    predicate ZeroInitialized(Session_Management_Core* p) =
      ZeroInitialized(p->Q_DIR)             &&
      ZeroInitialized(p->L_PACKET)          &&
      ZeroInitialized(p->Q_RBC);

    predicate EqualBits(Bitstream* stream, integer pos, Session_Management_Core* p) =
      EqualBits(stream, pos,       pos + 2,   p->Q_DIR)             &&
      EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET)          &&
      EqualBits(stream, pos + 15,  pos + 16,  p->Q_RBC);

    predicate UpperBitsNotSet(Session_Management_Core* p) =
      UpperBitsNotSet(p->Q_DIR,            2)   &&
      UpperBitsNotSet(p->L_PACKET,         13)  &&
      UpperBitsNotSet(p->Q_RBC,            1);

*/

/*@
    requires valid:      \valid_read(p);
    requires invariant:  Invariant(p);

    assigns \nothing;

    ensures result:  \result <==> UpperBitsNotSet(p);
*/
int Session_Management_UpperBitsNotSet(const Session_Management_Core* p);

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
int Session_Management_Encode_Bit(Bitstream* stream, const Session_Management_Core* p);

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
int Session_Management_Decode_Bit(Bitstream* stream, Session_Management_Core* p);

int Session_Management_Encode_Int(PacketInfo* data, kcg_int* stream, const Session_Management_Core* p);

int Session_Management_Decode_Int(PacketInfo* data, const kcg_int* stream, Session_Management_Core* p);

#ifdef __cplusplus

#include <iostream>

inline std::ostream& operator<<(std::ostream& stream, const Session_Management_Core& p)
{
    stream
            << +p.Q_DIR << ','
            << +p.L_PACKET << ','
            << +p.Q_RBC << ','
            << +p.NID_C << ','
            << +p.NID_RBC << ','
            << +p.NID_RADIO << ','
            << +p.Q_SLEEPSESSION;

    return stream;
}

inline bool operator==(const Session_Management_Core& a, const Session_Management_Core& b)
{
    bool status = true;

    status = status && (a.Q_DIR == b.Q_DIR);
    status = status && (a.L_PACKET == b.L_PACKET);
    status = status && (a.Q_RBC == b.Q_RBC);

    if (a.NID_RBC != 16383)
    {
        status = status && (a.NID_C == b.NID_C);
    }
    status = status && (a.NID_RBC == b.NID_RBC);

    if (a.NID_RBC != 16383)
    {
        status = status && (a.NID_RADIO == b.NID_RADIO);
    }
    status = status && (a.Q_SLEEPSESSION == b.Q_SLEEPSESSION);

    return status;
}

inline bool operator!=(const Session_Management_Core& a, const Session_Management_Core& b)
{
    return !(a == b);
}

inline int encode(Bitstream& stream, const Session_Management_Core& p)
{
    return Session_Management_Encode_Bit(&stream, &p);
}

inline int decode(Bitstream& stream, Session_Management_Core& p)
{
    return Session_Management_Decode_Bit(&stream, &p);
}

inline int encode(PacketInfo& data, kcg_int* stream, const Session_Management_Core& p)
{
    std::cerr << "encode int function not implemented for packet 42 yet." << std::endl;

    return Session_Management_Encode_Int(&data, stream, &p);
}

inline int decode(PacketInfo& data, const kcg_int* stream, Session_Management_Core& p)
{
    std::cerr << "decode int function not implemented for packet 42 yet." << std::endl;

    return Session_Management_Decode_Int(&data, stream, &p);
}

#endif // __cplusplus

#endif // SESSION_MANAGEMENT_CORE_H_INCLUDED

