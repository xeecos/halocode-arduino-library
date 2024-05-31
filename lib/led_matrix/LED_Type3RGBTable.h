#ifndef _LED_Type3RGBTable_H_
#define _LED_Type3RGBTable_H_

/*_____ D E F I N I T I O N S ______________________________________________*/


	//---------------------------------------------------------------------
	//															
	//				Type3 RGB Anode Control Table														
	//														
	//---------------------------------------------------------------------
	//Address 0x00 bits[7:2] 			/ 0x01 bits[7:0] 				=> Red	 D1~D14
	//Address 0x02 bits[7:2] 			/ 0x03 bits[7:0] 				=> Green	 D1~D14	
	//Address 0x04 bits[7:2] 			/ 0x05 bits[7:0] 				=> Blue	 D1~D14
	//---------------------------------------------------------------------
	//Address 0x06 bits[7:5][2:0] / 0x07 bits[7:0] 				=> Red	 D15~D28
	//Address 0x08 bits[7:5][2:0] / 0x09 bits[7:0] 				=> Green	 D15~D28	
	//Address 0x0A bits[7:5][2:0] / 0x0B bits[7:0] 				=> Blue	 D15~D28
	//---------------------------------------------------------------------
	//Address 0x0C bits[5:0]			/ 0x0D bits[7:0] 				=> Red	 D29~D42
	//Address 0x0E bits[5:0]			/ 0x0F bits[7:0] 				=> Green	 D29~D42	
	//Address 0x00 bits[5:0]			/ 0x01bits[7:0] 				=> Blue	 D29~D42
	//----------------------------------------------------------------------
	//Address 0x02 bits[7:0] 			/	0x03 bits[7:3][0] 		=> Red	 D43~D56	
	//Address 0x04 bits[7:0] 			/ 0x05 bits[7:3][0] 		=> Green	 D43~D56
	//Address 0x06 					 			/ 0x07 bits[7:3][0] 		=> Blue	 D43~D56
	//----------------------------------------------------------------------
	//Address 0x08 bits[7:0]      / 0x09 bits[7:6][3:0] 	=> Red	 D57~D70	
	//Address 0x0A bits[7:0]     	/ 0x0B bits[7:6][3:0] 	=> Green	 D57~D70	
	//Address 0x0C bits[7:0]      / 0x0D bits[7:6][3:0] 	=> Blue	 D57~D70		
	//----------------------------------------------------------------------
	//---------------------------------------------------------------------
	//LUT for Frame1Page : LED Control and Blink Control Ram 
	//Notice: This Table setting the R/G/B LEDs mapping value,
	//				Setting start Address from 0x00 to 0x11 : LED Control Ram
	//				Setting start Address from 0x12 to 0x23 : Blink Control Ram
	//----------------------------------------------------------------------
const uint8_t tabLED_Type3CTLAnodeRed[32] = { //Reference SLED1735 Datasheet Type3 Map
																0xFC,	0xFF, 			//Address 0x00 bits[7:2] 			/ 0x01 bits[7:0] 				=> Red	 D1~D14
																0x00,	0x00,				//Address 0x02 					 			/ 0x03					  
																0x00,	0x00,				//Address 0x04 				 			 	/ 0x05						  
																0xE7,	0xFF,				//Address 0x06 bits[7:5][2:0] / 0x07 bits[7:0] 				=> Red	 D15~D28
																0x00,	0x00,				//Address 0x08					 			/ 0x09						
																0x00,	0x00,				//Address 0x0A				 	 			/ 0x0B		
																0x3F,	0xFF,				//Address 0x0C bits[5:0]			/ 0x0D bits[7:0] 				=> Red	 D29~D42
																0x00,	0x00,				//Address 0x0E 							 	/ 0x0F					  	
																0x00,	0x00,				//Address 0x00					 			/ 0x01
																0xFF,	0xF9,				//Address 0x02 bits[7:0] 			/	0x03 bits[7:3][0] 		=> Red	 D43~D56		
																0x00,	0x00,				//Address 0x04 								/ 0x05	
																0x00,	0x00,				//Address 0x06					 			/ 0x07	
																0xFF,	0xCF,				//Address 0x08 bits[7:0]      / 0x09 bits[7:6][3:0] 	=> Red	 D57~D70		
																0x00,	0x00,				//Address 0x0A					 			/ 0x0B		
																0x00,	0x00,				//Address 0x0C					 			/ 0x0D		
																0x00,	0x00,				//Address 0x0E					 			/ 0x0F	
															};

