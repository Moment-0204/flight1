/*******************************************************************************
*  skI2Clib - $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)!)!)!)!)(BC$B!)(Bu$B!)!)!)!)(B                                             *
*             $B!)!)!)!)!)!)!)(BC$B!)(Bu$B!)!)!)!)!)!)(BI2C$B!)(Bf$B!)(Bo$B!)(BC$B!)(BX(RTC/EEPROM$B!)!)(B)$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)!)!)!)(BW  *
*                                                                              *
*    InterI2C       - $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BA$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B                                 *
*    InitI2C_Master - $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)(B             *
*    I2C_Start      - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BX$B!)(B^$B!)(B[$B!)(Bg$B!)(BR$B!)!)!)(Bf$B!)(BB$B!)(BV$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)(B           *
*    I2C_rStart     - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bs$B!)(B[$B!)(Bg$B!)(BE$B!)(BX$B!)(B^$B!)(B[$B!)(Bg$B!)(BR$B!)!)!)(Bf$B!)(BB$B!)(BV$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)(B *
*    I2C_Stop       - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BX$B!)(Bg$B!)(Bb$B!)(Bv$B!)(BR$B!)!)!)(Bf$B!)(BB$B!)(BV$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)(B           *
*    I2C_Send       - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(BP$B!)(Bo$B!)(BC$B!)(Bg$B!)!)!)(BM$B!)!)!)!)!)!)!)!)(B                   *
*    I2C_Receive    - $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(BP$B!)(Bo$B!)(BC$B!)(Bg$B!)!)!)(BM$B!)!)!)!)!)!)!)!)(B                 *
*                                                                              *
*    $B!)!)!)!)!)(BFSDA/SCL$B!)(Bs$B!)!)!)!)!)(BK$B!)!)!)(Bu$B!)(Bf$B!)(BW$B!)(B^$B!)!)!)!)!)!)!)(Bs$B!)!)!)(Bv$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)!)!)!)(BB         *
*          $B!)!)!)(BM$B!)(BN$B!)!)!)(Bb$B!)(BN$B!)!)(B100/400KHz(CPU8MHz)$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BB                  *
*          $B!)(B}$B!)!)!)(B`$B!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BA"I2C_Start"$B!)!)!)!)!)!)!)!)!)!)!)!)(B *
*          SSP2$B!)!)!)!)!)(Bp$B!)!)!)!)!)!)!)!)!)!)!)(BAskI2Clib.h$B!)!)(B"#define I2C_MSSP2_USE"$B!)!)!)!)!)!)!)!)!)!)(B *
* ============================================================================ *
*  VERSION DATE        BY                    CHANGE/COMMENT                    *
* ---------------------------------------------------------------------------- *
*  1.00    2012-01-20  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  Create                            *
*  1.01    2013-02-16  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  XC8 C Compiler $B!)!)!)!)!)!)!)!)!)(BX         *
*  2.00    2014-11-01  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  $B!)(B}$B!)!)!)(B`$B!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)!)(B              *
*  2.10    2015-03-04  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  $B!)!)!)!)!)!)!)!)(B100/400KHz$B!)(Bw$B!)!)!)!)!)!)!)!)!)(BX    *
*  3.00    2015-04-20  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  SSP1/SSP2$B!)!)!)!)!)!)(B16F193x$B!)!)!)!)!)!)(B      *
*  3.01    2015-07-19  $B!)!)!)!)!)!)!)(BH$B!)(B[($B!)!)!)!)!)!)!)!)(B)  $B!)(BR$B!)!)!)!)!)(Bg$B!)!)!)!)(B                      *
* ============================================================================ *
*  PIC 12F1822 16F18xx 16F193x 18F25K22 18F26J50                               *
*  MPLAB IDE(V8.63) MPLAB X(v2.15)                                             *
*  MPLAB(R) XC8 C Compiler Version 1.00/1.32                                   *
*******************************************************************************/
#include <xc.h>
#include "skI2Clib.h"

int AckCheck ;           // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)(Bp$B!)(Bt$B!)!)!)(BO$B!)!)!)!)(B
int CollisionCheck ;     // $B!)!)!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)(Bo$B!)(Bp$B!)(Bt$B!)!)!)(BO$B!)!)!)!)(B

