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

static const uint8_t DEBUG_UARTRXD = 5;  /* Receive  Data (RXD) at P1.5 */
static const uint8_t DEBUG_UARTTXD = 6;  /* Transmit Data (TXD) at P1.6 */

#define DEBUG_UARTRXD_SET_MODE (PORT_SELECTION0 | INPUT)
#define DEBUG_UARTTXD_SET_MODE (PORT_SELECTION0 | OUTPUT)

#endif

#define DEBUG_UART_MODULE_OFFSET 0x0

#if defined(__MSP430_HAS_USCI_B0__)

static const uint8_t SS      = 7 ;  /* P1.7 */
static const uint8_t SCK     = 4;  /* P1.4 */
static const uint8_t MOSI    = 3 ;  /* P1.3 */
static const uint8_t MISO    = 2;  /* P1.2 */
static const uint8_t TWISDA  = 3;  /* P1.3 */
static const uint8_t TWISCL  = 2;  /* P1.2 */

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
static const uint8_t P1_0 = 0;
static const uint8_t P1_1 = 1;
static const uint8_t P1_2 = 2;
static const uint8_t P1_3 = 3;
static const uint8_t P1_4 = 4;
static const uint8_t P1_5 = 5;
static const uint8_t P1_6 = 6;
static const uint8_t P1_7 = 7;

static const uint8_t P2_0 = 8;
static const uint8_t P2_1 = 9;
static const uint8_t P2_2 = 10;
static const uint8_t P2_3 = 11;
static const uint8_t P2_4 = 12;
static const uint8_t P2_5 = 13;
static const uint8_t P2_6 = 14;
static const uint8_t P2_7 = 15;

static const uint8_t P3_0 = 16;
static const uint8_t P3_1 = 17;
static const uint8_t P3_2 = 18;
static const uint8_t P3_3 = 19;
static const uint8_t P3_4 = 20;
static const uint8_t P3_5 = 21;
static const uint8_t P3_6 = 22;
static const uint8_t P3_7 = 23;

static const uint8_t P4_0 = 24;
static const uint8_t P4_1 = 25;
static const uint8_t P4_2 = 26;
static const uint8_t P4_3 = 27;
static const uint8_t P4_4 = 28;
static const uint8_t P4_5 = 29;
static const uint8_t P4_6 = 30;
static const uint8_t P4_7 = 31;

static const uint8_t P5_0 = 32;
static const uint8_t P5_1 = 33;
static const uint8_t P5_2 = 34;
static const uint8_t P5_3 = 35;
static const uint8_t P5_4 = 36;
static const uint8_t P5_5 = 37;
static const uint8_t P5_6 = 38;
static const uint8_t P5_7 = 39;


/* contants for LCD_B */
#if defined(__MSP430_HAS_LCD_B__)


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
#endif

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
	NOT_ON_TIMER, /*  1 - VCC */
	NOT_ON_TIMER, /*  2 - P1.0 */
	NOT_ON_TIMER,         /*  3 - P1.1, note: A0 output cannot be used with analogWrite */
	NOT_ON_TIMER,         /*  4 - P1.2 */
	NOT_ON_TIMER, /*  5 - P1.3 */
	NOT_ON_TIMER, /*  6 - P1.4 note: special case. Leaving as no timer due to difficulty determining if available */
	NOT_ON_TIMER,         /*  7 - P1.5 note: A0 output cannot be used with analogWrite  */
	NOT_ON_TIMER, /*  8 - P2.0 */
	NOT_ON_TIMER, /*  9 - P2.1 */
	NOT_ON_TIMER, /* 10 - P2.3 */
	NOT_ON_TIMER, /* 11 - P2.4 */
	NOT_ON_TIMER, /* 12 - P2.5 */
	NOT_ON_TIMER, /* 13 - P2.6 */
	NOT_ON_TIMER,         /* 14 - P1.6 */
	NOT_ON_TIMER, /* 15 - P1.7 */
	NOT_ON_TIMER, /* 16 - /RESET */  
	NOT_ON_TIMER, /* 17 - TEST */  
	NOT_ON_TIMER, /* 18 - XOUT - P2.7 */
	NOT_ON_TIMER,         /* 19 - XIN - P2.6: */
	NOT_ON_TIMER, /* 20 - GND */
};

const uint8_t digital_pin_to_port[] = {
	P1,        /* 0 */
	P1,        /* 1 */
	P1,        /* 2 */
	P1,        /* 3 */
	P1,        /* 4 */
	P1,        /* 5 */
	P1,        /* 6 */
	P1,        /* 7 */
	P2,        /* 8 */
	P2,        /* 9 */
	P2,        /* 10 */
	P2,        /* 11 */
	P2,        /* 12 */
	P2,        /* 13 */
	P2,        /* 14 */
	P2,        /* 15 */
	P3,        /* 16 */
	P3,        /* 17 */
	P3,        /* 18 */
	P3,        /* 19 */
	P3,        /* 20 */
	P3,        /* 21 */
	P3,        /* 22 */
	P3,        /* 23 */
	P4,        /* 24 */
	P4,        /* 25 */
	P4,        /* 26 */
	P4,        /* 27 */
	P4,        /* 28 */
	P4,        /* 29 */
	P4,        /* 30 */
	P4,        /* 31 */
	P5,        /* 32 */
	P5,        /* 33 */
	P5,        /* 34 */
	P5,        /* 35 */
	P5,        /* 36 */
	P5,        /* 37 */
	P5,        /* 38 */
	P5         /* 39 */
};

const uint8_t digital_pin_to_bit_mask[] = {
	           /* 0 */
	BV(0),     /* 1 */
	BV(1),     /* 2 */
	BV(2),     /* 2 */
	BV(3),     /* 3 */
	BV(4),     /* 4 */
	BV(5),     /* 5 */
	BV(6),     /* 6 */
	BV(7),     /* 7 */
	BV(0),     /* 8 */
	BV(1),     /* 9 */
	BV(2),     /* 10 */
	BV(3),     /* 11 */
	BV(4),     /* 12 */
	BV(5),     /* 13 */
	BV(6),     /* 14 */
	BV(7),     /* 15 */
	BV(0),     /* 16 */
	BV(1),     /* 17 */
	BV(2),     /* 18 */
	BV(3),     /* 19 */
	BV(4),     /* 20 */
	BV(5),     /* 21 */
	BV(6),     /* 22 */
	BV(7),     /* 23 */
	BV(0),     /* 24 */
	BV(1),     /* 25 */
	BV(2),     /* 26 */
	BV(3),     /* 27 */
	BV(4),     /* 28 */
	BV(5),     /* 29 */
	BV(6),     /* 30 */
	BV(7),     /* 31 */
	BV(0),     /* 32 */
	BV(1),     /* 33 */
	BV(2),     /* 34 */
	BV(3),     /* 35 */
	BV(4),     /* 36 */
	BV(5),     /* 37 */
	BV(6),     /* 38 */
	BV(7),     /* 39 */
	
};
#endif // #ifdef ARDUINO_MAIN
#endif // #ifndef Pins_Energia_h
