#include "Energia.h"

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

extern const u8 lcd_font[];
extern const u8 *segments_lcdmem[];
extern const u8 segments_bitmask[];
extern const u8 int_to_array_conversion_table[][3];

u8 switch_seg(u8 line, u8 index1, u8 index2);
void clear_line(u8 line);
// *************************************************************************************************
// Global Variable section

// Set of display flags
typedef union
{
    struct
    {
        // Line1 + Line2 + Icons
        u16 full_update : 1;            // 1 = Redraw all content
        u16 partial_update : 1;         // 1 = Update changes

        // Line only
        u16 line1_full_update : 1;      // 1 = Redraw Line1 content
        u16 line2_full_update : 1;      // 1 = Redraw Line2 content

        // Logic module data update flags
        u16 update_time : 1;            // 1 = Time was updated
        u16 update_stopwatch : 1;       // 1 = Stopwatch was updated
        u16 update_temperature : 1;     // 1 = Temperature was updated
        u16 update_battery_voltage : 1; // 1 = Battery voltage was updated
        u16 update_date : 1;            // 1 = Date was updated
        u16 update_alarm : 1;           // 1 = Alarm time was updated
        u16 update_acceleration : 1;    // 1 = Acceleration data was updated
    } flag;
    u16 all_flags;                      // Shortcut to all display flags (for reset)
} s_display_flags;

extern volatile s_display_flags display;

// *************************************************************************************************
// Defines section

// Display function modes
#define DISPLAY_LINE_UPDATE_FULL                (BIT0)
#define DISPLAY_LINE_UPDATE_PARTIAL             (BIT1)
#define DISPLAY_LINE_CLEAR                              (BIT2)

// Definitions for line view style
#define DISPLAY_DEFAULT_VIEW                    (0u)
#define DISPLAY_ALTERNATIVE_VIEW                (1u)

// Definitions for line access
#define LINE1                                                   (1u)
#define LINE2                                                   (2u)

// LCD display modes
#define SEG_OFF                                 (0u)
#define SEG_ON                                  (1u)
#define SEG_ON_BLINK_ON                 (2u)
#define SEG_ON_BLINK_OFF                (3u)
#define SEG_OFF_BLINK_OFF               (4u)

// 7-segment character bit assignments
#define SEG_A                   (BIT4)
#define SEG_B                   (BIT5)
#define SEG_C                   (BIT6)
#define SEG_D                   (BIT7)
#define SEG_E                   (BIT2)
#define SEG_F                   (BIT0)
#define SEG_G                   (BIT1)

// ------------------------------------------
// LCD symbols for easier access
//
// xxx_SEG_xxx          = Seven-segment character (sequence 5-4-3-2-1-0)
// xxx_SYMB_xxx         = Display symbol, e.g. "AM" for ante meridiem
// xxx_UNIT_xxx         = Display unit, e.g. "km/h" for kilometers per hour
// xxx_ICON_xxx         = Display icon, e.g. heart to indicate reception of heart rate data
// xxx_L1_xxx           = Item is part of Line1 information
// xxx_L2_xxx           = Item is part of Line2 information

// Symbols for Line1
#define LCD_SYMB_AM                                     0
#define LCD_SYMB_PM                                     1
#define LCD_SYMB_ARROW_UP                       2
#define LCD_SYMB_ARROW_DOWN                     3
#define LCD_SYMB_PERCENT                        4

// Symbols for Line2
#define LCD_SYMB_TOTAL                          5
#define LCD_SYMB_AVERAGE                        6
#define LCD_SYMB_MAX                            7
#define LCD_SYMB_BATTERY                        8

// Units for Line1
#define LCD_UNIT_L1_FT                          9
#define LCD_UNIT_L1_K                           10
#define LCD_UNIT_L1_M                           11
#define LCD_UNIT_L1_I                           12
#define LCD_UNIT_L1_PER_S                       13
#define LCD_UNIT_L1_PER_H                       14
#define LCD_UNIT_L1_DEGREE                      15

// Units for Line2
#define LCD_UNIT_L2_KCAL                        16
#define LCD_UNIT_L2_KM                          17
#define LCD_UNIT_L2_MI                          18

// Icons
#define LCD_ICON_HEART                          19
#define LCD_ICON_STOPWATCH                      20
#define LCD_ICON_RECORD                         21
#define LCD_ICON_ALARM                          22
#define LCD_ICON_BEEPER1                        23
#define LCD_ICON_BEEPER2                        24
#define LCD_ICON_BEEPER3                        25

