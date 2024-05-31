#ifndef _LED_Type4RGBTable_H_
#define _LED_Type4RGBTable_H_

/*_____ D E F I N I T I O N S ______________________________________________*/


	//---------------------------------------------------------------------
	//															
	//				Type4 RGB Anod Control Table														
	//														
	//---------------------------------------------------------------------
	//Address 0x00 bits[7:0] / 0x01 bits[3:0] => Red	 D1~D12
	//Address 0x01 bits[7:4] / 0x02 bits[7:0] => Green D1~D12	
	//Address 0x03 bits[7:0] / 0x04 bits[3:0] => Blue	 D1~D12
	//---------------------------------------------------------------------
	//Address 0x04 bits[7:4] / 0x05 bits[7:0] => Red	 D13~D24
	//Address 0x06 bits[7:0] / 0x07 bits[3:0] => Green D13~D24	
	//Address 0x07 bits[7:4] / 0x08 bits[7:0] => Blue	 D13~D24
	//----------------------------------------------------------------------
	//Address 0x09 bits[7:0] / 0x0A bits[3:0] => Red	 D25~D36
	//Address 0x0A bits[7:4] / 0x0B bits[7:0] => Green D25~D36	
	//Address 0x0C bits[7:0] / 0x0D bits[3:0] => Blue	 D25~D36	
	//---------------------------------------------------------------------
	//Address 0x0D bits[7:4] / 0x0E bits[7:0] => Red	 D37~D48
	//Address 0x0F bits[7:0] / 0x10 bits[3:0] => Green D37~D48	
	//Address 0x10 bits[7:4] / 0x11 bits[7:0] => Blue	 D37~D48
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	//LUT for Frame1Page : LED Control and Blink Control Ram 
	//Notice: This Table setting the R/G/B LEDs mapping value,
	//				Setting start Address from 0x00 to 0x11 : LED Control Ram
	//				Setting start Address from 0x12 to 0x23 : Blink Control Ram
	//----------------------------------------------------------------------
		
const uint8_t tabLED_Type4CTLAnodeRed[18] = { //Reference SLED1735 Datasheet Type4 Map
																0xFF,	0x0F, 0x00,	//Address 0x00 bits[7:0] / 0x01 bits[3:0] / 0x02 					 => Red	 D1~D12
																0x00, 0xF0, 0xFF,	//Address 0x03					 / 0x04 bits[7:4] / 0x05 bits[7:0] => Red	 D13~D24
																0x00, 0x00, 0x00,	//Address 0x06					 / 0x07 				  / 0x08 
																0xFF, 0x0F, 0x00,	//Address 0x09 bits[7:0] / 0x0A bits[3:0] / 0x0B					 => Red	 D25~D36
																0x00, 0xF0, 0xFF,	//Address 0x0C					 / 0x0D bits[7:4] / 0x0E bits[7:0] => Red	 D37~D48
																0x00, 0x00, 0x00,	//Address 0x0F					 / 0x10 				  / 0x11 
															};

const uint8_t tabLED_Type4CTLAnodeGreen[18] = { //Reference SLED1735 Datasheet Type4 Map
																0x00,	0xF0, 0xFF,	//Address 0x00					 / 0x01 bits[7:4] / 0x02 bits[7:0] => Green D1~D12	
																0x00, 0x00, 0x00,	//Address 0x03					 / 0x04 				  / 0x05 
																0xFF, 0x0F, 0x00,	//Address 0x06 bits[7:0] / 0x07 bits[3:0] / 0x08					 => Green D13~D24	
																0x00, 0xF0, 0xFF,	//Address 0x09					 / 0x0A bits[7:4] / 0x0B bits[7:0] => Green D25~D36
																0x00, 0x00, 0x00,	//Address 0x0C					 / 0x0D 				  / 0x0E 
																0xFF, 0x0F, 0x00,	//Address 0x0F bits[7:0] / 0x10 bits[3:0] / 0x11					 => Green D37~D48	
															};															
															
const uint8_t tabLED_Type4CTLAnodeBlue[18] = { //Reference SLED1735 Datasheet Type4 Map
																0x00,	0x00, 0x00,	//Address 0x00					 / 0x01 					/ 0x02
																0xFF, 0x0F, 0x00,	//Address 0x03 bits[7:0] / 0x04 bits[3:0] / 0x05					 => Blue	 D1~D12	
																0x00, 0xF0, 0xFF,	//Address 0x06					 / 0x07 bits[7:4] / 0x08 bits[7:0] => Blue	 D13~D24
																0x00, 0x00, 0x00, //Address 0x09					 / 0x0A 				  / 0x0B 
																0xFF, 0x0F, 0x00,	//Address 0x0C bits[7:0] / 0x0D bits[3:0] / 0x0E					 => Blue	 D25~D36
																0x00, 0xF0, 0xFF,	//Address 0x0F					 / 0x10 bits[7:4] / 0x11 bits[7:0] => Blue	 D37~D48	
															};		
																													
