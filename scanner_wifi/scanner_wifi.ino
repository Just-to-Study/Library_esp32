#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; // Tempo de varredura em segundos
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      // Só mostra se tiver nome, para limpar o lixo visual
      if (advertisedDevice.haveName()) {
        Serial.print("Dispositivo: ");
        Serial.print(advertisedDevice.getName().c_str());
        Serial.print(" | Sinal (RSSI): ");
        Serial.print(advertisedDevice.getRSSI());
        Serial.print(" dBm | Endereço MAC: ");
        Serial.println(advertisedDevice.getAddress().toString().c_str());
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando Scanner Bluetooth BLE...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); // Cria o scanner
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); // Scan ativo gasta mais energia mas acha mais dados
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  Serial.println("Procurando dispositivos Bluetooth...");
  
  // CORREÇÃO AQUI: Adicionado o '*' pois agora a função retorna um ponteiro
  BLEScanResults *foundDevices = pBLEScan->start(scanTime, false);
  
  Serial.print("Encontrados: ");
  // CORREÇÃO AQUI: Mudado de '.' para '->' para acessar o método através do ponteiro
  Serial.println(foundDevices->getCount());
  
  Serial.println("Scan concluído!");
  
  pBLEScan->clearResults();   // Limpa a memória para o próximo scan
  delay(2000);
}