// Line1 7-segments
#define LCD_SEG_L1_3                            26
#define LCD_SEG_L1_2                            27
#define LCD_SEG_L1_1                            28
#define LCD_SEG_L1_0                            29
#define LCD_SEG_L1_COL                          30
#define LCD_SEG_L1_DP1                          31
#define LCD_SEG_L1_DP0                          32

// Line2 7-segments
#define LCD_SEG_L2_5                            33
#define LCD_SEG_L2_4                            34
#define LCD_SEG_L2_3                            35
#define LCD_SEG_L2_2                            36
#define LCD_SEG_L2_1                            37
#define LCD_SEG_L2_0                            38
#define LCD_SEG_L2_COL1                         39
#define LCD_SEG_L2_COL0                         40
#define LCD_SEG_L2_DP                           41

// Line1 7-segment arrays
#define LCD_SEG_L1_3_0                          70
#define LCD_SEG_L1_2_0                          71
#define LCD_SEG_L1_1_0                          72
#define LCD_SEG_L1_3_1                          73
#define LCD_SEG_L1_3_2                          74

// Line2 7-segment arrays
#define LCD_SEG_L2_5_0                          90
#define LCD_SEG_L2_4_0                          91
#define LCD_SEG_L2_3_0                          92
#define LCD_SEG_L2_2_0                          93
#define LCD_SEG_L2_1_0                          94
#define LCD_SEG_L2_5_2                          95
#define LCD_SEG_L2_3_2                          96
#define LCD_SEG_L2_5_4                          97
#define LCD_SEG_L2_4_2                          98

// LCD controller memory map
#define LCD_MEM_1                               ((u8*)0x0A20)
#define LCD_MEM_2                               ((u8*)0x0A21)
#define LCD_MEM_3                               ((u8*)0x0A22)
#define LCD_MEM_4                               ((u8*)0x0A23)
#define LCD_MEM_5                               ((u8*)0x0A24)
#define LCD_MEM_6                               ((u8*)0x0A25)
#define LCD_MEM_7                               ((u8*)0x0A26)
#define LCD_MEM_8                               ((u8*)0x0A27)
#define LCD_MEM_9                               ((u8*)0x0A28)
#define LCD_MEM_10                              ((u8*)0x0A29)
#define LCD_MEM_11                              ((u8*)0x0A2A)
#define LCD_MEM_12                              ((u8*)0x0A2B)

// Memory assignment
#define LCD_SEG_L1_0_MEM                        (LCD_MEM_6)
#define LCD_SEG_L1_1_MEM                        (LCD_MEM_4)
#define LCD_SEG_L1_2_MEM                        (LCD_MEM_3)
#define LCD_SEG_L1_3_MEM                        (LCD_MEM_2)
#define LCD_SEG_L1_COL_MEM                      (LCD_MEM_1)
#define LCD_SEG_L1_DP1_MEM                      (LCD_MEM_1)
#define LCD_SEG_L1_DP0_MEM                      (LCD_MEM_5)
#define LCD_SEG_L2_0_MEM                        (LCD_MEM_8)
#define LCD_SEG_L2_1_MEM                        (LCD_MEM_9)
#define LCD_SEG_L2_2_MEM                        (LCD_MEM_10)
#define LCD_SEG_L2_3_MEM                        (LCD_MEM_11)
#define LCD_SEG_L2_4_MEM                        (LCD_MEM_12)
#define LCD_SEG_L2_5_MEM                        (LCD_MEM_12)
#define LCD_SEG_L2_COL1_MEM                     (LCD_MEM_1)
#define LCD_SEG_L2_COL0_MEM                     (LCD_MEM_5)
#define LCD_SEG_L2_DP_MEM                       (LCD_MEM_9)
#define LCD_SYMB_AM_MEM                         (LCD_MEM_1)
#define LCD_SYMB_PM_MEM                         (LCD_MEM_1)
#define LCD_SYMB_ARROW_UP_MEM           (LCD_MEM_1)
#define LCD_SYMB_ARROW_DOWN_MEM         (LCD_MEM_1)
#define LCD_SYMB_PERCENT_MEM            (LCD_MEM_5)
#define LCD_SYMB_TOTAL_MEM                      (LCD_MEM_11)
#define LCD_SYMB_AVERAGE_MEM            (LCD_MEM_10)
#define LCD_SYMB_MAX_MEM                        (LCD_MEM_8)
#define LCD_SYMB_BATTERY_MEM            (LCD_MEM_7)
#define LCD_UNIT_L1_FT_MEM                      (LCD_MEM_5)
#define LCD_UNIT_L1_K_MEM                       (LCD_MEM_5)
#define LCD_UNIT_L1_M_MEM                       (LCD_MEM_7)
#define LCD_UNIT_L1_I_MEM                       (LCD_MEM_7)
#define LCD_UNIT_L1_PER_S_MEM           (LCD_MEM_5)
#define LCD_UNIT_L1_PER_H_MEM           (LCD_MEM_7)
#define LCD_UNIT_L1_DEGREE_MEM          (LCD_MEM_5)
#define LCD_UNIT_L2_KCAL_MEM            (LCD_MEM_7)
#define LCD_UNIT_L2_KM_MEM                      (LCD_MEM_7)
#define LCD_UNIT_L2_MI_MEM                      (LCD_MEM_7)
#define LCD_ICON_HEART_MEM                      (LCD_MEM_2)
#define LCD_ICON_STOPWATCH_MEM          (LCD_MEM_3)
#define LCD_ICON_RECORD_MEM                     (LCD_MEM_1)
#define LCD_ICON_ALARM_MEM                      (LCD_MEM_4)
#define LCD_ICON_BEEPER1_MEM            (LCD_MEM_5)
#define LCD_ICON_BEEPER2_MEM            (LCD_MEM_6)
#define LCD_ICON_BEEPER3_MEM            (LCD_MEM_7)

