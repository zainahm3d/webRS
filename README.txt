# webRS
A web app and hardware solution to enable remote starting my car over the Hologram network. I opted to use the REST api for sending commands instead of the available Hologram javascript package on NPM as a learning experience. It works well, so I will transition to the Hologram api soon. 

Hologram dash code: /WebRS/HologramDashStarterCode.ino
Web app front end code: /WebRS/Web App/script.js and WebRS/Web App/index.html
Firebase functions code: /WebRS/Web App/functions/index.js



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

