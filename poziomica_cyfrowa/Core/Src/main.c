/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <math.h>

#define adxl_address 0x53<<1
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

/* USER CODE BEGIN PV */
uint8_t data_rec[6];
uint8_t chipid=0;
int16_t x,y,z;
float xg, yg, zg;
float mediana = 0;
char tx[120];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void adxl_write (uint8_t reg, uint8_t value)
{
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;
	HAL_I2C_Master_Transmit (&hi2c1, adxl_address, data, 2, 100);
}

void adxl_read_values (uint8_t reg)
{
	HAL_I2C_Mem_Read (&hi2c1, adxl_address, reg, 1, (uint8_t *)data_rec, 6, 100);
}

void adxl_read_address (uint8_t reg)
{
	HAL_I2C_Mem_Read (&hi2c1, adxl_address, reg, 1, &chipid, 1, 100);
}

void adxl_init (void)
{
	adxl_read_address (0x00); // read the DEV ID
	HAL_Delay(50);
	adxl_write (0x31, 0x01);  // data_format range= +- 4g
	HAL_Delay(50);
	adxl_write (0x2d, 0x00);  // reset all bits
	HAL_Delay(50);
	adxl_write (0x2d, 0x08);  // power_cntl measure and wake up 8hz
	HAL_Delay(50);
}

void tx_send(char *tx, uint16_t len)
{
	HAL_UART_Transmit(&huart2, (const uint8_t *) tx, len, 1000);
}

void led_check(void)
{
	HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_SET);
	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_SET);

	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);

	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_SET);

	HAL_Delay(400);
	HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);

	HAL_Delay(200);
	HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
}

void led(float x)
{
	x = fabs(x);
	if (x <= 10)
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);
	}
	else if (x <= 40)
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);
	}
	else if (x <= 80)
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);
	}
	else if (x <= 110)
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);
	}
	else if (x <= 150)
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);
	}
	else if (x <= 200)
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_SET);

		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_RESET);
	}
	else
	{
		HAL_GPIO_WritePin(Led_G1_GPIO_Port, Led_G1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G2_GPIO_Port, Led_G2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_G22_GPIO_Port, Led_G22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y1_GPIO_Port, Led_Y1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y11_GPIO_Port, Led_Y11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y2_GPIO_Port, Led_Y2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_Y22_GPIO_Port, Led_Y22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R1_GPIO_Port, Led_R1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R11_GPIO_Port, Led_R11_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R2_GPIO_Port, Led_R2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R22_GPIO_Port, Led_R22_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R3_GPIO_Port, Led_R3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(Led_R33_GPIO_Port, Led_R33_Pin, GPIO_PIN_SET);
	}
}

void adxl_check(int16_t x, int16_t y, int16_t z) {
	if (x == 0 && y == 0 && z == 0) {
		sprintf((char *)tx, "Bład inicjalizacji adxl...\n");
		tx_send(tx, strlen((char const *)tx));
		while (x == 0 && y == 0 && z == 0) {
			adxl_init();
			HAL_Delay(100);
			x = ((data_rec[1] << 8 ) | data_rec[0]);
			y = ((data_rec[3] << 8 ) | data_rec[2]);
			z = ((data_rec[5] << 8 ) | data_rec[4]);
			HAL_Delay(200);
		}
		sprintf((char *)tx, "Inicjalizacja zakonczona!\n");
		tx_send(tx, strlen((char const *)tx));
	}
	else {
		sprintf((char *)tx, "Inicjalizacja zakonczona!\n");
		tx_send(tx, strlen((char const *)tx));
	}
}
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
  HAL_Delay(5000);
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();
  HAL_Delay(10);
  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  HAL_Delay(10);
  MX_USART2_UART_Init();
  HAL_Delay(10);
  MX_I2C1_Init();
  HAL_Delay(10);
  /* USER CODE BEGIN 2 */
  adxl_init(); // initialize adxl
  HAL_Delay(10);
  led_check();
  HAL_Delay(10);
  adxl_read_values (0x32);
  x = ((data_rec[1] << 8 ) | data_rec[0]);
  y = ((data_rec[3] << 8 ) | data_rec[2]);
  z = ((data_rec[5] << 8 ) | data_rec[4]);
  adxl_check(x, y, z);
  HAL_Delay(2000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	float xm[81] = {};
	float xms[81] = {};
	int a = 0, count = 1;

	for(int i=0;i<81;i++) {
	adxl_read_values (0x32);
	x = ((data_rec[1] << 8 ) | data_rec[0]);
	y = ((data_rec[3] << 8 ) | data_rec[2]);
	z = ((data_rec[5] << 8 ) | data_rec[4]);

	xg = x * 7.8;
	yg = y * 7.8;
	zg = z * 7.8;

	if(count%10==0) {
	sprintf((char *)tx, "a_x = %6.2f [mg]\ta_y = %6.2f[mg]\ta_z = %6.2f [mg]\tx_mediana = %6.2f [mg]\n", xg, yg, zg, mediana);
	tx_send(tx, strlen((char const *)tx));
	sprintf((char *)tx, "------------------------------------------------------------------------------------------------\n");
	tx_send(tx, strlen((char const *)tx));
	count = 0 ;
	}
	count++;
	xm[i] = fabs(xg);
	}

	for(int j=0;j<81;j++) {
		for(int k=0;k<81;k++) {
			if(xms[j] < xm[k]) {
				xms[j] = xm[k];
				a=k;
			}
		}
	xm[a] = 0;
	}
	mediana = xms[40];
	led(mediana);											//wprowadzam wartość mediany do funckcji
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
