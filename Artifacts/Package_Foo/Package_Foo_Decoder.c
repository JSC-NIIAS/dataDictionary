
#include "Package_Foo_Decoder.h"
#include "Bitstream_Read_Normal.h"

int Package_Foo_Decoder(Bitstream* stream, Package_Foo* p)
{
    if (stream->bitpos + 28 > 8 * stream->size)
    {
        return 0;
    }
    else
    {
        //@ assert Normal(stream, 28);
        //@ ghost uint32_t pos = stream->bitpos;

        /*@
            requires ABC_normal: Normal(stream, 8);

            assigns stream->bitpos;
            assigns p->ABC;

            ensures ABC_bitpos: stream->bitpos == pos + 8;
            ensures ABC_equal:  BitstreamEqual64(stream, pos, pos + 8,  p->ABC);
            ensures ABC_upper:  UpperBitsNotSet(p->ABC, 8);
        */
        p->ABC = Bitstream_Read_Normal(stream, 8);

        /*@
            requires DEF_normal: Normal{Here}(stream, 3);

            assigns stream->bitpos;
            assigns p->DEF;

            ensures DEF_bitpos: stream->bitpos == pos + 11;
            ensures DEF_equal:  BitstreamEqual64(stream, pos + 8, pos + 11,  p->DEF);
            ensures DEF_upper:  UpperBitsNotSet(p->DEF, 3);
        */
        p->DEF = Bitstream_Read_Normal(stream, 3);

        /*@
            requires GHI_normal: Normal(stream, 17);

            assigns stream->bitpos;
            assigns p->GHI;

            ensures GHI_bitpos: stream->bitpos == pos + 28;
            ensures GHI_equal:  BitstreamEqual64(stream, pos + 11, pos + 28,  p->GHI);
            ensures GHI_upper:  UpperBitsNotSet(p->GHI, 17);
        */
        p->GHI = Bitstream_Read_Normal(stream, 17);

        //@ assert ABC_final:  BitstreamEqual64(stream, pos, pos + 8,  p->ABC);
        //@ assert DEF_final:  BitstreamEqual64(stream, pos + 8, pos + 11,  p->DEF);
        //@ assert GHI_final:  BitstreamEqual64(stream, pos + 11, pos + 28,  p->GHI);
        //@ assert p_equal: BitstreamEqual(stream, pos, p);

        return 1;
    }
}

