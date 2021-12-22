# Automatic-Billing-System

The Automatic Billing System is a an attempt towards recreating a basic version of the Amazon Dashkart.

1. Here, we have implemented a smart shopping cart which uses RFID technology, to scan the RFID tags attached to each product, when it is 
dropped into the shopping cart.
    - If the push button is pressed while scanning the product, it will be removed from the bill.
    - If the push button is not pressed while scanning the product, it will be added to the cart.
2. Based on the state of the push button, the details of the scanned products are updated on the webpage hosted by the ESP32 Web Server.
3. After the user completes shopping, the user must press the 'Pay Now' button on the webpage and the user will be directed to the payments page,
where the bill amount payment can be done via UPI by scanning the QR code displayed on the screen.

Note: If the grand total is 0, then the web server will remain on the billing web page on clicking ‘Pay Now’ button. Only when the grand total is greater than 0, 
it will switch to the payment web page with the QR code.

After the bill is paid in full, the customer can leave the supermarket.
This system can provide a hassle-free shopping experience for the customers by removing the need for lengthy billing queues in places like supermarkets etc. 
hence reducing shopping time and improving the customers’ shopping experience.

HARDWARE ARCHITECTURE:

![image](https://user-images.githubusercontent.com/69978515/147108802-a6827e6e-52a5-45df-aeba-5984e0671650.png)

SOFTWARE ARCHITECTURE:

![image](https://user-images.githubusercontent.com/69978515/147108832-242006fc-94c1-4f88-b64f-43be965f4fe4.png)

ALGORITHM FOR THE ENTIRE SYSTEM:

![image](https://user-images.githubusercontent.com/69978515/147108886-fd8b03aa-0896-4cb2-b539-ed45de1a9442.png)

HARDWARE CIRCUIT DIAGRAM:

![image](https://user-images.githubusercontent.com/69978515/147108928-50eb89a1-888b-45ad-ae83-d6b59df22d16.png)

•	The ESP32 communicates with the MFRC522 RFID Reader via the SPI protocol. The MISO and MOSI pins of the RFID Reader are connected to the ESP32 at pins 18 and 23 respectively. 
•	The Push Button is connected to pin 33 and the Red & Green LEDs are connected to pins 12 and 14 respectively.
•	The ESP32 has an inbuilt ability to connect to Wi-Fi. This ability has been harnessed for transmitting the data to the ESP32 Web Server.
•	The ESP32 also has the ability to host its own Web Server, which is where the user’s bill is being displayed in this project.

The major drawback of this project is that this project is entirely based on the assumption that all the customers entering the supermarket are rational and 
honest customers. If a customer doesn’t scan the product while adding it into his cart, it will not be recorded in his bill. Hence, this might lead to theft of 
products from the supermarket.

Cost Analysis:

![image](https://user-images.githubusercontent.com/69978515/147109164-ff97da61-8b8d-4f9c-b99a-8aac9295169d.png)

