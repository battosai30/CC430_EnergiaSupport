/*
  ************************************************************************
  *	pins_energia.h
  *
  *	Energia core files for MSP430/CC430
  *		Copyright (c) 2012 Robert Wessels. All right reserved.
  *
  *     Contribution: Yann LEFEBVRE
  *
  ***********************************************************************
  Derived from:
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA
*/

#ifndef Pins_Energia_h
#define Pins_Energia_h
#ifndef BV
#define BV(x) (1 << (x))
#endif

#if defined(__MSP430_HAS_USCI_A0__)

static const uint8_t DEBUG_UARTRXD = 6;  /* Receive  Data (RXD) at P1.5 */
static const uint8_t DEBUG_UARTTXD = 7;  /* Transmit Data (TXD) at P1.6 */

#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)

#endif

#define DEBUG_UART_MODULE_OFFSET 0x0

#if defined(__MSP430_HAS_USCI_B0__)

static const uint8_t SS      = 8 ;  /* P1.7 */
static const uint8_t SCK     = 5;  /* P1.4 */
static const uint8_t MOSI    = 4;  /* P1.3 */
static const uint8_t MISO    = 3;  /* P1.2 */
static const uint8_t TWISDA  = 4;  /* P1.3 */
static const uint8_t TWISCL  = 3;  /* P1.2 */

#define TWISDA_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)
#define TWISCL_SET_MODE  (PORT_SELECTION0 | INPUT_PULLUP)

#define SPISCK_SET_MODE (PORT_SELECTION0)
#define SPIMOSI_SET_MODE (PORT_SELECTION0)
#define SPIMISO_SET_MODE (PORT_SELECTION0)

#endif

/* analog contants */
static const uint8_t A0  = 0;
static const uint8_t A1  = 1;
static const uint8_t A2  = 2;
static const uint8_t A3  = 3;
static const uint8_t A4  = 4;
static const uint8_t A5  = 5;
static const uint8_t A6  = 6;
static const uint8_t A7  = 7;

static const uint8_t TEMPSENSOR = 10 ;

/* digital contants */
static const uint8_t P1_0 = 1;
static const uint8_t P1_1 = 2;
static const uint8_t P1_2 = 3;
static const uint8_t P1_3 = 4;
static const uint8_t P1_4 = 5;
static const uint8_t P1_5 = 6;
static const uint8_t P1_6 = 7;
static const uint8_t P1_7 = 8;

static const uint8_t P2_0 = 9;
static const uint8_t P2_1 = 10;
static const uint8_t P2_2 = 11;
static const uint8_t P2_3 = 12;
static const uint8_t P2_4 = 13;
static const uint8_t P2_5 = 14;
static const uint8_t P2_6 = 15;
static const uint8_t P2_7 = 16;

#ifdef __MSP430_HAS_PORT3_R__
static const uint8_t P3_0 = 17;
static const uint8_t P3_1 = 18;
static const uint8_t P3_2 = 19;
static const uint8_t P3_3 = 20;
static const uint8_t P3_4 = 21;
static const uint8_t P3_5 = 22;
static const uint8_t P3_6 = 23;
static const uint8_t P3_7 = 24;
#endif

#ifdef __MSP430_HAS_PORT4_R__
static const uint8_t P4_0 = 25;
static const uint8_t P4_1 = 26;
static const uint8_t P4_2 = 27;
static const uint8_t P4_3 = 28;
static const uint8_t P4_4 = 29;
static const uint8_t P4_5 = 30;
static const uint8_t P4_6 = 31;
static const uint8_t P4_7 = 32;
#endiF

#ifdef __MSP430_HAS_PORT5_R__
static const uint8_t P5_0 = 33;
static const uint8_t P5_1 = 34;
static const uint8_t P5_2 = 35;
static const uint8_t P5_3 = 36;
static const uint8_t P5_4 = 37;
static const uint8_t P5_5 = 38;
static const uint8_t P5_6 = 39;
static const uint8_t P5_7 = 40;
#endif


/* contants for LCD_B */

/*#if defined(__MSP430_HAS_LCD_B__)
static const uint8_t COM0 = 40;
static const uint8_t COM1 = 39;
static const uint8_t COM2 = 38;
static const uint8_t COM3 = 37;

static const uint8_t S0 = 34;
static const uint8_t S1 = 35;
static const uint8_t S2 = 24;
static const uint8_t S3 = 25;
static const uint8_t S4 = 26;
static const uint8_t S5 = 27;
static const uint8_t S6 = 28;
static const uint8_t S7 = 29;
static const uint8_t S8 = 30;
static const uint8_t S9 = 31;
static const uint8_t S10 = 16;
static const uint8_t S11 = 17;
static const uint8_t S12 = 18;
static const uint8_t S13 = 19;
static const uint8_t S14 = 20;
static const uint8_t S15 = 21;
static const uint8_t S16 = 22;
static const uint8_t S17 = 23;
static const uint8_t S18 = 0;
static const uint8_t S19 = 1;
static const uint8_t S20 = 2;
static const uint8_t S21 = 3;
static const uint8_t S22 = 4;
static const uint8_t S23 = 36;
static const uint8_t S24 = 37;
static const uint8_t S25 = 38;
static const uint8_t S26 = 39;
#endif*/

