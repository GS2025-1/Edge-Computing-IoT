#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display LCD I2C no endereço 0x27 com 20 colunas e 4 linhas
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Definições de pinos
#define ECHO_PIN     2
#define TRIG_PIN     3
#define GREEN_LED    4
#define YELLOW_LED   5
#define RED_LED      6
#define BUZZER_PIN   7
#define RAIN_BUTTON  8

// Variáveis de medição e controle
long duration;
int distance;
unsigned long previousBuzzTime = 0;
unsigned long buzzerStartTime = 0;
bool buzzerOn = false;

void setup() {
  // Configuração dos pinos
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RAIN_BUTTON, INPUT_PULLUP); // Botão com pull-up interno

  // Inicializa comunicação serial
  Serial.begin(9600);

  // Inicializa o LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("   Sensor Iniciado   ");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  bool isRaining = digitalRead(RAIN_BUTTON) == LOW; // Botão pressionado = chuva

  // Dispara o sensor ultrassônico
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Mede a duração do sinal de retorno
  duration = pulseIn(ECHO_PIN, HIGH);

  // Converte tempo em distância (cm)
  distance = duration * 0.034 / 2;

  // Imprime dados no Serial Monitor
  Serial.print("Nivel da agua (cm): ");
  Serial.println(distance);
  Serial.print("Chuva: ");
  Serial.println(isRaining ? "SIM" : "NAO");

  // --- Atualiza o LCD ---

  // Linha 0 - Nível da água
  lcd.setCursor(0, 0);
  lcd.print("Nivel: ");
  lcd.print(distance);
  lcd.print(" cm");
  int textoLength = 7 + String(distance).length();
  for (int i = textoLength; i < 20; i++) lcd.print(" "); // Limpa o restante da linha

  // Linha 1 - Status baseado na distância
  lcd.setCursor(0, 1);
  lcd.print("Status: ");
  if (distance > 100) {
    lcd.print("OK              ");
  } else if (distance > 50) {
    lcd.print("Atencao         ");
  } else {
    lcd.print("Critico         ");
  }

  // Linha 2 - Chuva
  lcd.setCursor(0, 2);
  if (isRaining) {
    lcd.print("Chovendo cuidado ");
  } else {
    lcd.print("Nao esta chovendo ");
  }

  // --- Controle dos LEDs e buzzer ---

  if (distance > 100) {
    // Situação normal
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    buzzerOn = false;
  } else if (distance > 50) {
    // Situação de atenção
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    buzzerOn = false;
  } else {
    // Situação crítica
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // Ativa o buzzer se não estiver tocando e já passou o intervalo
    if (!buzzerOn && currentMillis - previousBuzzTime >= 1000) {
      digitalWrite(BUZZER_PIN, HIGH);
      buzzerOn = true;
      buzzerStartTime = currentMillis;
    }
  }

  // Desativa o buzzer após 200ms
  if (buzzerOn && currentMillis - buzzerStartTime >= 200) {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerOn = false;
    previousBuzzTime = currentMillis;
  }

  // Linha 3 - Alerta de risco de alagamento
  lcd.setCursor(0, 3);
  if (isRaining) {
    lcd.print("RISCO ALAGAMENTO ");
  } else {
    lcd.print("                  ");
  }

  delay(2000); // Espera antes da próxima medição
}
