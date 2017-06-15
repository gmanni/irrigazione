
#include <LiquidCrystal_I2C.h>
class menu
{
	typedef struct {
		void*    val;
	}_var;

	typedef struct position {
		int row;
		int col;
	};

	typedef struct _option {
		int id;
		char testo[20];
		int valore;
		
		position pos;
	};

	typedef struct _menu {
		int id;
		char testo[20];
		_option opzioni[10];
		int idParent;
		int opzioniLength = 0;
	};

public:
	menu();
	
	_menu m;
	void addOption(int indice, char testo[20], int col, int row);

};

class menuLcd {

public:
	menu m[4];

	void addMenu(int indice, char testo[20]);
	void addOption(int indice, char testo[20], int col, int row);
	void addVar(int indiceMenu, int indiceOpzione, int *v);
	void addVar(int indiceMenu, int indiceOpzione, char* v);
	void begin(LiquidCrystal_I2C *lcd);
	void drawMenu(int indice);
	menuLcd();

	LiquidCrystal_I2C* l;
};


