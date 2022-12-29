/********************************************************************************
* main.c: Programmet l�gger till bilar i structen med olika egenskaper som
*         m�rke, model, f�rg, �r den gjordes och om den �r manuel eller
*         automatisk.
*         Det ska sedan g� att �ndra f�rg och byta mellan manuel eller
*         automatisk. Efter det har gjorts ska informationen om bilarna skrivas
*         ut i textfilen cars.txt och sedan l�sas d�r ifr�n till terminalen.
********************************************************************************/
#include "car.h"

// Deklarerar objekt med car structen och en cars array.
struct car car1, car2, car3, *car4;
struct car* cars[];

/********************************************************************************
* file_read: Funktionen f�r in filv�gen som argument. Med hj�lp av denna filv�g
*            l�ser den av vad som st�r i filen och skriver ut det i terminalen.
********************************************************************************/
void file_read(const char* filepath)
{
	FILE* istream = fopen(filepath, "r");

	if (!istream) return;

	char s[100] = { '\0' };

	while ((fgets(s, sizeof(s), istream)))
	{
		printf("%s", s);
	}
	
	fclose(istream);
	return;
}
/********************************************************************************
* main: H�r b�rjar programmet.
********************************************************************************/
int main(void)
{
	// Skapar en filpekare som pekar p� filen cars.txt och g�r den redo att bifoga text till.
	FILE* ostream = fopen("cars.txt", "a");

	// Initierar dem tre olika bilarna.
	car_init(&car1, "Volvo", "V70", "Black", 1995, CAR_TRANSMISSION_MANUAL);
	car_init(&car2, "BWM", "Z3", "Blue", 2001, CAR_TRANSMISSION_AUTOMATIC);
	car_init(&car3, "Skoda", "Octavia RS", "White", 2003, CAR_TRANSMISSION_MANUAL);

	car4 = car_new("Opel", "Astra", "Red", 2008, CAR_TRANSMISSION_MANUAL);

	if (!car4) return 1;

	// L�gger in alla bilarna i en array.
	struct car* cars[] = { &car1, &car2, &car3 };
	
	// Skriver ut alla bilarna till terminalen.
	for (size_t i = 0; i < 3; i++)
	{
		car_print(cars[i], ostream);
	}
	
	car4->vptr->print(car4, ostream);

	// St�nger pekaren ostream d� vi ej ska anv�nda den mer.
	fclose(ostream);

	car_delete(&car4);
	car_clear(&car4);


	file_read("cars.txt");

	return 0;
}

