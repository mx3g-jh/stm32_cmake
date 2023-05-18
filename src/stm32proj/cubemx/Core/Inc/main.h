/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include "lvgl.h"
extern volatile bool spi3_transmit_complete;
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
#define DC_TFT_Pin GPIO_PIN_2
#define DC_TFT_GPIO_Port GPIOE
#define BLK_TFT_Pin GPIO_PIN_3
#define BLK_TFT_GPIO_Port GPIOE
#define CS1_TFT_Pin GPIO_PIN_4
#define CS1_TFT_GPIO_Port GPIOE
#define CS2_TFT_Pin GPIO_PIN_5
#define CS2_TFT_GPIO_Port GPIOE
#define PEN_TFT_Pin GPIO_PIN_6
#define PEN_TFT_GPIO_Port GPIOE
#define BLUE_LED_Pin GPIO_PIN_13
#define BLUE_LED_GPIO_Port GPIOC
#define RES_Pin GPIO_PIN_0
#define RES_GPIO_Port GPIOA
#define DC_Pin GPIO_PIN_1
#define DC_GPIO_Port GPIOA
#define CS_Pin GPIO_PIN_2
#define CS_GPIO_Port GPIOA
#define BLK_Pin GPIO_PIN_3
#define BLK_GPIO_Port GPIOA
#define TFT_SCK_Pin GPIO_PIN_10
#define TFT_SCK_GPIO_Port GPIOC
#define TFT_MISO_Pin GPIO_PIN_11
#define TFT_MISO_GPIO_Port GPIOC
#define TFT_MOSI_Pin GPIO_PIN_12
#define TFT_MOSI_GPIO_Port GPIOC
#define BUTTON_UP_Pin GPIO_PIN_1
#define BUTTON_UP_GPIO_Port GPIOD
#define BUTTON_DWN_Pin GPIO_PIN_3
#define BUTTON_DWN_GPIO_Port GPIOD
#define BUTTON_LFT_Pin GPIO_PIN_4
#define BUTTON_LFT_GPIO_Port GPIOD
#define BUTTON_RHT_Pin GPIO_PIN_5
#define BUTTON_RHT_GPIO_Port GPIOD
#define BUTTON_MID_Pin GPIO_PIN_6
#define BUTTON_MID_GPIO_Port GPIOD
#define BUTTON_SET_Pin GPIO_PIN_7
#define BUTTON_SET_GPIO_Port GPIOD
#define BUTTON_RST_Pin GPIO_PIN_3
#define BUTTON_RST_GPIO_Port GPIOB
#define RES_TFT_Pin GPIO_PIN_1
#define RES_TFT_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
