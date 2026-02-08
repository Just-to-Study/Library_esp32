#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("Teste Iniciado!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // Acende
  Serial.println("Luz!");
  delay(1000);                 // Espera 1s
  digitalWrite(LED_PIN, LOW);  // Apaga
  Serial.println("Escuro...");
  delay(1000);                 // Espera 1s
}