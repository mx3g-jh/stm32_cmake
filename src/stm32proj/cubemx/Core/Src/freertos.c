/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include <string.h>
#include <stdio.h>
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "ili9341.h"
#include "tim.h"
#include "testimg.h"
#include "stm32h7xx_hal_tim.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_demos.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

void loop();

// static void lv_test(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask02 */
osThreadId_t myTask02Handle;
const osThreadAttr_t myTask02_attributes = {
  .name = "myTask02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LVGLTask04 */
osThreadId_t LVGLTask04Handle;
const osThreadAttr_t LVGLTask04_attributes = {
  .name = "LVGLTask04",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LVGL_HANDERTask */
osThreadId_t LVGL_HANDERTaskHandle;
const osThreadAttr_t LVGL_HANDERTask_attributes = {
  .name = "LVGL_HANDERTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartLVGL(void *argument);
void StartLVGL_HANDER(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationTickHook(void);

/* USER CODE BEGIN 3 */
void vApplicationTickHook( void )
{
	// 告诉lvgl已经过去了1毫秒
	lv_tick_inc(1);

   /* This function will be called by each tick interrupt if
   configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h. User code can be
   added here, but the tick hook is called from an interrupt context, so
   code must not attempt to block, and only the interrupt safe FreeRTOS API
   functions can be used (those that end in FromISR()). */
}
/* USER CODE END 3 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTask02 */
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* creation of LVGLTask04 */
  LVGLTask04Handle = osThreadNew(StartLVGL, NULL, &LVGLTask04_attributes);

  /* creation of LVGL_HANDERTask */
  LVGL_HANDERTaskHandle = osThreadNew(StartLVGL_HANDER, NULL, &LVGL_HANDERTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  // ssd1306_Init();

  /* Infinite loop */
  for(;;)
  {
    // ssd1306_TestAll();
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(200);
  #ifdef USE_HAL

    HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port,BLUE_LED_Pin);
  #else
    LL_GPIO_TogglePin(BLUE_LED_GPIO_Port,BLUE_LED_Pin);
  #endif
    osDelay(200);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartLVGL */
static void lv_test(void)
{
    static lv_style_t style_kaiti;

    lv_style_init(&style_kaiti);

    lv_style_set_text_font(&style_kaiti, &lv_font_montserrat_14);
    lv_style_set_text_color(&style_kaiti,lv_color_hex(0x8a86b8));
    lv_style_set_bg_color(&style_kaiti, lv_color_hex(0x00ff00));
    lv_obj_t *button = lv_btn_create(lv_scr_act());
    lv_obj_center(button);
    lv_obj_set_size(button, 150, 100);
    lv_obj_t *label = lv_label_create(button);
    lv_obj_center(label);
    lv_obj_add_style(label, &style_kaiti, 0);
    lv_label_set_text(label, "test\nButton");

}

/**
* @brief Function implementing the LVGLTask04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLVGL */
void StartLVGL(void *argument)
{
  /* USER CODE BEGIN StartLVGL */

    lv_init();
    lv_port_disp_init();

    // lv_demo_widgets();
    // lv_demo_stress();
    // lv_demo_benchmark();
    lv_test();
    // osDelay(3000);
    // TFT_ILI9341_Init();

  /* Infinite loop */
  for(;;)
  {
    // loop();
    osDelay(100);
  }
  /* USER CODE END StartLVGL */
}

/* USER CODE BEGIN Header_StartLVGL_HANDER */
/**
* @brief Function implementing the LVGL_HANDERTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartLVGL_HANDER */
void StartLVGL_HANDER(void *argument)
{
  /* USER CODE BEGIN StartLVGL_HANDER */
  	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS( 5 );
	
	// 使用当前时间初始化变量xLastWakeTime ,注意这和vTaskDelay()函数不同 
	xLastWakeTime = xTaskGetTickCount();  
  /* Infinite loop */
  for(;;)
  {
  	vTaskDelayUntil( &xLastWakeTime,xPeriod );
		lv_task_handler();
  }
  	vTaskDelete(NULL);
  /* USER CODE END StartLVGL_HANDER */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void loop() {
    // Check border
    ILI9341_FillScreen(ILI9341_BLACK);

    for(int x = 0; x < ILI9341_WIDTH; x++) {
        ILI9341_DrawPixel(x, 0, ILI9341_RED);
        ILI9341_DrawPixel(x, ILI9341_HEIGHT-1, ILI9341_RED);
    }

    for(int y = 0; y < ILI9341_HEIGHT; y++) {
        ILI9341_DrawPixel(0, y, ILI9341_RED);
        ILI9341_DrawPixel(ILI9341_WIDTH-1, y, ILI9341_RED);
    }

    osDelay(3000);

    // Check fonts
    ILI9341_FillScreen(ILI9341_BLACK);
    ILI9341_WriteString(0, 0, "TFT_Font_7x10, red on black, lorem ipsum dolor sit amet", TFT_Font_7x10, ILI9341_RED, ILI9341_BLACK);
    ILI9341_WriteString(0, 3*10, "TFT_Font_11x18, green, lorem ipsum dolor sit amet", TFT_Font_11x18, ILI9341_GREEN, ILI9341_BLACK);
    ILI9341_WriteString(0, 3*10+3*18, "TFT_Font_16x26, blue, lorem ipsum dolor sit amet", TFT_Font_16x26, ILI9341_BLUE, ILI9341_BLACK);

    osDelay(1000);
    ILI9341_InvertColors(true);
    osDelay(1000);
    ILI9341_InvertColors(false);

    osDelay(5000);

    // Check colors
    ILI9341_FillScreen(ILI9341_WHITE);
    ILI9341_WriteString(0, 0, "WHITE", TFT_Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_BLUE);
    ILI9341_WriteString(0, 0, "BLUE", TFT_Font_11x18, ILI9341_BLACK, ILI9341_BLUE);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_RED);
    ILI9341_WriteString(0, 0, "RED", TFT_Font_11x18, ILI9341_BLACK, ILI9341_RED);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_GREEN);
    ILI9341_WriteString(0, 0, "GREEN", TFT_Font_11x18, ILI9341_BLACK, ILI9341_GREEN);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_CYAN);
    ILI9341_WriteString(0, 0, "CYAN", TFT_Font_11x18, ILI9341_BLACK, ILI9341_CYAN);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_MAGENTA);
    ILI9341_WriteString(0, 0, "MAGENTA", TFT_Font_11x18, ILI9341_BLACK, ILI9341_MAGENTA);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_YELLOW);
    ILI9341_WriteString(0, 0, "YELLOW", TFT_Font_11x18, ILI9341_BLACK, ILI9341_YELLOW);
    osDelay(500);

    ILI9341_FillScreen(ILI9341_BLACK);
    ILI9341_WriteString(0, 0, "BLACK", TFT_Font_11x18, ILI9341_WHITE, ILI9341_BLACK);
    osDelay(500);

    // ILI9341_DrawImage((ILI9341_WIDTH - 240) / 2, (ILI9341_HEIGHT - 240) / 2, 240, 240, (const uint16_t*)test_img_240x240);

    osDelay(1000);
    ILI9341_FillScreen(ILI9341_BLACK);

}
/* USER CODE END Application */

