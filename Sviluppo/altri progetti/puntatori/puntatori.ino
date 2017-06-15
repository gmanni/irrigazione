#include <MenuBackend.h>
#include "LiquidCrystal_I2C.h"
#include "menu.h"
int sec;
//int orario[3];

MenuClass m;
LiquidCrystal_I2C lcd(0x27, 20, 4);
_tempo ora;
_data oggi;
_comune data;
_comune orario;
char *orario5;
char *data5;

void setup()
{
	sec = 12;
	/*orario[0] = 12;
	orario[1] = 13;
	orario[2] = 55;*/
	Serial.begin(9600);
	m.init(&Serial, &lcd);
	//m.addMenu2(&orario[0]);
	//m.addMenu2(&orario[1]);
	//m.addMenu2(&orario[2]);

	orario.stringa = "12:13.55";
	orario.type = 0;

	data.stringa = "27-11-2016";
	data.type = 1;

	orario5 = "12:13.55";
	data5 = "27-11-2016";
	m.addMenu5(orario5);
	m.addMenu5(data5);
	
}

void loop()
{

	delay(1000);
	/*orario[2]++;
	if (orario[2] >= 60) {
		orario[2] = 0;
		orario[1]++;
	}*/
	//Serial.print("LOOP ");
	//Serial.println(orario[2]);
	//Serial.println(orario.stringa);
	//Serial.println(data.stringa);
	m.debug();
	

}

