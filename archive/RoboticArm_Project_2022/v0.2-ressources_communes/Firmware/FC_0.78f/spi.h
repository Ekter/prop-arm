// ######################## SPI - FlightCtrl ###################
#ifndef _SPI_H
#define _SPI_H

#include <util/delay.h>

//-----------------------------------------
#define DDR_SPI DDRB
#define SLAVE_SELECT_DDR_PORT   DDRC
#define SLAVE_SELECT_PORT       PORTC

#if defined(__AVR_ATmega1284P__)
#define DD_SS               PORTB4
#define DD_SCK              PORTB7
#define DD_MOSI             PORTB5
#define DD_MISO             PORTB6
#define SPI_SLAVE_SELECT    PORTC5
#else
#define DD_SS               PB4
#define DD_SCK              PB7
#define DD_MOSI             PB5
#define DD_MISO             PB6
#define SPI_SLAVE_SELECT    PC5
#endif

// for compatibility reasons gcc3.x <-> gcc4.x
#ifndef SPCR
#define SPCR   SPCR0
#endif
#ifndef SPE
#define SPE   SPE0
#endif
#ifndef MSTR
#define MSTR   MSTR0
#endif
#ifndef SPR1
#define SPR1   SPR01
#endif
#ifndef SPR0
#define SPR0   SPR00
#endif
#ifndef SPIE
#define SPIE   SPIE0
#endif
#ifndef SPDR
#define SPDR   SPDR0
#endif
#ifndef SPIF
#define SPIF   SPIF0
#endif
#ifndef SPSR
#define SPSR   SPSR0
#endif
// -------------------------

#define SPI_FCCMD_USER            10
#define SPI_FCCMD_STICK            11
#define SPI_FCCMD_MISC            12
#define SPI_FCCMD_PARAMETER1    13
#define SPI_FCCMD_VERSION        14
#define SPI_FCCMD_SERVOS        15
#define SPI_FCCMD_ACCU            16

struct str_ToNaviCtrl
{
    unsigned char Sync1, Sync2;
    unsigned char Command;
    signed int  IntegralNick;
    signed int  IntegralRoll;
    signed int  AccNick;
    signed int  AccRoll;
    signed int  GyroCompass;
    signed int  GyroNick;
    signed int  GyroRoll;
    signed int  GyroGier;
    union
    {
        unsigned char Byte[12];
        char sByte[12];
        unsigned int Int[6];
        int  sInt[6];
        unsigned long Long[3];
        long sLong[3];
        float Float[3];
    } Param;
    unsigned char Chksum;
};

#define SPI_NCCMD_KALMAN        103
#define SPI_NCCMD_VERSION        104
#define SPI_NCCMD_GPSINFO        105

struct str_FromNaviCtrl
{
    unsigned char Command;
    signed int  GPS_Nick;
    signed int  GPS_Roll;
    signed int  GPS_Gier;
    signed int  CompassValue;
    signed int  Status;
    unsigned int BeepTime;
    union
    {
        unsigned char Byte[12];
        char sByte[12];
        unsigned int Int[6];
        int  sInt[6];
        unsigned long Long[3];
        long sLong[3];
        float Float[3];
    } Param;
    unsigned char Chksum;
};

struct str_FromNaviCtrl_Value
{
 signed char Kalman_K;
 signed char Kalman_MaxDrift;
 signed char Kalman_MaxFusion;
 unsigned char SerialDataOkay;
 signed char GpsZ;
};

struct str_SPI_VersionInfo
{
  unsigned char Major;
  unsigned char Minor;
  unsigned char Patch;
  unsigned char Compatible;
  unsigned char Hardware;
};

// Satfix types for GPSData.SatFix
#define SATFIX_NONE                0x00
#define SATFIX_DEADRECKOING        0x01
#define SATFIX_2D                0x02
#define SATFIX_3D                0x03
#define SATFIX_GPS_DEADRECKOING    0x04
#define SATFIX_TIMEONLY            0x05
// Flags for interpretation of the GPSData.Flags
#define FLAG_GPSFIXOK            0x01 // (i.e. within DOP & ACC Masks)
#define FLAG_DIFFSOLN            0x02 // (is DGPS used)
#define FLAG_WKNSET                0x04 // (is Week Number valid)
#define FLAG_TOWSET                0x08 //    (is Time of Week valid)

struct str_GPSInfo
{
    unsigned char    Flags;            // Status Flags
    unsigned char    NumOfSats;        // number of satelites
    unsigned char    SatFix;            // type of satfix
    unsigned int    HomeDistance;    // distance to Home in dm
    int                HomeBearing;    // bearing to home in deg
};

extern struct IntAnglesPR naviAcc; //from fc.c
extern struct LongAngles angleIntegral; //from fc.c

extern int NaviCntAcc;//from fc.c
extern long desiredHeight;//from fc.c

extern struct str_GPSInfo GPSInfo;
extern struct str_SPI_VersionInfo NC_Version;
extern struct str_FromNaviCtrl_Value FromNaviCtrl_Value;
extern struct str_ToNaviCtrl   ToNaviCtrl;
extern struct str_FromNaviCtrl FromNaviCtrl;
extern unsigned char SPI_CommandCounter,NaviDataOkay;

extern void SPI_MasterInit(void);
extern void SPI_StartTransmitPacket(void);
extern void UpdateSPI_Buffer(void);
extern void SPI_TransmitByte(void);

#endif