const uint8_t tabLED_Type3CTLAnodeGreen[32] = { //Reference SLED1735 Datasheet Type3 Map
																0x00,	0x00, 			//Address 0x00 					 			/ 0x01 
																0xFC,	0xFF,				//Address 0x02 bits[7:2] 			/ 0x03 bits[7:0] 				=> Green	 D1~D14
																0x00,	0x00,				//Address 0x04 								/ 0x05					  
																0x00,	0x00,				//Address 0x06 					 			/ 0x07
																0xE7,	0xFF,				//Address 0x08 bits[7:5][2:0] / 0x09 bits[7:0] 				=> Green	 D15~D28
																0x00,	0x00,				//Address 0x0A 					 			/ 0x0B 	
																0x00,	0x00,				//Address 0x0C				 	 			/ 0x0D		
																0x3F,	0xFF,				//Address 0x0E bits[5:0]			/ 0x0F bits[7:0] 				=> Green	 D29~D42	
																0x00,	0x00,				//Address 0x00 								/ 0x01
																0x00,	0x00,				//Address 0x02					 			/ 0x03		
																0xFF,	0xF9,				//Address 0x04 bits[7:0] 			/ 0x05 bits[7:3][0] 		=> Green	 D43~D56		
																0x00,	0x00,				//Address 0x06 								/ 0x07
																0x00,	0x00,				//Address 0x08							 	/ 0x09			
																0xFF,	0xCF,				//Address 0x0A bits[7:0]     	/ 0x0B bits[7:6][3:0] 	=> Green	 D57~D70			
																0x00,	0x00,				//Address 0x0C 								/ 0x0D		
																0x00,	0x00,				//Address 0x0E					 			/ 0x0F		
															};															
															
const uint8_t tabLED_Type3CTLAnodeBlue[32] = { //Reference SLED1735 Datasheet Type3 Map
																0x00,	0x00,				//Address 0x00					 			/ 0x01
																0x00,	0x00,				//Address 0x02					 			/ 0x03
																0xFC,	0xFF, 			//Address 0x04 bits[7:2] 			/ 0x05 bits[7:0] 				=> Blue	 D1~D14
																0x00,	0x00,				//Address 0x06								/ 0x07
																0x00,	0x00,				//Address 0x08 				 	 			/ 0x09						  
																0xE7,	0xFF,				//Address 0x0A bits[7:5][2:0] / 0x0B bits[7:0] 				=> Blue	 D15~D28
																0x00,	0x00,				//Address 0x0C 								/ 0x0D		
																0x00,	0x00,				//Address 0x0E				 	 			/ 0x0F		
																0x3F,	0xFF,				//Address 0x00 bits[5:0]			/ 0x01bits[7:0] 				=> Blue	 D29~D42
																0x00,	0x00,				//Address 0x02 								/ 0x03		
																0x00,	0x00,				//Address 0x04					 			/ 0x05
																0xFF,	0xF9,				//Address 0x06 					 			/ 0x07 bits[7:3][0] 		=> Blue	 D43~D56		
																0x00,	0x00,				//Address 0x08  							/ 0x09	
																0x00,	0x00,				//Address 0x0A					 			/ 0x0B	
																0xFF,	0xCF,				//Address 0x0C bits[7:0]      / 0x0D bits[7:6][3:0] 	=> Blue	 D57~D70	
																0x00,	0x00,				//Address 0x0E  							/ 0x0F		
															};																
