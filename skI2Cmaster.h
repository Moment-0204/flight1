// skI2Cmaster.h
// $B!)(Bh$B!)(BQ$B!)(Bb$B!)!)!)(BM$B!)!)!)(B}$B!)(BX$B!)(B^$B!)(B[$B!)!)!)!)!)(Bp$B!)!)!)(BC$B!)(Bu$B!)!)!)!)!)(Bp$B!)(BC$B!)!)!)(BN$B!)!)!)(B[$B!)(Bh$B!)(Bt$B!)(B@$B!)(BC$B!)!)(B
#ifndef _SKI2CMASTER_H_
#define _SKI2CMASTER_H_

int AckCheck;

void InitI2C_Master2() ;
int  I2C_Send2(unsigned char adrs,int len,char *buf) ;
int  I2C_Receive2(unsigned char adrs,int len,char *buf) ;


#endif
