
#ifndef PACKET_FOR_SENDING_PLAIN_TEXT_MESSAGES_CORE_H_INCLUDED
#define PACKET_FOR_SENDING_PLAIN_TEXT_MESSAGES_CORE_H_INCLUDED

#include "Bitstream.h"
#include "CompressedPackets.h"

struct Packet_for_sending_plain_text_messages_Core
{
    // TransmissionMedia=Any
    // Packet Number = 72

    uint64_t   Q_DIR;            // # 2
    uint64_t  L_PACKET;         // # 13
    uint64_t   Q_SCALE;          // # 2
    uint64_t   Q_TEXTCLASS;      // # 2
    uint64_t   Q_TEXTDISPLAY;    // # 1
    uint64_t  D_TEXTDISPLAY;    // # 15
    uint64_t   M_MODETEXTDISPLAY_0;// # 4
    uint64_t   M_LEVELTEXTDISPLAY_0;// # 3
    uint64_t   NID_STM_0;        // # 8
    uint64_t  L_TEXTDISPLAY;    // # 15
    uint64_t  T_TEXTDISPLAY;    // # 10
    uint64_t   M_MODETEXTDISPLAY_1;// # 4
    uint64_t   M_LEVELTEXTDISPLAY_1;// # 3
    uint64_t   NID_STM_1;        // # 8
    uint64_t   Q_TEXTCONFIRM;    // # 2
    uint64_t   L_TEXT;           // # 8
    uint64_t   X_TEXT;           // # 8
};

typedef struct Packet_for_sending_plain_text_messages_Core Packet_for_sending_plain_text_messages_Core;

#define PACKET_FOR_SENDING_PLAIN_TEXT_MESSAGES_CORE_BITSIZE 92

/*@
    logic integer BitSize{L}(Packet_for_sending_plain_text_messages_Core* p) = PACKET_FOR_SENDING_PLAIN_TEXT_MESSAGES_CORE_BITSIZE;

    logic integer MaxBitSize{L}(Packet_for_sending_plain_text_messages_Core* p) = BitSize(p);

    predicate Separated(Bitstream* stream, Packet_for_sending_plain_text_messages_Core* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(Packet_for_sending_plain_text_messages_Core* p) =
      Invariant(p->Q_DIR)             &&
      Invariant(p->L_PACKET)          &&
      Invariant(p->Q_SCALE)           &&
      Invariant(p->Q_TEXTCLASS)       &&
      Invariant(p->Q_TEXTDISPLAY)     &&
      Invariant(p->D_TEXTDISPLAY)     &&
      Invariant(p->M_MODETEXTDISPLAY_0) &&
      Invariant(p->M_LEVELTEXTDISPLAY_0);

    predicate ZeroInitialized(Packet_for_sending_plain_text_messages_Core* p) =
      ZeroInitialized(p->Q_DIR)             &&
      ZeroInitialized(p->L_PACKET)          &&
      ZeroInitialized(p->Q_SCALE)           &&
      ZeroInitialized(p->Q_TEXTCLASS)       &&
      ZeroInitialized(p->Q_TEXTDISPLAY)     &&
      ZeroInitialized(p->D_TEXTDISPLAY)     &&
      ZeroInitialized(p->M_MODETEXTDISPLAY_0) &&
      ZeroInitialized(p->M_LEVELTEXTDISPLAY_0);

    predicate EqualBits(Bitstream* stream, integer pos, Packet_for_sending_plain_text_messages_Core* p) =
      EqualBits(stream, pos,       pos + 2,   p->Q_DIR)             &&
      EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET)          &&
      EqualBits(stream, pos + 15,  pos + 17,  p->Q_SCALE)           &&
      EqualBits(stream, pos + 17,  pos + 19,  p->Q_TEXTCLASS)       &&
      EqualBits(stream, pos + 19,  pos + 20,  p->Q_TEXTDISPLAY)     &&
      EqualBits(stream, pos + 20,  pos + 35,  p->D_TEXTDISPLAY)     &&
      EqualBits(stream, pos + 35,  pos + 39,  p->M_MODETEXTDISPLAY_0) &&
      EqualBits(stream, pos + 39,  pos + 42,  p->M_LEVELTEXTDISPLAY_0);

    predicate UpperBitsNotSet(Packet_for_sending_plain_text_messages_Core* p) =
      UpperBitsNotSet(p->Q_DIR,            2)   &&
      UpperBitsNotSet(p->L_PACKET,         13)  &&
      UpperBitsNotSet(p->Q_SCALE,          2)   &&
      UpperBitsNotSet(p->Q_TEXTCLASS,      2)   &&
      UpperBitsNotSet(p->Q_TEXTDISPLAY,    1)   &&
      UpperBitsNotSet(p->D_TEXTDISPLAY,    15)  &&
      UpperBitsNotSet(p->M_MODETEXTDISPLAY_0,4)   &&
      UpperBitsNotSet(p->M_LEVELTEXTDISPLAY_0,3);

*/