// $B!)(BA$B!)(BC$B!)(Bh$B!)!)!)!)!)!)!)!)!)(B`$B!)(BF$B!)(Bb$B!)(BN
// ACKEN RCEN PEN RSEN SEN R/W BF $B!)!)!)(BS$B!)!)!)(BO$B!)!)!)!)!)(Bn$B!)(Bj
void I2C_IdleCheck(char mask)
{
     while (( I2C_SSPCON2 & 0x1F ) | (I2C_SSPSTAT & mask)) ;
}
/*******************************************************************************
*  InterI2C( void )                                                            *
*    $B!)(Bh$B!)(BQ$B!)(Bb($B!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh)$B!)!)!)(BA$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B                                  *
*     $B!)!)!)!)!)!)!)!)!)!)!)!)!)(BC$B!)!)!)(Bv$B!)!)!)(BO$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B                         *
*******************************************************************************/
/*void InterI2C( void )
{
     if (I2C_SSPIF == 1) {       // SSP(I2C)$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BH
          if (AckCheck == 1) AckCheck = 0 ;
          I2C_SSPIF = 0 ;        // $B!)(Bt$B!)!)!)(BO$B!)(BN$B!)!)!)(BA
     }
     if (I2C_BCLIF == 1) {       // MSSP(I2C)$B!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BH
          CollisionCheck = 1 ;
          I2C_BCLIF = 0 ;        // $B!)(Bt$B!)!)!)(BO$B!)(BN$B!)!)!)(BA
     }
}*/
/*******************************************************************************
*  InitI2C_Master(speed)                                                       *
*    $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)(B                              *
*                                                                              *
*    speed : I2C$B!)!)!)!)!)(BM$B!)!)!)(Bx$B!)!)!)(Bw$B!)!)(B(0=100KHz 1=400KHz)                            *
*                                                                              *
*    $B!)!)(B)$B!)(BN$B!)!)!)(Bb$B!)(BN8MHz$B!)!)!)!)!)!)!)!)!)!)!)!)!)(BA$B!)!)!)!)!)(BN$B!)!)!)(Bb$B!)(BN$B!)!)(BSSPADD$B!)!)!)!)!)(BX$B!)!)!)!)!)(BK$B!)(Bv$B!)!)!)(BL$B!)!)!)!)!)!)(B *
*             4MHz  8MHz  16MHz  32MHz  40MHz  48MHz  64MHz                    *
*    100KHz   0x09  0x13   0x27   0x4F   0x63   0x77   0x9F                    *
*    400kHz         0x04   0x09   0x13   0x18   0x1D   0x27                    *
*    400KHz$B!)!)!)!)!)!)!)!)!)!)(B250KHz$B!)!)!)!)!)!)!)!)!)(Bx$B!)!)!)(Bo$B!)!)!)!)!)!)!)!)!)!)!)!)!)(BA100KHz$B!)!)!)!)!)!)!)!)!)!)!)!)!)(Bx$B!)!)!)!)(B*
*    $B!)!)!)(Bl$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(Bx$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(Bv$B!)(BZ$B!)!)!)(Bx$B!)!)!)!)!)!)!)!)!)!)!)!)!)(BB          * 
*******************************************************************************/
/*void InitI2C_Master(int speed)
{
     I2C_SSPSTAT= 0b10000000 ;     // $B!)(BW$B!)!)!)!)!)(Bx$B!)!)!)(B[$B!)(Bh($B!)(BX$B!)!)!)(B[$B!)!)!)(B[$B!)(Bg$B!)!)!)!)(BOFF)$B!)!)!)!)!)!)!)!)!)!)(B(100kHz/1MHz)
     I2C_SSPCON1= 0b00101000 ;     // SDA/SCL$B!)(Bs$B!)!)!)!)(BI2C$B!)!)!)(Bg$B!)(Bp$B!)!)!)(BA$B!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)(B[$B!)(Bh$B!)!)!)!)!)!)(B
     if (speed == 0) {
          I2C_SSPADD = 0x4F  ;     // $B!)(BN$B!)!)!)(Bb$B!)(BN=FOSC/((SSPADD + 1)*4) 8MHz/((0x13+1)*4)=0.1(100KHz)
     } else {
          I2C_SSPADD = 0x13  ;     // $B!)(BN$B!)!)!)(Bb$B!)(BN=FOSC/((SSPADD + 1)*4) 8MHz/((0x04+1)*4)=0.4(400KHz)
          I2C_SSPSTAT_SMP = 0 ;    // $B!)!)!)!)!)!)!)(Bx$B!)!)!)(B[$B!)(Bh($B!)(BX$B!)!)!)(B[$B!)!)!)(B[$B!)(Bg$B!)!)!)!)(BON)$B!)!)!)!)!)!)!)!)!)!)(B(400kHz)
     }
     I2C_SSPIE = 1 ;               // SSP(I2C)$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B
     I2C_BCLIE = 1 ;               // MSSP(I2C)$B!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B
     PEIE      = 1 ;               // $B!)!)!)!)!)!)!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B
     GIE       = 1 ;               // $B!)(BS$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B 
     I2C_SSPIF = 0 ;               // SSP(I2C)$B!)!)!)!)!)!)!)!)!)(Bt$B!)!)!)(BO$B!)!)!)(BN$B!)!)!)(BA$B!)!)!)!)(B
     I2C_BCLIF = 0 ;               // MSSP(I2C)$B!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)!)!)!)!)!)(Bt$B!)!)!)(BO$B!)!)!)(BN$B!)!)!)(BA$B!)!)!)!)(B
}*/
/*******************************************************************************
*  ans = I2C_Start(adrs,rw)                                                    *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BX$B!)(B^$B!)(B[$B!)(Bg$B!)(BR$B!)!)!)(Bf$B!)(BB$B!)(BV$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)(B                            *
*                                                                              *
*    adrs : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)(B                                     *
*    rw   : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(Bw$B!)!)!)!)!)!)!)!)!)!)(B                                 *
*           0=$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(Bv$B!)!)!)(B@1=$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)!)(Bv$B!)!)(B         *
*    ans  : 0=$B!)!)!)!)(B                                                             *
*           1=$B!)!)!)!)(B($B!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B) -1=$B!)!)!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)(B  *
*******************************************************************************/
int I2C_Start(int adrs,int rw)
{
     CollisionCheck = 0 ;
     // $B!)(BX$B!)(B^$B!)(B[$B!)(Bg(START CONDITION)
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_SEN = 1 ;
     // [$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX]$B!)!)!)!)!)(BM$B!)!)!)!)(B
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == 1) return -1 ;
     AckCheck = 1 ;
     I2C_SSPBUF = (char)((adrs<<1)+rw) ;     // $B!)(BA$B!)(Bh$B!)!)!)(BX + R/W$B!)!)!)!)!)(BM
     while (AckCheck) ;                      // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)(B
     if (CollisionCheck == 1) return -1 ;
     return I2C_SSPCON2_ACKSTAT ;
}
/*******************************************************************************
*  ans = I2C_rStart(adrs,rw)                                                   *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bs$B!)(B[$B!)(Bg$B!)(BE$B!)(BX$B!)(B^$B!)(B[$B!)(Bg$B!)(BR$B!)!)!)(Bf$B!)(BB$B!)(BV$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)(B                  *
*                                                                              *
*    adrs : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)(B                                     *
*    rw   : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(Bw$B!)!)!)!)!)!)!)!)!)!)(B                                 *
*           0=$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(Bv$B!)!)!)(B@1=$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(BM$B!)!)!)!)!)!)!)!)!)(Bv$B!)!)(B         *
*    ans  : 0=$B!)!)!)!)(B                                                             *
*           1=$B!)!)!)!)(B($B!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)(B) -1=$B!)!)!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)(B  *
*******************************************************************************/
int I2C_rStart(int adrs,int rw)
{
     CollisionCheck = 0 ;
     // $B!)!)!)(Bs$B!)(B[$B!)(Bg$B!)(BE$B!)(BX$B!)(B^$B!)(B[$B!)(Bg(REPEATED START CONDITION)
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_RSEN = 1 ;
     // [$B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BA$B!)(Bh$B!)!)!)(BX]$B!)!)!)!)!)(BM$B!)!)!)!)(B
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == 1) return -1 ;
     AckCheck = 1 ;
     I2C_SSPBUF = (char)((adrs<<1)+rw) ;     // $B!)(BA$B!)(Bh$B!)!)!)(BX + R/W$B!)!)!)!)!)(BM
     while (AckCheck) ;                      // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)(B
     if (CollisionCheck == 1) return -1 ;
     return I2C_SSPCON2_ACKSTAT ;
}
/*******************************************************************************
*  ans = I2C_Stop()                                                            *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(BX$B!)(Bg$B!)(Bb$B!)(Bv$B!)(BR$B!)!)!)(Bf$B!)(BB$B!)(BV$B!)!)!)!)!)!)!)!)!)(Bs$B!)!)!)!)!)!)!)!)(B                            *
*    ans  :  0=$B!)!)!)!)(B                                                            *
*           -1=$B!)!)!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)(B                                    *
*******************************************************************************/
int I2C_Stop()
{
     CollisionCheck = 0 ;
     // $B!)(BX$B!)(Bg$B!)(Bb$B!)(Bv(STOP CONDITION)
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_PEN = 1 ;
     if (CollisionCheck == 1) return -1 ;
     else                     return  0 ;
}
/*******************************************************************************
*  ans = I2C_Send(dt)                                                          *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(BP$B!)(Bo$B!)(BC$B!)(Bg$B!)!)!)(BM$B!)!)!)!)!)!)!)!)(B                                    *
*                                                                              *
*    dt  : $B!)!)!)(BM$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)(B                                          *
*    ans  : 0=$B!)!)!)!)(B                                                             *
*           1=$B!)!)!)!)(B($B!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)!)(BNOACK$B!)!)!)!)!)!)!)!)(B)                 *
*          -1=$B!)!)!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)(B                                     *
*******************************************************************************/
int I2C_Send(char dt)
{
     CollisionCheck = 0 ;
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == 1) return -1 ;
     AckCheck = 1 ;
     I2C_SSPBUF = dt ;                  // $B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)(BM
     while (AckCheck) ;                 // $B!)!)!)!)!)!)!)!)!)!)(BACK$B!)!)!)!)!)!)!)!)!)!)(B
     if (CollisionCheck == 1) return -1 ;
     return I2C_SSPCON2_ACKSTAT ;
}
/*******************************************************************************
*  ans = I2C_Receive(ack)                                                      *
*    $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(BP$B!)(Bo$B!)(BC$B!)(Bg$B!)!)!)(BM$B!)!)!)!)!)!)!)!)(B                                  *
*                                                                              *
*    ack  : $B!)(BX$B!)!)!)(B[$B!)(Bu$B!)!)!)!)!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)(Bw$B!)!)!)!)!)!)!)!)(B                                 *
*           0:ACK$B!)!)!)!)!)!)!)(B@1:NOACK$B!)!)!)!)!)!)(B($B!)!)!)(BM$B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)!)!)!)!)!)(B1)                  *
*    ans  : $B!)!)!)(BM$B!)!)!)!)!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)!)(B                                               *
*           -1=$B!)!)!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bo$B!)(BX$B!)!)!)!)!)!)!)!)(B                                    *
*******************************************************************************/
int I2C_Receive(int ack)
{
     int dt ;

     CollisionCheck = 0 ;
     I2C_IdleCheck(0x5) ;
     I2C_SSPCON2_RCEN = 1 ;           // $B!)!)!)(BM$B!)!)!)!)!)!)!)!)!)!)(B
     I2C_IdleCheck(0x4) ;
     if (CollisionCheck == 1) return -1 ;
     dt = I2C_SSPBUF ;                // $B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)(BM
     I2C_IdleCheck(0x5) ;
     if (CollisionCheck == 1) return -1 ;
     I2C_SSPCON2_ACKDT = ack ;        // ACK$B!)(Bf$B!)(B[$B!)(B^$B!)!)!)(BZ$B!)(Bb$B!)(Bg
     I2C_SSPCON2_ACKEN = 1 ;          // ACK$B!)(Bf$B!)(B[$B!)(B^$B!)!)!)!)!)!)(B
     return dt ;
}
