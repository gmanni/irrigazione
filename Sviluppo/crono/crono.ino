
#include <TouchScreen.h>
#include <UTFT.h>
#include <SD.h>

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin

const int PIN_SD = 4; // pin of sd card

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
extern uint8_t Various_Symbols_16x32[];

int x, y, z;

// Remember to change the model parameter to suit your display module!
UTFT tft(ILI9341_S5P, 51, 52, 5, 0, 6);

int tempSoglia = 20;
String currentMenu = "";

TouchScreen ts(A0, A3, A2, A1); // LANDSCAPE init TouchScreen port pins

/*
		bmpFile = SD.open("test.bmp");
		if (!bmpFile){
			Serial.println("didnt find image");
			while (1);
		}

		if (!bmpReadHeader(bmpFile)){
			Serial.println("bad bmp");
			return;
		}

		bmpdraw(bmpFile, 0, 0);
		bmpFile.close();

		*/
void setup() {
	Serial.begin(9600);

	tft.InitLCD();

	createMainMenu();
	/*
	Sd2Card card;
	card.init(SPI_FULL_SPEED, PIN_SD);

	if (!SD.begin(PIN_SD)) {
		Serial.println("failed!");
		while (1);                               // init fail, die here
	}

	Serial.println("SD OK!");

	/*bmpFile = SD.open("test.bmp");
	if (!bmpFile) {
		Serial.println("didnt find image");
		while (1);
	}*/

	/*if (!bmpReadHeader(bmpFile)) {
		Serial.println("bad bmp");
		return;
	}*/

	//bmpdraw(bmpFile, 0, 0);
	//bmpFile.close();
}

#define TS_MAXY 879
#define TS_MINY 145
#define TS_MINX 12
#define TS_MAXX 930

void retrieveTouch() {
	// a point object holds x y and z coordinates
	TSPoint p = ts.getPoint();

	x = map(p.x, TS_MINX, TS_MAXX, tft.getDisplayXSize(), 0);
	y = map(p.y, TS_MINY, TS_MAXY, tft.getDisplayYSize(), 0);
	z = p.z;
}

void loop() {
	retrieveTouch();

	if (z > MINPRESSURE && z < MAXPRESSURE) {
		Serial.print("x = ");
		Serial.print(x);
		Serial.print("\ty = ");
		Serial.println(y);

		if (x > 100 && x < 140) {
			if (y > 50 && y < 85) {
				currentMenu = "S";
				disegnaMenu();
				disegnaCursore();
			}
		}else if (x > 0 && x < 40) {
			if (y > 200 && y < 240) {
				Serial.println("puls +");
				if (currentMenu == "S") {
					tempSoglia++;
					disegnaCursore();
				}
			}
		}else if (x>60 && x<100) {
			if (y > 200 && y < 240) {
				Serial.println("puls -");
				if (currentMenu == "S") {
					tempSoglia--;
					disegnaCursore();
				}
			}
		}else if (x > 120 && x < 180) {
			if (y > 200 && y < 240) {
				Serial.println("puls esc");
				currentMenu = "";
				disegnaMenu();
				disegnaCursore();

			}
		}

	}
}
void disegnaCursore() {
	if (currentMenu == "S") {
		tft.setColor(255, 255, 255);
		tft.setBackColor(0, 0, 0);
		tft.print("Soglia", LEFT, 60);
		tft.setColor(255, 0, 0);
		tft.printNumI(tempSoglia, 100, 60);
		tft.setColor(255, 255, 255);
	}else {
		tft.setColor(255, 255, 255);
		tft.setBackColor(0, 0, 0);
		tft.print("Soglia", LEFT, 60);
		tft.printNumI(tempSoglia, 100, 60);
	}
}

void disegnaMenu() {
	if (currentMenu != "") {
		tft.setColor(204,204,204);
		//tft.setBackColor(204, 204, 204);
		tft.fillRoundRect(0, 200, 40, 240);
		
		tft.fillRoundRect(60, 200, 100, 240);
		tft.fillRoundRect(120, 200, 180, 240);

		tft.setBackColor(204, 204, 204);
		tft.setColor(255, 0, 0);
		tft.print("+", 12, 212);
		tft.print("-", 72, 212);
		tft.print("esc", 125, 212);
	}else {
		tft.setBackColor(0, 0, 0);
		tft.setColor(0, 0, 0);
		tft.fillRect(0, 200, 180, 240);

	}
}

void createMainMenu() {
	tft.clrScr();

	/*
	tft.setColor(255, 0, 0);
	tft.fillRect(0, 0, 319, 13);

	tft.setColor(64, 64, 64);
	tft.fillRect(0, 226, 319, 239);

	tft.setColor(255, 255, 255);
	tft.setBackColor(255, 0, 0);
	tft.print("header", CENTER, 1);

	tft.setBackColor(64, 64, 64);
	tft.setColor(255, 255, 0);
	tft.print("footer", CENTER, 227);
	*/

	//tft.setFont(SevenSegNumFont);

	tft.setFont(BigFont);
	tft.print("12", LEFT, 10);

	tft.print("gradi", 30, 8);
	tft.setFont(BigFont);
	tft.print("16:08.41", LEFT, 30);

	//l'altezza del carattere è 15 pixel
	tft.fillRect(0,30,30,45); // ora
	tft.fillRect(50, 40, 80, 45); // minuti
	tft.fillRect(98, 40, 128, 45); // secondi

	disegnaCursore();

	tft.print("Sistema ON", LEFT, 90);

	//tft.setFont(SmallFont);

}
