/*
 * clock.h
 *
 *  Created on: 25 apr 2025
 *      Author: William
 */

#ifndef MW_CLOCK_CLOCK_H_
#define MW_CLOCK_CLOCK_H_

#include "stdint.h"

void clock_set_datetime();
void clock_tick_s();
uint8_t clock_get_seconds();

#endif /* MW_CLOCK_CLOCK_H_ */
