#include <Servo.h>

Servo servo1;  // Cria um objeto Servo para o primeiro servo motor
Servo servo2;
Servo servo3;
Servo servo4;  // Cria um objeto Servo para o segundo servo motor

void setup() {
    servo1.attach(8);  // Associa o servo motor ao pino digital 8
    servo2.attach(9);
    servo3.attach(13);  // Associa o servo motor ao pino digital 8
    servo4.attach(12);  // Associa o servo motor ao pino digital 9
    Serial.begin(9600); // Inicializa a comunicação serial
    delay(1000);        // Espera 1 segundo para garantir a conexão serial
    Serial.println("Sistema pronto. Envie comandos para controlar os servos.");
}

void loop() {
    if (Serial.available() > 0) {  // Verifica se há dados disponíveis na porta serial
        char command = Serial.read();  // Lê o caractere recebido
        
        // Imprime o caractere recebido para depuração
        Serial.print("Comando recebido: ");
        Serial.println(command);
        
        switch (command) {
            case 'r':  // Se o caractere é 'r'
                servo2.write(180);  // Move o servo2 para a posição 180 graus
                servo1.write(180); 
                servo3.write(180);  // Move o servo2 para a posição 180 graus
                servo4.write(180);  // Move o servo1 para a posição 180 graus
                Serial.println("Movendo para direita");  // Mensagem de depuração
                break;

            case 'l':  // Se o caractere é 'l'
                servo2.write(0);  // Move o servo2 para a posição 0 graus
                servo1.write(0);
                servo3.write(0);  // Move o servo2 para a posição 180 graus
                servo4.write(0);  // Move o servo1 para a posição 0 graus
                Serial.println("Movendo para esquerda");  // Mensagem de depuração
                break;

            case 's':  // Se o caractere é 's'
                servo2.write(90);  // Move o servo2 para a posição 90 graus
                servo1.write(90);
                servo3.write(90);  // Move o servo2 para a posição 180 graus
                servo4.write(90);  // Move o servo1 para a posição 90 graus
                Serial.println("Servos em posição neutra");  // Mensagem de depuração
                delay(60);  // Aguarda 60 segundos
                break;

            case 'p':  // Se o caractere é 'p'
                servo2.write(180);  // Move o servo2 para a posição 90 graus
                servo1.write(180);
                servo3.write(180);  // Move o servo2 para a posição 180 graus
                servo4.write(180);  // Ajuste conforme necessário
                Serial.println("Servos retornando à posição inicial (90 graus)");  // Mensagem de depuração
                break;

            default:
                Serial.println("Comando inválido. Use 'r', 'l', 's', ou 'p'");  // Mensagem de erro para comando inválido
                break;
        }
        Serial.flush();  // Garante que todos os dados sejam enviados para o monitor serial
        delay(500);  // Adiciona um pequeno atraso para estabilizar
    }
}
