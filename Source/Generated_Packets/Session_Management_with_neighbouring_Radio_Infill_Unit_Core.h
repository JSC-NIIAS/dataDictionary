
#ifndef SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_CORE_H_INCLUDED
#define SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_CORE_H_INCLUDED

#include "Bitstream.h"
#include <iostream>

struct Session_Management_with_neighbouring_Radio_Infill_Unit_Core
{
    // TransmissionMedia=RIU
    // Packet to give the identity and telephone number of the neighbouring
    // Radio Infill Unit with which a session shall be established or
    // terminated.          
    // Packet Number = 143

    uint32_t  Q_DIR;            // # 2
    uint16_t  L_PACKET;         // # 13
    uint32_t  Q_RIU;            // # 1
    uint16_t  NID_C;            // # 10
    uint16_t  NID_RIU;          // # 14
    uint64_t  NID_RADIO;        // # 64
};

#ifdef __cplusplus

inline std::ostream& operator<<(std::ostream& stream, const Session_Management_with_neighbouring_Radio_Infill_Unit_Core& p)
{
    stream 
       << +p.Q_DIR << ','
       << +p.L_PACKET << ','
       << +p.Q_RIU << ','
       << +p.NID_C << ','
       << +p.NID_RIU << ','
       << +p.NID_RADIO;

    return stream;
}

inline bool operator==(const Session_Management_with_neighbouring_Radio_Infill_Unit_Core& a, const Session_Management_with_neighbouring_Radio_Infill_Unit_Core& b)
{
    bool status = true;
    
    status = status && (a.Q_DIR == b.Q_DIR);
    status = status && (a.L_PACKET == b.L_PACKET);
    status = status && (a.Q_RIU == b.Q_RIU);
    status = status && (a.NID_C == b.NID_C);
    status = status && (a.NID_RIU == b.NID_RIU);
    status = status && (a.NID_RADIO == b.NID_RADIO);

    return status;
}

inline bool operator!=(const Session_Management_with_neighbouring_Radio_Infill_Unit_Core& a, const Session_Management_with_neighbouring_Radio_Infill_Unit_Core& b)
{
    return !(a == b);
}

#endif // __cplusplus

typedef struct Session_Management_with_neighbouring_Radio_Infill_Unit_Core Session_Management_with_neighbouring_Radio_Infill_Unit_Core;

#define SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_CORE_BITSIZE 104

/*@
    logic integer BitSize{L}(Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) = SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_CORE_BITSIZE;

    logic integer MaxBitSize{L}(Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) = BitSize(p);

    predicate Separated(Bitstream* stream, Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) =
      \separated(stream, p) &&
      \separated(stream->addr + (0..stream->size-1), p);

    predicate Invariant(Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) = \true;

    predicate ZeroInitialized(Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) = \true;

    predicate EqualBits(Bitstream* stream, integer pos, Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) =
      EqualBits(stream, pos,       pos + 2,   p->Q_DIR)             &&
      EqualBits(stream, pos + 2,   pos + 15,  p->L_PACKET)          &&
      EqualBits(stream, pos + 15,  pos + 16,  p->Q_RIU)             &&
      EqualBits(stream, pos + 16,  pos + 26,  p->NID_C)             &&
      EqualBits(stream, pos + 26,  pos + 40,  p->NID_RIU)           &&
      EqualBits(stream, pos + 40,  pos + 104, p->NID_RADIO);

    predicate UpperBitsNotSet(Session_Management_with_neighbouring_Radio_Infill_Unit_Core* p) =
      UpperBitsNotSet(p->Q_DIR,            2)   &&
      UpperBitsNotSet(p->L_PACKET,         13)  &&
      UpperBitsNotSet(p->Q_RIU,            1)   &&
      UpperBitsNotSet(p->NID_C,            10)  &&
      UpperBitsNotSet(p->NID_RIU,          14)  &&
      UpperBitsNotSet(p->NID_RADIO,        64);

*/

#endif // SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_CORE_H_INCLUDED

