// menu.h
#

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
typedef struct _comune {
	int type;
	char *stringa;
};

typedef struct _tempo
{
	int ora;
	int minuti;
	int secondi;
};
typedef struct _data
{
	int giorno;
	int mese;
	int anno;
};
typedef struct _posizione
{
	int col;
	int row;
};
typedef struct _item
{
	//int type;
	char *testo;
	//_data *d;
	//_tempo *t;
	_posizione p;
	_comune *c;
	char *stringa;
};


class MenuClass
{
 protected:


 public:
	 
	 _tempo *orario;
	 _data *data;

	 int *partenza;
	 int *variabili[5];
	 _item *items[5];
	 int indiceVariabili;
	 HardwareSerial *ser;
	 LiquidCrystal_I2C *lcd;
	 void init(HardwareSerial *s, LiquidCrystal_I2C *l);
	 void addMenu(int *value);
	 void addMenu2(int *value);
	 void addMenu4(_comune *);
	 void addMenu5(char *value);
	 void addTempo(_tempo *value, int col, int row, char *val);
	 void addData(_data *value, int col, int row);
	 void addMenu3(_comune *value);
	 void debug();

};

extern MenuClass Menu;

#endif

