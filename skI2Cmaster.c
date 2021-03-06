/*******************************************************************************
*  skI2Cmaster - $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(Bs$B!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)(Bp$B!)!)!)!)!)!)!)!)!)(BC$B!)(Bu$B!)!)!)!)(B                    *
*                                                                              *
*    InterI2C       - $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BA$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B                                 *
*    InitI2C_Master - $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)(B             *
*    I2C_Send      - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)(B            *
*    I2C_Receive   - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)(B          *
*                                                                              *
*    $B!)!)!)!)!)(BFSDA/SCL$B!)(Bs$B!)!)!)!)!)(BK$B!)!)!)(Bu$B!)(Bf$B!)(BW$B!)(B^$B!)!)!)!)!)!)!)(Bs$B!)!)!)(Bv$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)!)!)!)(BB         *
*          $B!)!)!)!)(BI2C$B!)!)!)!)!)!)!)(BC$B!)(Bu$B!)!)!)!)!)!)!)(BV$B!)(Br$B!)(Bb$B!)(Bg$B!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)!)!)!)!)!)!)!)(BB         *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2011-12-23  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  Create                            *
*  2.00    2012-01-21  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)!)!)!)(BX   *
* ============================================================================ *
*  PIC 12F1822 16F1827                                                         *
*  MPLAB IDE(V8.63)                                                            *
*  HI-TECH C Compiler for PIC10/12/16 MCUs Version 9.80 in Lite mode           *
*******************************************************************************/
#include <pic.h>
#include "skI2Clib.h"

int AckCheck=0;