const uint8_t tabLED_Type3CTLAnodeBlack[32] = {
																0x00,	0x00,				//Address 0x00					 			/ 0x01
																0x00,	0x00,				//Address 0x02					 			/ 0x03
																0x00,	0x00, 			//Address 0x04 bits[7:2] 			/ 0x05 bits[7:0] 				=> Blue	 D1~D14
																0x00,	0x00,				//Address 0x06								/ 0x07
																0x00,	0x00,				//Address 0x08 				 	 			/ 0x09						  
																0x00,	0x00,				//Address 0x0A bits[7:5][2:0] / 0x0B bits[7:0] 				=> Blue	 D15~D28
																0x00,	0x00,				//Address 0x0C 								/ 0x0D		
																0x00,	0x00,				//Address 0x0E				 	 			/ 0x0F		
																0x00,	0x00,				//Address 0x00 bits[5:0]			/ 0x01bits[7:0] 				=> Blue	 D29~D42
																0x00,	0x00,				//Address 0x02 								/ 0x03		
																0x00,	0x00,				//Address 0x04					 			/ 0x05
																0x00,	0x00,				//Address 0x06 					 			/ 0x07 bits[7:3][0] 		=> Blue	 D43~D56		
																0x00,	0x00,				//Address 0x08  							/ 0x09	
																0x00,	0x00,				//Address 0x0A					 			/ 0x0B	
																0x00,	0x00,				//Address 0x0C bits[7:0]      / 0x0D bits[7:6][3:0] 	=> Blue	 D57~D70	
																0x00,	0x00,				//Address 0x0E  							/ 0x0F		
															};			
