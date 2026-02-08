#define LED_PIN 2     // LED Azul nativo
#define TOUCH_PIN 4   // Pino D4 (GPIO 4) é sensível ao toque

// Valor de referência (Threshold).
// Quando você toca, a leitura cai (pois seu corpo rouba carga).
// Sem toque: ~70 a 80. Com toque: ~10 a 20.
const int threshold = 30;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Teste de Toque Iniciado!");
}

void loop() {
  // Lê o valor do sensor capacitivo
  int touchValue = touchRead(TOUCH_PIN);

  Serial.print("Leitura Capacitiva: ");
  Serial.println(touchValue); // Mostra o número no monitor para você calibrar

  // Lógica: Se o valor for MENOR que o limite, significa que você tocou
  if(touchValue < threshold){
    digitalWrite(LED_PIN, HIGH); // Acende LED
    Serial.println(" -> TOQUE DETECTADO!");
  }
  else{
    digitalWrite(LED_PIN, LOW);  // Apaga LED
  }
  
  delay(100); // Pequena pausa para não poluir o monitor
}