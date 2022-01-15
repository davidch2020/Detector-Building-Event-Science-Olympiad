int conditional_value;
float current_voltage_float;
int current_voltage_int;
int previous_voltage = 0;
int concentration;
int volume_of_saltwater = 500; //Volume of salt water measured in mL (118.295 mL in event) 
int concentration_benchmark_1; //Change concentration benchmarks to given values.
int concentration_benchmark_2;
int concentration_benchmark_3;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, INPUT);
  concentration_benchmark_1 = 500; //Change concentration benchmarks to given values.
  concentration_benchmark_2 = 1000;
  concentration_benchmark_3 = 1500;
}

int calculate_concentration(float current_voltage) {
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
  concentration = calculate_concentration(current_voltage_float);

  Serial.println(String(current_voltage_float) + " volts and a concentration of " + concentration + " ppm");

  if (concentration >= 0 && concentration <= concentration_benchmark_1) {
    digitalWrite(11, HIGH);
  } else if (concentration > concentration_benchmark_1 && concentration <= concentration_benchmark_2) {
    digitalWrite(12, HIGH);
  } else if (concentration > concentration_benchmark_2 && concentration <= 5000) {
    digitalWrite(13, HIGH);  
  }
  
  previous_voltage = current_voltage_int;
}