// Bit masks for write access
#define LCD_SEG_L1_0_MASK                       (BIT2 + BIT1 + BIT0 + BIT7 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L1_1_MASK                       (BIT2 + BIT1 + BIT0 + BIT7 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L1_2_MASK                       (BIT2 + BIT1 + BIT0 + BIT7 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L1_3_MASK                       (BIT2 + BIT1 + BIT0 + BIT7 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L1_COL_MASK                     (BIT5)
#define LCD_SEG_L1_DP1_MASK                     (BIT6)
#define LCD_SEG_L1_DP0_MASK                     (BIT2)
#define LCD_SEG_L2_0_MASK                       (BIT3 + BIT2 + BIT1 + BIT0 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L2_1_MASK                       (BIT3 + BIT2 + BIT1 + BIT0 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L2_2_MASK                       (BIT3 + BIT2 + BIT1 + BIT0 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L2_3_MASK                       (BIT3 + BIT2 + BIT1 + BIT0 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L2_4_MASK                       (BIT3 + BIT2 + BIT1 + BIT0 + BIT6 + BIT5 + BIT4)
#define LCD_SEG_L2_5_MASK                       (BIT7)
#define LCD_SEG_L2_COL1_MASK            (BIT4)
#define LCD_SEG_L2_COL0_MASK            (BIT0)
#define LCD_SEG_L2_DP_MASK                      (BIT7)
#define LCD_SYMB_AM_MASK                        (BIT1 + BIT0)
#define LCD_SYMB_PM_MASK                        (BIT0)
#define LCD_SYMB_ARROW_UP_MASK          (BIT2)
#define LCD_SYMB_ARROW_DOWN_MASK        (BIT3)
#define LCD_SYMB_PERCENT_MASK           (BIT4)
#define LCD_SYMB_TOTAL_MASK                     (BIT7)
#define LCD_SYMB_AVERAGE_MASK           (BIT7)
#define LCD_SYMB_MAX_MASK                       (BIT7)
#define LCD_SYMB_BATTERY_MASK           (BIT7)
#define LCD_UNIT_L1_FT_MASK                     (BIT5)
#define LCD_UNIT_L1_K_MASK                      (BIT6)
#define LCD_UNIT_L1_M_MASK                      (BIT1)
#define LCD_UNIT_L1_I_MASK                      (BIT0)
#define LCD_UNIT_L1_PER_S_MASK          (BIT7)
#define LCD_UNIT_L1_PER_H_MASK          (BIT2)
#define LCD_UNIT_L1_DEGREE_MASK         (BIT1)
#define LCD_UNIT_L2_KCAL_MASK           (BIT4)
#define LCD_UNIT_L2_KM_MASK                     (BIT5)
#define LCD_UNIT_L2_MI_MASK                     (BIT6)
#define LCD_ICON_HEART_MASK                     (BIT3)
#define LCD_ICON_STOPWATCH_MASK         (BIT3)
#define LCD_ICON_RECORD_MASK            (BIT7)
#define LCD_ICON_ALARM_MASK                     (BIT3)
#define LCD_ICON_BEEPER1_MASK           (BIT3)
#define LCD_ICON_BEEPER2_MASK           (BIT3)
#define LCD_ICON_BEEPER3_MASK           (BIT3)


void write_lcd_mem(u8 * lcdmem, u8 bits, u8 bitmask, u8 state);

void display_symbol(u8 symbol, u8 mode);
void display_char(u8 segment, u8 chr, u8 mode);
void display_chars(u8 segments, u8 * str, u8 mode);
void lcd_init(void);