//Table Index means the number of LED, and the data of table means PWM control ram address															
const uint8_t tabLED_Type3PWMCTLAnodeRed[70] = { //Reference SLED1735 Datasheet Type3 Map
																0x22,	0x23, 0x24, 0x25, 0x26, 0x27,	0x28, 0x29, 0x2A,	0x2B, 0x2C, 0x2D, 0x2E, 0x2F, // Red D1~D14 PWM CTL Mapping address
																0x50,	0x51, 0x52, 0x55, 0x56, 0x57,	0x58, 0x59, 0x5A,	0x5B, 0x5C, 0x5D, 0x5E, 0x5F,	// Red D15~D28 PWM CTL Mapping address
																0x80,	0x81, 0x82, 0x83, 0x84, 0x85, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D,	0x8E, 0x8F, // Red D29~D42 PWM CTL Mapping address
																0x30,	0x31,	0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,	0x3B, 0x3C, 0x3D, 0x3E, 0x3F, // Red D43~D56 PWM CTL Mapping address
																0x60, 0x61, 0x62, 0x63,	0x64, 0x65, 0x66,	0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6E, 0x6F, // Red D57~D70 PWM CTL Mapping address
															};							

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type3PWMCTLAnodeGreen[70] = { //Reference SLED1735 Datasheet Type3 Map
																0x32, 0x33, 0x34, 0x35,	0x36, 0x37, 0x38,	0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,	// Green D1~D14 PWM CTL Mapping address
																0x60,	0x61, 0x62, 0x65, 0x66, 0x67,	0x68, 0x69, 0x6A,	0x6B, 0x6C, 0x6D, 0x6E, 0x6F,	// Green D15~D28 PWM CTL Mapping address
																0x90,	0x91, 0x92, 0x93, 0x94, 0x95, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,	0x9E, 0x9F, // Green D29~D42 PWM CTL Mapping address
																0x40,	0x41,	0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,	0x4B, 0x4C, 0x4D, 0x4E, 0x4F, // Green D43~D56 PWM CTL Mapping address
																0x70, 0x71, 0x72, 0x73,	0x74, 0x75, 0x76,	0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7E, 0x7F, // Green D57~D70 PWM CTL Mapping address
															};															

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type3PWMCTLAnodeBlue[70] = { //Reference SLED1735 Datasheet Type3 Map
																0x42, 0x43, 0x44,	0x45, 0x46, 0x47,	0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, // Blue D1~D14 PWM CTL Mapping address
																0x70,	0x71, 0x72, 0x75, 0x76, 0x77,	0x78, 0x79, 0x7A,	0x7B, 0x7C, 0x7D, 0x7E, 0x7F,	// Blue D15~D28 PWM CTL Mapping address
																0x20,	0x21, 0x22, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D,	0x2E, 0x2F, // Blue D29~D42 PWM CTL Mapping address
																0x50,	0x51,	0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,	0x5B, 0x5C, 0x5D, 0x5E, 0x5F, // Blue D43~D56 PWM CTL Mapping address
																0x80, 0x81, 0x82, 0x83,	0x84, 0x85, 0x86,	0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8E, 0x8F, // Blue D57~D70 PWM CTL Mapping address
															};																			

	//---------------------------------------------------------------------
	//															
	//				Type3 RGB Cathode Control Table															
	//														
	//---------------------------------------------------------------------
	//Address 0x00 bits[6][3][0] 		/ 0x01 bits[4][1] 			=> Red	 D1~D5
	//Address 0x00 bits[7][4][1] 		/ 0x01 bits[5][2] 			=> Green D1~D5
	//Address 0x00 bits   [5][2] 		/ 0x01 bits[6][3][0] 	 	=> Blue	 D1~D5	
	//---------------------------------------------------------------------
	//Address 0x02 bits[6][3] 	 		/ 0x03 bits[4][1] 			=> Red	 D6~D9
	//Address 0x02 bits[7][4] 	 		/ 0x03 bits[5][2] 			=> Green D6~D9
	//Address 0x03 bits   [5]	   		/ 0x03 bits[6][3][0] 	 	=> Blue	 D6~D9	
	//----------------------------------------------------------------------
	//Address 0x04 bits[6][3][1] 		/ 0x05 bits[4][1] 			=> Red	 D10~D14
	//Address 0x04 bits[7][4][0] 		/ 0x05 bits[5][2] 			=> Green D10~D14
	//Address 0x04 bits   [5][2] 		/ 0x05 bits[6][3][0] 	 	=> Blue	 D10~D14
	//---------------------------------------------------------------------
	//Address 0x06 bits[6][3][1] 		/ 0x07 bits   [4][1] 	 	=> Red	 D15~D19
	//Address 0x06 bits[7][4][2] 		/ 0x07 bits   [5][2] 	 	=> Green D15~D19
	//Address 0x06 bits   [5] 	 		/ 0x07 bits[7][6][3][0] => Blue	 D15~D19
	//---------------------------------------------------------------------
	//Address 0x08 bits[6][1] 	 		/ 0x09 bits[4][1] 	 		=> Red	 D20~D23
	//Address 0x08 bits[7][2] 	 		/ 0x09 bits[5][2] 	 		=> Green D20~D23
	//Address 0x08 bits   [3] 	 		/ 0x09 bits[6][3][0] 	 	=> Blue	 D20~D23
	//---------------------------------------------------------------------
	//Address 0x0A bits[6][4][1] 		/ 0x0B bits[4][1] 	 	 	=> Red	 D24~D28
	//Address 0x0A bits[7][0][2] 		/ 0x0B bits[5][2] 	 	 	=> Green D24~D28
	//Address 0x0A bits   [5][3] 		/ 0x0B bits[6][3][0] 	 	=> Blue	 D24~D28
	//---------------------------------------------------------------------
	//Address 0x0C bits[6][4][1] 		/ 0x0D bits   [4][1] 	 	=> Red	 D29~D33
	//Address 0x0C bits[7][5][2] 		/ 0x0D bits   [5][2] 	  => Green D29~D33
	//Address 0x0C bits      [3] 		/ 0x0D bits[7][6][3][0] => Blue	 D29~D33
	//---------------------------------------------------------------------
	//Address 0x0E bits[4][1] 			/ 0x0F bits[4][1] 	 	 	=> Red	 D34~D37
	//Address 0x0E bits[5][2] 			/ 0x0F bits[5][2] 	 	 	=> Green D34~D37
	//Address 0x0E bits[6][3] 			/ 0x0F bits[6][3] 	 		=> Blue	 D34~D37	
	//---------------------------------------------------------------------
	//Address 0x00 bits[7][4][1] 		/ 0x01 bits[4][1] 	 	 	=> Red 	 D38~D42
	//Address 0x00 bits[0][5][2] 		/ 0x01 bits[5][2] 	 	 	=> Green D38~D42
	//Address 0x00 bits   [6][3] 		/ 0x01 bits[6][3][0] 	 	=> Blue	 D38~D42	
	//---------------------------------------------------------------------
	//Address 0x02 bits[7][4][1] 		/ 0x03 bits[4][1] 	 		=> Red 	 D43~D47
	//Address 0x02 bits		[5][2] 		/ 0x03 bits[5][2][0]	  => Green D43~D47
	//Address 0x02 bits   [6][3] 		/ 0x03 bits[6][3][7]	  => Blue	 D43~D47		
	//---------------------------------------------------------------------
	//Address 0x04 bits[7][4][1] 		/ 0x05 bits[4] 	 	 			=> Red 	 D48~D51
	//Address 0x04 bits		[5][2] 		/ 0x05 bits[5][0] 	 	 	=> Green D48~D51
	//Address 0x04 bits   [6][3] 		/ 0x05 bits[6][1] 	 		=> Blue	 D48~D51		
	//---------------------------------------------------------------------
	//Address 0x06 bits		[7][4][1] / 0x07 bits[4][2] 	 		=> Red	 D52~D56
	//Address 0x06 bits	[0]	 [5][2] / 0x07 bits[5]	 [0] 		=> Green D52~D56
	//Address 0x06 bits   	 [6][3] / 0x07 bits[6][3][1] 		=> Blue	 D52~D56
	//---------------------------------------------------------------------
	//Address 0x08 bits[7][4][1] 		/ 0x09 bits[4][2] 	 		=> Red	 D57~D61
	//Address 0x08 bits		[5][2] 		/ 0x09 bits[5][3][0] 	  => Green D57~D61
	//Address 0x08 bits   [6][3] 		/ 0x09 bits[6][7][1]	  => Blue	 D57~D61
	//---------------------------------------------------------------------
	//Address 0x0A bits[7][4][1] 		/ 0x0B bits[2] 	 				=> Red	 D62~D65
	//Address 0x0A bits		[5][2] 		/ 0x0B bits[3][0] 			=> Green D62~D65
	//Address 0x0A bits   [6][3] 		/ 0x0B bits[4][1] 			=> Blue	 D62~D65	
	//---------------------------------------------------------------------
	//Address 0x0C bits		[7][4][1] / 0x0D bits[5][2] 	 		=> Red	 D66~D70
	//Address 0x0C bits[0]	 [5][2] / 0x0D bits		[3][0] 	 	=> Green D66~D70
	//Address 0x0C bits      [6][3] / 0x0D bits[6][4][1]	 	=> Blue	 D66~D70
	//---------------------------------------------------------------------
	//Address 0x08 bits[7][4][1] 		/ 0x09 bits[5][2] 	 		=> Red	 D71~D75
	//Address 0x08 bits		[5][2] 		/ 0x09 bits[6][3][0] 	  => Green D71~D75
	//Address 0x08 bits   [6][3] 		/ 0x09 bits[7][4][1]	  => Blue	 D71~D75

	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	//LUT for Frame1Page : LED Control and Blink Control Ram 
	//Notice: This Table setting the R/G/B LEDs mapping value,
	//				Setting start Address from 0x00 to 0x11 : LED Control Ram
	//				Setting start Address from 0x12 to 0x23 : Blink Control Ram
	//----------------------------------------------------------------------															
