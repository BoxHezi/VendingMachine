/******************************************************************************

** Student Name: Boxuan Lu

** Student Number: s3654900

** Date of submission: <Fri, 13 Oct 2017>

** Course: COSC1076 / COSC2207, Semester 2, 2017

******************************************************************************/

#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */

void initCoins(Coin *cashRegister) {
   int i;
   Denomination denomination = FIVE_CENTS;
   for (i = 0; i < NUM_DENOMS; i++) {
      cashRegister[i].count = DEFAULT_COIN_COUNT;
      cashRegister[i].denom = denomination++;
   }
}

/* load coin from coin file */
void storeCoin(VmSystem *system, char *data) {
   char *coinValue;
   char *coinAmount;

   Denomination coin;
   unsigned coinVal;
   unsigned coinCount;

   static int i = 0;

   coinValue = strtok(data, COIN_DELIM);
   coinAmount = strtok(NULL, COIN_DELIM);

   coinVal = (unsigned) strtol(coinValue, NULL, 10);
   coinCount = (unsigned) strtol(coinAmount, NULL, 10);

   switch (coinVal) {
      case 5:
         coin = FIVE_CENTS;
         break;
      case 10:
         coin = TEN_CENTS;
         break;
      case 20:
         coin = TWENTY_CENTS;
         break;
      case 50:
         coin = FIFTY_CENTS;
         break;
      case 100:
         coin = ONE_DOLLAR;
         break;
      case 200:
         coin = TWO_DOLLARS;
         break;
      case 500:
         coin = FIVE_DOLLARS;
         break;
      case 1000:
         coin = TEN_DOLLARS;
         break;
      default:
         return;
   }

   system->cashRegister[i].denom = coin;
   system->cashRegister[i].count = coinCount;
   i++;
}

int denomToValue(int i) {
   if (i == 0) {
      i = 5;
   } else if (i == 1) {
      i = 10;
   } else if (i == 2) {
      i = 20;
   } else if (i == 3) {
      i = 50;
   } else if (i == 4) {
      i = 100;
   } else if (i == 5) {
      i = 200;
   } else if (i == 6) {
      i = 500;
   } else if (i == 7) {
      i = 1000;
   }

   return i;
}