//Table Index means the number of LED, and the data of table means PWM control ram address															
const uint8_t tabLED_Type4PWMCTLAnodeRed[48] = { //Reference SLED1735 Datasheet Type4 Map
																0x24,	0x25, 0x26, 0x27, 0x28, 0x29,	0x2A, 0x2B, 0x2C,	0x2D, 0x2E, 0x2F,	// Red D1~D12 PWM CTL Mapping address
																0x48,	0x49, 0x4A, 0x4B, 0x4C, 0x4D,	0x4E, 0x4F, 0x50,	0x51, 0x52, 0x53,	// Red D13~D24 PWM CTL Mapping address
																0x6C,	0x6D, 0x6E, 0x6F, 0x70, 0x71,	0x72, 0x73, 0x74,	0x75, 0x76, 0x77,	// Red D25~D36 PWM CTL Mapping address
																0x90,	0x91, 0x92, 0x93, 0x94, 0x95,	0x96, 0x97, 0x98,	0x99, 0x9A, 0x9B,	// Red D25~D36 PWM CTL Mapping address
															};							

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type4PWMCTLAnodeGreen[48] = { //Reference SLED1735 Datasheet Type4 Map
																0x30,	0x31, 0x32, 0x33, 0x34, 0x35,	0x36, 0x37, 0x38,	0x39, 0x3A, 0x3B,	// Green D1~D12 PWM CTL Mapping address
																0x54,	0x55, 0x56, 0x57, 0x58, 0x59,	0x5A, 0x5B, 0x5C,	0x5D, 0x5E, 0x5F,	// Green D13~D24 PWM CTL Mapping address
																0x78,	0x79, 0x7A, 0x7B, 0x7C, 0x7D,	0x7E, 0x7F, 0x80,	0x81, 0x82, 0x83,	// Green D25~D36 PWM CTL Mapping address
																0x9C,	0x9D, 0x9E, 0x9F, 0xA0, 0xA1,	0xA2, 0xA3, 0xA4,	0xA5, 0xA6, 0xA7,	// Green D25~D36 PWM CTL Mapping address
															};															

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type4PWMCTLAnodeBlue[48] = { //Reference SLED1735 Datasheet Type4 Map
																0x3C,	0x3D, 0x3E, 0x3F, 0x40, 0x41,	0x42, 0x43, 0x44,	0x45, 0x46, 0x47,	// Blue D1~D12 PWM CTL Mapping address
																0x60,	0x61, 0x62, 0x63, 0x64, 0x65,	0x66, 0x67, 0x68,	0x69, 0x6A, 0x6B,	// Blue D13~D24 PWM CTL Mapping address
																0x84,	0x85, 0x86, 0x87, 0x88, 0x89,	0x8A, 0x8B, 0x8C,	0x8D, 0x8E, 0x8F,	// Blue D25~D36 PWM CTL Mapping address
																0xA8,	0xA9, 0xAA, 0xAB, 0xAC, 0xAD,	0xAE, 0xAF, 0xB0,	0xB1, 0xB2, 0xB3,	// Blue D25~D36 PWM CTL Mapping address
															};		

	//---------------------------------------------------------------------
	//															
	//				Type4 RGB Cathode Control Table														
	//														
	//---------------------------------------------------------------------
	//Address 0x00 bits[6][3][0] / 0x01 bits[7][4][1] / 0x02 bits[5][2]	   => Red	 	 D1~D8
	//Address 0x00 bits[7][4][1] / 0x01 bits[5][2] 		/ 0x02 bits[6][3][0] => Green	 D1~D8
	//Address 0x00 bits[5][2] 	 / 0x01 bits[6][3][0] / 0x02 bits[7][4][1] => Blue	 D1~D8	
	//---------------------------------------------------------------------
	//Address 0x03 bits[6][3][0] / 0x04 bits[7][4][1] / 0x05 bits[5][2]	   => Red	   D9~D16
	//Address 0x03 bits[7][4][1] / 0x04 bits[5][2] 		/ 0x05 bits[6][3][0] => Green	 D9~D16
	//Address 0x03 bits[5][2] 	 / 0x04 bits[6][3][0] / 0x05 bits[7][4][1] => Blue	 D9~D16	
	//----------------------------------------------------------------------
	//Address 0x06 bits[6][3][0] / 0x07 bits[7][4][1] / 0x08 bits[5][2]	   => Red	   D17~24
	//Address 0x06 bits[7][4][1] / 0x07 bits[5][2] 		/ 0x08 bits[6][3][0] => Green	 D17~D24	
	//Address 0x06 bits[5][2] 	 / 0x07 bits[6][3][0] / 0x08 bits[7][4][1] => Blue	 D17~D24
	//---------------------------------------------------------------------
	//Address 0x09 bits[6][3][0] / 0x0A bits[7][4][1] / 0x0B bits[5][2]	   => Red	   D25~32
	//Address 0x09 bits[7][4][1] / 0x0A bits[5][2] 		/ 0x0B bits[6][3][0] => Green	 D25~D32
	//Address 0x09 bits[5][2] 	 / 0x0A bits[6][3][0] / 0x0B bits[7][4][1] => Blue	 D25~D32
	//---------------------------------------------------------------------
	//Address 0x0C bits[6][3][0] / 0x0D bits[7][4][1] / 0x0E bits[5][2]	   => Red	   D33~D40
	//Address 0x0C bits[7][4][1] / 0x0D bits[5][2] 		/ 0x0E bits[6][3][0] => Green	 D33~D40
	//Address 0x0C bits[5][2] 	 / 0x0D bits[6][3][0] / 0x0E bits[7][4][1] => Blue	 D33~D40
	//---------------------------------------------------------------------
	//Address 0x0F bits[6][3][0] / 0x10 bits[7][4][1] / 0x11 bits[5][2]	   => Red	   D41~D48
	//Address 0x0F bits[7][4][1] / 0x10 bits[5][2] 		/ 0x11 bits[6][3][0] => Green	 D41~D48	
	//Address 0x0F bits[5][2] 	 / 0x10 bits[6][3][0] / 0x11 bits[7][4][1] => Blue	 D41~d48	
	//---------------------------------------------------------------------
	//---------------------------------------------------------------------
	//LUT for Frame1Page : LED Control and Blink Control Ram 
	//Notice: This Table setting the R/G/B LEDs mapping value,
	//				Setting start Address from 0x00 to 0x11 : LED Control Ram
	//				Setting start Address from 0x12 to 0x23 : Blink Control Ram
	//----------------------------------------------------------------------													
