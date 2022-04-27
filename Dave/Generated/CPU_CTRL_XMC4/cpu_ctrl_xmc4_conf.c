/*********************************************************************************************************************
* DAVE APP Name : CPU_CTRL_XMC4       APP Version: 4.0.18
*
* NOTE:
* This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
*********************************************************************************************************************/

/**
 * @cond
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015-2020, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-16:
 *     - Initial version<br>
 *
 * 2015-08-28:
 *     - Added exceptions and MPU settings
 *
 * 2015-11-30:
 *     - Added disable write buffer
 *
 * 22-Nov-2018:
 *     - Fixed PMU_FLASH_WS definition for XMC4300 devices
 *
 * @endcond
 *
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "xmc_scu.h"
#include "xmc_gpio.h"
#include "cpu_ctrl_xmc4.h"
/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#if ((UC_SERIES == XMC48) || (UC_SERIES == XMC47) || (UC_SERIES == XMC43)) 
#define PMU_FLASH_WS          (0x4U)
#elif ((UC_SERIES == XMC45) || (UC_SERIES == XMC44))
#define PMU_FLASH_WS          (0x3U)
#else
#define PMU_FLASH_WS          (0x2U)
#endif

extern uint32_t __Vectors;
/**********************************************************************************************************************
* DATA STRUCTURES
**********************************************************************************************************************/
CPU_CTRL_XMC4_t CPU_CTRL_XMC4_0 =
{
  .initialized = false
};	


void SystemCoreSetup(void)
{
  uint32_t temp;

  NVIC_SetPriorityGrouping(1U);
	
  /* relocate vector table */
  __disable_irq();

#if !defined(__TASKING__)
  SCB->VTOR = (uint32_t)(&__Vectors);
#endif

  __DSB();
  __enable_irq();
	
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) |                 /* set CP10 Full Access */
				 (3UL << 11*2)  );               /* set CP11 Full Access */
#endif
  /* Set flash wait states */
  temp = FLASH0->FCON;
  temp &= ~FLASH_FCON_WSPFLASH_Msk;
  temp |= PMU_FLASH_WS;
  FLASH0->FCON = temp;


  /* Disable divide by zero trap */
  SCB->CCR &= ~SCB_CCR_DIV_0_TRP_Msk; 

  /* Disable unaligned memory access trap */
  SCB->CCR &= ~SCB_CCR_UNALIGN_TRP_Msk; 

  /* Disable memory management fault */
  SCB->SHCSR &= ~SCB_SHCSR_MEMFAULTENA_Msk;

  /* Disable bus fault */
  SCB->SHCSR &= ~SCB_SHCSR_BUSFAULTENA_Msk;

  /* Disable usage fault */
  SCB->SHCSR &= ~SCB_SHCSR_USGFAULTENA_Msk;
}
