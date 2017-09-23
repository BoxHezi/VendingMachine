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
        cashRegister[i].denom = denomination;
        denomination++;
    }
}

void addCoin(char *coinData, VmSystem *system) {
    static int i = 0;
    char *coinInString;
    char *coinCountInString;

    unsigned coin;
    unsigned coinCount;

    coinInString = strtok(coinData, COIN_DELIM);
    coinCountInString = strtok(NULL, COIN_DELIM);

    coin = (unsigned) strtol(coinInString, NULL, 10);
    coinCount = (unsigned) strtol(coinCountInString, NULL, 10);

    while (i < NUM_DENOMS) {
        system->cashRegister[i].denom = coin;
        system->cashRegister[i].count = coinCount;
    }
    i++;

}