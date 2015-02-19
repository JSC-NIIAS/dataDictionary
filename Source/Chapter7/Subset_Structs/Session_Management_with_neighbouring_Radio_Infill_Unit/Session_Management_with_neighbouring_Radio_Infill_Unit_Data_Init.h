
#ifndef SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_DATA_INIT_H_INCLUDED
#define SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_DATA_INIT_H_INCLUDED

#include "Session_Management_with_neighbouring_Radio_Infill_Unit_Data.h"

/*@
    requires valid:  \valid(p);

    assigns  *p;
 
    ensures  invariant: Invariant(p);
    ensures  init:      ZeroInitialized(p);
*/
void Session_Management_with_neighbouring_Radio_Infill_Unit_Data_Init(Session_Management_with_neighbouring_Radio_Infill_Unit_Data* p);


#endif // SESSION_MANAGEMENT_WITH_NEIGHBOURING_RADIO_INFILL_UNIT_DATA_INIT_H_INCLUDED