const uint8_t tabLED_Type3CTLCathodeRed[32] = { //Reference SLED1735 Datasheet Type3 Map
																0x49,	0x12, 			//Address 0x00 bits[6][3][0] 		/ 0x01 bits[4][1] 			=> Red	 D1~D5
																0x48,	0x12,				//Address 0x02 bits[6][3] 	 		/ 0x03 bits[4][1] 			=> Red	 D6~D9
																0x4A,	0x12,				//Address 0x04 bits[6][3][1] 		/ 0x05 bits[4][1] 			=> Red	 D10~D14
																0x4A,	0x12,				//Address 0x06 bits[6][3][1] 		/ 0x07 bits   [4][1] 	 	=> Red	 D15~D19
																0x42,	0x12,				//Address 0x08 bits[6][1] 	 		/ 0x09 bits[4][1] 	 		=> Red	 D20~D23
																0x52,	0x12,				//Address 0x0A bits[6][4][1] 		/ 0x0B bits[4][1] 	 	 	=> Red	 D24~D28
																0x52,	0x12,				//Address 0x0C bits[6][4][1] 		/ 0x0D bits   [4][1] 	 	=> Red	 D29~D33
																0x12,	0x12,				//Address 0x0E bits[4][1] 			/ 0x0F bits[4][1] 	 	 	=> Red	 D34~D37
																0x92,	0x12,				//Address 0x00 bits[7][4][1] 		/ 0x01 bits[4][1] 	 	 	=> Red 	 D38~D42
																0x92,	0x12,				//Address 0x02 bits[7][4][1] 		/ 0x03 bits[4][1] 	 		=> Red 	 D43~D47	
																0x92,	0x10,				//Address 0x04 bits[7][4][1] 		/ 0x05 bits[4] 	 	 			=> Red 	 D48~D51	
																0x92,	0x14,				//Address 0x06 bits		[7][4][1] / 0x07 bits[4][2] 	 		=> Red	 D52~D56
																0x92,	0x14,				//Address 0x08 bits[7][4][1] 		/ 0x09 bits[4][2] 	 		=> Red	 D57~D61		
																0x92,	0x04,				//Address 0x0A bits[7][4][1] 		/ 0x0B bits[2] 	 				=> Red	 D62~D65
																0x92,	0x24,				//Address 0x0C bits		[7][4][1] / 0x0D bits[5][2] 	 		=> Red	 D66~D70
																0x92,	0x24,				//Address 0x08 bits[7][4][1] 		/ 0x09 bits[5][2] 	 		=> Red	 D71~D75
															};

