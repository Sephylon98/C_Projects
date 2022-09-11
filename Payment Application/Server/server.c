/******************************************************************************
 *
 * Module: Terminal
 *
 * File Name: server.c
 *
 * Description: Source file for the Server Module.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/

ST_transaction_t transactions_DB[DB_SIZE] = {0};
ST_accountsDB_t validAccounts_DB[DB_SIZE] =
{
	{10000,"1234 5678 1234 5678"},
	{11000,"1111 1111 1111 1111"},
	{4000,"0000 0000 0000 0000"}
};

/*******************************************************************************
 *                         Functions Definitions                               *
 *******************************************************************************/

/* -----------------------------------------------------------------------------
 * [Function Name]: recieveTransactionData
 * [Description]: This function will take all transaction data and validate its data.
                  It checks the account details and amount availability.
                  If the account does not exist return DECLINED_STOLEN_CARD, if the amount is not available will return DECLINED_INSUFFECIENT_FUND, if a transaction can't be saved will return INTERNAL_SERVER_ERROR and will not save the transaction, else returns APPROVED.
                  It will update the database with the new balance.
 * [Args]: this function takes transaction Data (ST_transaction_t) as input
 * [Returns]: this function returns EN_transState_t
 * ----------------------------------------------------------------------------*/
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
	/* Terminal Module */
	getTransactionDate(&(transData->terminalData));
	if(isCardExpired((transData->cardHolderData),(transData->terminalData)))
	{
		printf("Declined: Expired Card\n");
		return INTERNAL_SERVER_ERROR;
	}

	if(getTransactionAmount(&(transData->terminalData)))
	{
		return INTERNAL_SERVER_ERROR;
	}

	if(isBelowMaxAmount(&(transData->terminalData)))
	{
	    printf("Declined: Amount Exceeding Limit\n");
		return INTERNAL_SERVER_ERROR;
	}
	/* End of Terminal Module */

	/* Server */
	//printf("PAN = %s , Strlen = %d \n",transData->cardHolderData.primaryAccountNumber,strlen(transData->cardHolderData.primaryAccountNumber));
	uint8_t index_i = 0;
	for(index_i = 0; index_i<DB_SIZE; index_i++)
	{
		if(strcmp(transData->cardHolderData.primaryAccountNumber,validAccounts_DB[index_i].primaryAccountNumber))
		{
			/* wait */
			if(index_i == 254)
			{
			   return DECLINED_STOLEN_CARD;
			}
		}

		else
		{
			break;
		}
	}

	if(transData->terminalData.transAmount > validAccounts_DB[index_i].balance)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}

	/* Updating Balance */
	validAccounts_DB[index_i].balance -= transData->terminalData.transAmount;
	printf("Your new balance = %f\n",validAccounts_DB[index_i].balance);
	return APPROVED;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: isValidAccount
 * [Description]: This function will take card data and validate these data.
                  It checks if the PAN exists or not in the server's database.
                  If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_serverError_t
 * ----------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    uint8_t index_i;
    for (index_i = 0; index_i < DB_SIZE; index_i++)
    {
        if (cardData->primaryAccountNumber == validAccounts_DB[index_i].primaryAccountNumber)
        {
            return SERVER_OK;
        }
    }

    return DECLINED_STOLEN_CARD;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: isAmountAvailable
 * [Description]: This function will take card data and validate these data.
                  It checks if the PAN exists or not in the server's database.
                  If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK.
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_serverError_t
 * ----------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    uint8_t index_i;
    for (index_i = 0; index_i < DB_SIZE; index_i++)
    {
        if (termData->transAmount > validAccounts_DB[index_i].balance)
        {
            return LOW_BALANCE;
        }
    }

    return SERVER_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: saveTransaction
 * [Description]: This function will take all transaction data into the transactions database.
                  It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
                  If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
                  If transaction can't be saved will return SAVING_FAILED, else will return OK
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_serverError_t
 * ----------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    transData->transactionSequenceNumber++;
    switch(recieveTransactionData(transData))
    {
    	case APPROVED:
    		printf("Approved. Transaction Saved.\n");
    		break;

    	case DECLINED_STOLEN_CARD:
    		printf("Declined: DECLINED_STOLEN_CARD\n");
    		return SAVING_FAILED;

    	case DECLINED_INSUFFECIENT_FUND:
    		printf("Declined: DECLINED_INSUFFECIENT_FUND\n");
    		return SAVING_FAILED;

    	case INTERNAL_SERVER_ERROR:
    		printf("Declined: INTERNAL_SERVER_ERROR\n");
    		return SAVING_FAILED;

    }
    return SERVER_OK;
}

// /* -----------------------------------------------------------------------------
//  * [Function Name]: getTransaction
//  * [Description]: This function will take a transaction sequence number and search for this transaction in the database.
//                   If the transaction can't be found will return TRANSACTION_NOT_FOUND,
//                   else will return OK and store the transaction in a structure
//  * [Args]: this function takes transaction Data & transaction squence number (uint32_t,ST_transaction_t) as input
//  * [Returns]: this function returns EN_serverError_t
//  * ----------------------------------------------------------------------------*/
// EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
// {
// }
