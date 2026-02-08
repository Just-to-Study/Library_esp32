#include <WiFi.h>
#include <WebServer.h>

// --- CONFIGURAÇÕES DE REDE (EDITAR AQUI) ---
const char* ssid = "NOME_DA_SUA_REDE";      // Coloque o nome exato do seu Wi-Fi
const char* password = "SENHA_DO_WIFI";     // Coloque a senha do seu Wi-Fi

// Define o pino do LED (GPIO 2 na maioria das placas)
const int ledPin = 2;

// Cria o objeto do servidor na porta 80 (padrão da web)
WebServer server(80);

// --- CÓDIGO HTML (A Interface que vai aparecer no celular) ---
// Isso é o que o navegador vai ler. Engenharia Civil + Web Design básico.
String htmlPage = R"rawliteral(
<!DOCTYPE html> <html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; background-color: #f4f4f4; }
    h1 { color: #333; }
    .button { display: inline-block; padding: 15px 30px; font-size: 24px; cursor: pointer; text-decoration: none; outline: none; color: #fff; background-color: #4CAF50; border: none; border-radius: 15px; box-shadow: 0 9px #999; margin: 10px; }
    .button:active { background-color: #3e8e41; box-shadow: 0 5px #666; transform: translateY(4px); }
    .off { background-color: #e60000; } 
    .off:active { background-color: #cc0000; }
  </style>
</head>
<body>
  <h1>Painel de Controle ESP32</h1>
  <p>Estado do LED Interno</p>
  <a href="/on"><button class="button">LIGAR</button></a>
  <a href="/off"><button class="button off">DESLIGAR</button></a>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Começa desligado

  // Conecta ao Wi-Fi
  Serial.print("Conectando ao ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // Loop de espera até conectar (pode demorar uns segundos)
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Conectado! Mostra o IP
  Serial.println("");
  Serial.println("WiFi conectado.");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP()); // <--- ESTE É O NÚMERO IMPORTANTE

  // --- Rotas do Servidor ---
  
  // 1. Quando você acessa o IP puro (Raiz)
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  // 2. Quando você clica em "LIGAR"
  server.on("/on", []() {
    digitalWrite(ledPin, HIGH);
    Serial.println("Comando Recebido: LIGAR");
    server.send(200, "text/html", htmlPage); // Recarrega a página
  });

  // 3. Quando você clica em "DESLIGAR"
  server.on("/off", []() {
    digitalWrite(ledPin, LOW);
    Serial.println("Comando Recebido: DESLIGAR");
    server.send(200, "text/html", htmlPage); // Recarrega a página
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop() {
  server.handleClient(); // Mantém o servidor ouvindo pedidos
}