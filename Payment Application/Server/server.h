/******************************************************************************
 *
 * Module: Server
 *
 * File Name: server.h
 *
 * Description: Header file for the server Module.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include "../Utilities/std_types.h"
#include "../Terminal/terminal.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define DB_SIZE 255

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/

typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLEN_CARD,
    INTERNAL_SERVER_ERROR
} EN_transState_t;

typedef enum EN_serverError_t
{
    SERVER_OK,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE
} EN_serverError_t;

/*******************************************************************************
 *                               Structures                                    *
 *******************************************************************************/

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
} ST_transaction_t;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8_t primaryAccountNumber[20];
} ST_accountsDB_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
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
EN_transState_t recieveTransactionData(ST_transaction_t *transData);

/* -----------------------------------------------------------------------------
 * [Function Name]: isValidAccount
 * [Description]: This function will take card data and validate these data.
                  It checks if the PAN exists or not in the server's database.
                  If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_serverError_t
 * ----------------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData);

/* -----------------------------------------------------------------------------
 * [Function Name]: isAmountAvailable
 * [Description]: This function will take card data and validate these data.
                  It checks if the PAN exists or not in the server's database.
                  If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK.
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_serverError_t
 * ----------------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);

/* -----------------------------------------------------------------------------
 * [Function Name]: saveTransaction
 * [Description]: This function will take all transaction data into the transactions database.
                  It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server.
                  If saves any type of transaction, APPROVED or DECLINED, with the specific reason for declining/transaction state.
                  If transaction can't be saved will return SAVING_FAILED, else will return OK
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_serverError_t
 * ----------------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t *transData);

// /* -----------------------------------------------------------------------------
//  * [Function Name]: getTransaction
//  * [Description]: This function fetches transaction data and transaction squence number.
//                   It checks if the PAN exists or not in the server's database.
//                   If the PAN doesn't exist will return DECLINED_STOLEN_CARD, else will return OK
//  * [Args]: this function takes transaction Data & transaction squence number (uint32_t,ST_transaction_t) as input
//  * [Returns]: this function returns EN_serverError_t
//  * ----------------------------------------------------------------------------*/
// EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

#endif /* End of server.h */
