
/******************************************************************************
 *
 * Module: Terminal
 *
 * File Name: terminal.c
 *
 * Description: Source file for the Terminal Module.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"

/*******************************************************************************
 *                         Functions Definitions                               *
 *******************************************************************************/

/* -----------------------------------------------------------------------------
 * [Function Name]: getTransactionDate
 * [Description]: This function will ask for the transaction data and store it in terminal data.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);

	uint8_t day[3];
	uint8_t month[3];
	uint8_t year[5];
	uint8_t *delimiter = "/";
	uint8_t *zero = "0";

	uint8_t x_day = tm.tm_mday;
	uint8_t x_month = tm.tm_mon + 1;
	uint16_t x_year = tm.tm_year + 1900;

	itoa(x_day, day, 10);
	itoa(x_month, month, 10);
	itoa(x_year, year, 10);

	if (x_month < 10 || x_day < 10)
	{
		if (x_day < 10)
		{
			strcat(termData->transactionDate, zero);
		}
		strcat(termData->transactionDate, day);
		strcat(termData->transactionDate, delimiter);
		if (x_month < 10)
		{
			strcat(termData->transactionDate, zero);
		}
		strcat(termData->transactionDate, month);
		strcat(termData->transactionDate, delimiter);
		strcat(termData->transactionDate, year);
	}
	else
	{
		strcat(termData->transactionDate, day);
		strcat(termData->transactionDate, delimiter);
		strcat(termData->transactionDate, month);
		strcat(termData->transactionDate, delimiter);
		strcat(termData->transactionDate, year);
	}
	printf("Transaction Date: %s\n",termData->transactionDate);
	return TERMINAL_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: isCardExpired
 * [Description]: This function compares the card expiry date with the transaction date.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint8_t temp[6];

	temp[0] = termData.transactionDate[3];
	temp[1] = termData.transactionDate[4];
	temp[2] = termData.transactionDate[5];
	temp[3] = termData.transactionDate[8];
	temp[4] = termData.transactionDate[9];
	temp[5] = '\0';

	uint8_t temp1[3] = {temp[0], temp[1], '\0'};
	uint8_t temp2[3] = {cardData.cardExpirationDate[0], cardData.cardExpirationDate[1], '\0'};
	uint8_t temp3[3] = {temp[3], temp[4], '\0'};
	uint8_t temp4[3] = {cardData.cardExpirationDate[3], cardData.cardExpirationDate[4], '\0'};

	if (atoi(temp4) < atoi(temp3))
	{
		//printf("Card is expired\n");
		return EXPIRED_CARD;
	}

	else if (atoi(temp2) < atoi(temp1))
	{
		//printf("Card is expired\n");
		return EXPIRED_CARD;
	}
	else
	{
		//printf("Card is OK\n");
	}

	return TERMINAL_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: isValidCardPAN
 * [Description]: This function checks if the PAN is a Luhn number or not.
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
// EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
//{
//	return TERMINAL_OK;
// }

/* -----------------------------------------------------------------------------
 * [Function Name]: getTransactionAmount
 * [Description]: This function asks for the transaction amount and saves it into terminal data.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	printf("Enter the transaction amount:\n");
	scanf("%f", &(termData->transAmount));
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	// printf("TransAmount = %f\n",termData->transAmount);
	return TERMINAL_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: isBelowMaxAmount
 * [Description]: This function compares the transaction amount with the terminal max amount.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}

	return TERMINAL_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: setMaxAmount
 * [Description]: This function sets the maximum allowed amount into terminal data.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
	termData->maxTransAmount = MAX_AMOUNT;
	if (termData->maxTransAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	// printf("MaxTransAmount = %f\n",termData->maxTransAmount);
	return TERMINAL_OK;
}
