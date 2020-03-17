#include "usart.h"
#include "string.h"
#include "stdlib.h"
#include "stdbool.h"

char dummy[100], UNIQUE_ID[20], MOB_NUMBER[15], SIM_NUMBER[21], APN[20],
		signal_strength[3], CONFIG_DATA[100], clocks[12],
		DUMMY_RECEIVE[100];
char AT[10];
char ip2[50];
char buffer[100];

unsigned int response_retry;
bool apn_manual;
//bool GSM_complete = false, data_received = false;
//char GSM_READ_DATA[1], GSM_DATA[100];
//unsigned int GSM_incerement = 0;

bool gsm_init();
bool gsm_setting();
uint8_t *GSM_command(uint8_t *command);
char *uinque_id();
bool sim_registration();
bool MOB_number();
void sim_number();
int signal_quality();
bool attach_GPRS(char *VPN);
bool get_config();
bool server_response(uint8_t* IP, uint8_t *data);
char *GSM_char(char *buff, uint8_t *command);
bool enable_time();
char *get_time();
void GSM_restart();
bool GSM_SLEEP_MODE();
bool SIM_AVAILABLE();
//************before trying method**************//

//	for (int i = 0; i < 3; i++) {
//	char test[20];
//	char command[] = "at+gsn\r";
//	char cha[] = "at\r";
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"ate0\r", 5, 100);
////	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	memset(dummy, 0, sizeof(dummy));
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"at+cnmi=1,0,0,0,0\r", 18, 100);
//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	memset(dummy, 0, sizeof(dummy));
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CIURC=0\r", 11, 100);
////	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	memset(dummy, 0, sizeof(dummy));
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+GSMBUSY=1\r", 13, 100);
//	//	__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	memset(dummy, 0, sizeof(dummy));
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+CPBR=1\r", 10, 100);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	memset(dummy, 0, sizeof(dummy));

//	uint8_t *test = GSM_command((uint8_t*) &command);
//	test = test + 2;
//	for (int i = 0; (*test != '\n') && (*test != '\r'); i++) {
//		UNIQUE_ID[i] = *test;
//		test++;
//	}

//	GSM_command((uint8_t*) &test, (uint8_t*) &command);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &test, sizeof(test), 100);
//	uint8_t *helo = GSM_command((uint8_t*) &"at+creg?\r");
//	if (strstr((char*) helo, "+CREG: 0,1")
//			|| strstr((char*) helo, "+CREG: 0,5")) {
//		HAL_UART_Transmit(&huart3, (uint8_t*) &"register\r\n", 10, 100);
//	} else
//		HAL_UART_Transmit(&huart3, (uint8_t*) &"not_reg\r\n", 9, 100);

//HAL_UART_Transmit(&huart3, (uint8_t*) &rec, strlen((char*) rec), 100);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &"without\r\n", 9, 100);
//	vTaskDelay(1000);
//	HAL_UART_Transmit(&huart1, (uint8_t*) &cha, sizeof(cha), 100);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &dummy, sizeof(dummy), 100);
//	memset(dummy, 0, sizeof(dummy));
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT\r", 3, 100);
//	HAL_UART_Receive(&huart1, (uint8_t*) &dummy, sizeof(dummy), 1000);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &dummy, sizeof(dummy), 100);
//HAL_UART_Transmit(&huart3, (uint8_t*) &"\r\n", 2, 100);
//	memset(dummy, 0, sizeof(dummy));
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+GSN\r\n", 8, 100);
//	HAL_UART_Receive(&huart1, (uint8_t*) &UNIQUE_ID, sizeof(UNIQUE_ID), 1000);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &UNIQUE_ID, sizeof(UNIQUE_ID), 100);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &"\r\n", 2, 100);
//memset(dummy, 0, sizeof(dummy));
//	}
//	HAL_UART_Transmit(&huart1, (uint8_t*) &"AT+GSN\r\n", 8, 100);
//	vTaskDelay(3000);
//	char ID[13];
//	HAL_UART_Receive(&huart1, (uint8_t*) &ID, sizeof(ID), 1000);
//	HAL_UART_Transmit(&huart3, (uint8_t*) &ID, sizeof(ID), 1000);
