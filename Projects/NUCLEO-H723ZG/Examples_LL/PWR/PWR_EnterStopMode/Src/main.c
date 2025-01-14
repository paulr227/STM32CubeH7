/**
  ******************************************************************************
  * @file    Examples_LL/PWR/PWR_EnterStopMode/Src/main.c
  * @author  MCD Application Team
  * @brief   This example describes how to enter and exit the Stop mode
  *          through the STM32H7xx PWR LL API.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32H7xx_LL_Examples
  * @{
  */

/** @addtogroup PWR_EnterStopMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void     SystemClock_Config(void);
void     Configure_PWR(void);
void     LED_Init(void);
void     LED_Off(void);
void     LED_Blinking_5s(void);
void     EnterStopMode(void);
static void CPU_CACHE_Enable(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Enable the CPU Cache */
  CPU_CACHE_Enable();
  /* Configure the system clock to 520 MHz */
  SystemClock_Config();

  /* Initialize LED1 */
  LED_Init();

  /* Configure Power Peripheral */
  Configure_PWR();

  /* Led blinking during 5s in RUN mode */
  LED_Blinking_5s();

  /* Switch OFF LED1 */
  LED_Off();

  /* Enter Stop mode */
  EnterStopMode();

  /* Here Device is in Stop mode */

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Initialize LED1.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  /* Enable the LED1 Clock */
  LED1_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED1 */
  LL_GPIO_SetPinMode(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_MODE_OUTPUT);
  /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
  //LL_GPIO_SetPinOutputType(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
  //LL_GPIO_SetPinSpeed(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_SPEED_FREQ_LOW);
  /* Reset value is LL_GPIO_PULL_NO */
  //LL_GPIO_SetPinPull(LED1_GPIO_PORT, LED1_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-off LED1.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
  /* Turn LED1 off */
  LL_GPIO_ResetOutputPin(LED1_GPIO_PORT, LED1_PIN);
}

/**
  * @brief  Set LED1 to Blinking mode during 5s.
  * @param  None

  * @retval None
  */
void LED_Blinking_5s(void)
{
  uint32_t i = 0;

  /* Toggle IO in during 5s (25*200ms) */
  for(i = 0; i < 25; i++)
  {
    LL_GPIO_TogglePin(LED1_GPIO_PORT, LED1_PIN);  
    LL_mDelay(200);
  }
}

/**
  * @brief  Function to configure and initialize PWR Peripheral.
  * @param  None
  * @retval None
  */
void Configure_PWR(void)
{
  /* Ensure that HSI is wake-up system clock */ 
  LL_RCC_SetSysWakeUpClkSource(LL_RCC_SYSWAKEUP_CLKSOURCE_HSI);
}

/**
  * @brief  Function to configure and enter in Stop Mode.
  * @param  None
  * @retval None
  */
