# webRS
A web app and hardware solution to enable remote starting my car over the Hologram network. 

Hardware: 
Hologram Dash 1.2
TIP31 based relay driver for secondary starter key

Command flow:

COMMAND TO THE CAR:
Command sent from web app > Firebase database > calls a Firebase function with HTTP request to Hologram > 
Hologram sends a tcp request with command data to the device in the car

CONFIRMATION BACK TO WEB APP:
Device receives command > executes the command > sends a tcp request to Hologram > 
sends an HTTP POST request to Firebase database > Firebase functions interprets data >
web app displays confirmation message to user

To do:
Error handling
Improve scalability
Reduce power draw

