/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED0_Pin GPIO_PIN_9
#define LED0_GPIO_Port GPIOF
#define CO_1_Pin GPIO_PIN_5
#define CO_1_GPIO_Port GPIOA
#define KEY0_Pin GPIO_PIN_11
#define KEY0_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_12
#define KEY1_GPIO_Port GPIOF
#define KEY2_Pin GPIO_PIN_13
#define KEY2_GPIO_Port GPIOF
#define KEY3_Pin GPIO_PIN_14
#define KEY3_GPIO_Port GPIOF
#define KEY4_Pin GPIO_PIN_15
#define KEY4_GPIO_Port GPIOF
#define DC_Pin GPIO_PIN_12
#define DC_GPIO_Port GPIOB
#define RST_Pin GPIO_PIN_13
#define RST_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_14
#define SDA_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_15
#define SCL_GPIO_Port GPIOB
#define SET_DATA_5_Pin GPIO_PIN_7
#define SET_DATA_5_GPIO_Port GPIOG
#define SET_DATA_4_Pin GPIO_PIN_6
#define SET_DATA_4_GPIO_Port GPIOC
#define SET_DATA_3_Pin GPIO_PIN_8
#define SET_DATA_3_GPIO_Port GPIOC
#define SET_DATA_2_Pin GPIO_PIN_8
#define SET_DATA_2_GPIO_Port GPIOA
#define SET_DATA_1_Pin GPIO_PIN_12
#define SET_DATA_1_GPIO_Port GPIOA
#define CO_2_Pin GPIO_PIN_7
#define CO_2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
