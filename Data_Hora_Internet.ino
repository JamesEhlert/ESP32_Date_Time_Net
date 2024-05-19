#include <time.h>
#include <WiFi.h>

const char* ssid     = "PRIMCIPAL";
const char* password = "16160248";

long timezone = -3;
byte daysavetime = 0; // 0 se não estiver no horário de verão, 1 se estiver

void setup() {
  Serial.begin(115200);
  // Conexão à rede WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int i = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      ESP.restart();
    }
    i++;
  }
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("Contatando Servidor de Horário");
  configTime(3600 * timezone, daysavetime * 3600, "pool.ntp.org");

}

void loop() {

  struct tm tmstruct ;

  tmstruct.tm_year = 0;
  getLocalTime(&tmstruct);

  char formattedDate[20];
  char formattedHour[20];

  // Formatando a data
  sprintf(formattedDate, "%04d-%02d-%02d", tmstruct.tm_year + 1900, tmstruct.tm_mon + 1, tmstruct.tm_mday);
  
  // Formatando a hora
  sprintf(formattedHour, "%02d:%02d:%02d", tmstruct.tm_hour, tmstruct.tm_min, tmstruct.tm_sec);

  Serial.print("Data: ");
  Serial.print(formattedDate);
  Serial.print(" - Hora: ");
  Serial.println(formattedHour);

  delay(1000);
}