const uint8_t tabLED_Type4CTLCathodeRed[18] = { //Reference SLED1735 Datasheet Type4 Map
																0x49,	0x92, 0x24,	//Address 0x00 bits[6][3][0] / 0x01 bits[7][4][1] / 0x02 bits[5][2]	   => Red	  D1~D8
																0x49,	0x92, 0x24,	//Address 0x03 bits[6][3][0] / 0x04 bits[7][4][1] / 0x05 bits[5][2]	   => Red	  D9~D16
																0x49,	0x92, 0x24,	//Address 0x06 bits[6][3][0] / 0x07 bits[7][4][1] / 0x08 bits[5][2]	   => Red	  D17~24
																0x49,	0x92, 0x24,	//Address 0x09 bits[6][3][0] / 0x0A bits[7][4][1] / 0x0B bits[5][2]	   => Red	  D25~32
																0x49,	0x92, 0x24,	//Address 0x0C bits[6][3][0] / 0x0D bits[7][4][1] / 0x0E bits[5][2]	   => Red	  D33~D40
																0x49,	0x92, 0x24,	//Address 0x0F bits[6][3][0] / 0x10 bits[7][4][1] / 0x11 bits[5][2]	   => Red	  D41~D48
															};

const uint8_t tabLED_Type4CTLCathodeGreen[18] = { //Reference SLED1735 Datasheet Type4 Map
																0x92,	0x24, 0x49,	//Address 0x00 bits[7][4][1] / 0x01 bits[5][2] 		/ 0x02 bits[6][3][0] => Green	 D1~D8
																0x92,	0x24, 0x49,	//Address 0x03 bits[7][4][1] / 0x04 bits[5][2] 		/ 0x05 bits[6][3][0] => Green	 D9~D16
																0x92,	0x24, 0x49,	//Address 0x06 bits[7][4][1] / 0x07 bits[5][2] 		/ 0x08 bits[6][3][0] => Green	 D17~D24
																0x92,	0x24, 0x49,	//Address 0x09 bits[7][4][1] / 0x0A bits[5][2] 		/ 0x0B bits[6][3][0] => Green	 D25~D32
																0x92,	0x24, 0x49,	//Address 0x0C bits[7][4][1] / 0x0D bits[5][2] 		/ 0x0E bits[6][3][0] => Green	 D33~D40
																0x92,	0x24, 0x49,	//Address 0x0F bits[7][4][1] / 0x10 bits[5][2] 		/ 0x11 bits[6][3][0] => Green	 D41~D48
															};															
															
