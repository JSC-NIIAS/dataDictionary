#include "Bitwalker_Poke.h"
#include "Bit8Array.h"
#include "Bit64.h"

int Bitwalker_Poke(uint32_t  start,
                   uint32_t  length,
                   uint8_t*  addr,
                   uint32_t  size,
                   uint64_t  value)
{
  if ((start + length)  > 8 * size)
  {
    return -1;	// error: invalid_bit_sequence
  }

  // compute pow2(length)
  const uint64_t MaxValue = ((uint64_t) 1) << length;
  //@ assert MaxValue == 1 << length;

  if (value >= MaxValue)
  {
    return -2;  // error: value_too_big
  }

  /*@
    loop invariant 0 <= i <= length;
    loop invariant \forall integer k; 0 <= k < start ==>
                    (LeftBitInStream(addr, k) <==> \at(LeftBitInStream(addr, k), Pre));

    loop invariant \forall integer k; 0 <= k < i ==>
                    (LeftBitInStream(addr, start+k) <==> LeftBit64(value, (64-length)+k));

    loop invariant \forall integer k; start+i <= k < 8*size ==>
                    (LeftBitInStream(addr, k) <==> \at(LeftBitInStream(addr, k), Pre));

    loop assigns i, addr[0..size-1];
    loop variant length - i;
  */
  for (uint32_t i = 0; i < length; ++i)
  {
    int flag = PeekBit64(value, (64 - length) + i);
    PokeBit8Array(addr, size, start + i, flag);
  }

  return 0;
}

