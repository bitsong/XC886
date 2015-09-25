//****************************************************************************
// @Module        High Speed Synchronous Serial Interface(SSC)
// @Filename      SSC.C
// @Project       ssc.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.3
//
// @Description:  This file contains functions that use the SSC module.
//
//----------------------------------------------------------------------------
// @Date          2015/9/2 12:35:12
//
//****************************************************************************

// USER CODE BEGIN (SSC_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (SSC_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (SSC_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (SSC_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (SSC_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (SSC_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (SSC_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (SSC_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (SSC_General,9)

// USER CODE END


//****************************************************************************
// @Function      void SSC_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the SSC function 
//                library. It is assumed that the SFRs used by this library 
//                are in their reset state. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

// USER CODE BEGIN (Init,1)

// USER CODE END

void SSC_vInit(void)
{
  // USER CODE BEGIN (Init,2)

  // USER CODE END

  ///  - Port Selection
  SSC_PISEL     =  0x00;         // load SSC Port Input Select Register to 
                                 // Port A

  ///  -----------------------------------------------------------------------
  ///  Configuration of the used SSC Port Pins:
  ///  -----------------------------------------------------------------------
  ///  Pin SCLK (P0.3) is Not selected for SCLK ouput 
  ///  Pin MTSR_1 (P0.4) is Not selected for Master Transmit Output 
  ///  Pin MRST_1 (P0.5) Not is selected for Master Receive Input 

  ///  Pin SCLK (P1.2) is selected for SCLK ouput 
  ///  Pin MTSR_0 (P1.3) is selected for Master Transmit Output 
  ///  Pin MRST_0 (P1.4) is selected for Master Receive Input 

  SFR_PAGE(_pp2, noSST);         // switch to page 2 without saving
  P1_ALTSEL0      |= 0x0C;              //  set AltSel0 
  P1_ALTSEL1      &= ~(ubyte)0x0C;      //  set AltSel1

  SFR_PAGE(_pp0, noSST);         // switch to page 0 without saving
  P1_DIR          |= 0x0C;      //  set OutPut Direction


  SSC_CONH_P &= ~(ubyte)0x80;           //  enable access to control bits

  ///  -----------------------------------------------------------------------
  ///  Configuration of the SSC Baud Rate Generator:
  ///  -----------------------------------------------------------------------
  ///  - required baud rate = 6000.000 kbaud
  ///  - real baud rate     =6000.000 kbaud
  ///  - deviation          = 0.000 %

  SSC_BRH       =  0x00;         // load SSC baud rate time reload register 
                                 // high
  SSC_BRL       =  0x01;         // load SSC baud rate time reload register 
                                 // low

  ///  -----------------------------------------------------------------------
  ///  Configuration of the SSC Operation Mode:
  ///  -----------------------------------------------------------------------
  ///  - this device is configured as SSC master
  ///  - transfer data width is 8 bit
  ///  - transfer/receive MSB first
  ///  - shift transmit data on the leading clock edge, latch on trailing edge
  ///  - idle clock line is low, leading clock edge is low-to-high transition
  ///  - ignore receive error
  ///  - ignore phase error


  SSC_CONH_P    =  0x40;         // load SSC control register

  SSC_CONL_P    =  0x17;         // load SSC control register

  SSC_CONH_P |= 0x80;           //  disable access to control bits

  ///  - SSC interrupt is disabled

  // USER CODE BEGIN (Init,3)
				   P1_DATA &=~0x20;
  // USER CODE END

} //  End of function SSC_vInit


//****************************************************************************
// @Function      void SSC_vSendData(ubyte Data) 
//
//----------------------------------------------------------------------------
// @Description   The master device can initiate the first data transfer by 
//                writing the transmit data into transmit buffer. This value 
//                is copied into the shift register (which is assumed to be 
//                empty at this time), and the selected first bit of the 
//                transmit data is placed onto the MTSR line on the next 
//                clock from the baud rate generator. 
//                A slave device immediately outputs the selected first bit 
//                (MSB or LSB of the transfer data) at pin MRST, when the 
//                contents of the transmit buffer are copied into the slave's 
//                shift register. 
//
//----------------------------------------------------------------------------
// @Returnvalue   None
//
//----------------------------------------------------------------------------
// @Parameters    Data: 
//                Data to be send
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

// USER CODE BEGIN (SendData,1)

// USER CODE END

void SSC_vSendData(ubyte Data)
{
  SSC_TBL  = Data;   //  load transmit buffer register

} //  End of function SSC_vSendData


//****************************************************************************
// @Function      ubyte SSC_vGetData(void) 
//
//----------------------------------------------------------------------------
// @Description   This function returns the contents of the receive buffer. 
//                When the receive interrupt request flag is set this implies 
//                that data is available for reading in the receive buffer. 
//
//----------------------------------------------------------------------------
// @Returnvalue   Received data
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

// USER CODE BEGIN (GetData,1)

// USER CODE END

ubyte SSC_vGetData(void)
{
  return(SSC_RBL);     // return receive buffer register

} //  End of function SSC_vGetData


//****************************************************************************
// @Function      ubyte SSC_ubError(void) 
//
//----------------------------------------------------------------------------
// @Description   This function checks if an error occured. With the help of 
//                error flags it is possible to establish the cause of 
//                errors. 
//                The possible values for the retuned error are: 
//                Bit 0 = 1   ->  Transmit error 
//                Bit 1 = 1   ->  receive error 
//                Bit 2 = 1   ->  phase error (only in slave mode) 
//                Bit 3 = 1   ->  baud rate error (only in slave mode) 
//
//----------------------------------------------------------------------------
// @Returnvalue   Returns the error code
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

// USER CODE BEGIN (Error,1)

// USER CODE END

ubyte SSC_ubError(void)
{
  ubyte ubReturn;

  ubReturn = 0;

  SFR_PAGE(_su0, SST1);          // switch to page 0

  if (IRCON1 & 0x01)  //  if error
  {
    IRCON1  &= ~(ubyte)0x01;

    SSC_CONH_P |= 0x80;           //  disable access to control bits

    if (SSC_CONH_O & 0x01)  //  if transmit error
    {

      SSC_CONH_O  &= ~(ubyte)0x01;

      ubReturn |= 0x01;

    }

    if (SSC_CONH_O & 0x02)  //  if receive error
    {

      SSC_CONH_O  &= ~(ubyte)0x02;

      ubReturn |= 0x02;

    }

    if (SSC_CONH_O & 0x04)  //  if phase error
    {

      SSC_CONH_O  &= ~(ubyte)0x04;

      ubReturn |= 0x04;

    }

    if (SSC_CONH_O & 0x08)  //  if baud rate error
    {

      SSC_CONH_O  &= ~(ubyte)0x08;

      ubReturn |= 0x08;

    }

  }

  SFR_PAGE(_su0, RST1);          // restore the old SCU page

  return(ubReturn);

} //  End of function SSC_ubError


// USER CODE BEGIN (SSC_General,10)

// USER CODE END

