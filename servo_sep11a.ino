#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int umidadeSolo = 0;
const int pinoSensor = A0; // Define the pin for the humidity sensor
const int umidadeLimite = 1; // Define the humidity limit (adjust as needed)

bool servosParados = false; // State variable to control servos

void setup() {
    servo1.attach(8);
    servo2.attach(9);
    servo3.attach(10); // Adjust according to your setup
    servo4.attach(11); // Adjust according to your setup
    
    Serial.begin(9600);
    delay(1000);        
    Serial.println("Sistema pronto. Envie 'stop' para a parada de emergência, 's' para parar os servos e 'p' para mover para a esquerda.");
}

void loop() {
    // Check for commands via Serial
    if (Serial.available() > 0) {
        String comando = Serial.readStringUntil('\n'); // Read the command until newline
        if (comando.equalsIgnoreCase("s")) { // Check if the command is "stop"
            Serial.println("Servos parados!");
            pararServos(); // Stop servos
            servosParados = true; // Update state
            return; // Exit the loop
        } else if (comando.equalsIgnoreCase("p")) { // Check if the command is "p"
            Serial.println("Movendo para a esquerda.");
            moverServos(180); // Move to 180 degrees
            return; // Exit the loop after moving
        }
    }

    if (servosParados) {
        return; // Skip the rest of the loop if servos are stopped
    }

    // Measure soil humidity
    umidadeSolo = analogRead(pinoSensor);
    umidadeSolo = map(umidadeSolo, 1023, 0, 0, 100);
    
    Serial.print("Umidade do solo: ");
    Serial.println(umidadeSolo);

    // Check if humidity is below the limit
    if (umidadeSolo < umidadeLimite) {
        // If humidity is low, move servos to the left
        Serial.println("Umidade baixa, movendo para a esquerda.");
        moverServos(0); // Move to 180 degrees
    } else {
        // If humidity is adequate, move servos to the right
        Serial.println("Umidade baixa, movendo para a direita.");
        moverServos(180); // Move to 0 degrees
    }

    // Set servos to neutral position after movement
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
    delay(1000); // Wait 1 second before the next reading
}

void moverServos(int angulo) {
    // Move servos to the specified angle
    servo1.write(angulo);
    servo2.write(angulo);
    servo3.write(angulo);
    servo4.write(angulo);
    delay(10000); // Wait for 10 seconds

    // Stop servos at 90 degrees for 1 second
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
    delay(1000); // Wait for 1 second
}
void pararServos() {
    // Stop all servos by setting them to neutral position
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
}
