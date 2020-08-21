/*
 *##############################################################################
 * 
 * Compilador : MPLAB XC8 - Ver. 2.20.
 * Microcontrolador: 18F2550 - 28-Pin PDIP
 * Arquivo: BitsConfig_PIC18F2550.h
 * Descrição: Arquivo de configuração:Fuses Bits do PIC18f2550
 * Autor: José Geraldo Diniz Júnior
 * Data:  20 de Agosto de 2020, 19:39
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

//############################################################################*/

#ifndef BITSCONFIG_PIC18F2550_H
#define	BITSCONFIG_PIC18F2550_H

#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

    //########################### Bits de Configuração  ############################

    /*   Tipos de Osciladores (FOSC)
     * 
     *        | XT_XT      : Oscilador XT, XT usado Pela USB.( cristal de 1 a 4 MHz)
     *        |
     *        | XTPLL_XT   : Oscilador XT com PLL habilitado, XT usado Pela USB.
     *        |
     *        | ECIO_EC    : Clock Externo, pino RA6 configurado como I/O, EC usado 
     *        |              Pela USB.
     *        |
     *        | EC_EC      : Clock Externo, CLKOUT (Fosc/4) sobre o pino RA6,  
     *        |              EC usado Pela USB.
     *        |
     *        | ECPLLIO_EC : Clock Externo com PLL habilitado, pino RA6 configurado 
     *        |              como I/O, EC usado Pela USB.
     *        |
     * FOSC = | ECPLL_EC   : Clock Externo com PLL habilitado, CLKOUT (Fosc/4) sobre
     *        |              o pino RA6, EC usado Pela USB.
     *        |
     *        | INTOSCIO_EC: Oscilador Interno, pino RA6 configurado como I/O,
     *        |              EC usado Pela USB.
     *        |
     *        | INTOSC_EC  : Oscilador Interno, CLKOUT (Fosc/4) sobre o pino RA6,
     *        |              EC usado Pela USB.
     *        |
     *        | INTOSC_XT  : Oscilador Interno, XT usado Pela USB.
     *        |
     *        | INTOSC_HS  : Oscilador Interno, HS usado Pela USB.
     *        |
     *        | HS         : Oscilador HS, HS usado Pela USB.
     *        |
     *        | HSPLL_HS   : Oscilador HS com PLL habilitado, HS usado Pela USB.
     */

#pragma config FOSC = HSPLL_HS

    //##############################################################################

    /* Configuração do Prescale (PLL) ( FIGURE 2-1:do Data Sheet)
     * 
     * Depende da config FOSC para ser habilitado
     * 
     *          | 1  : Oscilador de entrada 4 MHz, sem Prescale
     *          | 2  : Oscilador de entrada 8 MHz, dividido por 2
     *          | 3  : Oscilador de entrada 12 MHz, dividido por 3
     * PLLDIV = | 4  : Oscilador de entrada 16 MHz, dividido por 4
     *          | 5  : Oscilador de entrada 20 MHz, dividido por 5
     *          | 6  : Oscilador de entrada 24 MHz, dividido por 6
     *          | 10 : Oscilador de entrada 40 MHz, dividido por 10
     *          | 12 : Oscilador de entrada 48 MHz, dividido por 12
     */

#pragma config PLLDIV = 5

    //##############################################################################

    /* Divisor de Clock do Sistema ( FIGURE 2-1:do Data Sheet)
     * 
     *  Depende da config FOSC para ser habilitado
     * 
     *          | OSC1_PLL2 : Sem PLL - OSC1/OSC2 dividido por 1
     *          |             Com PLL - 96 MHz PLL dividido por 2
     *          |
     * CPUDIV = | OSC2_PLL3 : Sem PLL - OSC1/OSC2 dividido por 2
     *          |             Com PLL - 96 MHz PLL dividido por 3
     *          |
     *          | OSC3_PLL4 : Sem PLL - OSC1/OSC2 dividido por 3
     *          |             Com PLL - 96 MHz PLL dividido por 4
     *          |
     *          | OSC4_PLL6 : Sem PLL - OSC1/OSC2 dividido por 4
     *          |             Com PLL - 96 MHz PLL dividido por 6
     *   
     */

#pragma config CPUDIV = OSC3_PLL4

    // Freq cristal de entrada 20 MHz
    // Freq de CLOCK vinda do PLL 48 MHz
    // Tciclo = 4/48 = 0.0833 us
#define _XTAL_FREQ 24000000 // Freq de Clock do Sistema 48 MHz

    //##############################################################################

    /* 
     * Clock da USB - Usado somente no modo Full Speed (UCFG:FSEN = 1)
     * 
     * Depende da config FOSC para ser usada 
     * 
     *          | 1 : A fonte de clock p/ USB vem diretamente do oscilador primário
     * USBDIV = |
     *          | 2 : A fonte de clock p/ USB vem do bloco 96 MHz PLL dividido por 2
     *  
     */

#pragma config USBDIV = 2

    //##############################################################################

    /* Monitoramento do sinal de clock
     * 
     *         | OFF : Desabilita o monitoramento do sinal de clock
     * FCMEN = |
     *         | ON  : Habilita o monitoramento do sinal de clock
     * 
     */

#pragma config FCMEN = ON 

    //##############################################################################

    /* Mudança do oscilador Externo para interno
     *
     *         | OFF : Desabilita a mudança do oscilador Externo para interno
     * IESO  = |
     *         | ON  : Habilita a mudança do oscilador Externo para interno
     */

