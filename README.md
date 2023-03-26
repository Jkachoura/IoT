# Deelopdracht 2 - Netwerk en Security Vervolg
- Jaouad Kachoura
## Inhoudsopgave

- [Deelopdracht 2 - Netwerk en Security Vervolg](#deelopdracht-2---netwerk-en-security-vervolg)
  - [Inhoudsopgave](#inhoudsopgave)
  - [Installatie](#installatie)
    - [Benodigdheden](#benodigdheden)
    - [Bouwen](#bouwen)
      - [Bot](#bot)
      - [Webserver](#webserver)
  - [Gebruiken](#gebruiken)

## Installatie

### Benodigdheden
Installeer de volgende benodigheden

- [Docker](https://www.docker.com/products/docker-desktop/) 
- [Arduino](https://www.arduino.cc/en/software) of [PlatformIO](https://platformio.org/platformio-ide)
  
De volgende heb je nodig om de bot te maken:
    
- [ESP32](https://www.antratek.nl/nodemcu-32s-esp32-wifi-bluetooth-development-board) (Microcontroller)
- [DHT22](https://learn.adafruit.com/dht/overview) (Temperatuur en vochtigheid sensor)
- Jumpwires
- Micro USB Kabel


### Bouwen

#### Bot
1. Om de bot op te zetten maken we eerst de [schakeling](images/schakeling.png). De pinnen van de DHT22 sluiten we op de volgende manieren aan. Pin 1 sluiten we aan de 3.3V. Pin 2 sluiten we aan GPIO4 ([ESP32 layout](images/esp32layout.png)). Vervolgens Sluiten we Pin 4 aan de Ground. Pin 3 sluiten we niet aan.

2. In de secret.h staan de ssid en pass deze kun je veranderen naar de gewenste WiFi adres. Op de Hogeschool Rotterdam verbinden we standaard met Tesla IoT.
   
3. Vervolgens uploaden we de bot.cpp en de secure.h op de microcontroller m.b.v. Arduino IDE of PlatformIO. **Zorg ervoor dat je de juiste bord selecteert en de benodigde libraries hebt geinstalleerd**

#### Webserver
1. Om onze webpagina op te zetten beginnen we eerst met het starten van Docker Desktop.

2. Treedt de folder binnen in je terminal waar docker-compose.yml zit en voer de volgende commando in:
   
```bash
$ docker compose up -d
```

3. Open https://localhost

## Gebruiken

Nu we op onze webpagina kunnen, kunnen we berichten versturen naar de centrale broker, die op netwerkenbasis.com staat. De berichten die we versturen via onze webpagina zijn ook daar te lezen en de berichten die op netwerkenbasis verstuurd zijn ook op onze webpagina te lezen. We kunnen inloggen op netwerkenbasis.com met de volgende gebruikersnaam en wachtwoord

```bash
student:welkom01
```
Op onze webpagina of die van netwerkenbasis.com kunnen we de volgende commando's versturen naar onze bot als die is aangesloten. **Neem de commando's exact over anders werkt het niet, een spatie te veel maakt zelfs uit.**

Voor het aanzetten van het LED lampje op onze ESP32 verstuur de volgende commando
```
BOT-1021584: led:aan
```

Voor het uitzetten van het LED lampje op onze ESP32 verstuur de volgende commando
```
BOT-1021584: led:uit
```

Voor het opvragen van de temperatuur van de DHT22 verstuur de volgende commando
```
BOT-1021584: temperatuur
```

Voor het opvragen van de vochtigheid van de DHT22 verstuur de volgende commando
```
BOT-1021584: vochtigheid
```

Als er andere bots zijn aangesloten en als die dezelfde syntax gebruiken voor het versturen van commando's. Kunnen we ook commando's daarnaar toe versturen. We moeten alleen de studentennummer weten van de maker van die bot. Dan hoeven we alleen de 1021584 te veranderen van de BOT-1021584 naar de desbetreffende studentennummer.