#ifdef ARDUINO_MAIN

const uint16_t port_to_input[] = {
	NOT_A_PORT,
	(uint16_t) &P1IN,
	(uint16_t) &P2IN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3IN,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4IN,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5IN,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6IN,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7IN,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8IN,
#endif
};

const uint16_t port_to_output[] = {
	NOT_A_PORT,
	(uint16_t) &P1OUT,
	(uint16_t) &P2OUT,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3OUT,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4OUT,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5OUT,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6OUT,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7OUT,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8OUT,
#endif
};

const uint16_t port_to_dir[] = {
	NOT_A_PORT,
	(uint16_t) &P1DIR,
	(uint16_t) &P2DIR,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3DIR,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4DIR,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5DIR,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6DIR,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7DIR,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8DIR,
#endif
};

const uint16_t port_to_ren[] = {
	NOT_A_PORT,
	(uint16_t) &P1REN,
	(uint16_t) &P2REN,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3REN,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4REN,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5REN,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6REN,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7REN,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8REN,
#endif
};

const uint16_t port_to_sel0[] = {  /* put this PxSEL register under the group of PxSEL0 */
	NOT_A_PORT,
	(uint16_t) &P1SEL,
	(uint16_t) &P2SEL,
#ifdef __MSP430_HAS_PORT3_R__
	(uint16_t) &P3SEL,
#endif
#ifdef __MSP430_HAS_PORT4_R__
	(uint16_t) &P4SEL,
#endif
#ifdef __MSP430_HAS_PORT5_R__
	(uint16_t) &P5SEL,
#endif
#ifdef __MSP430_HAS_PORT6_R__
	(uint16_t) &P6SEL,
#endif
#ifdef __MSP430_HAS_PORT7_R__
	(uint16_t) &P7SEL,
#endif
#ifdef __MSP430_HAS_PORT8_R__
	(uint16_t) &P8SEL,
#endif
};

const uint16_t port_to_pmap[] = {
	NOT_A_PORT,	/* PMAP starts at port P1 */
	(uint16_t) &P1MAP0,
	(uint16_t) &P2MAP0,
	(uint16_t) &P3MAP0,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
	NOT_A_PORT,
};

const uint8_t digital_pin_to_timer[] = {
	NOT_ON_TIMER, /*  dummy */
	NOT_ON_TIMER, /*  1  */
	NOT_ON_TIMER, /*  2 */
	NOT_ON_TIMER, /*  3 - P1.1, note: A0 output cannot be used with analogWrite */
	NOT_ON_TIMER, /*  4 - P1.2 */
	NOT_ON_TIMER, /*  5 - P1.3 */
	NOT_ON_TIMER, /*  6 - P1.4 note: special case. Leaving as no timer due to difficulty determining if available */
	NOT_ON_TIMER, /*  7 - P1.5 note: A0 output cannot be used with analogWrite  */
	NOT_ON_TIMER, /*  8 - P2.0 */
	NOT_ON_TIMER, /*  9 - P2.1 */
	NOT_ON_TIMER, /* 10 - P2.3 */
	NOT_ON_TIMER, /* 11 - P2.4 */
	NOT_ON_TIMER, /* 12 - P2.5 */
	NOT_ON_TIMER, /* 13 - P2.6 */
	NOT_ON_TIMER, /* 14 - P1.6 */
	NOT_ON_TIMER, /* 15 - P1.7 */
	NOT_ON_TIMER, /* 16 - /RESET */  
	NOT_ON_TIMER, /* 17 - TEST */  
	NOT_ON_TIMER, /* 18 - XOUT - P2.7 */
	NOT_ON_TIMER, /* 19 - XIN - P2.6: */
	NOT_ON_TIMER, /* 20 - GND */
};

