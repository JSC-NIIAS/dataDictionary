
#ifndef MOVEMENT_AUTHORITY_REQUEST_PARAMETERS_INIT_H_INCLUDED
#define MOVEMENT_AUTHORITY_REQUEST_PARAMETERS_INIT_H_INCLUDED

#include "Movement_Authority_Request_Parameters.h"

/*@
    requires valid:  \valid(p);

    assigns  *p;
 
    ensures  invariant: Invariant(p);
    ensures  init:      ZeroInitialized(p);
*/
void Movement_Authority_Request_Parameters_Init(Movement_Authority_Request_Parameters* p);


#endif // MOVEMENT_AUTHORITY_REQUEST_PARAMETERS_INIT_H_INCLUDED