// *************************************************************************************************
// Defines section

// *************************************************************************************************
// Global Variable section

// Table with memory bit assignment for digits "0" to "9" and characters "A" to "Z"
const u8 lcd_font[] = {
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F,         // Displays "0"
    SEG_B + SEG_C,                                         // Displays "1"
    SEG_A + SEG_B + SEG_D + SEG_E + SEG_G,                 // Displays "2"
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_G,                 // Displays "3"
    SEG_B + SEG_C + SEG_F + SEG_G,                         // Displays "4"
    SEG_A + SEG_C + SEG_D + SEG_F + SEG_G,                 // Displays "5"
    SEG_A + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G,         // Displays "6"
    SEG_A + SEG_B + SEG_C,                                 // Displays "7"
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F + SEG_G, // Displays "8"
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_F + SEG_G,         // Displays "9"
    0,                                                     // Displays " "
    0,                                                     // Displays " "
    0,                                                     // Displays " "
    0,                                                     // Displays " "
    0,                                                     // Displays " "
    SEG_D + SEG_E + SEG_G,                                 // Displays "c"
    0,                                                     // Displays " "
    SEG_A + SEG_B + SEG_C + SEG_E + SEG_F + SEG_G,         // Displays "A"
    SEG_C + SEG_D + SEG_E + SEG_F + SEG_G,                 // Displays "b"
    SEG_A + SEG_D + SEG_E + SEG_F,                         // Displays "C"
    SEG_B + SEG_C + SEG_D + SEG_E + SEG_G,                 // Displays "d"
    SEG_A + +SEG_D + SEG_E + SEG_F + SEG_G,                // Displays "E"
    SEG_A + SEG_E + SEG_F + SEG_G,                         // Displays "F"
    //  SEG_A+      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,       // Displays "G"
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_F + SEG_G,         // Displays "g"
    SEG_B + SEG_C + SEG_E + SEG_F + SEG_G,                 // Displays "H"
    SEG_E + SEG_F,                                         // Displays "I"
    SEG_A + SEG_B + SEG_C + SEG_D,                         // Displays "J"
    //              SEG_B+SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "k"
    SEG_D + SEG_E + SEG_F + SEG_G,                         // Displays "k"
    SEG_D + SEG_E + SEG_F,                                 // Displays "L"
    SEG_A + SEG_B + SEG_C + SEG_E + SEG_F,                 // Displays "M"
    SEG_C + SEG_E + SEG_G,                                 // Displays "n"
    SEG_C + SEG_D + SEG_E + SEG_G,                         // Displays "o"
    SEG_A + SEG_B + SEG_E + SEG_F + SEG_G,                 // Displays "P"
    SEG_A + SEG_B + SEG_C + SEG_D + SEG_E + SEG_F,         // Displays "Q"
    SEG_E + SEG_G,                                         // Displays "r"
    SEG_A + SEG_C + SEG_D + SEG_F + SEG_G,                 // Displays "S"
    SEG_D + SEG_E + SEG_F + SEG_G,                         // Displays "t"
    SEG_C + SEG_D + SEG_E,                                 // Displays "u"
    SEG_C + SEG_D + SEG_E,                                 // Displays "u"
    SEG_G,                                                 // Displays "-"
    SEG_B + SEG_C + +SEG_E + SEG_F + SEG_G,                // Displays "X"
    SEG_B + SEG_C + SEG_D + SEG_F + SEG_G,                 // Displays "Y"
    SEG_A + SEG_B + SEG_D + SEG_E + SEG_G,                 // Displays "Z"
};