#pragma config IESO = OFF

    //##############################################################################

    /* Power-Up-Time 
     * 
     * Aguarda um tempo fixo apos o  microcontrolador se ligado ou resetado antes 
     * de iniciar o programa pricinpal para estabilização do microcontrolador
     *
     *         | OFF : Desabilita o Power-Up-Time
     * PWRT  = |
     *         | ON  : Habilita o Power-Up-Time
     */

#pragma config PWRT = ON 

    //##############################################################################

    /* Brown-out Reset
     * 
     * Monitoramento dos níveis de tenção de operação
     * 
     *       | OFF       : Brown-out Reset Desabilitado em Hardware e Software
     *       | 
     *       | SOFT      : Brown-out Reset Habilitado e controlado por software
     * BOR = |
     *       | ON_ACTIVE : Brown-out Reset Habilitado em Hardware e desabilitado no
     *       |             no modo SLEEP
     *       | 
     *       | ON        : Brown-out Reset Habilitado em Hardware
     * 
     */

#pragma config BOR = ON 

    //##############################################################################

    /* Voltegem de referência do Brown-out Reset
     * 
     *        | 0 : Aproximadamente 4,59 V
     *        | 
     *        | 1 : Aproximadamente 4,33 V
     * BORV = |
     *        | 2 : Aproximadamente 2,79 V
     *        | 
     *        | 3 : Aproximadamente 2,05 V
     * 
     */

#pragma config BORV = 1

    //##############################################################################

    /* Regulador interno de 3,3 V para a USB ( Vsub )
     * 
     *          | OFF : Desabilita o regulador de tensão da USB
     * VREGEN = |
     *          | ON  : Habilita o regulador de tensão da USB
     */
#pragma config VREGEN = OFF

    //##############################################################################

    /* Watchdog Timer
     *
     *       | OFF : WDT Desabilita no Hardware e controlado por software
     * WDT = |
     *       | ON  : WDT Habilita no Hardware e desabilita no software
     */

#pragma config WDT = OFF

    //##############################################################################

    /* Watchdog Timer Postscale
     * 
     *         | 1     |>   1 : 1 
     *         | 2     |>   1 : 2 
     *         | 4     |>   1 : 4 
     *         | 8     |>   1 : 8 
     *         | 16    |>   1 : 16 
     *         | 32    |>   1 : 32 
     *         | 64    |>   1 : 64  
     *         | 128   |>   1 : 128  
     * WDTPS = | 256   |>   1 : 256
     *         | 512   |>   1 : 512
     *         | 1024  |>   1 : 1024
     *         | 2048  |>   1 : 2048
     *         | 4096  |>   1 : 4096 
     *         | 8192  |>   1 : 8192
     *         | 16384 |>   1 : 16384
     *         | 32768 |>   1 : 32768
     */

    //#pragma config WDTPS = 32768

    //##############################################################################

    /* Master Clear Reset 
     * 
     *         | OFF : Habilita o pino RE3 como entrada e Desabilita o MCLR
     * MCLRE = |
     *         | ON  : Desabilita o pino RE3 como entrada e Habilita o MCLR
     *
     */

#pragma config MCLRE = ON

    //##############################################################################

    /* Consumo de energia associado ao TIMER1
     * 
     * Oscilador LOW-POWER no TIMER1
     *
     *           | OFF : TIMER1 configurado para funcionar no modo de alto consumo
     * LPT1OSC = |
     *           | ON  : TIMER1 configurado para funcionar no modo de baixo consumo
     *
     */

#pragma config LPT1OSC = OFF 

    //##############################################################################

    /* Conversores A/D do PORTB
     *
     *          | OFF : Configura os pinos PORTB <4:0> (RB4, RB3, RB2, RB1, RB0)
     *          |       como I/O sobre o RESET
     * PBADEN = |
     *          | ON  : Configura os pinos PORTB <4:0> (AN12, AN11, AN10, AN9, AN8)
     *          |       como canal de entrada de sinal analógico sobre o RESET
     *     
     */

#pragma config PBADEN = OFF

    //##############################################################################

    /* Multiplexação do pino do módulo CCP2 
     * 
     *          | OFF : Define o pino RB3 como sendo I/O utilizada pelo módulo CCP2
     * CCP2MX = |
     *          | ON  : Define o pino RC1 como sendo I/O utilizada pelo módulo CCP2
     *
     */

    //#pragma config CCP2MX = ON  

    //##############################################################################

    /* Stack Full/Underflow
     * 
     *          | OFF : Desabilita o Reset por Stack Full/Underflow
     * STVREN = |
     *          | ON  : Habilita o Reset por Stack Full/Underflow
     *
     */

#pragma config STVREN = OFF

    //##############################################################################

    /* Single-Supply ICSP - Gravação ICSP com baixa tensão
     * 
     *       | OFF : Desabilita o Single-Supply ICSP.
     * LVP = |
     *       | ON  :  Habilita o Single-Supply ICSP.
     *
     */

#pragma config LVP = OFF


    //##############################################################################

    /* Instruções Extendidas
     * 
     *          | OFF : Repertório de instruções estendida e modo de endereçamento
     *          |       indexado desabilitado (modo legal).
     * XINST  = |
     *          | ON  : Repertório de instruções estendida e modo de endereçamento
     *          |       indexado habilitado
     *
     */

#pragma config XINST = OFF 

    //##############################################################################

    // 
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

    // CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

    // CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

    // CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

    // CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

    // CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

    //##############################################################################


#ifdef	__cplusplus
}
#endif

#endif	/* BITSCONFIG_PIC18F2550_H */


//##################################### FIM ####################################
//##############################################################################