void EnterStopMode(void)
{
  LL_GPIO_InitTypeDef gpio_initstruct = {LL_GPIO_PIN_ALL, LL_GPIO_MODE_ANALOG, 
                                         LL_GPIO_SPEED_FREQ_HIGH, LL_GPIO_OUTPUT_PUSHPULL, 
                                         LL_GPIO_PULL_NO, LL_GPIO_AF_0};

  /* Set all GPIO in analog state to reduce power consumption,                */
  /* Note: Debug using ST-Link is not possible during the execution of this   */
  /*       example because communication between ST-link and the device       */
  /*       under test is done through UART. All GPIO pins are disabled (set   */
  /*       to analog input mode) including  UART I/O pins.                    */
  LL_AHB4_GRP1_EnableClock(LL_AHB4_GRP1_PERIPH_GPIOA |
                           LL_AHB4_GRP1_PERIPH_GPIOB |
                           LL_AHB4_GRP1_PERIPH_GPIOC |
                           LL_AHB4_GRP1_PERIPH_GPIOD |
                           LL_AHB4_GRP1_PERIPH_GPIOE |
                           LL_AHB4_GRP1_PERIPH_GPIOF |
                           LL_AHB4_GRP1_PERIPH_GPIOG |
                           LL_AHB4_GRP1_PERIPH_GPIOH |
                           LL_AHB4_GRP1_PERIPH_GPIOJ |
                           LL_AHB4_GRP1_PERIPH_GPIOK);

  LL_GPIO_Init(GPIOA, &gpio_initstruct);
  LL_GPIO_Init(GPIOB, &gpio_initstruct);
  LL_GPIO_Init(GPIOC, &gpio_initstruct);
  LL_GPIO_Init(GPIOD, &gpio_initstruct);
  LL_GPIO_Init(GPIOE, &gpio_initstruct);
  LL_GPIO_Init(GPIOF, &gpio_initstruct);
  LL_GPIO_Init(GPIOG, &gpio_initstruct);
  LL_GPIO_Init(GPIOH, &gpio_initstruct);
  LL_GPIO_Init(GPIOJ, &gpio_initstruct);
  LL_GPIO_Init(GPIOK, &gpio_initstruct);

  LL_AHB4_GRP1_DisableClock(LL_AHB4_GRP1_PERIPH_GPIOA |
                           LL_AHB4_GRP1_PERIPH_GPIOB |
                           LL_AHB4_GRP1_PERIPH_GPIOC |
                           LL_AHB4_GRP1_PERIPH_GPIOD |
                           LL_AHB4_GRP1_PERIPH_GPIOE |
                           LL_AHB4_GRP1_PERIPH_GPIOF |
                           LL_AHB4_GRP1_PERIPH_GPIOG |
                           LL_AHB4_GRP1_PERIPH_GPIOH |
                           LL_AHB4_GRP1_PERIPH_GPIOJ |
                           LL_AHB4_GRP1_PERIPH_GPIOK);

  /** Request to enter Stop mode
    * Following procedure describe in STM32H7xx Reference Manual
    * See PWR part, section Low-power modes, Stop mode
    */
  /* Select the regulator state in STOP mode */
  LL_PWR_SetRegulModeDS(LL_PWR_REGU_DSMODE_LOW_POWER);

  /* Set Stop mode when CPU enters deepsleep */
  LL_PWR_CPU_SetD1PowerMode(LL_PWR_CPU_MODE_D1STOP);
  LL_PWR_CPU_SetD2PowerMode(LL_PWR_CPU_MODE_D2STOP);
  LL_PWR_CPU_SetD3PowerMode(LL_PWR_CPU_MODE_D3STOP);
  
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  LL_LPM_EnableDeepSleep();

  /* Request Wait For Interrupt */
  __WFI();
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL1 (HSE BYPASS)
  *            SYSCLK(Hz)                     = 520000000 (CPU Clock)
  *            HCLK(Hz)                       = 260000000 (AXI and AHBs Clock)
  *            AHB Prescaler                  = 2
  *            D1 APB3 Prescaler              = 2 (APB3 Clock  130MHz)
  *            D2 APB1 Prescaler              = 2 (APB1 Clock  130MHz)
  *            D2 APB2 Prescaler              = 2 (APB2 Clock  130MHz)
  *            D3 APB4 Prescaler              = 2 (APB4 Clock  130MHz)
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 4
  *            PLL_N                          = 260
  *            PLL_P                          = 1
  *            PLL_Q                          = 4
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Flash Latency(WS)              = 3
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  /* Power Configuration */
  LL_PWR_ConfigSupply(LL_PWR_LDO_SUPPLY);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE0);
  while (LL_PWR_IsActiveFlag_VOS() == 0)
  {
  }

  /* Enable HSE oscillator */
  LL_RCC_HSE_EnableBypass();
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* Set FLASH latency */
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

  /* Main PLL configuration and activation */
  LL_RCC_PLL_SetSource(LL_RCC_PLLSOURCE_HSE);
  LL_RCC_PLL1P_Enable();
  LL_RCC_PLL1Q_Enable();
  LL_RCC_PLL1R_Enable();
  LL_RCC_PLL1FRACN_Disable();
  LL_RCC_PLL1_SetVCOInputRange(LL_RCC_PLLINPUTRANGE_2_4);
  LL_RCC_PLL1_SetVCOOutputRange(LL_RCC_PLLVCORANGE_WIDE);
  LL_RCC_PLL1_SetM(4);
  LL_RCC_PLL1_SetN(260);
  LL_RCC_PLL1_SetP(1);
  LL_RCC_PLL1_SetQ(4);
  LL_RCC_PLL1_SetR(2);
  LL_RCC_PLL1_Enable();
  while(LL_RCC_PLL1_IsReady() != 1)
  {
  }

  /* Set Sys & AHB & APB1 & APB2 & APB4  prescaler */
  LL_RCC_SetSysPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetAHBPrescaler(LL_RCC_AHB_DIV_2);
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);
  LL_RCC_SetAPB4Prescaler(LL_RCC_APB4_DIV_2);

  /* Set PLL1 as System Clock Source */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL1);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL1)
  {
  }

  /* Set systick to 1ms */
  SysTick_Config(520000000 / 1000);

  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  SystemCoreClock = 520000000;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
