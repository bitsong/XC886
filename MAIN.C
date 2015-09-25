//****************************************************************************
// @Module        Project Settings
// @Filename      MAIN.C
// @Project       ssc.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.3
//
// @Description   This file contains the Project initialization function.
//
//----------------------------------------------------------------------------
// @Date          2015/9/2 12:35:11
//
//****************************************************************************

// USER CODE BEGIN (MAIN_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (MAIN_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (MAIN_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (MAIN_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (MAIN_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (MAIN_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************


// USER CODE BEGIN (MAIN_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (MAIN_General,9)
	 void WatchDogInit();
	 void WatchDog();
	 void WatchDogDisable();
// USER CODE END


//****************************************************************************
// @Function      void MAIN_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This function initializes the microcontroller. It is 
//                assumed that the SFRs are in their reset state.
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

// USER CODE BEGIN (MAIN_Init,1)

// USER CODE END

void MAIN_vInit(void)
{
  // USER CODE BEGIN (MAIN_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Configuration of the System Clock:
  ///  -----------------------------------------------------------------------
  ///  - On Chip Osc is Selected
  ///  - PLL Mode, NDIV =  20
  ///  - input frequency is 9.6 MHz



  //   FCLK runs at 2 times the frequency of PCLK.
  SFR_PAGE(_su1, noSST);         // switch to page1

  CMCON         =  0x10;         // load Clock Control Register

  SFR_PAGE(_su0, noSST);         // switch to page0


  ///  *********************************************************************************
  ///  Note : All peripheral related IO configurations are done in the 
  ///  respective peripheral modules (alternate functions selection)
  ///  *********************************************************************************

  ///  Initialization of module 'GPIO'
  IO_vInit();

  ///  Initialization of module 'Timer 0/1'
  T01_vInit();

  ///  Initialization of module 'High Speed Synchronous Serial Interface(SSC)'
  SSC_vInit();


  //   Interrupt Priority

  IP            =  0x00;         // load Interrupt Priority Register
  IPH           =  0x00;         // load Interrupt Priority High Register
  IP1           =  0x00;         // load Interrupt Priority 1 Register
  IPH1          =  0x00;         // load Interrupt Priority 1 High Register


  // USER CODE BEGIN (MAIN_Init,3)

  // USER CODE END

  //// Interrupt structure 2 mode 0 is selected.

  //// Interrupt service routine choice 2 is selected.

  //   globally enable interrupts
  EA            =  0;           

} //  End of function MAIN_vInit


//****************************************************************************
// @Function      void main(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the main function.
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

// USER CODE BEGIN (MAIN_Main,1)
			ubyte dat=0x05;
			uword feeding_times	;
// USER CODE END

void main(void)
{
  // USER CODE BEGIN (MAIN_Main,2)
	
  // USER CODE END

  MAIN_vInit();

  // USER CODE BEGIN (MAIN_Main,3)
	
	WatchDogInit();
    EA            =  1;   
  // USER CODE END

 

  // USER CODE BEGIN (MAIN_Main,4)
   while(1)
  {
  		WatchDog();
  }

} //  End of function main


// USER CODE BEGIN (MAIN_General,10)
   void WatchDogInit()
{
	P4_DIR        =  0x08; //IO_vSetOutput(P4, 0x08);
	feeding_times=0;
	IO_vResetPin(P4_3);
	IO_vSetPin(P4_3);
}
void WatchDog()
{
	if(feeding_times>=20)//feeding_times*5ms
	{
		feeding_times=0;
		IO_vResetPin(P4_3);
		IO_vSetPin(P4_3);
	}
	else
	{
		//feeding_times++;
	}

}
void WatchDogDisable()
{
	IO_vSetInput(P4, 0x08);
}
// USER CODE END

