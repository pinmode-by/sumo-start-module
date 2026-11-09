Use AVR USB-ASP programmer and avrdude utility

===To burn fuses ===
avrdude -p t13a -c usbasp -P usb -B 10 -Ulfuse:w:0x79:m -Uhfuse:w:0xef:m

===To flash firmware =========
avrdude -p t13a -c usbasp -P usb -Uflash:w:StartModule.hex:a 