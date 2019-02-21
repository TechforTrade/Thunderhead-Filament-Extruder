#ifndef Test_h
#define Test_h



//void test(){}

void testAuger(){
	lcd.clear();
	lcd.print(F("WARNING: The Auger"));
	lcd.setCursor(0,1);
	lcd.print(F("must be free to move"));
	lcd.setCursor(0,2);
	lcd.print(F("to perform the"));
	lcd.setCursor(0,3);
	lcd.print(F("following tests."));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	boolean waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
			waitForResponse = false;
		}
	}
	lcd.clear();
	lcd.print(F("A) Enable/Disable"));
	lcd.setCursor(0,1);
	lcd.print(F("C) When Disabled"));
	lcd.setCursor(0,2);
	lcd.print(F("D) EXIT"));

	waitForResponse = true;
	boolean flag = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				auger.enable();
				flag = false;
				} else {
				auger.disable();
				flag = true;
			}
			break;

			case 'C':

			if (!flag){
				configuration.physical.augerEnable = !configuration.physical.augerEnable;
			}
			waitForResponse = false;
			break;

			case 'D':
			activeMenu->display();
			return;
			break;

		}
	}

	//Auger Direction test
	lcd.clear();
	lcd.print(F("Auger Direction Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Continue?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}

	auger.enable();
	auger.setRPM(1);

	lcd.clear();
	lcd.print(F("Auger direction OK?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	lcd.setCursor(0,3);
	lcd.print(F("D) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		switch (key){
			case 'A':
			if (flag){
				auger.disable();
				waitForResponse = false;
			}
			break;

			case 'B':
			configuration.physical.augerDirection = !configuration.physical.augerDirection;
			auger.setDirection();

			break;

			case 'D':
			auger.disable();
			activeMenu->display();
			return;
			break;

		}
	}

	// MicroStepping test
	lcd.clear();
	lcd.print(F("Microsteping Test"));
	delay(5000);
	lcd.clear();
	lcd.print(F("Mark the shaft. "));
	lcd.setCursor(0,1);
	lcd.print(F("Attempting 1 rev"));
	lcd.setCursor(0,2);
	lcd.print(F("A) Begin"));
	lcd.setCursor(0,3);
	lcd.print(F("B) Exit"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			waitForResponse = false;
		}

		if (key == 'B') {
			activeMenu->display();
			return;
		}
	}
	lcd.clear();
	lcd.print(F("Rotating 1 rev..."));
	auger.enable();
	pinMode(6,OUTPUT);

	auger.enable();
	int rpm = 10;
	auger.setRPM(rpm);
	delay(1000.0*60.0/rpm);
	auger.disable();

	lcd.clear();
	lcd.print(F("If the auger didn't"));
	lcd.setCursor(0,1);
	lcd.print(F("make 1 rev, check"));
	lcd.setCursor(0,2);
	lcd.print(F("the wiring and"));
	lcd.setCursor(0,3);
	lcd.print(F("microstep settings"));
	delay(5000);

	//Save the settings
	lcd.clear();
	lcd.print(F("Save Settings?"));
	lcd.setCursor(0,1);
	lcd.print(F("A) Yes"));
	lcd.setCursor(0,2);
	lcd.print(F("B) No"));
	waitForResponse = true;
	while (waitForResponse) {
		key = kpd.getKey();

		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}

		if (key == 'A') {
			configuration.saveConfig();
			waitForResponse = false;
		}

		if (key == 'B') {
			waitForResponse = false;
		}
	}
	activeMenu->display();
}


double getNumber(char *title, char *subTitle){
	char diameterString[6];
	char *diameterPtr;//pointer to char in diameterString.
	bool noDecimal = true;
	lcd.clear();
	lcd.write(title);
	lcd.setCursor(0,1);
	lcd.write(subTitle);
	lcd.setCursor(0,3);
	lcd.write("(Esc press <-)");
	lcd.setCursor(0,2);

	boolean invalid = true;
	diameterPtr = diameterString;// set pointer to first digit

	while (invalid){
		key=kpd.waitForKey();//get user input
		
		//Allow for keyboard input as well
		if (Serial.available() > 0) {
			key = (char)Serial.read();
		}
		
		switch(key){

			case 'D':
			//Check to see that a valid diameter was entered
			if (atof(diameterString) == 0.0){
				return -1;
				}else{
				//return number
				return atof(diameterString);
			}

			case 'A': //backspace was pressed so go back.
			if (diameterPtr > diameterString){
				lcd.setCursor(diameterPtr - diameterString - 1,2);
				lcd.write(' ');
				lcd.setCursor(diameterPtr - diameterString - 1,2);
				diameterPtr--;
				if (*diameterPtr == '.'){
					noDecimal = true;
				}

			}
			else {//back space was pressed to exit 
				//keep state as selectProfile
				return -1;
			}

			case 'B'://invalid do nothing
			break;

			case 'C'://invalid do nothing
			break;

			case '#'://invalid do nothing
			break;

			case '*'://decimal place
			case '.'://decimal place
			if (diameterPtr - diameterString < 5 && noDecimal == true){ //Make sure that the diameterString isn't full
				*diameterPtr = '.';
				lcd.write('.');
				diameterPtr++;
				noDecimal = false;
			}
			break;

			default:
			if (diameterPtr - diameterString < 5){ //Make sure that the diameterString isn't full
				*diameterPtr = key;
				diameterPtr++;
				lcd.write(key);
			}
		}
	}
	return 0.0;
}

void calibrateCalipers(){
	//lcd.clear();
	//lcd.print(F("Caliper Calibration"));
	//Serial.println(F("Caliper Calibration"));
	//delay (4000);
//
	//lcd.clear();
	//lcd.setCursor(0,0);
	//lcd.print(F("Step 1:Load filament"));
	//lcd.setCursor(0,1);
	//lcd.print(F("with target Diameter"));
	//lcd.setCursor(0,3);
	//lcd.print(F("Press <enter>"));
	//Serial.println(F("Step 1: Load filament with target diameter."));
	//
	//char key;
	//while (1){
		//key = kpd.getKey();
		//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if(key == 'D'){
			//break;
		//}
		//if (key == 'A'){
			////      stateMachine.setState(StateMachine::SELECT_PROFILE);
			//return;
		//}
	//}
	//lcd.clear();
	//lcd.print(F("Step 2: Adjust the"));
	//lcd.setCursor(0,1);
	//lcd.write("sensor until it is");
	//lcd.setCursor(0,2);
	//lcd.write("between 450 and 550.");
	//lcd.setCursor(0,3);
	//lcd.write("Then press <enter>.");
	//Serial.println(F("Step2: Adjust the sensor until it is between 450 and 550."));
	//Serial.println(F("Then Press <enter>"));
	//delay(4000);
	//lcd.clear();
//
	//lcd.write("Sensor Adjust");
//
	//double rawADC;
	//while(1){
		//rawADC = outfeed.getRawADC(2);
		//lcd.setCursor(7,1);
		//
		////Replace the following line with code that prints the double on the lcd screen.
	    //lcd.print(rawADC);
		//
		//Serial.println(rawADC);
		//delay(1000);
//
		//if (rawADC < 550.0 && rawADC > 450.0){
			//lcd.setCursor(0,3);
			//lcd.write("Press <enter>");
		//}
//
		//key = kpd.getKey();
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
		//if( key == 'D' /*&& rawADC < 550.0 && rawADC > 450.0*/  ){
			//break;
		//}
		//if (key == 'A'){
			//return;
		//}
	//}
//
	//lcd.clear();
	//lcd.write("Step 3: Load samples");
	//lcd.setCursor(0,1);
	//lcd.write("with known diameter.");
	//lcd.setCursor(0,2);
	//lcd.write("Minimum of 3");
	//lcd.setCursor(0,3);
	//lcd.write("Then record Diameter");
	//Serial.println(F("Step 3: Load samples with known Diameter. Minimum of 3. Then Record Diameter."));
	//delay(4000);
//
	//key = 0;
	//float sampleDias[10];
	//float sampleADCs[10];
	//int i = 0;
	//boolean finished = false;
	//while(i<10 || finished){
		//lcd.clear();
		//lcd.write("Load sample ");
		//lcd.print(i+1);
//
		//lcd.setCursor(0,2);
		//lcd.write("Press 'D' or");
		//
		//lcd.setCursor(0,3);
		//lcd.write("Press 'C' when done");
		//Serial.println(F("Load sample then press 'D'. Press 'C' when Done."));
		//while (1){
			//key = kpd.getKey();
//
			////Allow for keyboard input as well
			//if (Serial.available() > 0) {
				//key = (char)Serial.read();
			//}
//
			//if(key == 'D'){
				//break;
			//}
			//if(key == 'C'){
				//if (i<2){ //abort. Finished but too few samples
					//return;
				//}
				//finished = true;
				//break;
			//}
			//if (key == 'A'){//Abort
				//return;
			//}
		//}
		//if (finished){ break;}
		//sampleADCs[i] = outfeed.getRawADC(2);
		//lcd.clear();
		//Serial.println("sampleADCs[i]");
		//Serial.println(sampleADCs[i]);
		//lcd.print(sampleADCs[i]);
		//delay(7500);
		//lcd.clear();
		//sampleDias[i] = getNumber("Enter Diameter", "<enter> to exit");
		//if (sampleDias[i] == -1){
			//if (i<2){//Invalid number
				//return;
			//}
			//break;
		//}
		//i++;
	//}
	//float slopeAndInt[2];
	//outfeed.linReg(slopeAndInt, &sampleADCs[0], &sampleDias[0],&i);
	//configuration.physical.slope = slopeAndInt[0];
	//configuration.physical.yIntercept = slopeAndInt[1];
	//lcd.clear();
	//lcd.write("Calibration Complete");
	//lcd.setCursor(0,1);
	//lcd.write("Slope: ");
	//lcd.print(configuration.physical.slope,6);
	//lcd.setCursor(0,2);
	//lcd.write("yInt: ");
	//lcd.print(configuration.physical.yIntercept,4);
	//lcd.setCursor(0,3);
	//lcd.write("Press <enter>");
        //configuration.saveConfig();
	//while (1){
		//key = kpd.getKey();
		//if(key){//Return to menu calibrateCalipers is finished
			//return;
		//}
	//}
}

void testOutfeed(){
	//The following is commented out so that the only operation performed is to calibrate the calipers.
	//Change back when needed.
	
	//lcd.clear();
	//lcd.print(F("WARNING: The Outfeed"));
	//lcd.setCursor(0,1);
	//lcd.print(F("must be free to move"));
	//lcd.setCursor(0,2);
	//lcd.print(F("to perform the"));
	//lcd.setCursor(0,3);
	//lcd.print(F("following tests."));
	//delay(5000);
	//lcd.clear();
	//lcd.print(F("Continue?"));
	//lcd.setCursor(0,1);
	//lcd.print(F("A) Yes"));
	//lcd.setCursor(0,2);
	//lcd.print(F("B) No"));
	//boolean waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if (key == 'A') {
			//waitForResponse = false;
		//}
//
		//if (key == 'B') {
			//activeMenu->display();
			//return;
			//waitForResponse = false;
		//}
	//}
	//lcd.clear();
	//lcd.print(F("A) Enable/Disable"));
	//lcd.setCursor(0,1);
	//lcd.print(F("C) When Disabled"));
	//lcd.setCursor(0,2);
	//lcd.print(F("D) EXIT"));
//
	//waitForResponse = true;
	//boolean flag = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//switch (key){
			//case 'A':
			//if (flag){
				//outfeed.enable();
				//flag = false;
				//} else {
				//outfeed.disable();
				//flag = true;
			//}
			//break;
//
			//case 'C':
//
			//if (!flag){
				//configuration.physical.outfeedEnable = !configuration.physical.outfeedEnable;
			//}
			//waitForResponse = false;
			//break;
//
			//case 'D':
			//activeMenu->display();
			//return;
			//break;
//
		//}
	//}
//
	////OUtfeed Direction test
	//lcd.clear();
	//lcd.print(F("Outfeed Direction..."));
	//delay(5000);
	//lcd.clear();
	//lcd.print(F("Continue?"));
	//lcd.setCursor(0,1);
	//lcd.print(F("A) Yes"));
	//lcd.setCursor(0,2);
	//lcd.print(F("B) No"));
	//waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if (key == 'A') {
			//waitForResponse = false;
		//}
//
		//if (key == 'B') {
			//activeMenu->display();
			//return;
		//}
	//}
//
	//outfeed.enable();
	//outfeed.setRPM(1);
//
	//lcd.clear();
	//lcd.print(F("Outfeed dir OK?"));
	//lcd.setCursor(0,1);
	//lcd.print(F("A) Yes"));
	//lcd.setCursor(0,2);
	//lcd.print(F("B) No"));
	//lcd.setCursor(0,3);
	//lcd.print(F("D) Exit"));
	//waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//switch (key){
			//case 'A':
			//if (flag){
				//outfeed.disable();
				//waitForResponse = false;
			//}
			//break;
//
			//case 'B':
			//configuration.physical.outfeedDirection = !configuration.physical.outfeedDirection;
			//outfeed.setDirection();
//
			//break;
//
			//case 'D':
			//outfeed.disable();
			//activeMenu->display();
			//return;
			//break;
//
		//}
	//}
//
	//// MicroStepping test
	//lcd.clear();
	//lcd.print(F("Microsteping Test"));
	//delay(5000);
	//lcd.clear();
	//lcd.print(F("Mark the Roller. "));
	//lcd.setCursor(0,1);
	//lcd.print(F("Attempting 1 rev"));
	//lcd.setCursor(0,2);
	//lcd.print(F("A) Begin"));
	//lcd.setCursor(0,3);
	//lcd.print(F("B) Exit"));
	//waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if (key == 'A') {
			//waitForResponse = false;
		//}
//
		//if (key == 'B') {
			//activeMenu->display();
			//return;
		//}
	//}
	//lcd.clear();
	//lcd.print(F("Rotating 1 rev..."));
	//outfeed.enable();
	//pinMode(6,OUTPUT);
//
	//outfeed.enable();
	//float rpm = 10.0;
	//outfeed.setRPM(rpm);
	//delay(1000.0*60.0/rpm);
	//outfeed.disable();
//
	//lcd.clear();
	//lcd.print(F("If outfeed didn't"));
	//lcd.setCursor(0,1);
	//lcd.print(F("make 1 rev, check"));
	//lcd.setCursor(0,2);
	//lcd.print(F("the wiring and"));
	//lcd.setCursor(0,3);
	//lcd.print(F("microstep settings"));
	//delay(5000);
//
	////Test Roller diameter
	//lcd.clear();
	//lcd.print(F("Roller Diameter Test"));
	//delay(5000);
	//lcd.clear();
	//lcd.print(F("Load 10ft filament."));
	//lcd.setCursor(0,1);
	//lcd.print(F("press Stop at 10Ft."));
	//lcd.setCursor(0,2);
	//lcd.print(F("A) Begin"));
	//lcd.setCursor(0,3);
	//lcd.print(F("B) Exit"));
	//waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if (key == 'A') {
			//waitForResponse = false;
		//}
//
		//if (key == 'B') {
			//activeMenu->display();
			//return;
		//}
	//}
	//outfeed.enable();
	//rpm = 20.0;
	//outfeed.setRPM(rpm);
	//unsigned long startTime = millis();
	//lcd.clear();
	//lcd.print(F("press Stop at 10ft."));
	//lcd.setCursor(0,1);
	//lcd.print(F("A) Stop"));
	//lcd.setCursor(0,2);
	//lcd.print(F("B) Exit"));
	//waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if (key == 'A') {
			//waitForResponse = false;
		//}
//
		//if (key == 'B') {
			//outfeed.disable();
			//activeMenu->display();
			//return;
		//}
	//}
//
	//outfeed.disable();
	//unsigned long stopTime = millis();
	//configuration.physical.outfeedRollerRadius = (300.0*60.0*1000.0)/((float)(stopTime-startTime)*rpm*2.0*3.14159);
//
	////Save the settings
	//lcd.clear();
	//lcd.print(F("Save Settings?"));
	//lcd.setCursor(0,1);
	//lcd.print(F("A) Yes"));
	//lcd.setCursor(0,2);
	//lcd.print(F("B) No"));
	//waitForResponse = true;
	//while (waitForResponse) {
		//key = kpd.getKey();
//
		////Allow for keyboard input as well
		//if (Serial.available() > 0) {
			//key = (char)Serial.read();
		//}
//
		//if (key == 'A') {
			//configuration.saveConfig();
			//waitForResponse = false;
		//}
//
		//if (key == 'B') {
			//waitForResponse = false;
		//}
	//}
	//activeMenu->display();
	//calibrateCalipers();
}

void testStarveFeeder(){

}

void testSpooler(){
//	spooler.setRPM(10);
//	spooler.enable();
//	delay(6000);
//	spooler.disable();
//	activeMenu->display();
// 	lcd.clear();
// 	lcd.print(F("WARNING: The Spooler"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("must be free to move"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("to perform the"));
// 	lcd.setCursor(0,3);
// 	lcd.print(F("following tests."));
// 	delay(5000);
// 	lcd.clear();
// 	lcd.print(F("Continue?"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("A) Yes"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("B) No"));
// 	boolean waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		if (key == 'A') {
// 			waitForResponse = false;
// 		}
// 
// 		if (key == 'B') {
// 			activeMenu->display();
// 			return;
// 			waitForResponse = false;
// 		}
// 	}
// 	lcd.clear();
// 	lcd.print(F("A) Enable/Disable"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("C) When Disabled"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("D) EXIT"));
// 
// 	waitForResponse = true;
// 	boolean flag = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		switch (key){
// 			case 'A':
// 			if (flag){
// 				spooler.enable();
// 				flag = false;
// 				} else {
// 				spooler.disable();
// 				flag = true;
// 			}
// 			break;
// 
// 			case 'C':
// 
// 			if (!flag){
// 				configuration.physical.spoolerEnable = !configuration.physical.spoolerEnable;
// 			}
// 			waitForResponse = false;
// 			break;
// 
// 			case 'D':
// 			activeMenu->display();
// 			return;
// 			break;
// 
// 		}
// 	}
// 
// 	//spooler Direction test
// 	lcd.clear();
// 	lcd.print(F("spooler Direction..."));
// 	delay(5000);
// 	lcd.clear();
// 	lcd.print(F("Continue?"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("A) Yes"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("B) No"));
// 	waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		if (key == 'A') {
// 			waitForResponse = false;
// 		}
// 
// 		if (key == 'B') {
// 			activeMenu->display();
// 			return;
// 		}
// 	}
// 
// 	spooler.enable();
// 	spooler.setRPM(1);
// 
// 	lcd.clear();
// 	lcd.print(F("spooler dir OK?"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("A) Yes"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("B) No"));
// 	lcd.setCursor(0,3);
// 	lcd.print(F("D) Exit"));
// 	waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		switch (key){
// 			case 'A':
// 			if (flag){
// 				spooler.disable();
// 				waitForResponse = false;
// 			}
// 			break;
// 
// 			case 'B':
// 			configuration.physical.spoolerDirection = !configuration.physical.spoolerDirection;
// 			spooler.setDirection();
// 
// 			break;
// 
// 			case 'D':
// 			spooler.disable();
// 			activeMenu->display();
// 			return;
// 			break;
// 
// 		}
// 	}
// 
// 	// MicroStepping test
// 	lcd.clear();
// 	lcd.print(F("Microsteping Test"));
// 	delay(5000);
// 	lcd.clear();
// 	lcd.print(F("Mark the Roller. "));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("Attempting 1 rev"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("A) Begin"));
// 	lcd.setCursor(0,3);
// 	lcd.print(F("B) Exit"));
// 	waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		if (key == 'A') {
// 			waitForResponse = false;
// 		}
// 
// 		if (key == 'B') {
// 			activeMenu->display();
// 			return;
// 		}
// 	}
// 	lcd.clear();
// 	lcd.print(F("Rotating 1 rev..."));
// 	spooler.enable();
// 	pinMode(6,OUTPUT);
// 
// 	spooler.enable();
// 	float rpm = 10.0;
// 	spooler.setRPM(rpm);
// 	delay(1000.0*60.0/rpm);
// 	spooler.disable();
// 
// 	lcd.clear();
// 	lcd.print(F("If spooler didn't"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("make 1 rev, check"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("the wiring and"));
// 	lcd.setCursor(0,3);
// 	lcd.print(F("microstep settings"));
// 	delay(5000);
// 
// 	//Test Roller/spool ratio diameter
// 	lcd.clear();
// 	lcd.print(F("Roller/Disk Test"));
// 	delay(5000);
// 	lcd.clear();
// 	lcd.print(F("Place roller on Disk"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("press Stop at 1 rev."));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("A) Begin"));
// 	lcd.setCursor(0,3);
// 	lcd.print(F("B) Exit"));
// 	waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		if (key == 'A') {
// 			waitForResponse = false;
// 		}
// 
// 		if (key == 'B') {
// 			activeMenu->display();
// 			return;
// 		}
// 	}
// 	spooler.enable();
// 	rpm = 20.0;
// 	spooler.setRPM(rpm);
// 	unsigned long startTime = millis();
// 	lcd.clear();
// 	lcd.print(F("press Stop at 1 rev."));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("A) Stop"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("B) Exit"));
// 	waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		if (key == 'A') {
// 			waitForResponse = false;
// 		}
// 
// 		if (key == 'B') {
// 			outfeed.disable();
// 			activeMenu->display();
// 			return;
// 		}
// 	}
// 
// 	spooler.disable();
// 	unsigned long stopTime = millis();
// 	configuration.physical.spoolerMotorRollerRadius = 1.0;
// 	configuration.physical.spoolerDiskRadius = (rpm*(float)(stopTime-startTime))/(1000.0*60.0);
// 
// 	//Don't forget to check spool dimensions
// 	lcd.clear();
// 	lcd.print(F("Don't forget to set "));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("the spool Dimensions"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("in the spooler menu"));
// 	delay(5000);
// 
// 	//Save the settings
// 	lcd.clear();
// 	lcd.print(F("Save Settings?"));
// 	lcd.setCursor(0,1);
// 	lcd.print(F("A) Yes"));
// 	lcd.setCursor(0,2);
// 	lcd.print(F("B) No"));
// 	waitForResponse = true;
// 	while (waitForResponse) {
// 		key = kpd.getKey();
// 
// 		//Allow for keyboard input as well
// 		if (Serial.available() > 0) {
// 			key = (char)Serial.read();
// 		}
// 
// 		if (key == 'A') {
// 			configuration.saveConfig();
// 			waitForResponse = false;
// 		}
// 
// 		if (key == 'B') {
// 			waitForResponse = false;
// 		}
// 	}
// 	activeMenu->display();
}


void sendCyclesToStarveFeeder(){
	starveFeeder.loadConfig();
	starveFeeder.setCycles(cyclesToSendToStarveFeeder);
}

void sendTimeToStarveFeeder(){
	starveFeeder.loadConfig();
	starveFeeder.setTime(timeToSendToStarveFeeder*60L*1000L);
}

void stopStarveFeeder(){
	starveFeeder.off();
	currentState = STANDBY;
}


#endif









