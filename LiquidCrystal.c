/*
 *##############################################################################
 * 
 * Projeto: Ex5.1_LCD_8_Bits
 * Descrição: Biblioteca Liquid Crystal Com Barramento de 8 Bits
 * Compilador : MPLAB XC8 - Ver. 2.20
 * Microcontrolador: 18F2550 - 28-Pin PPIN_DIP
 * Arquivo: LiquidCrystal.c
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
#include "LiquidCrystal.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNÇÃO DE CONFIGURAÇÃO %%%%%%%%%%%%%%%%%%%%%%%%%%%
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//############################## Função lcd_start ##############################

void lcd_start() {

    __delay_ms(15); // Aguarda 15 ms pela inicialização do Display

    // Configuração dos Pinos de controle e dados do LCD
    PIN_D7_Direction = OUTPUT;
    PIN_D6_Direction = OUTPUT;
    PIN_D5_Direction = OUTPUT;
    PIN_D4_Direction = OUTPUT;
    PIN_D3_Direction = OUTPUT;
    PIN_D2_Direction = OUTPUT;
    PIN_D1_Direction = OUTPUT;
    PIN_D0_Direction = OUTPUT;

    PIN_RS_Direction = OUTPUT;
    PIN_EN_Direction = OUTPUT;

    // Configuração do Display 0b00111000 = 0x38
    // Comunicação do barramento de dados em 8 bits.
    // Display de duas ou mais linhas.
    // Matriz de 7x5 + Cursor.
    lcd_cmd(0x38);
    __delay_us(60);

    // Configuração do Cursor
    // 0b00001110 comando padrão
    // Display Ligado 
    // Cursor Ligado
    // Cursor Blink Desligado
    lcd_cmd(DISPLAY_CONTROL);
    __delay_us(60);

    // Limpa o display
    lcd_clear();

    // Exibe uma mensagem de inicialização
    lcd_print_Text(1, 1, "LCD STARTING...");
    __delay_ms(3000);

    // Limpa o display
    lcd_clear();

}

//%%%%%%%%%%%%%%%%%%%% FUNÇÕES DE ENVIO DE COMANDO E DADOS %%%%%%%%%%%%%%%%%%%%%
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//##############################################################################
//############################## Função lcd_cmd8 ###############################

void lcd_cmd(char cmd) {

    PIN_EN = 0x00;

    PIN_D7 = cmd >> 7;
    PIN_D6 = cmd >> 6;
    PIN_D5 = cmd >> 5;
    PIN_D4 = cmd >> 4;
    PIN_D3 = cmd >> 3;
    PIN_D2 = cmd >> 2;
    PIN_D1 = cmd >> 1;
    PIN_D0 = cmd >> 0;

    PIN_EN = 0x01;
    __delay_us(40);
    PIN_EN = 0x00;

}

//##############################################################################
//############################ Função lcd_printByte ############################

void lcd_print_Byte(char col, char row, char data) {

    lcd_setCursor(col, row); // Posiciona o cursor na coluna e linha desejada

    PIN_RS = 0x01; // Seleciona o registrador de dados do Display

    lcd_cmd(data);

}

//##############################################################################
//############################ Função lcd_printText ############################

void lcd_print_Text(char col, char row, char *dados) {

    lcd_setCursor(col, row); // Posiciona o cursor na coluna e linha desejada

    PIN_RS = 0x01; // Seleciona o registrador de dados do Display

    while (*dados != 0) {
        lcd_cmd(*dados);
        dados++;
    }
}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FUNÇÃO DE CONTROLE %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//############################# Função lcd_clear ###############################

void lcd_clear() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    lcd_cmd(0x01); // limpar display e posicionar o cursor na linha 1 coluna 1 

    __delay_ms(2);

}

//##############################################################################
//########################## Função lcd_display_ON #############################

void lcd_display_ON() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    DISPLAY_CONTROL = DISPLAY_CONTROL | 0b00000100;

    lcd_cmd(DISPLAY_CONTROL); // Envia o comando para ligar o Display 

    __delay_ms(2);

}


//##############################################################################
//######################### Função lcd_display_OFF #############################

void lcd_display_OFF() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    DISPLAY_CONTROL = DISPLAY_CONTROL & ~0b00000100;

    lcd_cmd(DISPLAY_CONTROL); // Envia o comando para Desligar o Display 

    __delay_ms(2);


}

//##############################################################################
//########################### Função lcd_cursor_ON #############################

void lcd_cursor_ON() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    DISPLAY_CONTROL = DISPLAY_CONTROL | 0b00000010;

    lcd_cmd(DISPLAY_CONTROL); // Envia o comando para ligar o Cursor 

    __delay_ms(2);


}

//##############################################################################
//########################## Função lcd_cursor_OFF #############################

void lcd_cursor_OFF() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    DISPLAY_CONTROL = DISPLAY_CONTROL & ~0b00000010;

    lcd_cmd(DISPLAY_CONTROL); // Envia o comando para Desligar o Cursor 

    __delay_ms(2);

}

//##############################################################################
//####################### Função lcd_cursor_blink_ON ###########################

void lcd_cursor_blink_ON() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    DISPLAY_CONTROL = DISPLAY_CONTROL | 0b00000001;

    lcd_cmd(DISPLAY_CONTROL); // Envia o comando para ligar o Cursor Blink

    __delay_ms(2);

}

//##############################################################################
//####################### Função lcd_cursor_blink_OFF ##########################

void lcd_cursor_blink_OFF() {

    PIN_RS = 0x00; // Habilita o envio de comandos para o LCD

    DISPLAY_CONTROL = DISPLAY_CONTROL & ~0b00000001;

    lcd_cmd(DISPLAY_CONTROL); // Envia o comando para Desligar o Cursor Blink

    __delay_ms(2);

}

//##############################################################################
//########################## Função lcd_setCursor ##############################

void lcd_setCursor(char col, char row) {

    PIN_RS = 0x00; // Seleciona o registrador de instrução do Display

    char address1[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
        0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8F};

    char address2[] = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8,
        0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCF};

    if (row == 1) {
        lcd_cmd(address1[col - 1]);
    }

    if (row == 2) {
        lcd_cmd(address2[col - 1]);
    }
}

//##############################################################################
//###################### Função lcd_shift_cursor_left ##########################

void lcd_shift_cursor_left(char shiftCol) {

    for (char i = 0; i < shiftCol; i++) {

        PIN_RS = 0x00; // Habilita o envio de comandos para o LCD 

        lcd_cmd(0x10); // Envia o comando para mover o cursor para esquerda

        __delay_ms(2);

    }

}

//##############################################################################
//####################### Função lcd_shift_cursor_right ########################

void lcd_shift_cursor_right(char shiftCol) {

    for (char i = 0; i < shiftCol; i++) {

        PIN_RS = 0x00; // Habilita o envio de comandos para o LCD 

        lcd_cmd(0x14); // Envia o comando para mover o cursor para direita

        __delay_ms(2);
    }

}

//##############################################################################
//######################## Função lcd_shift_text_left ##########################

void lcd_shift_text_left(char shiftCol) {

    for (char i = 0; i < shiftCol; i++) {
        PIN_RS = 0x00; // Habilita o envio de comandos para o LCD 

        lcd_cmd(0x18); // Envia o comando para mover o texto para esquerda

        __delay_ms(2);

    }

}

//##############################################################################
//####################### Função lcd_shift_text_right ##########################

void lcd_shift_text_right(char shiftCol) {

    for (char i = 0; i < shiftCol; i++) {

        PIN_RS = 0x00; // Habilita o envio de comandos para o LCD 

        lcd_cmd(0x1C); // Envia o comando para mover o texto para direita

        __delay_ms(2);
    }

}


//############################### FIM DO ARQUIVO ###############################
//##############################################################################
