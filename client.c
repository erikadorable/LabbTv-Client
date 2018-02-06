/*********************************************
* client.c
*
* Desc: lab-skeleton for the client side of an
* client-server application
* 
* Revised by Dag Nystrom & Jukka Maki-Turja
* NOTE: the server must be started BEFORE the
* client.
*********************************************/
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "wrapper.h"

#define MESSAGE "Hello!"
LPTSTR Slot = TEXT("\\\\.\\mailslot\\mailslot");
void enterPlanet(planet_type *planet);
void main(void) {

	HANDLE hWrite;
	HANDLE hRead;
	DWORD bytesWritten;
	int loops = 2000;
	planet_type *planet = malloc(sizeof(planet_type));
	
	//hRead = mailslotCreate(Slot);
	hWrite = mailslotConnect(Slot); 


	if (hWrite == INVALID_HANDLE_VALUE) {
		printf("Failed to get a handle to the mailslot!!\nHave you started the server?\n");
		return;
	}

						/* NOTE: replace code below for sending planet data to the server. */
	while(loops-- > 0) {
						/* send a friendly greeting to the server */
					/* NOTE: The messages sent to the server need not to be of equal size.       */
					/* Messages can be of different sizes as long as they don't exceed the       */
					/* maximum message size that the mailslot can handle (defined upon creation).*/
		
		enterPlanet(planet);
		bytesWritten = mailslotWrite (hWrite, &planet, sizeof(planet_type));
		if (bytesWritten!=-1)
			printf("data sent to server (bytes = %d)\n", bytesWritten);
		else
			printf("failed sending data to server\n");
	}

//	mailslotClose(hRead);
	mailslotClose(hWrite);

					/* (sleep for a while, enables you to catch a glimpse of what the */
					/*  client prints on the console)                                 */
	Sleep(2000);
	return;
}
void enterPlanet(planet_type *planet)
{
	printf("Please enter your planets name:");
	fgets(planet->name, 20, stdin);
	printf("\n Please enter your planets x-axis pos:");
	scanf_s("%lf", &planet->sx);
	printf("\n Please enter your planets y-axis pos:");
	scanf_s("%lf", &planet->sy);
	printf("\n Please enter your planets x-axis velocity:");
	scanf_s("%lf", &planet->vx);
	printf("\n Please enter your planets y-axis velocity:");
	scanf_s("%lf", &planet->vy);
	printf("\n Please enter your planets lifetime: ");
	scanf_s("%d", &planet->life);
	getchar();
}