const uint8_t digital_pin_to_port[] = {
	NOT_A_PIN,
	P1,        /* 1 */
	P1,        /* 2 */
	P1,        /* 3 */
	P1,        /* 4 */
	P1,        /* 5 */
	P1,        /* 3 */
	P1,        /* 7 */
	P1,        /* 8 */
	P2,        /* 9 */
	P2,        /* 10 */
	P2,        /* 11 */
	P2,        /* 12 */
	P2,        /* 13 */
	P2,        /* 14 */
	P2,        /* 15 */
	P2,        /* 16 */
	P3,        /* 17 */
	P3,        /* 18 */
	P3,        /* 19 */
	P3,        /* 20 */
	P3,        /* 21 */
	P3,        /* 22 */
	P3,        /* 23 */
	P3,        /* 24 */
	P4,        /* 25 */
	P4,        /* 26 */
	P4,        /* 27 */
	P4,        /* 28 */
	P4,        /* 29 */
	P4,        /* 30 */
	P4,        /* 31 */
	P4,        /* 32 */
	P5,        /* 33 */
	P5,        /* 34 */
	P5,        /* 35 */
	P5,        /* 36 */
	P5,        /* 37 */
	P5,        /* 38 */
	P5,        /* 39 */
	P5         /* 40 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	NOT_A_PIN, /* 0 */
	BV(0),     /* 1 */
	BV(1),     /* 2 */
	BV(2),     /* 3 */
	BV(3),     /* 4 */
	BV(4),     /* 5 */
	BV(5),     /* 6 */
	BV(6),     /* 7 */
	BV(7),     /* 8 */
	BV(0),     /* 9 */
	BV(1),     /* 10 */
	BV(2),     /* 11 */
	BV(3),     /* 12 */
	BV(4),     /* 13 */
	BV(5),     /* 14 */
	BV(6),     /* 15 */
	BV(7),     /* 16 */
	BV(0),     /* 17 */
	BV(1),     /* 18 */
	BV(2),     /* 19 */
	BV(3),     /* 20 */
	BV(4),     /* 21 */
	BV(5),     /* 22 */
	BV(6),     /* 23 */
	BV(7),     /* 24 */
	BV(0),     /* 25 */
	BV(1),     /* 26 */
	BV(2),     /* 27 */
	BV(3),     /* 28 */
	BV(4),     /* 29 */
	BV(5),     /* 30 */
	BV(6),     /* 31 */
	BV(7),     /* 32 */
	BV(0),     /* 33 */
	BV(1),     /* 34 */
	BV(2),     /* 35 */
	BV(3),     /* 36 */
	BV(4),     /* 37 */
	BV(5),     /* 38 */
	BV(6),     /* 39 */
	BV(7),     /* 40 */
	
};

const uint32_t digital_pin_to_analog_in[] = {
        NOT_ON_ADC,     /*  0  */
        NOT_ON_ADC,     /*  1  */
        NOT_ON_ADC,	/*  2  */
        NOT_ON_ADC,	/*  3  */
        NOT_ON_ADC,	/*  4  */
        NOT_ON_ADC, 	/*  5  */
        NOT_ON_ADC,	/*  6  */
        NOT_ON_ADC,	/*  7  */
        NOT_ON_ADC, 	/*  8  */
        0,      	/*  9  - A0 (device analog channel 0)*/
        1,      	/*  10 - A1 (device analog channel 1)*/
        2,      	/*  11 - A2 (device analog channel 2)*/
        3,      	/*  12 - A3 (device analog channel 3)*/
        4,     		/*  13 - A4 (device analog channel 4)*/
        5,     		/*  14 - A5 (device analog channel 5)*/
        6, 		/*  15 - A6 (device analog channel 6)*/
        7,       	/*  16 - A7 (device analog channel 7)*/
        NOT_ON_ADC,  	/*  17  */
        NOT_ON_ADC,  	/*  18  */
        NOT_ON_ADC,  	/*  19  */
        NOT_ON_ADC,  	/*  20  */
        NOT_ON_ADC,   	/*  21  */
        NOT_ON_ADC,   	/*  22  */	
	NOT_ON_ADC,	/*  23  */
	NOT_ON_ADC,	/*  24  */
	NOT_ON_ADC,     /*  25  */
        NOT_ON_ADC,     /*  26  */
	NOT_ON_ADC,     /*  27  */
	NOT_ON_ADC,     /*  28  */
	NOT_ON_ADC,     /*  29  */
	NOT_ON_ADC,     /*  30  */
	NOT_ON_ADC,     /*  31  */
	NOT_ON_ADC,     /*  32  */
	NOT_ON_ADC,     /*  33  */
	NOT_ON_ADC,     /*  34  */
	NOT_ON_ADC,     /*  35  */
	NOT_ON_ADC,     /*  36  */
	NOT_ON_ADC,     /*  37  */
	NOT_ON_ADC,     /*  38  */
	NOT_ON_ADC,     /*  39  */
	NOT_ON_ADC,     /*  40  */
	
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
