# encoder
Just one universal, well optimized function that interfaces incremental encoder.

## Example Arduino UNO code, to print encoder value 'a' every 20ms
```
#define Encoder_A_Pin 2
#define Encoder_B_Pin 3



void setup() {
	pinMode(Encoder_A_Pin, INPUT_PULLUP);
	pinMode(Encoder_B_Pin, INPUT_PULLUP);
	Serial.begin(115200);
}



void Encoder_loop(int *v) {

	// int A2 = HAL_GPIO_ReadPin(Encoder_A_GPIO_Port, Encoder_A_Pin);
	// int B2 = HAL_GPIO_ReadPin(Encoder_B_GPIO_Port, Encoder_B_Pin);
	int A2 = digitalRead(Encoder_A_Pin);
	int B2 = digitalRead(Encoder_B_Pin);

	static int X;
	X <<= 1;
	X &= 0xA;
	X |= A2 << 2 | B2;

	switch(X) {
	case 2:
	case 4:
	case 11:
	case 13:
		(*v)++;
		break;
	case 1:
	case 7:
	case 8:
	case 14:
		(*v)--;
		break;
	case 5:
	case 10:
		(*v) += 2;
		break;
	case 6:
	case 9:
		(*v) -= 2;
		break;
	}

}

int a = 0;

void loop() {

	unsigned long time = millis();

	Encoder_loop(&a);

	static unsigned long _t;
	if(time - _t > 20) {
		Serial.println((int) a);
		_t = time;
	}

}
```
