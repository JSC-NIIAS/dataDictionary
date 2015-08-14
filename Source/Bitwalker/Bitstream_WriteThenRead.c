
#include "Bitstream_Read.h"
#include "Bitstream_Write.h"

/*
   lemma CompareBit64:
     \forall uint8_t* addr, integer first, last, uint64_t x, y;
        EqualBits(addr, first, last, x) ==> EqualBits(addr, first, last, y) ==> 
        \forall integer k; 0 <= k < last - first ==> (BitTest(x, k) <==> BitTest(y, k));

*/

/*@
    requires valid:      Writeable(stream);
    requires invariant:  Invariant(stream, length);
    requires normal:     Normal(stream, length);
    requires upper:      UpperBitsNotSet(value, length);

    assigns stream->addr[0..stream->size-1];
    assigns stream->bitpos;

    ensures compare:     EqualBits64(\result, value, 0, 64);
*/
uint64_t Bitstream_WriteThenRead(Bitstream* stream, uint32_t length, uint64_t value)
{
    //@ ghost uint32_t pos = stream->bitpos;

    Bitstream_Write(stream, length, value);
    //@ assert equal:  EqualBits(stream, pos, pos+length, value);

    stream->bitpos -= length;
    //@ assert stream->bitpos == \at(stream->bitpos,Pre);

    uint64_t result = Bitstream_Read(stream, length);
    //@ assert equal:  EqualBits(stream, pos, pos+length, result);
    //@ assert left:   EqualBits64(result, value, 64-length, 64);

    return result;
}

