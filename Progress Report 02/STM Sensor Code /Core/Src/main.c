/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "lz4.h"  

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
	uint8_t accXH;
	uint8_t accXL;
	uint8_t accYH;
	uint8_t accYL;
	uint8_t accZH;
	uint8_t accZL;

	uint8_t gyroXH;
	uint8_t gyroXL;
	uint8_t gyroYH;
	uint8_t gyroYL;
	uint8_t gyroZH;
	uint8_t gyroZL;
  
  char buffer[128];
  char header[64];

  int16_t accX;
  int16_t accY;
  int16_t accZ;

  int16_t gyroX;
  int16_t gyroY;
  int16_t gyroZ;

  double temp;
  double out;

  uint32_t time;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
uint8_t reverseBits(uint8_t num);

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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  //Take board out of sleep mode. 
  HAL_I2C_Mem_Write(&hi2c1, 0b11010000, 0x06, 1, 0b00000001, 1, 1000);

  //Setup Gyro
  //Switch to user bank 2
  HAL_I2C_Mem_Write(&hi2c1, 0b11010000, 0x7F, 1, 0x20, 1, 1000);

  //Set sensitivity
  /*
  HAL_I2C_Mem_Write(&hi2c1, 0b11010000, 0x01, 1, 0x00, 1, 1000);
  //HAL_I2C_Mem_Write(&hi2c1, 0b11010000, 0x07, 1, 0x00, 1, 1000);
  HAL_I2C_Mem_Write(&hi2c1, 0b11010000, 0x7F, 1, 0x20, 1, 1000);
  */
  

  //HAL_I2C_Mem_Write(&hi2c1, 0b11010000, 0x14, 1, 0b00000001, 1, 1000);
  //sprintf(header,"\r\n%s\r\n", "Time,AccX,AccY,AccZ,GyroX,GyroY,GryoZ");
  sprintf(header,"\r\n%s\r\n", "Time (ms),AccX (g),AccY (g),AccZ (g)");
  HAL_UART_Transmit(&huart1, (uint8_t *)&header, 64, 1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    time = HAL_GetTick();

    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x2D, 1, &accXH, 1, 1000);
    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x2E, 1, &accXL, 1, 1000);

    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x2F, 1, &accYH, 1, 1000);
    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x30, 1, &accYL, 1, 1000);

    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x31, 1, &accZH, 1, 1000);
    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x32, 1, &accZL, 1, 1000);

/*

    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x33, 1, &gyroXH, 1, 1000);
    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x34, 1, &gyroXL, 1, 1000);

    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x35, 1, &gyroYH, 1, 1000);
    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x36, 1, &gyroYL, 1, 1000);

    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x37, 1, &gyroZH, 1, 1000);
    HAL_I2C_Mem_Read(&hi2c1, 0b11010000, 0x38, 1, &gyroZL, 1, 1000);
    */

    accX = ((accXH<<8)|accXL);
    accY = ((accYH<<8)|accYL);
    accZ = ((accZH<<8)|accZL);

/*
    gyroX = ((gyroXH<<8)|gyroXL);
    gyroY = ((gyroYH<<8)|gyroYL);
    gyroZ = ((gyroZH<<8)|gyroZL);
    */

    sprintf(buffer, "%d,%.2f,%.2f,%.2f\r\n", time, accX/16384.0, accY/16384.0, accZ/16384.0, gyroX, gyroY, gyroZ);
    //sprintf(buffer, "%ld,%.2f,%.2f,%.2f\r\n", time, gyroX/131.0, gyroY/131.0, gyroZ/131.0);
    HAL_UART_Transmit(&huart1, (uint8_t *)&buffer, 128, 1000);

    //sprintf(buffer, "%d\r\n", reverseBits(temp));
    //HAL_UART_Transmit(&huart1, (uint8_t *)&buffer, 32, 1000);
    HAL_Delay(10);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x2000090E;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 38400;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
uint8_t reverseBits(uint8_t num)
{
    uint8_t NO_OF_BITS = 8;
    uint8_t reverse_num = 0;
    int i;
    for (i = 0; i < NO_OF_BITS; i++) {
        if ((num & (1 << i)))
            reverse_num |= 1 << ((NO_OF_BITS - 1) - i);
    }
    return reverse_num;
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

#ifdef  USE_FULL_ASSERT
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
