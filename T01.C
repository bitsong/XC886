//****************************************************************************
// @Module        Timer 0/1
// @Filename      T01.C
// @Project       ssc.dav
//----------------------------------------------------------------------------
// @Controller    Infineon XC886CLM-8FF
//
// @Compiler      Keil
//
// @Codegenerator 1.3
//
// @Description:  This file contains functions that use the T01 module.
//
//----------------------------------------------------------------------------
// @Date          2015/9/2 12:35:12
//
//****************************************************************************

// USER CODE BEGIN (T01_General,1)

// USER CODE END



//****************************************************************************
// @Project Includes
//****************************************************************************

#include "MAIN.H"

// USER CODE BEGIN (T01_General,2)

// USER CODE END


//****************************************************************************
// @Macros
//****************************************************************************

// USER CODE BEGIN (T01_General,3)

// USER CODE END


//****************************************************************************
// @Defines
//****************************************************************************

// USER CODE BEGIN (T01_General,4)

// USER CODE END


//****************************************************************************
// @Typedefs
//****************************************************************************

// USER CODE BEGIN (T01_General,5)

// USER CODE END


//****************************************************************************
// @Imported Global Variables
//****************************************************************************

// USER CODE BEGIN (T01_General,6)

// USER CODE END


//****************************************************************************
// @Global Variables
//****************************************************************************

// USER CODE BEGIN (T01_General,7)

// USER CODE END


//****************************************************************************
// @External Prototypes
//****************************************************************************

// USER CODE BEGIN (T01_General,8)

// USER CODE END


//****************************************************************************
// @Prototypes Of Local Functions
//****************************************************************************

// USER CODE BEGIN (T01_General,9)

// USER CODE END


//****************************************************************************
// @Function      void T01_vInit(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the initialization function of the Timer 0/1 
//                function library. It is assumed that the SFRs used by this 
//                library are in their reset state. 
//                
//                The following SFR fields will be initialized for both 
//                timers 0 and 1:
//                T0M            - Timer 0 mode
//                T1M            - Timer 1 mode
//                GATE0/GATE1    - gating control
//                TLx, THx       - timer low/high registers
//                ETx            - interrupt enable
//                TRx            - timer run control (this is the final 
//                action)
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

// USER CODE BEGIN (T01_Init,1)

// USER CODE END

void T01_vInit(void)
{
  // USER CODE BEGIN (T01_Init,2)

  // USER CODE END

  ///  -----------------------------------------------------------------------
  ///  Timer 0
  ///  -----------------------------------------------------------------------
  ///  Mode 0: 8-bit timer (TH0) with a divide-by-32 prescaler (TL0)
  ///  the timer 0 overflow is 682.667 ?s


  ///  -----------------------------------------------------------------------
  ///  Timer 1
  ///  -----------------------------------------------------------------------
  ///  Mode 1: 16-bit timer (TH1, TL1)
  ///  the timer 1 overflow is 5461.333 ?s


  TMOD = 0x10;

  TL0 = 0x00;
  TH0 = 0x00;

  TL1 = 0x00;
  TH1 = 0x00;

  ///  Enable Timer 1 interrupt
  ET1 = 1;

  // USER CODE BEGIN (T01_Init,3)

  // USER CODE END

  ///  Start Timer 1
  TR1 = 1;
} //  End of function T01_vInit


//****************************************************************************
// @Function      void T01_viTmr1(void) 
//
//----------------------------------------------------------------------------
// @Description   This is the service routine for the timer 1 interrupt. It 
//                is called 
//                - when TH1 overflows if timer 1 is in mode 0 or 1 and timer 
//                0 is not in mode 3
//                - when TL1 overflows if timer 1 is in mode 2 and timer 0 is 
//                not in mode 3
//                - when TH0 overflows if timer 0 is in mode 3
//                Please note that you have to add application specific code 
//                to this function.
//
//----------------------------------------------------------------------------
// @Returnvalue   none
//
//----------------------------------------------------------------------------
// @Parameters    None
//
//----------------------------------------------------------------------------
// @Date          2015/9/2
//
//****************************************************************************

//   You have two choices for interrupt type select in Project Settings Page 
//   under Global Settings Section.
//   If you select CHOICE 1 then ISR will be generated with push and pop.
//   If you select CHOICE 2 then ISR will be generated without push and pop.
//   Default choice is CHOICE 2.
//   Current selection is CHOICE 2 

// USER CODE BEGIN (T01_IsrTmr1,1)
	static	ubyte dat;
	static msg_header send_t;
// USER CODE END

void T01_viTmr1(void) interrupt T1INT
{

  // USER CODE BEGIN (T01_IsrTmr1,2)
  //the period is 5.223ms
	  send_t.type=0x01;
	  send_t.len=0x03;
	  send(send_t);
	  if(rcvbuf[0]==0xBB)
		{
		    feeding_times=0;
		}
	else
		{
			feeding_times++;	
		}
  // USER CODE END

} //  End of function T01_viTmr1


// USER CODE BEGIN (T01_General,10)

// USER CODE END

