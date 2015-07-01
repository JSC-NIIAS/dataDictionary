
#include "International_Static_Speed_Profile_Core_1_UpperBitsNotSet.h"
#include "UpperBitsNotSet.h"

int International_Static_Speed_Profile_Core_1_UpperBitsNotSet(const International_Static_Speed_Profile_Core_1* p)
{
    bool status = true;

    status = status && UpperBitsNotSet64(p->Q_DIFF_n,          2) ;
    if (p->Q_DIFF_n == 0)
    {
    status = status && UpperBitsNotSet64(p->NC_CDDIFF_n,       4) ;
    }
    if ((p->Q_DIFF_n == 1) || (p->Q_DIFF_n == 2))
    {
    status = status && UpperBitsNotSet64(p->NC_DIFF_n,         4) ;
    }
    status = status && UpperBitsNotSet64(p->V_DIFF_n,          7) ;

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

