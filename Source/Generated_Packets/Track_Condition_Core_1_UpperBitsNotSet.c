
#include "Track_Condition_Core_1_UpperBitsNotSet.h"
#include "UpperBitsNotSet.h"

int Track_Condition_Core_1_UpperBitsNotSet(const Track_Condition_Core_1* p)
{
    if (UpperBitsNotSet64(p->D_TRACKCOND_k,     15)  &&
        UpperBitsNotSet64(p->L_TRACKCOND_k,     15)  &&
        UpperBitsNotSet64(p->M_TRACKCOND_k,     4))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

