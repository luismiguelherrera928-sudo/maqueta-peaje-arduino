#include <Servo.h>

// Definición de pines según tu conexión estándar
const int trigPin = 7;
const int echoPin = 6;
const int servoPin = 9;

Servo barreraServo;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  barreraServo.attach(servoPin);
  barreraServo.write(0); // Posición inicial: barrera cerrada (0 grados)
  
  Serial.begin(9600);
}

void loop() {
  long duracion;
  int distancia;

  // Enviar pulso de ultrasonido para medir distancia
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer el tiempo de retorno del eco
  duracion = pulseIn(echoPin, HIGH);
  distancia = duracion * 0.034 / 2; // Calcular distancia en centímetros

  // Si un vehículo está a menos de 10 cm del sensor
  if (distancia > 0 && distancia < 10) {
    barreraServo.write(90);       // Abrir barrera (90 grados)
    delay(4000);                  // Esperar 4 segundos para que pase el auto
    barreraServo.write(0);        // Cerrar barrera
    delay(1000);                  // Pausa antes de la siguiente lectura
  } else {
    // Mantener barrera cerrada si no hay autos cerca
    barreraServo.write(0);
  }
  
  delay(100);
}
