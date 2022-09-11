/******************************************************************************
 *
 * Application: Payment Application
 *
 * File Name: app.c
 *
 * Description: source file for Payment Application.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "app.h"

extern ST_transaction_t transactions_DB[DB_SIZE];

/*******************************************************************************
 *                         Functions Definitions                               *
 *******************************************************************************/

/* -----------------------------------------------------------------------------
 * [Function Name]: appStart
 * [Description]: This function starts application
 * [Args]: Void
 * [Returns]: Void
 * ----------------------------------------------------------------------------*/
void appStart(void)
{
	/* Setting Max Account for testing */
	setMaxAmount(&(transactions_DB[0].terminalData));

	/* Card Module */
	getCardHolderName(&(transactions_DB[0].cardHolderData));
	getCardExpiryDate(&(transactions_DB[0].cardHolderData));
	getCardPAN(&(transactions_DB[0].cardHolderData));
	/* End of Card Module */



	/* Server Module */
	saveTransaction(&transactions_DB[0]);
}
