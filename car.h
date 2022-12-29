#ifndef CAR_STRUCT_H_
#define CAR_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>

// Enumeration som innehåller vilken växellåda som finns i bilen.
enum car_transmission
{
	CAR_TRANSMISSION_MANUAL,
	CAR_TRANSMISSION_AUTOMATIC,
	CAR_TRANSMISSION_NULL
};

// struct som innehåller alla bilarna.
struct car
{
	const char* brand;
	const char* model;
	const char* color;
	int year_of_launch;
	enum car_transmission transmission;

	const struct car_vtable* vptr; /* Pekare till vtable innehållande funktionspekare. */
};

// Funktionspekare relaterade till bilarna
struct car_vtable
{
	void (*change_color)(struct car* self, char* new_color);
	void (*change_transmission)(struct car* self);
	void (*print)(struct car* self, FILE* ostream);
};

// Deklarerar funktioner som har med bilarna att göra.
void car_init(struct car* self,
         	  char* brand,
	          char* model,
	          char* color,
	          int year_of_launch,
	          enum car_transmission transmission);
void car_clear(struct car* self);
struct car* car_new(char* brand,
	                char* model,
	                char* color,
	                int year_of_launch,
	                enum car_transmission transmission);
void car_delete(struct car** self);
void car_print(struct car* self, FILE* ostream);
void car_change_color(struct car* self, char* new_color);
void car_change_transmission(struct car* self);

#endif /* CAR_STRUCT_H_ */