/********************************************************************************
* car.c: Funktioner som har med bilobjekten att göra.
********************************************************************************/

#include "car.h"

// Deklarerar statisk struct.
static struct car_vtable* car_vptr_get(void);

/********************************************************************************
* car_init: Initierar ett objekt med värden till alla datatyper som finns i car
*           structen.
********************************************************************************/
void car_init(struct car* self,
	char* brand,
	char* model,
	char* color,
	int year_of_launch,
	enum car_transmission transmission)
{
	self->brand = brand;
	self->model = model;
	self->color = color;
	self->year_of_launch = year_of_launch;
	self->transmission = transmission;
	self->vptr = car_vptr_get();
}

/********************************************************************************
* car_vptr_get: Innehåller alla definitioner till funktionspekarna. returnerar
*               sedan adressen till vtable.
********************************************************************************/
static struct car_vtable* car_vptr_get(void)
{
	static struct car_vtable vtable;

	vtable.change_color = &car_change_color;
	vtable.change_transmission = &car_change_transmission;
	vtable.print = &car_print;

	return &vtable;
}

/********************************************************************************
* car_new: allokerar minne för nytt objekt, funkar det ej så returneras 0.
*          Nytt objekt initieras med dem parameterar som skickats med i
*          funktionen.
********************************************************************************/
struct car* car_new(char* brand,
	                char* model,
	                char* color,
	                int year_of_launch,
	                enum car_transmission transmission)
{
	struct car* self = (struct car*)malloc(sizeof(struct car));
	if (!self) return 0;
	car_init(self, brand, model, color, year_of_launch, transmission);
	return self;
}

/********************************************************************************
* car_delete: Tar bort heapallokerat objekt genom att frigöra minnet.
*             Pekaren till objektet sätts till NULL för att inte lämna en
*             "dinglande pekare".
********************************************************************************/
void car_delete(struct car** self)
{
	free(*self);
	*self = 0;
	return;
}

/********************************************************************************
* car_clear: Raderar det objekt som skickats med i parametern.
********************************************************************************/
void car_clear(struct car* self)
{
	self->brand = NULL;
	self->model = NULL;
	self->color = NULL;
	self->year_of_launch = 0;
	self->transmission = CAR_TRANSMISSION_NULL;
	self->vptr = NULL;
}

/********************************************************************************
* car_print: Skriver ut all information om objektet till terminalen.
********************************************************************************/
void car_print(struct car* self,
	FILE* ostream)
{
	fprintf(ostream, "--------------------------------------------------------------------------------\n");
	fprintf(ostream, "Brand: %s\n", self->brand);
	fprintf(ostream, "Model: %s\n", self->model);
	fprintf(ostream, "Color: %s\n", self->color);
	fprintf(ostream, "year of launch: %d\n", self->year_of_launch);


	switch (self->transmission)
	{
	case CAR_TRANSMISSION_MANUAL:
	{
		fprintf(ostream, "Transmisson: Manual\n");
		break;
	}

	case CAR_TRANSMISSION_AUTOMATIC:
	{
		fprintf(ostream, "Transmisson: Automatic\n");
		break;
	}

	default:
	{
		self->transmission = CAR_TRANSMISSION_NULL;
		break;
	}
	}
	fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
}

/********************************************************************************
* car_change_color: Ändrar färgen på bilen.
********************************************************************************/
static void car_change_color(struct car* self, char* new_color)
{
	self->color = new_color;
}

/********************************************************************************
* car_change_transmission: Ändrar mellan automatisk och manuel växelåda beroende
*                          på vad bilen hade innan.
********************************************************************************/
void car_change_transmission(struct car* self)
{
	if (self->transmission == CAR_TRANSMISSION_MANUAL)
	{
		self->transmission = CAR_TRANSMISSION_AUTOMATIC;
	}
	else if (self->transmission == CAR_TRANSMISSION_AUTOMATIC)
	{
		self->transmission = CAR_TRANSMISSION_MANUAL;
	}
}
