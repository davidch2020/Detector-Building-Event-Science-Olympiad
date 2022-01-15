int conditional_value;
float current_voltage_float;
int current_voltage_int;
int previous_voltage = 0;
int concentration;
int volume_of_saltwater = 118.294 //Volume of salt water measured in mL 
int concentration_benchmark_1 = 0; //Change concentration benchmarks to given values.
int concentration_benchmark_2 = 0;
int_concentration_benchmark_3 = 0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, INPUT);
}

int calculate_concentration(int current_voltage) {
  float volume_of_salt_grams = (current_voltage - 1.01) / 0.666; //Formula to find volume of salt in grams
  float concentration_g_ml = volume_of_salt_grams / volume_of_saltwater; 
  float concentration_ppm = concentration_g_ml / 0.000001;  
  return (int) concentration_ppm; 
}

// The loop function runs over and over again forever
void loop() {
  conditional_value = analogRead(A0);
  current_voltage_float = conditional_value*(5.0/1023.0);
  current_voltage_int = (int) current_voltage_float;
  concentration = calculate_concentration(current_voltage_int);

  if (current_voltage_int != previous_voltage) {
    Serial.println(String(current_voltage_int) + " volts and a concentration of " + concentration + " ppm");
  }

  if (concentration >= 0 && concentration <= concentration_benchmark_1) {
    digitalWrite(11, HIGH);
  } else if (concentration > concentration_benchmark_1 && concentration <= concentration_benchmark_2) {
    digitalWrite(12, HIGH);
  } else if (concentration > concentration_benchmark_2 && concentration <= 5000) {
    digitalWrite(13, HIGH);  
  }
  
  previous_voltage = current_voltage_int;
}
