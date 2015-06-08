
#ifndef SESSION_MANAGEMENT_CORE_H_INCLUDED
#define SESSION_MANAGEMENT_CORE_H_INCLUDED

#include "Bitstream.h"

struct Session_Management_Core
{
    // TransmissionMedia=Balise, RBC
    // Packet to give the identity and telephone number of the RBC
    // with which a session shall be established or terminated.  
    // Packet Number = 42

    uint32_t  Q_DIR;            // # 2
    uint16_t  L_PACKET;         // # 13
    uint32_t  Q_RBC;            // # 1
    uint16_t  NID_C;            // # 10
    uint16_t  NID_RBC;          // # 14
    uint64_t  NID_RADIO;        // # 64
    uint32_t  Q_SLEEPSESSION;   // # 1
};

#ifdef __cplusplus

inline bool operator==(const Session_Management_Core& a, const Session_Management_Core& b)
{
    return
        (a.Q_DIR == b.Q_DIR) &&
        (a.L_PACKET == b.L_PACKET) &&
        (a.Q_RBC == b.Q_RBC) &&
        (a.NID_C == b.NID_C) &&
        (a.NID_RBC == b.NID_RBC) &&
        (a.NID_RADIO == b.NID_RADIO) &&
        (a.Q_SLEEPSESSION == b.Q_SLEEPSESSION);
}

inline bool operator!=(const Session_Management_Core& a, const Session_Management_Core& b)
{
    return !(a == b);
}

#endif // __cplusplus

typedef struct Session_Management_Core Session_Management_Core;

#define SESSION_MANAGEMENT_CORE_BITSIZE 105

/*@
    logic integer BitSize{L}(Session_Management_Core* p) = SESSION_MANAGEMENT_CORE_BITSIZE;

    logic integer MaxBitSize{L}(Session_Management_Core* p) = BitSize(p);

    predicate Separated(Bitstream* stream, Session_Management_Core* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(Session_Management_Core* p) =
      Invariant(p->Q_DIR)             &&
      Invariant(p->L_PACKET)          &&
      Invariant(p->Q_RBC)             &&
      Invariant(p->NID_C)             &&
      Invariant(p->NID_RBC)           &&
      Invariant(p->NID_RADIO)         &&
      Invariant(p->Q_SLEEPSESSION);

    predicate ZeroInitialized(Session_Management_Core* p) =
      ZeroInitialized(p->Q_DIR)             &&
      ZeroInitialized(p->L_PACKET)          &&
      ZeroInitialized(p->Q_RBC)             &&
      ZeroInitialized(p->NID_C)             &&
      ZeroInitialized(p->NID_RBC)           &&
      ZeroInitialized(p->NID_RADIO)         &&
      ZeroInitialized(p->Q_SLEEPSESSION);

    predicate EqualBits(Bitstream* stream, integer pos, Session_Management_Core* p) =
      EqualBits(stream, pos,       pos + 2,   p->Q_DIR)             &&
      EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET)          &&
      EqualBits(stream, pos + 15,  pos + 16,  p->Q_RBC)             &&
      EqualBits(stream, pos + 16,  pos + 26,  p->NID_C)             &&
      EqualBits(stream, pos + 26,  pos + 40,  p->NID_RBC)           &&
      EqualBits(stream, pos + 40,  pos + 104, p->NID_RADIO)         &&
      EqualBits(stream, pos + 104, pos + 105, p->Q_SLEEPSESSION);

    predicate UpperBitsNotSet(Session_Management_Core* p) =
      UpperBitsNotSet(p->Q_DIR,            2)   &&
      UpperBitsNotSet(p->L_PACKET,         13)  &&
      UpperBitsNotSet(p->Q_RBC,            1)   &&
      UpperBitsNotSet(p->NID_C,            10)  &&
      UpperBitsNotSet(p->NID_RBC,          14)  &&
      UpperBitsNotSet(p->NID_RADIO,        64)  &&
      UpperBitsNotSet(p->Q_SLEEPSESSION,   1);

*/

#endif // SESSION_MANAGEMENT_CORE_H_INCLUDED

