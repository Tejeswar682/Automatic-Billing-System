#include <WiFi.h>
#include <WebServer.h>
#include <SPI.h>
#include <MFRC522.h>

const char* ssid = "SSID";  
const char* password = "PASSWORD*";  

WebServer server(80);

#define SS_PIN 21
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);   

int BUTTON = 33;
int buttonState;

String RFID[3] = {" "," "," "};
String item[3] = {" "," "," "};
int qty[3] = {0,0,0};
int price[3] = {0,0,0};
int cost[3] = {0,0,0};
int j = 0;
String paymentPage = "#";

int totalProducts;
int totalPrice;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);  
  pinMode(BUTTON, INPUT_PULLUP);
  
  SPI.begin();      
  mfrc522.PCD_Init();
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  

  server.on("/", []()
  {
    String page = "<html><head><title>Automatic Billing System</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  #000000 ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Automatic Billing System</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>ITEMS</th><th>QUANTITY</th><th>COST</th></tr><tr><td>"+String(item[0])+"</td><td>"+String(qty[0])+"</td><td>"+String(cost[0])+"</td></tr>";
    page += "<tr><td>"+String(item[1])+"</td><td>"+String(qty[1])+"</td><td>"+String(cost[1])+"</td></tr><tr><td>"+String(item[2])+"</td><td>"+String(qty[2])+"</td><td>"+String(cost[2])+"</td>";
    page += "</tr><tr><th>Grand Total</th><th>"+String(totalProducts)+"</th><th>"+String(totalPrice)+"</th>";
    page += "</tr></table><br><a href="+paymentPage+"><input type=\"button\" name=\"Pay Now\" value=\"Pay Now\" style=\"width: 200px;height: 50px\"></a></center></body></html>";
    page += "<meta http-equiv=\"refresh\" content=\"2\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(BUTTON);
  server.handleClient();
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
 
  Serial.print("UID tag :");
  String content= "";
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  content.toUpperCase();
  String rfid = content.substring(1);
  
  if(rfid == RFID[0])
  {
    if(buttonState == 0)
    {
      qty[0] = qty[0] + 1;
    }
    else if(buttonState == 1)
    {
      if(qty[0]>0)
      {
        qty[0] = qty[0] - 1;  
      }
      else
      {
        Serial.println("Quantity should be positive");
      }
    }
    cost[0] = qty[0]*price[0];
  }

  else if (rfid == RFID[1])
  {
    if(buttonState == 0)
    {
      qty[1] = qty[1] + 1;
    }
    else if(buttonState == 1)
    {
      if(qty[1]>0)
      {
        qty[1] = qty[1] - 1;  
      }
     
      else
      {
        Serial.println("Quantity should be positive");
      }
    }
    
    cost[1] = qty[1]*price[1];
  }

  else if (rfid == RFID[2])
  {
    if(buttonState == 0)
    {
      qty[2] = qty[2] + 1;
    }
    else if(buttonState == 1)
    {
      if(qty[2]>0)
      {
        qty[2] = qty[2] - 1;  
      }
       
      else
      {
        Serial.println("Quantity should be positive");
      }
    }
    cost[2] = qty[2]*price[2];
  }
  
  else
  {
    RFID[j] = rfid;
    qty[j] = qty[j] + 1;
     
    if(RFID[j] == "2C 37 B2 6E")
    {
      item[j] = "Banana"; 
      price[j] = 20; 
    }
    else if(RFID[j] == "83 12 DA 08")
    {
      item[j] = "Apple"; 
      price[j] = 30; 
    }
    else if(RFID[j] == "41 77 8A 09")
    {
      item[j] = "Cake"; 
      price[j] = 40; 
    }
    cost[j] = qty[j]*price[j]; 
    j = j+1;
  }

  totalProducts = qty[0]+qty[1]+qty[2];
  totalPrice = cost[0]+cost[1]+cost[2];

  if(totalPrice>0)
  {
    paymentPage = "https://eloquent-wright-2b68f4.netlify.app/";
  }

  else if(totalPrice<=0)
  {
    paymentPage = "#";
  }

  if(WiFi.status()== WL_CONNECTED)
  {
    WiFiClient client;
    
    if(buttonState == 0)
    {
      digitalWrite(14,HIGH);
      digitalWrite(12,LOW);
      Serial.print(rfid);
      Serial.println(" ADD");
    }
    else if(buttonState == 1)
    {
      digitalWrite(12,HIGH);
      digitalWrite(14,LOW);
      Serial.print(rfid);
      Serial.println(" REMOVE");
    }
  }
  delay(5000);
}