// Table with memory address for each display element
const u8 *segments_lcdmem[] = {
    LCD_SYMB_AM_MEM,
    LCD_SYMB_PM_MEM,
    LCD_SYMB_ARROW_UP_MEM,
    LCD_SYMB_ARROW_DOWN_MEM,
    LCD_SYMB_PERCENT_MEM,
    LCD_SYMB_TOTAL_MEM,
    LCD_SYMB_AVERAGE_MEM,
    LCD_SYMB_MAX_MEM,
    LCD_SYMB_BATTERY_MEM,
    LCD_UNIT_L1_FT_MEM,
    LCD_UNIT_L1_K_MEM,
    LCD_UNIT_L1_M_MEM,
    LCD_UNIT_L1_I_MEM,
    LCD_UNIT_L1_PER_S_MEM,
    LCD_UNIT_L1_PER_H_MEM,
    LCD_UNIT_L1_DEGREE_MEM,
    LCD_UNIT_L2_KCAL_MEM,
    LCD_UNIT_L2_KM_MEM,
    LCD_UNIT_L2_MI_MEM,
    LCD_ICON_HEART_MEM,
    LCD_ICON_STOPWATCH_MEM,
    LCD_ICON_RECORD_MEM,
    LCD_ICON_ALARM_MEM,
    LCD_ICON_BEEPER1_MEM,
    LCD_ICON_BEEPER2_MEM,
    LCD_ICON_BEEPER3_MEM,
    LCD_SEG_L1_3_MEM,
    LCD_SEG_L1_2_MEM,
    LCD_SEG_L1_1_MEM,
    LCD_SEG_L1_0_MEM,
    LCD_SEG_L1_COL_MEM,
    LCD_SEG_L1_DP1_MEM,
    LCD_SEG_L1_DP0_MEM,
    LCD_SEG_L2_5_MEM,
    LCD_SEG_L2_4_MEM,
    LCD_SEG_L2_3_MEM,
    LCD_SEG_L2_2_MEM,
    LCD_SEG_L2_1_MEM,
    LCD_SEG_L2_0_MEM,
    LCD_SEG_L2_COL1_MEM,
    LCD_SEG_L2_COL0_MEM,
    LCD_SEG_L2_DP_MEM,
};

// Table with bit mask for each display element
const u8 segments_bitmask[] = {
    LCD_SYMB_AM_MASK,
    LCD_SYMB_PM_MASK,
    LCD_SYMB_ARROW_UP_MASK,
    LCD_SYMB_ARROW_DOWN_MASK,
    LCD_SYMB_PERCENT_MASK,
    LCD_SYMB_TOTAL_MASK,
    LCD_SYMB_AVERAGE_MASK,
    LCD_SYMB_MAX_MASK,
    LCD_SYMB_BATTERY_MASK,
    LCD_UNIT_L1_FT_MASK,
    LCD_UNIT_L1_K_MASK,
    LCD_UNIT_L1_M_MASK,
    LCD_UNIT_L1_I_MASK,
    LCD_UNIT_L1_PER_S_MASK,
    LCD_UNIT_L1_PER_H_MASK,
    LCD_UNIT_L1_DEGREE_MASK,
    LCD_UNIT_L2_KCAL_MASK,
    LCD_UNIT_L2_KM_MASK,
    LCD_UNIT_L2_MI_MASK,
    LCD_ICON_HEART_MASK,
    LCD_ICON_STOPWATCH_MASK,
    LCD_ICON_RECORD_MASK,
    LCD_ICON_ALARM_MASK,
    LCD_ICON_BEEPER1_MASK,
    LCD_ICON_BEEPER2_MASK,
    LCD_ICON_BEEPER3_MASK,
    LCD_SEG_L1_3_MASK,
    LCD_SEG_L1_2_MASK,
    LCD_SEG_L1_1_MASK,
    LCD_SEG_L1_0_MASK,
    LCD_SEG_L1_COL_MASK,
    LCD_SEG_L1_DP1_MASK,
    LCD_SEG_L1_DP0_MASK,
    LCD_SEG_L2_5_MASK,
    LCD_SEG_L2_4_MASK,
    LCD_SEG_L2_3_MASK,
    LCD_SEG_L2_2_MASK,
    LCD_SEG_L2_1_MASK,
    LCD_SEG_L2_0_MASK,
    LCD_SEG_L2_COL1_MASK,
    LCD_SEG_L2_COL0_MASK,
    LCD_SEG_L2_DP_MASK,
};



// Display flags
volatile s_display_flags display;

// Global return string for int_to_array function
u8 int_to_array_str[8];

// *************************************************************************************************
// Extern section
extern void (*fptr_lcd_function_line1)(u8 line, u8 update);
extern void (*fptr_lcd_function_line2)(u8 line, u8 update);


void setup()
{

	lcd_init();
	display_symbol(LCD_ICON_HEART, SEG_ON  );
}

void loop()
{
 
	display_symbol(LCD_ICON_HEART, SEG_ON  );
	delay(1000);
	display_symbol(LCD_ICON_HEART, SEG_OFF  );
		delay(1000);

}



 

