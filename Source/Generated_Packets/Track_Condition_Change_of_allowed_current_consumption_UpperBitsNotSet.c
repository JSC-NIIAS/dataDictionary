
#include "Track_Condition_Change_of_allowed_current_consumption_UpperBitsNotSet.h"
#include "UpperBitsNotSet.h"

int Track_Condition_Change_of_allowed_current_consumption_UpperBitsNotSet(const Track_Condition_Change_of_allowed_current_consumption_Core* p)
{
    bool status = true;

    status = status && UpperBitsNotSet64(p->Q_DIR,             2) ;
    status = status && UpperBitsNotSet64(p->L_PACKET,          13);
    status = status && UpperBitsNotSet64(p->Q_SCALE,           2) ;
    status = status && UpperBitsNotSet64(p->D_CURRENT,         15);
    status = status && UpperBitsNotSet64(p->M_CURRENT,         10);

    if (status)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

