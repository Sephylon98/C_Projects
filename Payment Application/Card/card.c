/******************************************************************************
 *
 * Module: Card
 *
 * File Name: card.c
 *
 * Description: Source file for the Card Module.
 *
 * Author: Mohamed Ashraf
 *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "card.h"

/*******************************************************************************
 *                      Functions Definitions                                   *
 *******************************************************************************/

/* -----------------------------------------------------------------------------
 * [Function Name]: getCardHolderName
 * [Description]: fetches card holder name
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_cardError_t
 * ----------------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Please enter cardholder's name:\n");
    gets((cardData->cardHolderName));

    uint8_t strIndex_i = 0;

    while (cardData->cardHolderName[strIndex_i] != '\0')
    {
        if (!isalpha(cardData->cardHolderName[strIndex_i]) && !isspace(cardData->cardHolderName[strIndex_i]))
        {
            return WRONG_NAME;
        }
        strIndex_i++;
    }

    if (strlen(cardData->cardHolderName) > MAX_CARD_NAME_SIZE || strlen(cardData->cardHolderName) < MIN_CARD_NAME_SIZE)
    {
        return WRONG_NAME;
    }

    return CARD_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: getCardExpiryDate
 * [Description]: fetches card's expiry date
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_cardError_t
 * ----------------------------------------------------------------------------*/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Please enter card expiry date:\n");
    gets((cardData->cardExpirationDate));

    uint8_t strIndex_i = 0;

    while (cardData->cardExpirationDate[strIndex_i] != '\0')
    {
        if (strIndex_i != 2)
        {
            if (!isdigit(cardData->cardExpirationDate[strIndex_i]))
            {
                return WRONG_EXP_DATE;
            }
        }

        if (cardData->cardExpirationDate[2] != '/')
        {
            return WRONG_EXP_DATE;
        }

        strIndex_i++;
    }

    if (strlen(cardData->cardExpirationDate) > EXPIRY_DATE_SIZE || strlen(cardData->cardExpirationDate) < EXPIRY_DATE_SIZE)
    {
        return WRONG_EXP_DATE;
    }

    // printf("Length of Card ExpDate = %d\n",strlen(cardData->cardExpirationDate));
    return CARD_OK;
}

/* -----------------------------------------------------------------------------
 * [Function Name]: getCardPAN
 * [Description]: fetches card PAN
 * [Args]: this function takes Card Data (ST_cardData_t) as input
 * [Returns]: this function returns EN_cardError_t
 * ----------------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Please enter card's PAN:\n");
    gets((cardData->primaryAccountNumber));

    uint8_t strIndex_i = 0;

    while (cardData->primaryAccountNumber[strIndex_i] != '\0')
    {
        if (!isdigit(cardData->primaryAccountNumber[strIndex_i]) && !isspace(cardData->primaryAccountNumber[strIndex_i]))
        {
            //printf("%s",(cardData->primaryAccountNumber));
            return WRONG_PAN;
        }
        strIndex_i++;
    }

    if (strlen(cardData->primaryAccountNumber) > MAX_CARD_PAN_SIZE || strlen(cardData->primaryAccountNumber) < MIN_CARD_PAN_SIZE)
    {
        //printf("%s",(cardData->primaryAccountNumber));
        return WRONG_PAN;
    }

    //printf("%s , %d\n",(cardData->primaryAccountNumber),strlen(cardData->primaryAccountNumber));
    return CARD_OK;
}
