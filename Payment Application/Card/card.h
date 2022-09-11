/******************************************************************************
 *
 * Module: Card
 *
 * File Name: card.h
 *
 * Description: Header file for the Card Module.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#ifndef CARD_H
#define CARD_H

#include "../Utilities/std_types.h"

/*******************************************************************************
 *                               Definitions                                   *
 *******************************************************************************/

#define MAX_CARD_NAME_SIZE 24
#define MIN_CARD_NAME_SIZE 20
#define EXPIRY_DATE_SIZE 5
#define MAX_CARD_PAN_SIZE 19
#define MIN_CARD_PAN_SIZE 16

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/

typedef enum EN_cardError_t {
	CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
} EN_cardError_t;

/*******************************************************************************
 *                               Structures                                    *
 *******************************************************************************/

typedef struct ST_cardData_t {
	uint8_t cardHolderName[25];
	uint8_t primaryAccountNumber[20];
	uint8_t cardExpirationDate[6];
} ST_cardData_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* -----------------------------------------------------------------------------
 * [Function Name]: getCardHolderName
 * [Description]: fetches card holder name
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_cardError_t
 * ----------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);

/* -----------------------------------------------------------------------------
 * [Function Name]: getCardExpiryDate
 * [Description]: fetches card's expiry date
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_cardError_t
 * ----------------------------------------------------------------------------*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);

/* -----------------------------------------------------------------------------
 * [Function Name]: getCardPAN
 * [Description]: fetches card PAN
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_cardError_t
 * ----------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif /* End of card.h */
