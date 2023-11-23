/*
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file    CV9.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

volatile uint32_t g_systickCounter;
/* TODO: insert other definitions and declarations here. */
void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}


int strcmp_safe(const char *s1, const char *s2, const uint32_t delay)
{
	volatile uint32_t DWT1,DWT2;
	volatile uint32_t status;
	volatile uint32_t pause;

	DWT1=DWT->CYCCNT;
	status=strcmp(s1,s2);
	DWT2=DWT->CYCCNT;

	pause=delay-(DWT1-DWT2);
	for (uint32_t i=0; i<pause; i++)
	{
		SysTick_DelayTicks(1U);
	}
	return status;
}

/*
 * @brief   Application entry point.
 */
int main(void) {
	uint32_t DWT1,DWT2;

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\n");

    /* Force the counter to be placed into memory. */
    /* Enter an infinite loop, just incrementing a counter. */

    char password_stored[20]="12345678";
    char input[20];

    uint32_t status;




    while (1)
        {
    		PRINTF("\r\nEnter password: ");

    	    SCANF("%s", input);

    	    DWT1=DWT->CYCCNT;
    	    status= strcmp(input,password_stored);
    	    DWT2=DWT->CYCCNT;



    	    PRINTF("\r\ninput: %s", input);

    	    PRINTF("\r\nCycles in function: %d", DWT2-DWT1);

    	    DWT1=DWT->CYCCNT;
    	    	status= strcmp_safe(input,password_stored,200U);
    	    DWT2=DWT->CYCCNT;
    	    PRINTF("\r\nCycles in function: %d", DWT2-DWT1);


    	    if (status==0)
    	    	{PRINTF("\r\ninput correct");}
    	    else
    	    	{PRINTF("\r\ninput invalid");}


        }
}