// *************************************************************************************************
// @fn          lcd_init
// @brief       Erase LCD memory. Init LCD peripheral.
// @param       none
// @return      none
// *************************************************************************************************
void lcd_init(void)
{
    // Clear entire display memory
    LCDBMEMCTL |= LCDCLRBM + LCDCLRM;

    // LCD_FREQ = ACLK/16/8 = 256Hz
    // Frame frequency = 256Hz/4 = 64Hz, LCD mux 4, LCD on
    LCDBCTL0 = (LCDDIV0 + LCDDIV1 + LCDDIV2 + LCDDIV3) | (LCDPRE0 + LCDPRE1) | LCD4MUX | LCDON;

    // LCB_BLK_FREQ = ACLK/8/4096 = 1Hz
    LCDBBLKCTL = LCDBLKPRE0 | LCDBLKPRE1 | LCDBLKDIV0 | LCDBLKDIV1 | LCDBLKDIV2 | LCDBLKMOD0;

    // I/O to COM outputs
    P5SEL |= (BIT5 | BIT6 | BIT7);
    P5DIR |= (BIT5 | BIT6 | BIT7);

    // Activate LCD output
    LCDBPCTL0 = 0xFFFF;         // Select LCD segments S0-S15
    LCDBPCTL1 = 0x00FF;         // Select LCD segments S16-S22

#ifdef USE_LCD_CHARGE_PUMP
    // Charge pump voltage generated internally, internal bias (V2-V4) generation
    LCDBVCTL = LCDCPEN | VLCD_2_72;
#endif
}

// *************************************************************************************************
// @fn          clear_display_all
// @brief       Erase LINE1 and LINE2 segments. Clear also function-specific content.
// @param       none
// @return      none
// *************************************************************************************************
void clear_display_all(void)
{
    // Clear generic content
    clear_line(LINE1);
    clear_line(LINE2);

    // Clean up function-specific content
    fptr_lcd_function_line1(LINE1, DISPLAY_LINE_CLEAR);
    fptr_lcd_function_line2(LINE2, DISPLAY_LINE_CLEAR);
}

// *************************************************************************************************
// @fn          clear_display
// @brief       Erase LINE1 and LINE2 segments. Keep icons.
// @param       none
// @return      none
// *************************************************************************************************
void clear_display(void)
{
    clear_line(LINE1);
    clear_line(LINE2);
}

// *************************************************************************************************
// @fn          clear_line
// @brief       Erase segments of a given line.
// @param       u8 line LINE1, LINE2
// @return      none
// *************************************************************************************************
void clear_line(u8 line)
{
    display_chars(switch_seg(line, LCD_SEG_L1_3_0, LCD_SEG_L2_5_0), NULL, SEG_OFF);
    if (line == LINE1)
    {
        display_symbol(LCD_SEG_L1_DP1, SEG_OFF);
        display_symbol(LCD_SEG_L1_DP0, SEG_OFF);
        display_symbol(LCD_SEG_L1_COL, SEG_OFF);
    }
    else                        // line == LINE2
    {
        display_symbol(LCD_SEG_L2_DP, SEG_OFF);
        display_symbol(LCD_SEG_L2_COL1, SEG_OFF);
        display_symbol(LCD_SEG_L2_COL0, SEG_OFF);
    }
}

// *************************************************************************************************
// @fn          write_segment
// @brief       Write to one or multiple LCD segments
// @param       lcdmem          Pointer to LCD byte memory
//                              bits            Segments to address
//                              bitmask         Bitmask for particular display item
//                              mode            On, off or blink segments
// @return
// *************************************************************************************************
void write_lcd_mem(u8 * lcdmem, u8 bits, u8 bitmask, u8 state)
{
    if (state == SEG_ON)
    {
        // Clear segments before writing
        *lcdmem = (u8) (*lcdmem & ~bitmask);

        // Set visible segments
        *lcdmem = (u8) (*lcdmem | bits);
    }
    else if (state == SEG_OFF)
    {
        // Clear segments
        *lcdmem = (u8) (*lcdmem & ~bitmask);
    }
    else if (state == SEG_ON_BLINK_ON)
    {
        // Clear visible / blink segments before writing
        *lcdmem = (u8) (*lcdmem & ~bitmask);
        *(lcdmem + 0x20) = (u8) (*(lcdmem + 0x20) & ~bitmask);

        // Set visible / blink segments
        *lcdmem = (u8) (*lcdmem | bits);
        *(lcdmem + 0x20) = (u8) (*(lcdmem + 0x20) | bits);
    }
    else if (state == SEG_ON_BLINK_OFF)
    {
        // Clear visible segments before writing
        *lcdmem = (u8) (*lcdmem & ~bitmask);

        // Set visible segments
        *lcdmem = (u8) (*lcdmem | bits);

        // Clear blink segments
        *(lcdmem + 0x20) = (u8) (*(lcdmem + 0x20) & ~bitmask);
    }
    else if (state == SEG_OFF_BLINK_OFF)
    {
        // Clear segments
        *lcdmem = (u8) (*lcdmem & ~bitmask);

        // Clear blink segments
        *(lcdmem + 0x20) = (u8) (*(lcdmem + 0x20) & ~bitmask);
    }
}

