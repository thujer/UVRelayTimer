
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

	this->lamp = new Lamp(GPIO_NUM_5, this->bluetooth->getInstance());

}


/**
 * Called from setup()
 */
void App::init() {
	this->bluetooth->setup();
}


void App::showBluetoothHelp() {
	this->bluetooth->getInstance()->printf(
		"\r\n-----------------------------------------\r\n"
		"Welcome to UVRelayTimer\r\n\n"
		"Start timer:\r\n"
		"<time>sec/min/hour\r\n\n"
		"Commands:\r\n"
		"help   ... this menu\r\n"
		"stop   ... stop and reset timer\r\n"
		"pause  ... pause timer and remember time for resume\r\n"
		"resume ... resume in countdown after pause\r\n"
		"ON		... switch light on manually\r\n"
		"OFF	... switch light off manually\r\n"
		"-----------------------------------------\r\n\n");
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
		
		Serial.printf("Detected number: %d\r\n", num);
		this->bluetooth->getInstance()->printf("Detected number: %d\r\n", num);

		if(message.indexOf("sec") > -1) {
			time = num * 1000;
			Serial.printf(" in seconds, calculated time: %d\r\n", time);
			this->bluetooth->getInstance()->printf(" in seconds, calculated time: %d\r\n", time);
		}

		if(message.indexOf("min") > -1) {
			time = num * 1000 * 60;
			Serial.printf(" in minutes, calculated time: %d\r\n", time);
			this->bluetooth->getInstance()->printf("in minutes, calculated time: %d\r\n", time);
		}

		if(message.indexOf("hour") > -1) {
			time = num * 1000 * 60 * 60;
			Serial.printf(" in hours, calculated time: %d\r\n", time);
			this->bluetooth->getInstance()->printf(" in hours, calculated time: %d\r\n", time);
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

		if(message == "pause") {
			this->lamp->pause();
		}

		if(message == "resume") {
			this->lamp->resume();
		}

		if(message == "help") {
			this->showBluetoothHelp();
		}

		if(time) {
			this->lamp->shineDuration(time);
		}

	}



	if(this->mainTimeout->timeout()) {

		if(this->lamp->getRunningState()) {
			
			unsigned long time = this->lamp->getTimeLeft();

			Serial.printf("Running...time left: %lu sec\r\n", time / 1000);

			this->bluetooth->getInstance()->printf("Running, time left: %lu sec\r\n", time / 1000);

			this->mainTimeout->set(REFRESH_TIME);

			//this->bluetooth->getInstance()->printf("Finished.\r\n");
		} 
	}

	if(clientConnected) {
		this->showBluetoothHelp();
		clientConnected = false;
	}
}
