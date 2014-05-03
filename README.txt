CC430_EnergiaSupport
====================

How to install CC430 chronos support :

All files needed are in this git.

Copy variant eZ430_Chronos in your variant folder in Energia/hardware/msp430/variant 

Modify hardware/msp430/core/msp430/wiring.c like this :

find this line :

#if defined(__MSP430_HAS_UCS__) 

and replace it by 

#if defined(__MSP430_HAS_UCS__) || defined(__MSP430_HAS_UCS_RF__)

Finally update your hardaware/msp430/board.txt file adding :

##############################################################
ez430.name=eZ430 (12 mhz)
ez430.upload.protocol=rf2500
ez430.upload.maximum_size=32767
ez430.build.mcu=cc430f6137
ez430.build.f_cpu=12000000L
ez430.build.core=msp430
ez430.build.variant=eZ430_Chronos
ez430.upload.maximum_ram_size=4096

Lauch Energia and normally a new board is available board list ;)