// *************************************************************************************************
// @fn          int_to_array
// @brief       Generic integer to array routine. Converts integer n to string.
//                              Default conversion result has leading zeros, e.g. "00123"
//                              Option to convert leading '0' into whitespace (blanks)
// @param       u32 n                   integer to convert
//                              u8 digits               number of digits
//                              u8 blanks               fill up result string with number of
// whitespaces instead of leading zeros
// @return      u8                              string
// *************************************************************************************************
u8 *int_to_array(u32 n, u8 digits, u8 blanks) {
    u8 i;
    u8 digits1 = digits;

    // Preset result string
    memcpy(int_to_array_str, "0000000", 7);

    // Return empty string if number of digits is invalid (valid range for digits: 1-7)
    if ((digits == 0) || (digits > 7))
        return (int_to_array_str);

    // Numbers 0 .. 180 can be copied from int_to_array_conversion_table without conversion
    if (n <= 180)
    {
        if (digits >= 3)
        {
            memcpy(int_to_array_str + (digits - 3), int_to_array_conversion_table[n], 3);
        }
        else                    // digits == 1 || 2
        {
            memcpy(int_to_array_str, int_to_array_conversion_table[n] + (3 - digits), digits);
        }
    }
    else                        // For n > 180 need to calculate string content
    {
        // Calculate digits from least to most significant number
        do
        {
            int_to_array_str[digits - 1] = n % 10 + '0';
            n /= 10;
        }
        while (--digits > 0);
    }

    // Remove specified number of leading '0', always keep last one
    i = 0;
    while ((int_to_array_str[i] == '0') && (i < digits1 - 1))
    {
        if (blanks > 0)
        {
            // Convert only specified number of leading '0'
            int_to_array_str[i] = ' ';
            blanks--;
        }
        i++;
    }

    return (int_to_array_str);
}

// *************************************************************************************************
// @fn          display_value
// @brief       Generic decimal display routine. Used exclusively by set_value function.
// @param       u8 segments                     LCD segments where value is displayed
//                              u32 value                       Integer value to be displayed
//                              u8 digits                       Number of digits to convert
//                              u8 blanks                       Number of leadings blanks in
// int_to_array result string
// @return      none
// *************************************************************************************************
void display_value(u8 segments, u32 value, u8 digits, u8 blanks)
{
    u8 *str;

    str = int_to_array(value, digits, blanks);

    // Display string in blink mode
    display_chars(segments, str, SEG_ON_BLINK_ON);
}


// *************************************************************************************************
// @fn          display_symbol
// @brief       Switch symbol on or off on LCD.
// @param       u8 symbol               A valid LCD symbol (index 0..42)
//                              u8 state                SEG_ON, SEG_OFF, SEG_BLINK
// @return      none
// *************************************************************************************************
void display_symbol(u8 symbol, u8 mode)
{
    u8 *lcdmem;
    u8 bits;
    u8 bitmask;

    if (symbol <= LCD_SEG_L2_DP)
    {
        // Get LCD memory address for symbol from table
        lcdmem = (u8 *) segments_lcdmem[symbol];

        // Get bits for symbol from table
        bits = segments_bitmask[symbol];

        // Bitmask for symbols equals bits
        bitmask = bits;

        // Write LCD memory
        write_lcd_mem(lcdmem, bits, bitmask, mode);
    }
}

// *************************************************************************************************
// @fn          display_char
// @brief       Write to 7-segment characters.
// @param       u8 segment              A valid LCD segment
//                              u8 chr                  Character to display
//                              u8 mode         SEG_ON, SEG_OFF, SEG_BLINK
// @return      none
// *************************************************************************************************
void display_char(u8 segment, u8 chr, u8 mode)
{
    u8 *lcdmem;                 // Pointer to LCD memory
    u8 bitmask;                 // Bitmask for character
    u8 bits, bits1;             // Bits to write

    // Write to single 7-segment character
    if ((segment >= LCD_SEG_L1_3) && (segment <= LCD_SEG_L2_DP))
    {
        // Get LCD memory address for segment from table
        lcdmem = (u8 *) segments_lcdmem[segment];

        // Get bitmask for character from table
        bitmask = segments_bitmask[segment];

        // Get bits from font set
        if ((chr >= 0x30) && (chr <= 0x5A))
        {
            // Use font set
            bits = lcd_font[chr - 0x30];
        }
        else if (chr == 0x2D)
        {
            // '-' not in font set
            bits = BIT1;
        }
        else
        {
            // Other characters map to ' ' (blank)
            bits = 0;
        }

        // When addressing LINE2 7-segment characters need to swap high- and low-nibble,
        // because LCD COM/SEG assignment is mirrored against LINE1
        if (segment >= LCD_SEG_L2_5)
        {
            bits1 = ((bits << 4) & 0xF0) | ((bits >> 4) & 0x0F);
            bits = bits1;

            // When addressing LCD_SEG_L2_5, need to convert ASCII '1' and 'L' to 1 bit,
            // because LCD COM/SEG assignment is special for this incomplete character
            if (segment == LCD_SEG_L2_5)
            {
                if ((chr == '1') || (chr == 'L'))
                    bits = BIT7;
            }
        }

        // Physically write to LCD memory
        write_lcd_mem(lcdmem, bits, bitmask, mode);
    }
}