/*@
    requires valid:      \valid_read(p);
    requires invariant:  Invariant(p);

    assigns \nothing;

    ensures result:  \result <==> UpperBitsNotSet(p);
*/
int Packet_for_sending_plain_text_messages_UpperBitsNotSet(const Packet_for_sending_plain_text_messages_Core* p);

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
int Packet_for_sending_plain_text_messages_Encode_Bit(Bitstream* stream, const Packet_for_sending_plain_text_messages_Core* p);

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
int Packet_for_sending_plain_text_messages_Decode_Bit(Bitstream* stream, Packet_for_sending_plain_text_messages_Core* p);

int Packet_for_sending_plain_text_messages_Encode_Int(PacketInfo* data, kcg_int* stream, const Packet_for_sending_plain_text_messages_Core* p);

int Packet_for_sending_plain_text_messages_Decode_Int(PacketInfo* data, const kcg_int* stream, Packet_for_sending_plain_text_messages_Core* p);

#ifdef __cplusplus

#include <iostream>

inline std::ostream& operator<<(std::ostream& stream, const Packet_for_sending_plain_text_messages_Core& p)
{
    stream
            << +p.Q_DIR << ','
            << +p.L_PACKET << ','
            << +p.Q_SCALE << ','
            << +p.Q_TEXTCLASS << ','
            << +p.Q_TEXTDISPLAY << ','
            << +p.D_TEXTDISPLAY << ','
            << +p.M_MODETEXTDISPLAY_0 << ','
            << +p.M_LEVELTEXTDISPLAY_0 << ','
            << +p.NID_STM_0 << ','
            << +p.L_TEXTDISPLAY << ','
            << +p.T_TEXTDISPLAY << ','
            << +p.M_MODETEXTDISPLAY_1 << ','
            << +p.M_LEVELTEXTDISPLAY_1 << ','
            << +p.NID_STM_1 << ','
            << +p.Q_TEXTCONFIRM << ','
            << +p.L_TEXT << ','
            << +p.X_TEXT;

    return stream;
}

inline bool operator==(const Packet_for_sending_plain_text_messages_Core& a, const Packet_for_sending_plain_text_messages_Core& b)
{
    bool status = true;

    status = status && (a.Q_DIR == b.Q_DIR);
    status = status && (a.L_PACKET == b.L_PACKET);
    status = status && (a.Q_SCALE == b.Q_SCALE);
    status = status && (a.Q_TEXTCLASS == b.Q_TEXTCLASS);
    status = status && (a.Q_TEXTDISPLAY == b.Q_TEXTDISPLAY);
    status = status && (a.D_TEXTDISPLAY == b.D_TEXTDISPLAY);
    status = status && (a.M_MODETEXTDISPLAY_0 == b.M_MODETEXTDISPLAY_0);
    status = status && (a.M_LEVELTEXTDISPLAY_0 == b.M_LEVELTEXTDISPLAY_0);

    if (a.M_LEVELTEXTDISPLAY_0 == 1)
    {
        status = status && (a.NID_STM_0 == b.NID_STM_0);
    }
    status = status && (a.L_TEXTDISPLAY == b.L_TEXTDISPLAY);
    status = status && (a.T_TEXTDISPLAY == b.T_TEXTDISPLAY);
    status = status && (a.M_MODETEXTDISPLAY_1 == b.M_MODETEXTDISPLAY_1);
    status = status && (a.M_LEVELTEXTDISPLAY_1 == b.M_LEVELTEXTDISPLAY_1);

    if (a.M_LEVELTEXTDISPLAY_1 == 1)
    {
        status = status && (a.NID_STM_1 == b.NID_STM_1);
    }
    status = status && (a.Q_TEXTCONFIRM == b.Q_TEXTCONFIRM);
    status = status && (a.L_TEXT == b.L_TEXT);
    status = status && (a.X_TEXT == b.X_TEXT);

    return status;
}

inline bool operator!=(const Packet_for_sending_plain_text_messages_Core& a, const Packet_for_sending_plain_text_messages_Core& b)
{
    return !(a == b);
}

inline int encode(Bitstream& stream, const Packet_for_sending_plain_text_messages_Core& p)
{
    return Packet_for_sending_plain_text_messages_Encode_Bit(&stream, &p);
}

inline int decode(Bitstream& stream, Packet_for_sending_plain_text_messages_Core& p)
{
    return Packet_for_sending_plain_text_messages_Decode_Bit(&stream, &p);
}

inline int encode(PacketInfo& data, kcg_int* stream, const Packet_for_sending_plain_text_messages_Core& p)
{
    std::cerr << "encode int function not implemented for packet 72 yet." << std::endl;

    return Packet_for_sending_plain_text_messages_Encode_Int(&data, stream, &p);
}

inline int decode(PacketInfo& data, const kcg_int* stream, Packet_for_sending_plain_text_messages_Core& p)
{
    std::cerr << "decode int function not implemented for packet 72 yet." << std::endl;

    return Packet_for_sending_plain_text_messages_Decode_Int(&data, stream, &p);
}

#endif // __cplusplus

#endif // PACKET_FOR_SENDING_PLAIN_TEXT_MESSAGES_CORE_H_INCLUDED