const uint8_t tabLED_Type3CTLCathodeGreen[32] = { //Reference SLED1735 Datasheet Type3 Map
																0x92,	0x24, 			//Address 0x00 bits[7][4][1] 		/ 0x01 bits[5][2] 			=> Green D1~D5
																0x90,	0x24,				//Address 0x02 bits[7][4] 	 		/ 0x03 bits[5][2] 			=> Green D6~D9
																0x91,	0x24,				//Address 0x04 bits[7][4][0] 		/ 0x05 bits[5][2] 			=> Green D10~D14
																0x94,	0x24,				//Address 0x06 bits[7][4][2] 		/ 0x07 bits   [5][2] 	 	=> Green D15~D19
																0x84,	0x24,				//Address 0x08 bits[7][2] 	 		/ 0x09 bits[5][2] 	 		=> Green D20~D23
																0x85,	0x24,				//Address 0x0A bits[7][0][2] 		/ 0x0B bits[5][2] 	 	 	=> Green D24~D28
																0xA4,	0x24,				//Address 0x0C bits[7][5][2] 		/ 0x0D bits   [5][2] 	  => Green D29~D33
																0x24,	0x24,				//Address 0x0E bits[5][2] 			/ 0x0F bits[5][2] 	 	 	=> Green D34~D37
																0x25,	0x24,				//Address 0x00 bits[0][5][2] 		/ 0x01 bits[5][2] 	 	 	=> Green D38~D42
																0x24,	0x25,				//Address 0x02 bits		[5][2] 		/ 0x03 bits[5][2][0]	  => Green D43~D47
																0x24,	0x21,				//Address 0x04 bits		[5][2] 		/ 0x05 bits[5][0] 	 	 	=> Green D48~D51	
																0x25,	0x21,				//Address 0x06 bits	[0]	 [5][2] / 0x07 bits[5]	 [0] 		=> Green D52~D56
																0x24,	0x29,				//Address 0x08 bits		[5][2] 		/ 0x09 bits[5][3][0] 	  => Green D57~D61
																0x24,	0x09,				//Address 0x0A bits		[5][2] 		/ 0x0B bits[3][0] 			=> Green D62~D65			
																0x25,	0x09,				//Address 0x0C bits[0]	 [5][2] / 0x0D bits		[3][0] 	 	=> Green D66~D70			
																0x24,	0x49,				//Address 0x08 bits		[5][2] 		/ 0x09 bits[6][3][0] 	  => Green D71~D75
															};															
															
