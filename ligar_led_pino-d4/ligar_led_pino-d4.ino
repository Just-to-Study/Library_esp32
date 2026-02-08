// 1. Definição de Variáveis Globais
// Em Python seria apenas: led = 2
int ledPin = 2; 
int valorMagnetico = 0; // Variável para guardar a leitura do sensor

// 2. Configuração (Roda 1 vez)
void setup() {
  Serial.begin(115200);      // Inicia a comunicação com o PC
  pinMode(ledPin, OUTPUT);   // Diz que o pino do LED é uma SAÍDA de energia
}

// 3. Loop Infinito (Roda para sempre)
void loop() {
  // A. INPUT: Lê o sensor Hall interno do ESP32
  valorMagnetico = hallRead();

  // B. PROCESSAMENTO (Debug): Mostra o valor na tela para você calibrar
  Serial.print("Leitura do Sensor: ");
  Serial.println(valorMagnetico);

  // C. LÓGICA DE DECISÃO (O "if" do Python)
  // O sensor Hall oscila perto de 0 ou valores pequenos. 
  // Um ímã forte vai jogar esse valor para cima de 50 ou abaixo de -50.
  // A função abs() pega o valor absoluto (tira o sinal de negativo).
  
  if (abs(valorMagnetico) > 40) { // Se a força for maior que 40 (calibre este número!)
    digitalWrite(ledPin, HIGH);   // OUTPUT: Liga LED
    Serial.println("-> IMÃ DETECTADO!"); 
  } else {
    digitalWrite(ledPin, LOW);    // OUTPUT: Desliga LED
  }

  delay(200); // Espera um pouquinho para não travar o monitor serial
}