// *************************************************************************************************
// @fn          display_chars
// @brief       Write to consecutive 7-segment characters.
// @param       u8 segments     LCD segment array
//                              u8 * str                Pointer to a string
//                              u8 mode             SEG_ON, SEG_OFF, SEG_BLINK
// @return      none
// *************************************************************************************************
void display_chars(u8 segments, u8 * str, u8 mode)
{
    u8 i;
    u8 length = 0;              // Write length
    u8 char_start;              // Starting point for consecutive write

    switch (segments)
    {
        // LINE1
        case LCD_SEG_L1_3_0:
            length = 4;
            char_start = LCD_SEG_L1_3;
            break;
        case LCD_SEG_L1_2_0:
            length = 3;
            char_start = LCD_SEG_L1_2;
            break;
        case LCD_SEG_L1_1_0:
            length = 2;
            char_start = LCD_SEG_L1_1;
            break;
        case LCD_SEG_L1_3_1:
            length = 3;
            char_start = LCD_SEG_L1_3;
            break;
        case LCD_SEG_L1_3_2:
            length = 2;
            char_start = LCD_SEG_L1_3;
            break;

        // LINE2
        case LCD_SEG_L2_5_0:
            length = 6;
            char_start = LCD_SEG_L2_5;
            break;
        case LCD_SEG_L2_4_0:
            length = 5;
            char_start = LCD_SEG_L2_4;
            break;
        case LCD_SEG_L2_3_0:
            length = 4;
            char_start = LCD_SEG_L2_3;
            break;
        case LCD_SEG_L2_2_0:
            length = 3;
            char_start = LCD_SEG_L2_2;
            break;
        case LCD_SEG_L2_1_0:
            length = 2;
            char_start = LCD_SEG_L2_1;
            break;
        case LCD_SEG_L2_5_4:
            length = 2;
            char_start = LCD_SEG_L2_5;
            break;
        case LCD_SEG_L2_5_2:
            length = 4;
            char_start = LCD_SEG_L2_5;
            break;
        case LCD_SEG_L2_3_2:
            length = 2;
            char_start = LCD_SEG_L2_3;
            break;
        case LCD_SEG_L2_4_2:
            length = 3;
            char_start = LCD_SEG_L2_4;
            break;
    }

    // Write to consecutive digits
    for (i = 0; i < length; i++)
    {
        // Use single character routine to write display memory
        display_char(char_start + i, *(str + i), mode);
    }
}

// *************************************************************************************************
// @fn          switch_seg
// @brief       Returns index of 7-segment character. Required for display routines that can draw
//                              information on both lines.
// @param       u8 line             LINE1 or LINE2
//                              u8 index1               Index of LINE1
//                              u8 index2               Index of LINE2
// @return      uint8
// *************************************************************************************************
u8 switch_seg(u8 line, u8 index1, u8 index2) {
    if (line == LINE1)
    {
        return index1;
    }
    else                        // line == LINE2
    {
        return index2;
    }
}

// *************************************************************************************************
// @fn          start_blink
// @brief       Start blinking.
// @param       none
// @return      none
// *************************************************************************************************
void start_blink(void)
{
    LCDBBLKCTL |= LCDBLKMOD0;
}

// *************************************************************************************************
// @fn          stop_blink
// @brief       Stop blinking.
// @param       none
// @return      none
// *************************************************************************************************
void stop_blink(void)
{
    LCDBBLKCTL &= ~LCDBLKMOD0;
}

// *************************************************************************************************
// @fn          stop_blink
// @brief       Clear blinking memory.
// @param       none
// @return      none
// *************************************************************************************************
void clear_blink_mem(void)
{
    LCDBMEMCTL |= LCDCLRBM;
}

// *************************************************************************************************
// @fn          set_blink_rate
// @brief       Set blink rate register bits.
// @param       none
// @return      none
// *************************************************************************************************
void set_blink_rate(u8 bits)
{
    LCDBBLKCTL &= ~(BIT7 | BIT6 | BIT5);
    LCDBBLKCTL |= bits;
}
