#ifndef NESTINGMARK_Radio_Message_TrackToTrain_SR_Authorisation
#define NESTINGMARK_Radio_Message_TrackToTrain_SR_Authorisation
/* =============================================================================
Formalization of Subset-026-8 (Chapter 8: ERTMS/ETCS language)

- Name: Subset-026-7 / TrackToTrain_SR_Authorisation
- Description: UNISIG SUBSET-026-8, ISSUE : 3.3.0, 3.5 ERTMS/ETCS language) 
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

typedef enum { 
	SR_Authorisation_OptionalPacketNumber_63 = 63
} SR_Authorisation_OptionalPackets ;

struct DATA_Radio_TrackToTrain_SR_Authorisation {
  int vUsed_idx;                             // aktueller Fuellgrad von aPacket

  struct 
  {
          uint32_t v_TOccurence;            // Zeitpunkt des Empfangs
          uint64_t v_DOccurrence;           // Ort des Empfangs
          uint32_t vState;                  // Bearbeitungszustaende  
  } info;

  struct 
 { 
// Packet Number = 2

	uint32_t NID_MESSAGE;                     		// # 8		// int
	uint32_t               L_MESSAGE             ;		// # 10		// int
	uint32_t               T_TRAIN               ;		// # 32		// float
	T_m_ack                M_ACK                 ;		// # 1		// enum
	uint32_t               NID_LRBG              ;		// # 24		// int
	T_q_scale              Q_SCALE               ;		// # 2		// enum
	uint32_t               D_SR                  ;		// # 15		// int
	uint32_t               PADDING12             ;		// # 4	
	uint32_t SR_Authorisation_OptionalPackets;		 // # Length is unknown here; depends on current package number(s)


} 


   Message[2];       // Instanz der Sturkur mit dem content
};

// struct -> type
typedef struct DATA_Radio_TrackToTrain_SR_Authorisation T_DATA_Radio_TrackToTrain_SR_Authorisation;
// typ -> ptrtyp
typedef  T_DATA_Radio_TrackToTrain_SR_Authorisation* TP_DATA_Radio_TrackToTrain_SR_Authorisation;
// declaration of variable of ptrtyp
extern TP_DATA_Radio_TrackToTrain_SR_Authorisation  Radio_Packet_TrackToTrain_SR_Authorisation;
// instatiate this ptrtype variable like this: (get memory and fill memory)
// TP_DATA_Radio_TrackToTrain_SR_Authorisation  Radio_Packet_TrackToTrain_SR_Authorisation = new(T_DATA_Radio_TrackToTrain_SR_Authorisation);
// and now fill in the content to start with ...
// Access variable like this: Radio_Packet_TrackToTrain_SR_Authorisation->...
// maybe : memset(Radio_Packet_TrackToTrain_SR_Authorisation, 0, sizeof(T_DATA_Radio_Packet_TrackToTrain_SR_Authorisation));
// for complete 0 content.

#endif