const uint8_t tabLED_Type4CTLCathodeBlue[18] = { //Reference SLED1735 Datasheet Type4 Map
																0x24,	0x49, 0x92,	//Address 0x00 bits[5][2] 	 / 0x01 bits[6][3][0] / 0x02 bits[7][4][1] => Blue	 D1~D8	
																0x24,	0x49, 0x92,	//Address 0x03 bits[5][2] 	 / 0x04 bits[6][3][0] / 0x05 bits[7][4][1] => Blue	 D9~D16	
																0x24,	0x49, 0x92,	//Address 0x06 bits[5][2] 	 / 0x07 bits[6][3][0] / 0x08 bits[7][4][1] => Blue	 D17~D24
																0x24,	0x49, 0x92, //Address 0x09 bits[5][2] 	 / 0x0A bits[6][3][0] / 0x0B bits[7][4][1] => Blue	 D25~D32
																0x24,	0x49, 0x92,	//Address 0x0C bits[5][2] 	 / 0x0D bits[6][3][0] / 0x0E bits[7][4][1] => Blue	 D33~D40
																0x24,	0x49, 0x92,	//Address 0x0F bits[5][2] 	 / 0x10 bits[6][3][0] / 0x11 bits[7][4][1] => Blue	 D41~d48	
															};																
																																																			
//Table Index means the number of LED, and the data of table means PWM control ram address															
const uint8_t tabLED_Type4PWMCTLCathodeRed[48] = { //Reference SLED1735 Datasheet Type4 Map
																0x24,	0x27, 0x2A, 0x2D, 0x30, 0x33,	0x36, 0x39, 0x3C,	0x3F, 0x42, 0x45,	// Red D1~D12 PWM CTL Mapping address
																0x48,	0x4B, 0x4E, 0x51, 0x54, 0x57,	0x5A, 0x5D, 0x60,	0x63, 0x66, 0x69,	// Red D13~D24 PWM CTL Mapping address
																0x6C,	0x6F, 0x72, 0x75, 0x78, 0x7B,	0x7E, 0x81, 0x84,	0x87, 0x8A, 0x8D,	// Red D25~D36 PWM CTL Mapping address
																0x90,	0x93, 0x96, 0x99, 0x9C, 0x9F,	0xA2, 0xA5, 0xA8,	0xAB, 0xAE, 0xB1,	// Red D25~D36 PWM CTL Mapping address
															};							

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type4PWMCTLCathodeGreen[48] = { //Reference SLED1735 Datasheet Type4 Map
																0x25,	0x28, 0x2B, 0x2E, 0x31, 0x34,	0x37, 0x3A, 0x3D,	0x40, 0x43, 0x46,	// Green D1~D12 PWM CTL Mapping address
																0x49,	0x4C, 0x4F, 0x52, 0x55, 0x58,	0x5B, 0x5E, 0x61,	0x64, 0x67, 0x6A,	// Green D13~D24 PWM CTL Mapping address
																0x6D,	0x70, 0x73, 0x76, 0x79, 0x7C,	0x7F, 0x82, 0x85,	0x88, 0x8B, 0x8E,	// Green D25~D36 PWM CTL Mapping address
																0x91,	0x94, 0x97, 0x9A, 0x9D, 0xA0,	0xA3, 0xA6, 0xA9,	0xAC, 0xAF, 0xB2,	// Green D25~D36 PWM CTL Mapping address
															};															

//Table Index means the number of LED, and the data of table means PWM control ram address																	
const uint8_t tabLED_Type4PWMCTLCathodeBlue[48] = { //Reference SLED1735 Datasheet Type4 Map
																0x26,	0x29, 0x2C, 0x2F, 0x32, 0x35,	0x38, 0x3B, 0x3E,	0x41, 0x44, 0x47,	// Blue D1~D12 PWM CTL Mapping address
																0x4A,	0x4D, 0x50, 0x53, 0x56, 0x59,	0x5C, 0x5F, 0x62,	0x65, 0x68, 0x6B,	// Blue D13~D24 PWM CTL Mapping address
																0x6E,	0x71, 0x74, 0x77, 0x7A, 0x7D,	0x80, 0x83, 0x86,	0x89, 0x8C, 0x8F,	// Blue D25~D36 PWM CTL Mapping address
																0x92,	0x95, 0x98, 0x9B, 0x9E, 0xA1,	0xA4, 0xA7, 0xAA,	0xAD, 0xB0, 0xB3,	// Blue D25~D36 PWM CTL Mapping address
															};																	
														
#endif	/*__SN32F240_LED_Type4RGBTable_H*/
