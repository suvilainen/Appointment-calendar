#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

/*Kutsuu syötteen ensimmäisen kirjaimen perusteella funktiota*/
AppList callFunction(char input[81], AppList appList)
{
	if (input[0] == 'A') {
		return addEntry(input, appList);
	}
	else if (input[0] == 'D') {
		return deleteEntry(input, appList);
	}
	else if (input[0] == 'L') {
		printCalendar(appList);
		return appList;
	}
	else if (input[0] == 'W') {
		saveCalendar(input, appList);
		return appList;
	}
	else if (input[0] == 'O') {
		return loadCalendar(input, appList);
	}
	else if (input[0] == 'Q') {
		return exitProgram(appList);
	}
	else {
		printf("Invalid string.\n"); 
	}
	return appList;
}

int main()
{
	Appointment* allApps = NULL; //tähän tallennetaan ajanvaraukset

	/*pitää yllä varauslistaa ja varauksien lukumäärää*/
	AppList appList;
	appList.allApps = allApps;
	appList.howManyApps = 0;

	char str[81];
	memset(str, 0, 81);
	//tarkista eka kirjain ja kutsu funktiota
	while (appList.howManyApps != -1) {
		fgets(str, 80, stdin);
		appList = callFunction(str, appList);
	}
	printf("Ending program.\n");
	return 1;
}