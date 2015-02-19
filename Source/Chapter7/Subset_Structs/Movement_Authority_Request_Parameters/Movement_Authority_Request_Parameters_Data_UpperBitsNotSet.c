
#include "Movement_Authority_Request_Parameters_Data_UpperBitsNotSet.h"
#include "UpperBitsNotSet.h"

int Movement_Authority_Request_Parameters_Data_UpperBitsNotSet(const Movement_Authority_Request_Parameters_Data* p)
{
    if (UpperBitsNotSet64(p->Q_DIR,             2)   &&
        UpperBitsNotSet64(p->T_MAR,             8)   &&
        UpperBitsNotSet64(p->T_TIMEOUTRQST,     10)  &&
        UpperBitsNotSet64(p->T_CYCRQST,         8))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

