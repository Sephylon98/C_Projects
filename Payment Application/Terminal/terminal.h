/******************************************************************************
 *
 * Module: Terminal
 *
 * File Name: terminal.h
 *
 * Description: Header file for the Terminal Module.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef TERMINAL_H
#define TERMINAL_H

#include "../Utilities/std_types.h"
#include "../Card/card.h"

/*******************************************************************************
 *                             Definitions                                     *
 *******************************************************************************/

#define MAX_AMOUNT 8000

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/

typedef enum EN_terminalError_t
{
    TERMINAL_OK,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT
} EN_terminalError_t;

/*******************************************************************************
 *                               Structures                                    *
 *******************************************************************************/

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
} ST_terminalData_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* -----------------------------------------------------------------------------
 * [Function Name]: getTransactionDate
 * [Description]: This function will ask for the transaction data and store it in terminal data.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

/* -----------------------------------------------------------------------------
 * [Function Name]: isCardExpired
 * [Description]: This function compares the card expiry date with the transaction date.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

/* -----------------------------------------------------------------------------
 * [Function Name]: isValidCardPAN
 * [Description]: This function checks if the PAN is a Luhn number or not.
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);

/* -----------------------------------------------------------------------------
 * [Function Name]: getTransactionAmount
 * [Description]: This function asks for the transaction amount and saves it into terminal data.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

/* -----------------------------------------------------------------------------
 * [Function Name]: isBelowMaxAmount
 * [Description]: This function compares the transaction amount with the terminal max amount.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

/* -----------------------------------------------------------------------------
 * [Function Name]: setMaxAmount
 * [Description]: This function sets the maximum allowed amount into terminal data.
 * [Args]: this function takes terminal Data (ST_terminalData_t) as input
 * [Returns]: this function returns EN_terminalError_t
 * ----------------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif /* End of terminal.h */
