/* -------------------------------------------------------------------------------
	USER SETTINGS FOR CONFIGURATION OF IOs used to drive LCd with HD44780 driver
	---------------------------------------------------------------------------- */
#define LCD_RS_DDR		DDRC
#define LCD_RS_PORT 	PORTC
#define LCD_RS_BIT		(1 << PC0)

#define LCD_E_DDR		DDRC
#define LCD_E_PORT		PORTC
#define LCD_E_BIT		(1 << PC1)

#define LCD_D4_DDR		DDRC
#define LCD_D4_PORT		PORTC
#define LCD_D4_BIT		(1 << PC2)

#define LCD_D5_DDR		DDRC
#define LCD_D5_PORT		PORTC
#define LCD_D5_BIT		(1 << PC3)

#define LCD_D6_DDR		DDRC
#define LCD_D6_PORT		PORTC
#define LCD_D6_BIT		(1 << PC4)

#define LCD_D7_DDR		DDRC
#define LCD_D7_PORT		PORTC
#define LCD_D7_BIT		(1 << PC5)