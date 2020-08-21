/*
 *##############################################################################
 * 
 * Projeto: Ex5.1_LCD_8_Bits
 * Descrição: Biblioteca Liquid Crystal Com Barramento de 8 Bits
 * Compilador : MPLAB XC8 - Ver. 2.20
 * Microcontrolador: 18F2550 - 28-Pin PPIN_DIP
 * Arquivo: LiquidCrystal.h
 * Autor: José Geraldo PIN_Diniz Júnior
 * Data: 20 de Agosto de 2020, 19:38
 *
 *##############################################################################
 
                              PIC18F2550 - 28-Pin PDIP
                                  ____________
            ~MCLR/VPP/RE3   ---> | 1        28| <---> RB7/KBI3/PGD      
                  RA0/AN0  <---> | 2        27| <---> RB6/KBI2/PGC
                  RA1/AN1  <---> | 3        26| <---> RB5/KBI1/PGM
      RA2/AN2/VREF-/CVREF  <---> | 4        25| <---> RB4/AN11/KBI0
            RA3/AN3/VREF+  <---> | 5        24| <---> RB3/AN9/CCP2/VPO
      RA4/T0CKI/C1OUT/RCV  <---> | 6        23| <---> RB2/AN8/INT2/VMO
 RA5/AN4/~SS/HLVDIN/C2OUT  <---> | 7        22| <---> RB1/AN10/INT1/SCK/SCL
                      VSS   ---> | 8        21| <---> RB0/AN12/INT0/FLT0/SDI/SDA
                OSC1/CLKI   ---> | 9        20| <---  VDD
            OSC2/CLKO/RA6  <---  | 10       19| <---  VSS
      RC0/T1OSO/T13CKIVDD  <---> | 11       18| <---> RC7/RX/DT/SDO
   RC1/T1OSI/CCP2(1)/~UOE  <---> | 12       17| <---> RC6/TX/CK
                 RC2/CCP1  <---> | 13       16| <---> RC5/D+/VP
                     VUSB  <---> | 14       15| <---> RC4/D-/VM
                                 |____________|
 
 
 *############################################################################*/

//##############################################################################
//########################### Arquivos de Cabeçalho ############################
#include "BitsConfig_PIC18F2550.h"

//##############################################################################
//########################## Mapeamento de Hardware ############################

#define PIN_D7 PORTBbits.RB7  // Define o Pino de Dados D7
#define PIN_D6 PORTBbits.RB6  // Define o Pino de Dados D6
#define PIN_D5 PORTBbits.RB5  // Define o Pino de Dados D5
#define PIN_D4 PORTBbits.RB4  // Define o Pino de Dados D4
#define PIN_D3 PORTBbits.RB3  // Define o Pino de Dados D3
#define PIN_D2 PORTBbits.RB2  // Define o Pino de Dados D2
#define PIN_D1 PORTBbits.RB1  // Define o Pino de Dados D1
#define PIN_D0 PORTBbits.RB0  // Define o Pino de Dados D0

// Associa os PIN_D(7 à 0)_Direction ao Reg. de direção do TRISBbits.RB(7 à 0)
#define PIN_D7_Direction TRISBbits.RB7  
#define PIN_D6_Direction TRISBbits.RB6  
#define PIN_D5_Direction TRISBbits.RB5
#define PIN_D4_Direction TRISBbits.RB4
#define PIN_D3_Direction TRISBbits.RB3
#define PIN_D2_Direction TRISBbits.RB2
#define PIN_D1_Direction TRISBbits.RB1
#define PIN_D0_Direction TRISBbits.RB0

#define PIN_RS PORTCbits.RC0  // Define o Pino de Seleção do Registrador RS
#define PIN_EN PORTCbits.RC1  // Define o Pino de Enable

// Associa o PIN_RS_Direction ao Reg. de direção do TRISCbits.RC0
#define PIN_RS_Direction TRISCbits.RC0 

// Associa o PIN_EN_Direction ao Reg. de direção do TRISCbits.RC1
#define PIN_EN_Direction TRISCbits.RC1 

//##############################################################################
//############################# Variáveis Globais ##############################
#define OUTPUT 0b0
#define INPUT 0b1


// 0b00001110 comando padrão
// Display Ligado 
// Cursor Ligado
// Cursor Blink Desligado
unsigned char DISPLAY_CONTROL = 0x0E; // 0b00001110 comando padrão

unsigned char CURSOR_DISPLAY_SHIFT = 0x00; 


//%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNÇÃO DE CONFIGURAÇÃO %%%%%%%%%%%%%%%%%%%%%%%%%%%
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//############################## Função lcd_start ##############################

void lcd_start(void);

//%%%%%%%%%%%%%%%%%%%% FUNÇÕES DE ENVIO DE COMANDO E DADOS %%%%%%%%%%%%%%%%%%%%%
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//##############################################################################
//############################### Função lcd_cmd ###############################

void lcd_cmd(char cmd);

//##############################################################################
//############################ Função lcd_printByte ############################

void lcd_print_Byte(char col, char row, char data);

//##############################################################################
//############################ Função lcd_printText ############################

void lcd_print_Text(char col, char row, char *dados);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNÇÃO DE CONTROLE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//############################# Função lcd_clear ###############################

void lcd_clear(void);

//##############################################################################
//########################## Função lcd_display_ON #############################

void lcd_display_ON(void);

//##############################################################################
//######################### Função lcd_display_OFF #############################

void lcd_display_OFF(void);

//##############################################################################
//########################### Função lcd_cursor_ON #############################

void lcd_cursor_ON(void);

//##############################################################################
//########################## Função lcd_cursor_OFF #############################

void lcd_cursor_OFF(void);

//##############################################################################
//####################### Função lcd_cursor_blink_ON ###########################

void lcd_cursor_blink_ON(void);

//##############################################################################
//####################### Função lcd_cursor_blink_OFF ##########################

void lcd_cursor_blink_OFF(void);

//##############################################################################
//########################## Função lcd_setCursor ##############################

void lcd_setCursor(char col, char row);

//##############################################################################
//###################### Função lcd_shift_cursor_left ##########################

void lcd_shift_cursor_left(char shiftCol);

//##############################################################################
//####################### Função lcd_shift_cursor_right ########################

void lcd_shift_cursor_right(char shiftCol);

//##############################################################################
//######################## Função lcd_shift_text_left ##########################

void lcd_shift_text_left(char shiftCol);

//##############################################################################
//####################### Função lcd_shift_text_right ##########################

void lcd_shift_text_right(char shiftCol);

//############################### FIM DO ARQUIVO ###############################
//##############################################################################

