# D. Guide de programmation (v1.0)
Ce présent guide détail le programme de la sonde de température. En aucun cas il n'abordera comment utiliser le logiciel Arduino IDE pour programmer une carte électronique. Pour apprendre cette manipultaion élémentaire d'arduino, sé référer à des tutoriels en lignes (mots clés : téléverser, arduino, C++).  

## 1/ Prérequis
 * [Avoir installé le logiciel Arduino IDE compatible avec votre système d'exploitation.](https://www.arduino.cc/en/software) 
 * [Avoir installé les pilotes nécéssaires pour la carte adafruit adalogger M0 sur Arduino IDE en suivant le tutoriel proposé par adafruit. ](https://learn.adafruit.com/adafruit-feather-m0-adalogger/setup)
 * Avoir installé les librairies :
   * [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)
   * [RTClib](https://www.arduino.cc/reference/en/libraries/rtclib/)
   * [TSYS01](https://github.com/bluerobotics/BlueRobotics_TSYS01_Library.git) (Librairie pour le capteur de température Blue robotics)
   * [SPI](https://www.arduino.cc/reference/en/language/functions/communication/spi/)
   * [SD](https://www.arduino.cc/reference/en/libraries/sd/)


## 2/ Programme
Le programme (Software) de la sonde de température est disponible dans l'archive au chemin suivant : ```/software/0-1-0_software_temp/0-1-0_software_temp.ino.```
 - [Télécharger le programme au format .ino](https://github.com/gheleguen/open_educational_ocean_recorder/blob/main/software/0-1-0_software_temp/0-1-0_software_temp.ino)


### 2.1 Détail du programme
<section style="border: 2px solid red; padding: 20px; border-radius:20px; color: red;">
Attention ! Le détail du programme ci-dessous ne reprend pas toutes les lignes du code. Pour programmer la sonde, préférez télécharger le fichier présent dans l'archive. </section>

#### 2.1.1 Les variables paramétrables

Dans cette section, il est possible de modifier les variables de temps. La sonde est programmé pour réaliser une série de mesures à intervalles réguliers. Tel que :

            M1 M2 M3 - - -Mn            M1 M2 M3 - - -Mn            M1 M2 M3 - - -Mn

 - L’intervalle entre deux séries de mesures est représenté par la variable **"delay_read_temp"**
 - Le nombre de répétitions pour chacune des séquences de prises de mesures **"repetition_mesures"**
 - L’intervalle entre chacune des répétition est défini par la variable : **"repetition_mesures"**

```c++
int delay_read_temp = 10000 ; // Temps entre chacune des série de prises de mesures
int repetition_mesures = 5 ; // Nombre de Répétitions de prises de mesures
int delay_repetition_temp = 10 ; // Temps entre chacune des répétitions
```

Ici on appel les librairies nécessaires pour l'éxecution du programme : 

```c++
//Fonctions d'appel de librairies (I2C et Wire) pour l'horloge RTC DS3231
#include <Wire.h>
#include "RTClib.h"

//Librairie pour lire le capteur de température
#include "TSYS01.h"

//Périphérique de série et la Librairie de la carte SD
#include <SPI.h> //serial peripheral interface for SD card reader
#include <SD.h> //library for SD card reader
```


Quelques variables de branchements qu'il pourrait-être nécessaire de modifier si vous n'utilisez pas tout à fait le même matériel.
```c++
// Définition des variables
float temp;
const int chipSelect = 4; //Broche de lecture du RTC
char datalogFileName[25];
char dateTimeString[40];
int Date2;
int x ;  delay(5000);
pinMode(led, OUTPUT);
int led = 6; // Broche du voyant lumineux
```

#### 2.1.2 Initialisation

Le moniteur série devra être réglé sur 9600 pour permettre la lecture lorsque la carte Arduino sera connecté au PC en USB. 
```c++
  Serial.begin(9600);
```

Initialisation de la carte SD. Dans le cas où la carte serait introuvable, aucun fichier ne sera créé et aucune mesure ne sera prise. 
```c++
  //Initialisation de la carte SD
  Serial.println("Initialisation de la carte SD...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Erreur de lecture de carte SD, ou carte non présente.");
    while (1);
  }
  Serial.println("Carte SD initialisé.");


  /* Cette fonction permet à la bibliothèque SD de définir les dates correctes de création et de modification des fichiers pour tous les fichiers de la carte SD.
  SdFile::dateTimeCallback(SDCardDateTimeCallback);*/
  digitalWrite(led, HIGH);   // LED allumé
  delay(1000);
```

Ici, on teste l'horloge RTC. Puis on l'initialise. Dans le cas où la RTC aurai perdu l'heure, et sera automatiquement réglé sur l'heure de l'ordinateur qui l'a programmé. 
```c++
  //Essai de la lecture du RTC. Si l'horloge est introuvable le programme ne pourra se dérouler. 
  if (! rtc.begin()) {
    Serial.println("Erreur, RTC introuvable.");
    while (1);
  }
  
  //Initialisation de l'horloge RTC sur l'heure de l'ordinateur au téléversement.
  if (rtc.lostPower()) {

    //reset RTC with time when code was compiled if RTC loses power
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  get_numbered_filename(datalogFileName,"LOG" , "CSV");
```

Initialisation de fichier de stockage de données sur la carte SD. Certaines fonctions appel à des sous-fonctions qui seront détaillés plus bas. 
```c++
  // Initialisation du fichier de données LOG en .csv
  Serial.print("Ecriture dans le datalog: ");
  Serial.println(datalogFileName);

  File dataFile = SD.open(datalogFileName, FILE_WRITE);
  delay(250); 

  if (dataFile) {
    Serial.println("====================================================");
    Serial.println("Date,Time [UTC],Temp [°C]");
    dataFile.println("Date,Time [UTC],Temp [°C]");
    dataFile.close();

  }
  // Si le datalog ne peut-être ouvert, un message d'erreur s'affichera sur le moniteur série.
  else {
    Serial.println("Erreur: Impossible d'ouvrir le datalog");
  }

  Serial.println("Starting mesurements");
  Wire.begin();

  sensor.init();
  digitalWrite(led, LOW);   // LEd etteinte
}
```

#### 2.1.3 Boucle

Au début de la boucle on initialise la variable "x" à 0. Cette variable permet de compter le nombre de mesures de reproductions pour chacune des phases.
```c++
  x=0;
```

Tant que le nombre de répétitions de mesures n'est pas atteinte, le programme reproduit une mesure.
```c++
  while (x < repetition_mesures){
    digitalWrite(led, HIGH);   // LEd allumé
    DateTime now = rtc.now(); //check RTC
    get_date_time_string(dateTimeString, now);
    temp = sensor.temperature();

    // Lecture de la température
    sensor.read();

    // Ecriture des données sur le moniteur série
    Serial.print(dateTimeString);
    Serial.print(",");
    Serial.println(temp);
  
    //Stockage de la donnée dans le fichier de données
    File dataFile = SD.open(datalogFileName, FILE_WRITE);
    if (dataFile) {
      dataFile.print(dateTimeString);
      dataFile.print(",");
      dataFile.println(temp);
      dataFile.close();
      x = x+1;
      delay(delay_repetition_temp); // Attente entre chacune des mesures de répétition
    }
  }
```

La LED s'allume à chacune des prise de mesure de température. 
```c++
  digitalWrite(led, LOW);   // LEd etteinte
```

Cette fonction permet d'attendre le temps nécessaire avant de reproduire une séquence de mesure.
```c++
  delay(delay_read_temp); // Attente avant nouvelle séquence de mesures
```

#### 2.1.4 Fonctions secondaires

Fonction permettant le nommage du fichier de données. Elle utilise les données de date et d'heure. 
```c++
void get_numbered_filename(char* outStr, char* filePrefix, char* fileExtension) {

  //sprintf(outStr, "%s000.%s", filePrefix, fileExtension);
  DateTime now = rtc.now();
  Date2 = now.year()-2000;
  sprintf(outStr,"%02d%02d%02d00.%s",Date2,now.month(),now.day(),fileExtension); 
  int namelength = strlen(outStr);
  if (namelength > 12) Serial.println("Erreur: Nom de fichier trop long. Réduire votre nom de fichier à moins de 5 caractères (12 caractères maximum en incluant l'extension) !");

  int i = 1;
  while (SD.exists(outStr)) { 

    int hundreds = i / 100;
    outStr[namelength - 6] = '0' + (i / 10) - (hundreds * 10);
    outStr[namelength - 5] = '0' + i % 10;
    i++;
  }
}
```

Fonction d'écriture de l'heure et de la date sur chaque ligne du tableau.
```c++

void get_date_time_string(char* outStr, DateTime date) {
  sprintf(outStr, "%02d/%02d/%02d,%02d:%02d:%02d", date.year(), date.month(), date.day(), date.hour(), date.minute(), date.second());
  // Note: If you would like the date & time to be seperate columns change the space in the formatting string to a comma - this works because the file type is CSV (Comma Seperated Values)
}
```

### 2.2 Programme complet

En date du : 06/06/2024

```c++
/*
 * Ce programme écrit en C++ est destiné à une sonde de température de fond réalisé par Guillaume Leguen (guillaumeleguen.xyz).
 * Retrouvez la totalité du projet sur readthe doc : https://open-educational-ocean-recorder.readthedocs.io/fr/latest/
 * 
 * Licence : open_educational_ocean_recorder est un projet de Guillaume Leguen proposé sous licence CC-by-sa 4.0
 * Ce programme est basé en partie sur le travail d'oceanography for everyone (https://oceanographyforeveryone.com/)
*/

// Les paramétres suivant peuvent être modifiés comme réglage de la sonde
int delay_read_temp = 10000 ; // Temps entre chacune des série de prises de mesures
int repetition_mesures = 5 ; // Nombre de Répétitions de prises de mesures
int delay_repetition_temp = 10 ; // Temps entre chacune des répétitions

//Fonction d'appel de librairies (I2C et Wire) pour l'horloge RTC DS3231
#include <Wire.h>
#include "RTClib.h"

//Librairie pour lire le capteur de température
#include "TSYS01.h"

//Périphérique de série et la Librairie de la carte SD
#include <SPI.h> //serial peripheral interface for SD card reader
#include <SD.h> //library for SD card reader

TSYS01 sensor;
RTC_DS3231 rtc; // Commenter si utilisation de l'autre RTC
//RTC_PCF8523 rtc; //Décommenter si utilisation de ce RTC

// Définition des variables
float temp;
const int chipSelect = 4; //Broche de lecture du RTC
char datalogFileName[25];
char dateTimeString[40];
int Date2;
int x ;
int led = 6; // Brche du voyant lumineux

// Actions d'initialisation
void setup() {

  Serial.begin(9600);
  delay(5000);
  pinMode(led, OUTPUT);
  //Initialisation de la carte SD
  Serial.println("Initialisation de la carte SD...");

  if (!SD.begin(chipSelect)) {
    Serial.println("Erreur de lecture de carte SD, ou carte non présente.");
    while (1);
  }
  Serial.println("Carte SD initialisé.");


  /* Cette fonction permet à la bibliothèque SD de définir les dates correctes de création et de modification des fichiers pour tous les fichiers de la carte SD.
  SdFile::dateTimeCallback(SDCardDateTimeCallback);*/
  digitalWrite(led, HIGH);   // LED allumé
  delay(1000);

  //Essai de la lecture du RTC. Si l'horloge est introuvable le programme ne pourra se dérouler. 
  if (! rtc.begin()) {
    Serial.println("Erreur, RTC introuvable.");
    while (1);
  }
  
  //Initialisation de l'horloge RTC sur l'heure de l'ordinateur au téléversement.
  if (rtc.lostPower()) {

    //reset RTC with time when code was compiled if RTC loses power
    Serial.println("RTC lost power, lets set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  get_numbered_filename(datalogFileName,"LOG" , "CSV");

  // Initialisation du fichier de données LOG en .csv
  Serial.print("Ecriture dans le datalog: ");
  Serial.println(datalogFileName);

  File dataFile = SD.open(datalogFileName, FILE_WRITE);
  delay(250); 

  if (dataFile) {
    Serial.println("====================================================");
    Serial.println("Date,Time [UTC],Temp [°C]");
    dataFile.println("Date,Time [UTC],Temp [°C]");
    dataFile.close();

  }
  // Si le datalog ne peut-être ouvert, un message d'erreur s'affichera sur le moniteur série.
  else {
    Serial.println("Erreur: Impossible d'ouvrir le datalog");
  }

  Serial.println("Starting mesurements");
  Wire.begin();

  sensor.init();
  digitalWrite(led, LOW);   // LEd etteinte
}

// Début du programme en boucle
void loop() {
  x=0;

  // Tant que le nombre de répétition de mesure n'est pas atteinte, le programme reproduit une mesure
  while (x < repetition_mesures){
    digitalWrite(led, HIGH);   // LEd allumé
    DateTime now = rtc.now(); //check RTC
    get_date_time_string(dateTimeString, now);
    temp = sensor.temperature();

    // Lecture de la température
    sensor.read();

    // Ecriture des données sur le moniteur série
    Serial.print(dateTimeString);
    Serial.print(",");
    Serial.println(temp);
  
    //Stockage de la donnée dans le fichier de données
    File dataFile = SD.open(datalogFileName, FILE_WRITE);
    if (dataFile) {
      dataFile.print(dateTimeString);
      dataFile.print(",");
      dataFile.println(temp);
      dataFile.close();
      x = x+1;
      delay(delay_repetition_temp); // Attente entre chacune des mesures de répétition
    }
  }
  digitalWrite(led, LOW);   // LEd etteinte
  delay(delay_read_temp); // Attente avant nouvelle séquence de mesures

 
}

// Fonction de nommage du fichier de données.
void get_numbered_filename(char* outStr, char* filePrefix, char* fileExtension) {

  //sprintf(outStr, "%s000.%s", filePrefix, fileExtension);
  DateTime now = rtc.now();
  Date2 = now.year()-2000;
  sprintf(outStr,"%02d%02d%02d00.%s",Date2,now.month(),now.day(),fileExtension); 
  int namelength = strlen(outStr);
  if (namelength > 12) Serial.println("Erreur: Nom de fichier trop long. Réduire votre nom de fichier à moins de 5 caractères (12 caractères maximum en incluant l'extension) !");

  int i = 1;
  while (SD.exists(outStr)) { 

    int hundreds = i / 100;
    outStr[namelength - 6] = '0' + (i / 10) - (hundreds * 10);
    outStr[namelength - 5] = '0' + i % 10;
    i++;

  }

}

// Fonction d'écriture de l'heure et de la date.
void get_date_time_string(char* outStr, DateTime date) {
  sprintf(outStr, "%02d/%02d/%02d,%02d:%02d:%02d", date.year(), date.month(), date.day(), date.hour(), date.minute(), date.second());
  // Note: If you would like the date & time to be seperate columns change the space in the formatting string to a comma - this works because the file type is CSV (Comma Seperated Values)
}

// Fonction permettant à la bibliothèque SD de définir les dates correctes de création et de modification des fichiers pour tous les fichiers de la carte SD 
void SDCardDateTimeCallback(uint16_t* date, uint16_t* time)
{
  DateTime now = rtc.now();
  *date = FAT_DATE(now.year(), now.month(), now.day());
  *time = FAT_TIME(now.hour(), now.minute(), now.second());
}
```
