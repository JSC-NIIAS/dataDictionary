#ifndef NESTINGMARK_oETCS_Packet_TrackToTrain_Level_Transition_Order
#define NESTINGMARK_oETCS_Packet_TrackToTrain_Level_Transition_Order
/* =============================================================================
Formalization of Subset-026-7 (Chapter 7: ERTMS/ETCS language)

- Name: Subset-026-7 / TrackToTrain_Level_Transition_Order
- Description: UNISIG SUBSET-026-7, ISSUE : 3.3.0, 3.5 ERTMS/ETCS language) 
- Copyright (c) Siemens AG, 2014, All Rights Reserved
 	
- Licensed under the EUPL V.1.1 ( http://joinup.ec.europa.eu/software/page/eupl/licence-eupl )
- Gist URL: none
- Cryptography: No
- Author(s): SiemensRailAutomation

Disclaimer:

The use of this software is limited to NON-vital applications. 
It has NOT been developed for vital operation purposes and MUST NOT be used for applications 
which may cause harm to people, physical accidents or financial loss. 

THEREFORE, NO LIABILITY WILL BE GIVEN FOR SUCH AND ANY OTHER KIND OF USE.  	
============================================================================= */
#include <stdint.h>
#include "opnETCS_Variables.h"

struct DATA_oETCS_TrackToTrain_Level_Transition_Order {
  int vUsed_idx;                             // aktueller Fuellgrad von aPacket

  struct 
  {
          uint32_t v_TOccurence;            // Zeitpunkt des Empfangs
          uint64_t v_DOccurrence;           // Ort des Empfangs
          uint32_t vState;                  // Bearbeitungszustaende  
  } info;

  struct 
 { 
// TransmissionMedia=Any
// Packet to identify where a level transition shall take place. In case of mixed levels, the successive M_LEVELTR go from the highest priority level to the lowest one.
// Packet Number = 41

	uint32_t               NID_PACKET;            		// # 8	
	T_q_dir                Q_DIR                 ;		// # 2	
	uint32_t               L_PACKET              ;		// # 13	
	T_q_scale              Q_SCALE               ;		// # 2	
	uint32_t               D_LEVELTR             ;		// # 15	
	T_m_leveltr            M_LEVELTR             ;		// # 3		// if (M_LEVELTR == 1)
	uint32_t               NID_NTC               ;		// # 8		// If  M_LEVELTR = 1  (NTC)
	uint32_t               L_ACKLEVELTR          ;		// # 15	    
        struct {
            uint32_t used;                        //N_ITER+1              // # 5
            struct {

		uint32_t M_LEVELTR;                       		// # 3		// if (M_LEVELTR(k) == 1)
		uint32_t NID_NTC;                         		// # 8		// If M_LEVELTR(k) = 1
		uint32_t L_ACKLEVELTR;                    		// # 15	        
        } a_data[33];
        } k;

} 


   aPacket[2];       // Instanz der Sturkur mit dem content
};

// struct -> type
typedef struct DATA_oETCS_TrackToTrain_Level_Transition_Order T_DATA_oETCS_TrackToTrain_Level_Transition_Order;
// typ -> ptrtyp
typedef  T_DATA_oETCS_TrackToTrain_Level_Transition_Order* TP_DATA_oETCS_TrackToTrain_Level_Transition_Order;
// declaration of variable of ptrtyp
extern TP_DATA_oETCS_TrackToTrain_Level_Transition_Order  oETCS_Packet_TrackToTrain_Level_Transition_Order;
// instatiate this ptrtype variable like this: (get memory and fill memory)
// TP_DATA_oETCS_TrackToTrain_Level_Transition_Order  oETCS_Packet_TrackToTrain_Level_Transition_Order = new(T_DATA_oETCS_TrackToTrain_Level_Transition_Order);
// and now fill in the content to start with ...
// Access variable like this: oETCS_Packet_TrackToTrain_Level_Transition_Order->...
// maybe : memset(oETCS_Packet_TrackToTrain_Level_Transition_Order, 0, sizeof(T_DATA_oETCS_Packet_TrackToTrain_Level_Transition_Order));
// for complete 0 content.

#endif


