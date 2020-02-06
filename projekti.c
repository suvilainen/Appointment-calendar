#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "projekti.h"

/*Funktioiden selitykset projekti.h -tiedostossa :)*/

/*apufunktio päivämäärien vertailuun*/
/*palauttaa 0 jos App1 on ennen App2:sta*/
int compareDates(const void *a, const void *b)
{
	const Appointment *App1 = a;
	const Appointment *App2 = b;

	if (App1->month < App2->month) {
		return 0;
	}
	if (App1->month == App2->month && App1->day < App2->day) {
		return 0;
	}
	if (App1->month == App2->month && App1->day == App2->day && App1->hour < App2->hour) {
		return 0;
	}
	return 1;
} 

/*apufunktio joka testaa, onko parametrina annettu aika jo varattu*/
int isFree(AppList appList, int month, int day, int hour)
{
	for (int i = 0; i < appList.howManyApps; i++) {
		if (appList.allApps[i].month == month && appList.allApps[i].day == day && appList.allApps[i].hour == hour)
			return 0; //eli on varattu!
	}
	return 1; //eli ei ole varattu
}


AppList addEntry(char str[81], AppList appList)
{
	char call;
	char appName[31];
	char extra[51];
	memset(appName, 0, 31);
	int month;
	int day;
	int hour; 
	int howManyApps = appList.howManyApps; //jotta koodi olisi lyhyempi

	if ( sscanf(str, "%c %30s %i %i %i\n", &call, appName, &month, &day, &hour) == 5 ) {
		/*testataan mahdolliset ylimääräiset parametrit*/
		if ( sscanf(str, "%c %30s %i %i %i %50s\n", &call, appName, &month, &day, &hour, extra) == 6 ) {
			printf("Invalid input. Can't add appointment.\n");
			return appList;
		}
		//testaa onko vapaa
		if (isFree(appList, month, day, hour)) {
			//testaa onko aika hyväksyttävä
			if (month < 13 && month > 0 && day < 32 && day > 0 && hour < 25 && hour > 0) {
				appList.allApps = realloc(appList.allApps, sizeof(Appointment) * (howManyApps + 1));
				/*tallennetaan nimi ajanvaraukselle*/
				int i;
				for (i = 0; i < strlen(appName); i++) {
					appList.allApps[howManyApps].name[i] = appName[i];
				}
				appList.allApps[howManyApps].name[i] = '\0';
				
				appList.allApps[howManyApps].month = month;
				appList.allApps[howManyApps].day = day;
				appList.allApps[howManyApps].hour = hour;
				appList.howManyApps++;
				printf("Appointment %s succesfully made!\n", appList.allApps[howManyApps].name);
				return appList;
			} else {
				printf("The time is not valid.\n");
				return appList;
			}
		} else {
			printf("There is another appointment at that time!\n");
			return appList;
		}
	} else {
		printf("Invalid string. Adding an appointment failed.\n");
		return appList;
	}

}


AppList deleteEntry(char str[81], AppList appList)
{
	char call;
	int month;
	int day;
	int hour;
	char extra[51];

	/*nämä vain koodin lyhentämistä varten*/
	int howManyApps = appList.howManyApps;
	Appointment *allApps = appList.allApps;

	if (sscanf(str, "%c %i %i %i", &call, &month, &day, &hour) == 4) {
		if (sscanf(str, "%c %i %i %i %s", &call, &month, &day, &hour, extra) == 5) {
			printf("Invalid input. Can't delete entry.\n");
			return appList;
		}
		/*Tarkistetaan onko kyseiseen aikaan ajanvaraus*/
		if (!isFree(appList, month, day, hour)) {
			/*etsitään missä kohdassa ajanvaraus on*/
			int i = 0;
			for (; i < howManyApps; i++) {
				if (allApps[i].month == month && allApps[i].day == day && allApps[i].hour == hour)
					break;
			}
			/*siirretään viimeinen indeksi poistettavan indeksin paikalle*/
			appList.allApps[i] = allApps[howManyApps-1];
			/*uusi allApps-lista*/
			Appointment* allAppsNew = malloc(sizeof(Appointment)*(howManyApps-1));
			/*ja kopioidaan muut paitsi viimeinen indeksi uuteen listaan*/
			appList.allApps = memcpy(allAppsNew, allApps, sizeof(Appointment)*(howManyApps-1));
			/*muutetaan vielä howManyApps:n kokoa*/
			appList.howManyApps--;
			/*vapautetaan vanha allApps vielä*/
			free(allApps);
			printf("Appointment succesfully cancelled.\n");
			return appList;
		} else {
			printf("There's no appointment at that time!\n");
			return appList;
		}
	} else {
		printf("Invalid string!\n");
		return appList;
	}
}


void printCalendar(AppList appList)
{
	if (appList.howManyApps == 0) {
		printf("No appointments.\n");
		return;
	}
	qsort(appList.allApps, appList.howManyApps, sizeof(Appointment), compareDates);
	for (int i = 0; i < appList.howManyApps; i++) {
		printf("%s %02i.%02i. klo %02i.\n", appList.allApps[i].name, appList.allApps[i].day, appList.allApps[i].month, appList.allApps[i].hour);
	}
	return;
}


void saveCalendar(char str[81], AppList appList)
{
	char c;
	char filename[61];
	memset(filename, 0, 61);
	if (sscanf(str, "%c %s\n", &c, filename) == 2) {
		FILE *f = fopen(filename, "w");
		if (!f) {
			fclose(f);
			printf("File not found.\n");
			return;
		}
		for (int i = 0; i < appList.howManyApps; i++) {
			fprintf(f, "%s %i %i %i\n", appList.allApps[i].name, appList.allApps[i].month, appList.allApps[i].day, appList.allApps[i].hour);
		}
		fclose(f);
		printf("Appointments saved on file %s.\n", filename);
	} else {
		printf("Invalid string or file name!\n");
	}
	return;
}


AppList loadCalendar(char str[81], AppList appList)
{
	char c;
	char filename[61];
	memset(filename, 0, 61);

	if (sscanf(str, "%c %s\n", &c, filename) == 2) {
		FILE *f;
		f = fopen(filename, "r");

		if (!f) {
			printf("Couldn't open the file.\n");
			return appList;
		}

		char *line = malloc(sizeof(char)*81);
		int i = 0;
		free(appList.allApps);
		appList.allApps = malloc(sizeof(Appointment)*0);
		appList.howManyApps = 0;

		while (fgets(line, 81, f) != NULL && !feof(f) && line[0] != '\n') {
			appList.allApps = realloc(appList.allApps, sizeof(Appointment)*(i+1));
			sscanf(line, "%s %i %i %i", appList.allApps[i].name, &appList.allApps[i].month, &appList.allApps[i].day, &appList.allApps[i].hour);
			appList.howManyApps++;
			i++;
		}
		fclose(f);
		printf("Appointments saved from file %s\n", filename);
		free(line);
		return appList;
	} else {
		printf("Invalid string or file name!\n");
		return appList;
	}
}


AppList exitProgram(AppList appList)
{
	free(appList.allApps);
	appList.howManyApps = -1; //ohjelma loppuu kun howManyApps = -1
	return appList;
}

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
	//tarkista syötteen eka kirjain ja kutsu apufunktiota
	while (appList.howManyApps != -1) {
		if (fgets(str, 80, stdin) == NULL) {
			exitProgram(appList);
			printf("End of file encountered.\n");
			break;
		}
		appList = callFunction(str, appList);
	}
	printf("Ending program.\n");
	return 1;
}