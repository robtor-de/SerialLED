# Serial LED
## Funktion
Dies ist eine Software für den Arduino Nano und zur Steuerung eines **P9813** LED Controllers
Die Daten werden per serieller Schnittstelle an den Arduino Nano mit folgendem Protokoll übertragen


### Anschluss
pin  |  function
-----|----------
2    |  clock_pin
3    |  data_pin

### Protokoll
Daten werden in byte-Werten übergeben

Byte0  |Byte1 | Byte2 | Byte3 | Byte4 | Byte5 | Byte6
-------|------|-------|-------|-------|-------|---------
255    |mode  | red   | green | blue  | data  | checksum
       |      | 0-255 | 0-255 | 0-255 | 0-255 | r^g^b

**Jedes gültige paket startet mit einem byte voller Einsen!**

_Die Prüfsumme wird aus der XOR Verknüpfung der Rot, Grün und Blau bytes berechnet_

#### Die Modi

Byte0  | Funktion
--|--
00000001  |  Farbe auf RGB einstellen, **data** hat keine funktion
00000010  |  Fading zu RGB, **data** ist der Übergangsintervall (in Hundertstel Sekunden)
00000100  |  Strobe in RGB, **data** ist die Blinkdauer (1x)
00001000  |  Pulse in RGB, **data** ist die Einblendedauer (Gesamtdauer = **data** *2)