const uint8_t tabLED_Type3CTLCathodeBlue[32] = { //Reference SLED1735 Datasheet Type3 Map
																0x24,	0x49,				//Address 0x00 bits   [5][2] 		/ 0x01 bits[6][3][0] 	 	=> Blue	 D1~D5	
																0x20,	0x49,				//Address 0x03 bits   [5]	   		/ 0x03 bits[6][3][0] 	 	=> Blue	 D6~D9
																0x24,	0x49, 			//Address 0x04 bits   [5][2] 		/ 0x05 bits[6][3][0] 	 	=> Blue	 D10~D14
																0x20,	0xC9,				//Address 0x06 bits   [5] 	 		/ 0x07 bits[7][6][3][0] => Blue	 D15~D19
																0x08,	0x49,				//Address 0x08 bits   [3] 	 		/ 0x09 bits[6][3][0] 	 	=> Blue	 D20~D23
																0x28,	0x49,				//Address 0x0A bits   [5][3] 		/ 0x0B bits[6][3][0] 	 	=> Blue	 D24~D28
																0x08,	0xC9,				//Address 0x0C bits      [3] 		/ 0x0D bits[7][6][3][0] => Blue	 D29~D33
																0x48,	0x48,				//Address 0x0E bits[6][3] 			/ 0x0F bits[6][3] 	 		=> Blue	 D34~D37
																0x48,	0x49,				//Address 0x00 bits   [6][3] 		/ 0x01 bits[6][3][0] 	 	=> Blue	 D38~D42	
																0x48,	0xC8,				//Address 0x02 bits   [6][3] 		/ 0x03 bits[6][3][7]	  => Blue	 D43~D47
																0x48,	0x42,				//Address 0x04 bits   [6][3] 		/ 0x05 bits[6][1] 	 		=> Blue	 D48~D51
																0x48,	0x4A,				//Address 0x06 bits   	 [6][3] / 0x07 bits[6][3][1] 		=> Blue	 D52~D56	
																0x48,	0xC2,				//Address 0x08 bits   [6][3] 		/ 0x09 bits[6][7][1]	  => Blue	 D57~D61		
																0x48,	0x12,				//Address 0x0A bits   [6][3] 		/ 0x0B bits[4][1] 			=> Blue	 D62~D65
																0x48,	0x52,				//Address 0x0C bits      [6][3] / 0x0D bits[6][4][1]	 	=> Blue	 D66~D70	
																0x48,	0x92,				//Address 0x08 bits   [6][3] 		/ 0x09 bits[7][4][1]	  => Blue	 D71~D75	
															};			

