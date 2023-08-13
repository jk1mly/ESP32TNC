# ESP32TNC

このブランチはKB4802Pを使った無線機機能を実装した基板で、調整やデータ取得用に連続送信をするためのもの
SW2を押すことで連続送信することが可能になるが、このソフトを通常の状態では使用しない方が良い

対応基板
https://github.com/jk1mly/pcb-qrp-tnc/tree/v2023

本家
https://github.com/amedes/ESP32TNC

以下は本家READMEから差がないところのみ

ESP32TNC is a Terminal Node Controller (TNC) that is implemented for Espressif ESP32 processor.

feature

* supported hardware: FX.25 KISS TNC rev.1/2/3/4/5 and M5Atom, M5StickC Plus
* using small interface board (ESP32TNC HAT) connecting to a transceiver
* using ESP-IDF development framework to install TNC software
* support Bell202 1200bps AFSK
* implementing software modem, decoding capability same as TI TCM3105 modem chip
  * about 980 packets can be decoded against WA8LMF TNC TEST CD Track 1
* support FX.25 forward error correction (Direwolf compatible)
* support KISS protocol only
* using USB serial for host connection and power supply
* support Wi-Fi connection (TCP and UDP)
* display received packet on the LCD (M5StickC Plus only)
* working with internal battery (M5StickC Plus only)
* decoding packet sound without TNC HAT using internal MIC (M5StickC Plus only)

*Caution*: not supported normal **M5StickC**


## Installing the ESP32TNC software

* install [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/), ESP-IDF v4.4 is needed
* download TNC software
```
git clone https://github.com/amedes/ESP32TNC.git
```
* configure TNC software
```
idf.py menuconfig
```
  * chose KISS TNC rev.5  
```
* compile and install
```
idf.py -p PORT -b 1500000 flash monitor
```
(To exit the serial monitor, type Ctrl-].)
* have fun!

# Known Issues

* ESP32TNC will hang up when a packet radio application opens the USB com port.

* unplug the ESP32TNC from the computer
* plug the ESP32TNC to the computer again and pray for luck
* re-execute the packet radio application
* repeat above procedure until good luck becomes...
