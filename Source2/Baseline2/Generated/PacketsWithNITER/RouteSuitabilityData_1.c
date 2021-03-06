
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

#include "RouteSuitabilityData_1.h"
#include "Bit64.h"

int RouteSuitabilityData_1_UpperBitsNotSet(const RouteSuitabilityData_1* p)
{
    int status = 1;

    status = status && UpperBitsNotSet64(p->D_SUITABILITY,     15);
    status = status && UpperBitsNotSet64(p->Q_SUITABILITY,     2) ;
    if (p->Q_SUITABILITY == 0)
    {
        status = status && UpperBitsNotSet64(p->M_LOADINGGAUGE,    8) ;
    }
    if (p->Q_SUITABILITY == 1)
    {
        status = status && UpperBitsNotSet64(p->M_AXLELOAD,        7) ;
    }
    if (p->Q_SUITABILITY == 2)
    {
        status = status && UpperBitsNotSet64(p->M_TRACTION,        8) ;
    }

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int RouteSuitabilityData_1_EncodeBit(const RouteSuitabilityData_1* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, ROUTESUITABILITYDATA_1_BITSIZE))
    {
        if (RouteSuitabilityData_1_UpperBitsNotSet(p))
        {
            //@ ghost const uint32_t pos = stream->bitpos;

            Bitstream_Write(stream, 15, p->D_SUITABILITY);
            Bitstream_Write(stream, 2,  p->Q_SUITABILITY);
            if (p->Q_SUITABILITY == 0)
            {
                Bitstream_Write(stream, 8,  p->M_LOADINGGAUGE);
            }

            if (p->Q_SUITABILITY == 1)
            {
                Bitstream_Write(stream, 7,  p->M_AXLELOAD);
            }

            if (p->Q_SUITABILITY == 2)
            {
                Bitstream_Write(stream, 8,  p->M_TRACTION);
            }



            //@ assert D_SUITABILITY:     EqualBits(stream, pos,       pos + 15,  p->D_SUITABILITY);
            //@ assert Q_SUITABILITY:     EqualBits(stream, pos + 15,  pos + 17,  p->Q_SUITABILITY);

            return 1;
        }
        else
        {
            return -2;
        }
    }
    else
    {
        return -1;
    }
}

int RouteSuitabilityData_1_DecodeBit(RouteSuitabilityData_1* p, Bitstream* stream)
{
    if (Bitstream_Normal(stream, ROUTESUITABILITYDATA_1_BITSIZE))
    {
        //@ ghost const uint32_t pos = stream->bitpos;

        /*@
          requires D_SUITABILITY:  stream->bitpos == pos + 0;
          assigns                  stream->bitpos;
          assigns                  p->D_SUITABILITY;
          ensures  D_SUITABILITY:  stream->bitpos == pos + 15;
          ensures  D_SUITABILITY:  EqualBits(stream, pos + 0, pos + 15, p->D_SUITABILITY);
          ensures  D_SUITABILITY:  UpperBitsNotSet(p->D_SUITABILITY, 15);
        */
        {
            p->D_SUITABILITY        = Bitstream_Read(stream, 15);
        }

        /*@
          requires Q_SUITABILITY:  stream->bitpos == pos + 15;
          assigns                  stream->bitpos;
          assigns                  p->Q_SUITABILITY;
          ensures  Q_SUITABILITY:  stream->bitpos == pos + 17;
          ensures  Q_SUITABILITY:  EqualBits(stream, pos + 15, pos + 17, p->Q_SUITABILITY);
          ensures  Q_SUITABILITY:  UpperBitsNotSet(p->Q_SUITABILITY, 2);
        */
        {
            p->Q_SUITABILITY        = Bitstream_Read(stream, 2);
        }

        if (p->Q_SUITABILITY == 0)
        {
            {
                p->M_LOADINGGAUGE        = Bitstream_Read(stream, 8);
            }

        }

        if (p->Q_SUITABILITY == 1)
        {
            {
                p->M_AXLELOAD        = Bitstream_Read(stream, 7);
            }

        }

        if (p->Q_SUITABILITY == 2)
        {
            {
                p->M_TRACTION        = Bitstream_Read(stream, 8);
            }

        }

        //@ assert D_SUITABILITY:     EqualBits(stream, pos,       pos + 15,  p->D_SUITABILITY);
        //@ assert Q_SUITABILITY:     EqualBits(stream, pos + 15,  pos + 17,  p->Q_SUITABILITY);

        //@ assert D_SUITABILITY:     UpperBitsNotSet(p->D_SUITABILITY,     15);
        //@ assert Q_SUITABILITY:     UpperBitsNotSet(p->Q_SUITABILITY,     2);

        //@ assert final: EqualBits(stream, pos, p);

        return 1;
    }
    else
    {
        return 0;
    }
}

#ifndef FRAMAC_IGNORE

int RouteSuitabilityData_1_EncodeInt(const RouteSuitabilityData_1* p, kcg_int* startAddress, kcg_int* stream)
{
    stream[(*startAddress)++] = p->D_SUITABILITY;
    stream[(*startAddress)++] = p->Q_SUITABILITY;
    stream[(*startAddress)++] = p->M_LOADINGGAUGE;
    stream[(*startAddress)++] = p->M_AXLELOAD;
    stream[(*startAddress)++] = p->M_TRACTION;

    return 1;
}

int RouteSuitabilityData_1_DecodeInt(RouteSuitabilityData_1* p, kcg_int* startAddress, const kcg_int* stream)
{
    p->D_SUITABILITY = stream[(*startAddress)++];
    p->Q_SUITABILITY = stream[(*startAddress)++];
    p->M_LOADINGGAUGE = stream[(*startAddress)++];
    p->M_AXLELOAD = stream[(*startAddress)++];
    p->M_TRACTION = stream[(*startAddress)++];

    return 1;
}

#endif // FRAMAC_IGNORE

