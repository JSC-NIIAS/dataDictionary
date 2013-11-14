#ifndef NESTINGMARK_oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC
#define NESTINGMARK_oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC
/* =============================================================================
Formalization of Subset-026-8 (Chapter 8: ERTMS/ETCS language)

- Name: Subset-026-8 / Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC
- Description: UNISIG SUBSET-026-8, ISSUE : 3.3.0, 3.5 ERTMS/ETCS language) 
- Copyright (c) Siemens AG, 2013, All Rights Reserved
 	
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



struct DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC {
  int vUsed_idx;                             // aktueller Fuellgrad von aPacket

  struct 
  {
          uint32_t v_TOccurence;            // Zeitpunkt des Empfangs
          uint64_t v_DOccurrence;           // Ort des Empfangs
          uint32_t vState;                  // Bearbeitungszust�nde  
  } info;

  struct 
 { 
// TransmissionMedia=RBC

	uint32_t NID_MESSAGE;                            			// # 8		// int
	uint32_t L_MESSAGE;                              			// # 10		// int
	uint32_t T_TRAIN;                                			// # 32		// real
	uint32_t M_ACK;                                  			// # 1		// enum
	uint32_t NID_LRBG;                               			// # 24		// int
} 


   aPacket[2];       // Instanz der Sturkur mit dem content
};

// struct -> type
typedef struct DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC T_DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC;
// typ -> ptrtyp
typedef  T_DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC* TP_DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC;
// declaration of variable of ptrtyp
extern TP_DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC  oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC;
// instatiate this ptrtype variable like this: (get memory and fill memory)
// TP_DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC  oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC = new(T_DATA_oETCS_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC);
// and now fill in the content to start with ...
// Access variable like this: oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC->...
// maybe : memset(oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC, 0, sizeof(T_DATA_oETCS_Packet_Radio_TrackToTrain_SoM_position_report_confirmed_by_RBC));
// for complete 0 content.

#endif