// $B!)(BA$B!)(BC$B!)(Bh$B!)!)!)!)!)!)!)!)!)(B`$B!)(BF$B!)(Bb$B!)(BN
// ACKEN RCEN PEN RSEN SEN R/W BF $B!)!)!)(BS$B!)!)!)(BO$B!)!)!)!)!)(Bn$B!)(Bj
/*void I2C_IdleCheck2(char mask)
{
     while (( I2C_SSPCON2 & 0x1F ) | (I2C_SSPSTAT & mask)) ;
}*/
/*******************************************************************************
*  interrupt InterI2C( void )                                                  *
*    $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BA$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B                                                  *
*******************************************************************************/
/*******************************************************************************
*  InitI2C_Master()                                                            *
*    $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)(B                              *
*                                                                              *
*   $B!)!)(B)CPU$B!)!)!)!)(B(FOSC)8MHz$B!)!)!)!)!)!)!)!)!)!)!)!)!)(BA$B!)!)!)!)!)!)!)!)!)!)(BSSP1ADD$B!)!)!)!)!)(BX$B!)!)!)!)!)(BK$B!)(Bv$B!)!)!)(BL$B!)!)!)!)!)!)(B*
*******************************************************************************/
void InitI2C_Master2()
{
     SSPSTAT= 0b10000000 ;   // $B!)(BW$B!)!)!)!)!)(Bx$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)!)!)!)!)(B(100kHz)
     SSPCON1= 0b00101000 ;   // SDA/SCL$B!)(Bs$B!)!)!)!)(BI2C$B!)!)!)(Bg$B!)(Bp$B!)!)!)(BA$B!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)(B
     SSPADD = 0x52       ;   // $B!)(BN$B!)!)!)(Bb$B!)(BN=FOSC/((SSPADD + 1)*4) 8MHz/((0x13+1)*4)=0.1(100KHz)
     SSPIE = 1 ;             // SSP(I2C)$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B
     BCLIE = 1 ;             // MSSP(I2C)$B!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B
     PEIE   = 1 ;             // $B!)!)!)!)!)!)!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B
     GIE    = 1 ;             // $B!)(BS$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B 
     SSPIF = 0 ;             // SSP(I2C)$B!)!)!)!)!)!)!)!)!)(Bt$B!)!)!)(BO$B!)!)!)(BN$B!)!)!)(BA$B!)!)!)!)(B
     BCLIF = 0 ;             // MSSP(I2C)$B!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)!)!)!)!)!)(Bt$B!)!)!)(BO$B!)!)!)(BN$B!)!)!)(BA$B!)!)!)!)(B
}
/*******************************************************************************
*  ans = I2C_Send(adrs,len,buf)                                                *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)!)!)(B(len)$B!)!)!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)(B                       *
*                                                                              *
*    adrs : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)(Bw$B!)!)!)!)!)!)(B(8$B!)(B`119$B!)!)!)!)!)!)(B)                         *
*    len  : $B!)!)!)(BM$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^($B!)(Bo$B!)(BC$B!)(Bg)$B!)!)!)!)!)!)!)!)!)(Bw$B!)!)!)!)!)!)(B                             *
*    buf  : $B!)!)!)(BM$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bi$B!)(B[$B!)!)!)!)!)(Bz$B!)!)!)!)!)(Bw$B!)!)!)!)!)!)(B                             *
*    ans  : 0=$B!)!)!)!)!)(B@1=$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)(B@2=$B!)!)!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)!)!)(B     *
*******************************************************************************/
/*int I2C_Send2(unsigned char adrs,int len,char *buf)
{
     int i , ans ;

     // $B!)(BX$B!)(B^$B!)(B[$B!)(Bg(START CONDITION)
     I2C_IdleCheck2(0x5) ;
     SSPCON2bits.SEN = 1 ;
     // [$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX+$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(BM$B!)!)!)(Bv$B!)!)(B]$B!)!)!)!)!)(BM$B!)!)!)!)(B
     I2C_IdleCheck2(0x5) ;
     AckCheck = 1 ;
     SSPBUF = (char)(adrs<<1) ;             // $B!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)!)!)(BM R/W=0
     while (AckCheck) ;                      // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)(B
     ans = SSPCON2bits.ACKSTAT ;
     if (ans == 0) {
          // [$B!)(Bf$B!)(B[$B!)(B^]$B!)!)!)!)!)(BM$B!)!)!)!)(B
          for (i=0 ; i<len ; i++) {
               I2C_IdleCheck2(0x5) ;
               AckCheck = 1 ;
               SSPBUF = (char)*buf ;        // $B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)(BM
               buf++ ;
               while (AckCheck) ;            // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)(B
               ans = SSPCON2bits.ACKSTAT ;
               if (ans != 0) {
                    ans = 2 ;                // $B!)!)!)!)!)!)(BNOACK$B!)!)!)!)!)!)!)!)(B
                    break ;
               }
          }
     }
     // $B!)(BX$B!)(Bg$B!)(Bb$B!)(Bv(STOP CONDITION)
     I2C_IdleCheck2(0x5) ;
     SSPCON2bits.PEN = 1 ;
     return ans ;
}*/
/*******************************************************************************
*  ans = I2C_Receive(adrs,len,buf)                                             *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)!)!)(B(len)$B!)!)!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)(B                     *
*                                                                              *
*    adrs : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)(Bw$B!)!)!)!)!)!)(B(8$B!)(B`119$B!)!)!)!)!)!)(B)                         *
*    len  : $B!)!)!)(BM$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^($B!)(Bo$B!)(BC$B!)(Bg)$B!)!)!)!)!)!)!)!)!)(Bw$B!)!)!)!)!)!)(B                             *
*    buf  : $B!)!)!)(BM$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bi$B!)(B[$B!)!)!)!)!)(Bz$B!)!)!)!)!)(Bw$B!)!)!)!)!)!)(B                             *
*    ans  : 0=$B!)!)!)!)!)(B@1=$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)(B                                     *
*******************************************************************************/
/*int I2C_Receive2(unsigned char adrs,int len,char *buf)
{
	unsigned dt ;
     int i , ans ;
     
     // $B!)(BX$B!)(B^$B!)(B[$B!)(Bg(START CONDITION)
     I2C_IdleCheck2(0x5) ;
     SSPCON2bits.SEN = 1 ;
     // [$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX+$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(Bf$B!)(B[$B!)(B^$B!)(Bv$B!)!)(B]$B!)!)!)!)!)(BM$B!)!)!)!)(B
     I2C_IdleCheck2(0x5) ;
     AckCheck = 1 ;
     SSPBUF = (char)((adrs<<1)+1) ;    // $B!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)!)!)(BM R/W=1
     while (AckCheck) ;                 // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)(B
     ans = SSPCON2bits.ACKSTAT ;
     if (ans == 0) {
          for (i=1 ; i<=len ; i++) {
               // [$B!)(Bf$B!)(B[$B!)(B^]$B!)!)!)!)!)(BM$B!)!)!)!)(B
               I2C_IdleCheck2(0x5) ;
               SSPCON2bits.RCEN = 1 ;  // $B!)!)!)(BM$B!)!)!)!)!)!)!)!)!)!)(B
               I2C_IdleCheck2(0x4) ;
               *buf = SSPBUF ;         // $B!)!)!)(BM
               buf++ ;
               I2C_IdleCheck2(0x5) ;
               if (i=len) SSPCON2bits.ACKDT = 1 ; // ACK$B!)(Bf$B!)(B[$B!)(B^$B!)!)(BNOACK
               else       SSPCON2bits.ACKDT = 0 ; // ACK$B!)(Bf$B!)(B[$B!)(B^$B!)!)(BACK
               SSPCON2bits.ACKEN = 1 ;            // ACK$B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)!)(B
          }
     }
     // $B!)(BX$B!)(Bg$B!)(Bb$B!)(Bv(STOP CONDITION)
     I2C_IdleCheck2(0x5) ;
     SSPCON2bits.PEN = 1 ;
     return ans ;
}
*/