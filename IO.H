//****************************************************************************
// @Module        GPIO
// @Filename      IO.H
// @Project       ssc.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.3
//
// @Description:  This file contains all function prototypes and macros for 
//                the IO module.
//
//----------------------------------------------------------------------------
// @Date          2015/9/2 12:35:11
//
//****************************************************************************

// USER CODE BEGIN (IO_Header,1)

// USER CODE END



#ifndef _IO_H_
#define _IO_H_

//****************************************************************************
// @Project Includes
//****************************************************************************

// USER CODE BEGIN (IO_Header,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (IO_Header,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (IO_Header,4)

// USER CODE END

//   Port 0

sbit P0_0       = 0x80;    
sbit P0_1       = 0x81;    
sbit P0_2       = 0x82;    
sbit P0_3       = 0x83;    
sbit P0_4       = 0x84;    
sbit P0_5       = 0x85;    
sbit P0_7       = 0x87;    

//   Port 1

sbit P1_0       = 0x90;    
sbit P1_1       = 0x91;    
sbit P1_2       = 0x92;    
sbit P1_3       = 0x93;    
sbit P1_4       = 0x94;    
sbit P1_5       = 0x95;    
sbit P1_6       = 0x96;    
sbit P1_7       = 0x97;    

//   Port 2

sbit P2_0       = 0xA0;    
sbit P2_1       = 0xA1;    
sbit P2_2       = 0xA2;    
sbit P2_3       = 0xA3;    
sbit P2_4       = 0xA4;    
sbit P2_5       = 0xA5;    
sbit P2_6       = 0xA6;    
sbit P2_7       = 0xA7;    

//   Port 3

sbit P3_0       = 0xB0;    
sbit P3_1       = 0xB1;    
sbit P3_2       = 0xB2;    
sbit P3_3       = 0xB3;    
sbit P3_4       = 0xB4;    
sbit P3_5       = 0xB5;    
sbit P3_6       = 0xB6;    
sbit P3_7       = 0xB7;    

//   Port 4

sbit P4_0       = 0xC8;    
sbit P4_1       = 0xC9;    
sbit P4_3       = 0xCB;    

//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (IO_Header,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_Header,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (IO_Header,7)

// USER CODE END


//****************************************************************************
// @Prototypes Of Global Functions
//****************************************************************************

void IO_vInit(void);


// USER CODE BEGIN (IO_Header,8)

// USER CODE END


//****************************************************************************
// @Macro         IO_ubReadPin(PinName) 
//
//----------------------------------------------------------------------------
// @Description   This macro returns the status of the chosen portpin.
//                Note:
//                'PinName' identifies the pin of a bit-addressable port. The 
//                default names can be changed in the port configuration 
//                dialog. 
//
//----------------------------------------------------------------------------
// @Returnvalue   Status of the chosen portpin
//
//----------------------------------------------------------------------------
// @Parameters    PinName: 
//                Pin to be read
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

#define IO_ubReadPin(PinName) PinName

//****************************************************************************
// @Macro         IO_vSetPin(PinName) 
//
//----------------------------------------------------------------------------
// @Description   The chosen portpin is set to '1'.
//                Note:
//                'PinName' identifies the pin of a bit-addressable port. The 
//                default names can be changed in the port configuration 
//                dialog. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    PinName: 
//                Pin to be set to '1'
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

#define IO_vSetPin(PinName) PinName = 1

//****************************************************************************
// @Macro         IO_vResetPin(PinName) 
//
//----------------------------------------------------------------------------
// @Description   The chosen portpin is set to '0'. 
//                Note: 
//                'PinName' identifies the pin of a bit-addressable port. The 
//                default names can be changed in the port configuration 
//                dialog. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    PinName: 
//                Pin to be set to '0'
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

#define IO_vResetPin(PinName) PinName = 0

//****************************************************************************
// @Macro         IO_vTogglePin(PinName) 
//
//----------------------------------------------------------------------------
// @Description   The chosen portpin will be toggled. 
//                Note:
//                'PinName' identifies the pin of a bit-addressable port. The 
//                default names can be changed in the port configuration 
//                dialog. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    PinName: 
//                Pin to be toggled
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

#define IO_vTogglePin(PinName) PinName ^= 1

//****************************************************************************
// @Macro         IO_vSetInput(PortName, Mask) 
//
//----------------------------------------------------------------------------
// @Description   This macro changes the direction of I/O port pins to input. 
//                Parameter 'PortName' selects the port and parameter 'Mask' 
//                selects the lines of this port. 
//                Example: IO_vSetInput(P1, 0x11) sets P1.0 and P1.4 to input.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    PortName: 
//                Port to be configured
// @Parameters    Mask: 
//                Mask for port pins to be configured
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

#define IO_vSetInput(PortName, Mask) { \
  ubyte ubEA = IEN0 & 0x80; \
  IEN0 &= ~(ubyte)0x80; \
  SFR_PAGE(_pp0, SST1); \
  PortName##_DIR &= ~(ubyte)(Mask); \
  SFR_PAGE(_pp0, RST1); \
  IEN0 |= ubEA; }

//****************************************************************************
// @Macro         IO_vSetOutput(PortName, Mask) 
//
//----------------------------------------------------------------------------
// @Description   This macro changes the direction of I/O port pins to 
//                output. Parameter 'PortName' selects the port and parameter 
//                'Mask' selects the lines of this port. 
//                Example: IO_vSetOutput(P1, 0x11) sets P1.0 and P1.4 to 
//                output.
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    PortName: 
//                Port to be configured
// @Parameters    Mask: 
//                Mask for port pins to be configured
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

#define IO_vSetOutput(PortName, Mask) { \
  ubyte ubEA = IEN0 & 0x80; \
  IEN0 &= ~(ubyte)0x80; \
  SFR_PAGE(_pp0, SST1); \
  PortName##_DIR |= Mask; \
  SFR_PAGE(_pp0, RST1); \
  IEN0 |= ubEA; }

//****************************************************************************
// @Interrupt Vectors
//****************************************************************************

// USER CODE BEGIN (IO_Header,9)

// USER CODE END


#endif  // ifndef _IO_H_
