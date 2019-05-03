
#include <App/App.h>

bool clientConnected = false;

void callback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
	if(event == ESP_SPP_SRV_OPEN_EVT) {
		Serial.println("Client Connected");
		clientConnected = true;
	}
}

/**
 * App constructor
 */
App::App() {

	Serial.begin(115200);

	delay(700); // Delay before minicom terminal starts

	Serial.printf("\n--- UVRelayTimer %s started ---\n", APP_VERSION);
	Serial.print("Press:\r\n1 ... switch lamp ON\r\n0 ... lamp OFF\r\n");

	// Timeouts controller
	this->mainTimeout = new Countdown();

	this->bluetooth = new Bluetooth("UVRelayTimer");

	this->bluetooth->getInstance()->register_callback(callback);

	this->lamp = new Lamp(GPIO_NUM_5);
	
}


/**
 * Called from setup()
 */
void App::init() {
	this->bluetooth->setup();
}


/**
 * Main application processes
 */
void App::process() {
	this->bluetooth->process();
	this->lamp->process();


	if(Serial.available()) {
		char incomingChar = Serial.read();
		switch(incomingChar) {
			case '0': this->lamp->off(); break;
			case '1': this->lamp->on(); break;
		}
	}

	if(this->bluetooth->isMessageReady()) {

		String message = this->bluetooth->getMessage();

		Serial.print("Bluetooth command received:");
		Serial.println(message);

		unsigned int time = 0;
		unsigned int num = (int) message.toInt();
		
		Serial.printf("Detected number: %d", num);
		
		if(message.indexOf("min") > -1) {
			time = num * 1000 * 60;
			Serial.printf("Detected minutes, calculated time: %d", time);
		}

		if(message.indexOf("sec") > -1) {
			time = num * 1000;
			Serial.printf("Detected seconds, calculated time: %d", time);
		}

		if(message.indexOf("hod") > -1) {
			time = num * 1000 * 60 * 60;
			Serial.printf("Detected hours, calculated time: %d", time);
		}

		if(message == "ON") {
			this->lamp->on();
		}

		if(message == "OFF") {
			this->lamp->off();
		}

		if(message == "stop") {
			this->lamp->stop();
		}

		if(time) {
			this->lamp->shineDuration(time);
		}

	}



	if(this->mainTimeout->timeout()) {

		if(this->lamp->getRunningState()) {
			
			unsigned long time = this->lamp->getTimeLeft();

			Serial.printf("Running...time left: %lu sec\r\n", time / 1000);

			this->bluetooth->getInstance()->printf("Running...time left: %lu sec\r\n", time / 1000);

			this->mainTimeout->set(REFRESH_TIME);

			//this->bluetooth->getInstance()->printf("Finished.\r\n");
		} 
	}

	if(clientConnected) {
		this->bluetooth->getInstance()->printf("\r\n----------------\r\nWelcome to UVRelayTimer\r\nCommands:\r\nstart,stop,pause,resume,10..30sec,1..30min\r\n----------------\r\n");
		clientConnected = false;
	}
}
