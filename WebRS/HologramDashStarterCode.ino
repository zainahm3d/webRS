
String myPhone = "+1MYNUMBER";
String iftttPhone = "+1IFTTTNUMBER"; //actually not used anymore

const int controlPin = R03;

#define SIZE_INBOUND 4096               //Inbound message size limit
char buffer_inbound[SIZE_INBOUND];      //Holds inbound message



bool shouldSleep = true;

void lock() {
  //Serial.println("Car is now locked");

  digitalWrite(controlPin, HIGH);
  Dash.snooze(100);
  digitalWrite(controlPin, LOW);
}

void unlock() {
 // Serial.println("Car is now unlocked");

  digitalWrite(controlPin, HIGH);
  Dash.snooze(120);
  digitalWrite(controlPin, LOW);
  Dash.snooze(120);
  digitalWrite(controlPin, HIGH);
  Dash.snooze(120);
  digitalWrite(controlPin, LOW);
}

void start() {
  //Serial.println("Car has been started");

  digitalWrite(controlPin, HIGH);
  Dash.snooze(4000);
  digitalWrite(controlPin, LOW);
}

void up() {
  lock();
  Dash.snooze(2000);
  lock();
  //Serial.println("Windows have been rolled up");
}

void executeCommand(String message) {

  SerialCloud.println("r"); // means successful command sent, will be
                            // interpreted on Hologram's dashboard.

  if ((message == "lock") || (message == "Lock")) {
    lock();
  } else if ((message == "unlock") || (message == "Unlock")) {
    unlock();
  } else if ((message == "start") || (message == "Start")) {
    start();
  } else if ((message == "up") || (message == "Up")) {
    up();
  } else {
     int batVolts = Charger.batteryMillivolts();
     SerialCloud.println(batVolts);
   // SerialCloud.println("No command parsed");
  }
}

void dataMessageHandler(int length) {
  buffer_inbound[length] = 0;

  shouldSleep = false;

  String dataMessage = buffer_inbound;
  executeCommand(dataMessage);
  HologramCloud.setRGB("RED");
  Dash.snooze(200);
  HologramCloud.offRGB();

  shouldSleep = true;

}

void cloud_notify(cloud_event e) {
  switch(e) {
    case CLOUD_EVENT_CONNECTED:
      //re-open the server socket on port 4010
      HologramCloud.listen(4010);
      break;
  }
}


void smsHandler(const String &sender, const rtc_datetime_t &timestamp,
                const String &message) {

  if ((sender == myPhone) || (sender == iftttPhone)) {
    //Serial.println("Command Recieved: ");
  //  Serial.println(message);
    executeCommand(message);
  } else {
  //  Serial.println("Command from unknown sender: ");
  //  Serial.println(message);
  }

  HologramCloud.setRGB("AQUA");
  Dash.snooze(200);
  HologramCloud.offRGB();
  Dash.snooze(20);
}

void setup() {
  Dash.begin();
  //HologramCloud.powerUp();
  HologramCloud.connect();

  pinMode(controlPin, OUTPUT);
  digitalWrite(controlPin, LOW);
  HologramCloud.setRGB("AQUA");

  while(!HologramCloud.isConnected()); //block code while connecting

  HologramCloud.listen(4010);
  HologramCloud.attachHandlerInbound(dataMessageHandler, buffer_inbound, SIZE_INBOUND-1);
  HologramCloud.attachHandlerNotify(cloud_notify);

  //Serial.begin(9600);
  SerialCloud.begin(115200);
  HologramCloud.attachHandlerSMS(smsHandler);

  Serial.println("Online");
  int batPercent = Charger.batteryMillivolts();
  String networkOp = HologramCloud.getNetworkOperator();
  SerialCloud.println(networkOp + " " + batPercent);
  HologramCloud.offRGB();
}
void loop(){}
