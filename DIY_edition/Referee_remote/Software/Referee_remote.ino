// Программа для самодельного судейского пульта
// На пульте есть 3 кнопки: СТАРТ, СТОП и ПРОГРАММИРОВАНИЕ
// и 2 ИК светодиода разной интенсивности излучения

#include <IRremote.h>  // 4.7.1
IRsend irsendHi;
IRsend irsendLo;

//Номер ринга
const uint8_t dohyoID = 5;
uint8_t startCommand = (dohyoID << 1) | 1;
uint8_t stopCommand = (dohyoID << 1);
uint8_t programCommand = (dohyoID << 1);

// Команды стандарта RobotChallenge
const uint8_t ADDRESS_START_STOP = 0x07;
const uint8_t ADDRESS_PROGRAM = 0x0B;

//Подключение ИК светодиодов и кнопок
const int POWERLED = 5;
const int WEAKLED = 4;
const int START_BUTTON = 2;
const int STOP_BUTTON = 6;
const int PROG_BUTTON = 3;

void setup() {
  pinMode(POWERLED, OUTPUT);
  pinMode(WEAKLED, OUTPUT);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  pinMode(PROG_BUTTON, INPUT_PULLUP);
  irsendHi.begin(POWERLED, DISABLE_LED_FEEDBACK);
  irsendLo.begin(WEAKLED, DISABLE_LED_FEEDBACK);
}

void loop() {
  // Обработка кнопок
  if (!digitalRead(START_BUTTON)) {  // --------------------- START
    irsendHi.sendRC5(ADDRESS_START_STOP, startCommand, 0);
    delay(100);
  }

  if (!digitalRead(STOP_BUTTON)) {  // ------------------------ STOP
    irsendHi.sendRC5(ADDRESS_START_STOP, stopCommand, 1);
    delay(100);
  }

  if (!digitalRead(PROG_BUTTON)) {  // --------------------- PROGRAM
    irsendLo.sendRC5(ADDRESS_PROGRAM, programCommand, 1);
    delay(100);
  }
}
