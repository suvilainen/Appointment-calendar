#ifndef PROJEKTI_H
#define PROJEKTI_H

typedef struct {
	char name[30];
	int day;
	int month;
	int hour;
} Appointment;

/*Lista kaikista ajanvarauksista sekä niiden lukumäärä yhteensä*/
typedef struct {
	Appointment *allApps;
	int howManyApps;
} AppList;

/*Lisää merkinnen ajanvarausjärjestelmään, A */
/*Tarkistaa, että kuukausi, päivä ja tunti ovat realistisa*/
/*Jos ajankohta oli jo varattu, tulostaa virheen*/
/*Palauttaa päivitetyn appListin*/
AppList addEntry(char str[81], AppList appList);

/*Poistaa merkinnän annetulta ajankohdalta, D*/
/*Jos varausta ei ollut ajankohdalla, tulostaa virheen*/
/*Palauttaa päivitetyn appListin*/
AppList deleteEntry(char str[81], AppList appList);

/*Tulostaa tämänhetkiset varaukset aikajärjestyksessä, L*/
/*Tuloste formaatissa "kuvaus XX.YY. klo ZZ*/
void printCalendar(AppList appList);

/*Tallentaa kaikki ajanvaraukset tiedostoon, W*/
void saveCalendar(char str[81], AppList appList);

/*Lataa kalenterin tiedostosta, O*/
/*korvaa muistissa olleen kalenterin tällä tiedostosta ladatulla*/
/*Palauttaa päivitetyn appListin*/
AppList loadCalendar(char str[81], AppList appList);

/*Vapauttaa kaiken käytetyn muistin, Q*/
/*Asettaa howManyAppsille arvon -1, joka päättää main-funktion while-loopin */
AppList exitProgram(AppList appList);


#endif /* PROJEKTI_H */