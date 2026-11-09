// DIY start module
// IR receiver: TSOP34838(Vishay)(protocol RC-5)

#include <IRremote.hpp> //v. 4.7.1
#include <EEPROM.h>

// pins
const byte LED = 9;
const byte RECEIVE_PIN = 7;
int state = 0;  // состояние робота: 0 - остановлен, 1 - запущен

byte dohio = 0;            // номер ринга
const int DOHIO_ADR = 10;  //адрес в памяти, где хранится номер ринга

void Blink(int ms) {
  digitalWrite(LED, 1);
  delay(ms);
  digitalWrite(LED, 0);
}

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(RECEIVE_PIN, INPUT);
  IrReceiver.begin(RECEIVE_PIN);
  EEPROM.get(DOHIO_ADR, dohio);  //читаем номер ринга из EEPROM
  if (dohio > 31) dohio = 0;     //проверяем номер ринга на допустимый диапазон
  Serial.println(dohio);         // выводим номер ринга
  Blink(1000);                   // проверяем светодиод
}

void loop() {
  int receive = chekIReceive();  // опрашиваем ИК приемник TSOP
  if (receive == 1) {            // пришла команда START
    state = 1;
    Serial.println("START");
  } else if (receive == 0) {    //пришла команда STOP
    state = 0;
    Serial.println("STOP");
  }

  digitalWrite(LED, state);
}


int chekIReceive() {
  int result = -99;
  if (IrReceiver.decode()) {
    if ((IrReceiver.decodedIRData.address) == 0x0B) {  // PROGRAMMING
      dohio = IrReceiver.decodedIRData.command;
      EEPROM.put(DOHIO_ADR, dohio);  //сохраняем номер ринга в EEPROM
      Blink(50);
      result = -1;
    } else if ((IrReceiver.decodedIRData.address) == 0x07) {  // START/STOP
      uint8_t comm = IrReceiver.decodedIRData.command;
      if (comm == (dohio + 1)) {  //START
        result = 1;
      } else if (comm == dohio) {  //STOP
        result = 0;
      }
    }
    IrReceiver.resume();
  }
  return result;
}