//Table Index means the number of LED, and the data of table means PWM control ram address															
const uint8_t tabLED_Type3PWMCTLCathodeRed[75] = { //Reference SLED1735 Datasheet Type3 Map
																0x20,	0x23, 0x26, 0x29, 0x2C, 0x33,	0x36, 0x39, 0x3C,	0x41, 0x43, 0x46, 0x49, 0x4C, 0x51,	// Red D1~D15 PWM CTL Mapping address
																0x53,	0x56, 0x59, 0x5C, 0x61, 0x66,	0x69, 0x6C, 0x71,	0x74, 0x76, 0x79, 0x7C, 0x81, 0x84,	// Red D16~D30 PWM CTL Mapping address
																0x86,	0x89, 0x8C, 0x91, 0x94, 0x99,	0x9C, 0x21, 0x24,	0x27, 0x29, 0x2C,	0x31, 0x34, 0x37, // Red D31~D45 PWM CTL Mapping address
																0x39,	0x3C, 0x41, 0x44, 0x47, 0x4C,	0x51, 0x54, 0x57,	0x5A, 0x5C, 0x61, 0x64, 0x67, 0x6A,	// Red D46~D60 PWM CTL Mapping address
																0x6C,	0x71, 0x74, 0x77, 0x7A, 0x81,	0x84, 0x87, 0x8A,	0x8D, 0x91, 0x94, 0x97, 0x9A, 0x9D	// Red D61~D75 PWM CTL Mapping address
															};							

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type3PWMCTLCathodeGreen[75] = { //Reference SLED1735 Datasheet Type3 Map
																0x21, 0x24, 0x27, 0x2A,	0x2D, 0x34, 0x37,	0x3A, 0x3D, 0x40, 0x44, 0x47, 0x4A, 0x4D, 0x52,	// Green D1~D15 PWM CTL Mapping address
																0x54,	0x57, 0x5A, 0x5D, 0x62,	0x67, 0x6A, 0x6D,	0x72, 0x70, 0x77,	0x7A, 0x7D, 0x82, 0x85, // Green D16~D30 PWM CTL Mapping address
																0x87,	0x8A, 0x8D, 0x92, 0x95, 0x9A,	0x9D, 0x22, 0x25,	0x20, 0x2A, 0x2D,	0x32, 0x35, 0x38, // Green D31~D45 PWM CTL Mapping address
																0x3A,	0x3D, 0x42, 0x45, 0x48, 0x4D,	0x52, 0x55, 0x58,	0x50, 0x5D, 0x62, 0x65, 0x68, 0x6B,	// Green D46~D60 PWM CTL Mapping address
																0x6D,	0x72, 0x75, 0x78, 0x7B, 0x82,	0x85, 0x88, 0x8B,	0x80, 0x92, 0x95, 0x98, 0x9B, 0x9E	// Green D61~D75 PWM CTL Mapping address
															};															

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type3PWMCTLCathodeBlue[75] = { //Reference SLED1735 Datasheet Type3 Map
																0x22, 0x25, 0x28,	0x2B, 0x2E, 0x35,	0x38, 0x3B, 0x3E, 0x42, 0x45, 0x48, 0x4B, 0x4E, 0x5F, // Blue D1~D15 PWM CTL Mapping address
																0x55,	0x58, 0x5B, 0x5E, 0x63,	0x68, 0x6B, 0x6E,	0x73, 0x75, 0x78,	0x7B, 0x7E, 0x83, 0x8F,	// Blue D16~D30 PWM CTL Mapping address
																0x88,	0x8B, 0x8E, 0x93, 0x96, 0x9B,	0x9E, 0x23, 0x26,	0x28, 0x2B, 0x2E,	0x33, 0x36, 0x3F, // Blue D31~D45 PWM CTL Mapping address
																0x3B,	0x3E, 0x43, 0x46, 0x49, 0x4E,	0x53, 0x56, 0x59,	0x5B, 0x5E, 0x63, 0x66, 0x69, 0x6F,	// Blue D46~D60 PWM CTL Mapping address
															  0x6E,	0x73, 0x76, 0x79, 0x7C, 0x83,	0x86, 0x89, 0x8C,	0x8E, 0x93, 0x96, 0x99, 0x9C, 0x9F	// Blue D61~D75 PWM CTL Mapping address
															};				

#endif	/*__SN32F240_LED_Type3RGBTable_H*/
