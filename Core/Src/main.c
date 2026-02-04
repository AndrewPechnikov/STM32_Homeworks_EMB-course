/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdbool.h"
#include <stdio.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LED_RED_PIN GPIO_PIN_11
#define LED_GREEN_PIN GPIO_PIN_10
#define FIRST_BUTTON_PIN GPIO_PIN_15
#define SECOND_BUTTON_PIN GPIO_PIN_8
#define SHORT_TIME_PAUSE 100
#define LONG_TIME_PAUSE 1000
#define DEBOUNCE_TIME 50
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE BEGIN PFP */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);



/* USER CODE BEGIN PFP */
/*0 - повільне перемикання
1 - швидке перемикання
2 - одночасне перемикання*/
char mode = 0;

/*0 - не має закільцьованого перемикання
1 - є закільцьоване перемикання з повернення на mode 0 при одночасному натисканні */
const bool CYCLIC_MODE = true;

/* USER CODE END PV */



void switchLedLogika(char mode);
void fast_blinking(int LED1, int LED2);
void blinking(int LED1, int LED2);

int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */



/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */




  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  printf("UART is working!!!");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {


	  bool firstButton = (HAL_GPIO_ReadPin(GPIOA, FIRST_BUTTON_PIN) == GPIO_PIN_SET);
	  bool secondButton = (HAL_GPIO_ReadPin(GPIOA, SECOND_BUTTON_PIN) == GPIO_PIN_SET);


	  HAL_Delay(DEBOUNCE_TIME);
	  if(!CYCLIC_MODE){
	    mode = (firstButton) ? 1 : mode;
	    mode = (secondButton) ? 2 : mode;
	    mode = (secondButton && firstButton) ? 0 : mode;
	    printf("Mode = %d\r\n", mode);
	    switchLedLogika(mode);
	  }
	  else{
	    mode = (firstButton) ? ((mode + 1) % 3) : mode;
	    mode = (secondButton) ? ((mode - 1 + 3) % 3) : mode;
	    mode = (secondButton && firstButton) ? 0 : mode;
	    printf("Mode = %d\r\n", mode);
	    switchLedLogika(mode);
	  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10|GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA8 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */


  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void blinking(int LED1, int LED2){

  HAL_GPIO_WritePin(GPIOA ,LED1, GPIO_PIN_SET);
  HAL_Delay(LONG_TIME_PAUSE);
  HAL_GPIO_WritePin(GPIOA ,LED1, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOA ,LED2, GPIO_PIN_SET);
  HAL_Delay(LONG_TIME_PAUSE);
  HAL_GPIO_WritePin(GPIOA ,LED2, GPIO_PIN_RESET);
}


void fast_blinking(int LED1, int LED2){
  for(int i = 0; i < 4; i++){
	HAL_GPIO_WritePin(GPIOA ,LED1, GPIO_PIN_SET);
    HAL_Delay(SHORT_TIME_PAUSE);
    HAL_GPIO_WritePin(GPIOA ,LED1, GPIO_PIN_RESET);
    HAL_Delay(SHORT_TIME_PAUSE);
  }

  for(int i = 0; i < 4; i++){
	HAL_GPIO_WritePin(GPIOA ,LED2, GPIO_PIN_SET);
    HAL_Delay(SHORT_TIME_PAUSE);
    HAL_GPIO_WritePin(GPIOA ,LED2, GPIO_PIN_RESET);
    HAL_Delay(SHORT_TIME_PAUSE);
  }

}

void alarm(int LED1, int LED2)
{
	HAL_GPIO_WritePin(GPIOA ,LED2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA ,LED1, GPIO_PIN_SET);
	HAL_Delay(LONG_TIME_PAUSE);
	HAL_GPIO_WritePin(GPIOA ,LED2, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA ,LED1, GPIO_PIN_RESET);
	HAL_Delay(LONG_TIME_PAUSE);


}


void switchLedLogika(char mode){
  if (mode == 0)
    {
      blinking(LED_RED_PIN, LED_GREEN_PIN);
    }
    else if (mode == 1)
    {
      fast_blinking(LED_RED_PIN, LED_GREEN_PIN);
    }

    else if (mode == 2)
    {
      alarm(LED_RED_PIN, LED_GREEN_PIN);
    }

}







/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
