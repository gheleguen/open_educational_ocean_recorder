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
