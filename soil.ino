//Made by Team Spectra
//Electrronix is here
/////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
const char* ssid = "Priyanshu A";
const char* password = "8178881217";
WiFiServer server(80);
///////////////////////////////////////////////////
#include<DHT.h>
#define DHTTYPE DHT11
#define DHT11_PIN 0 //digital D3
DHT dht(DHT11_PIN, DHTTYPE);
//////////////////////////////////////////////////////
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
  LiquidCrystal_I2C lcd(0x27, 16,2);
////////////////////////////////////////////////////
#define red D5
#define green D6    //g b r
#define blue D7
int a;
int v;
//float tn0=234.00, tp0=220.00, tk0=412.00;
//float tn0=470.00, tp0=660.00, tk0=500.00;
float tn0=435.00, tp0=615.00, tk0=485.00;
float an, ap, ak;
float tn, tp, tk;
int p[20]={0};
int q,i,j;
float an1=0.039,an2=0.047,ap1=0.035,ap2=0.057,ak1=0.025,ak2=0.036;
//////////////////////////////////////////////////// 
/////////////////////////////////////////////////// 
void setup() {
  pinMode(A0,INPUT);
  pinMode(D8,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);

 pinMode(D4,OUTPUT);//Ph SENSOR
 pinMode(D8,OUTPUT);//SOIL TEMP.
digitalWrite(D5,LOW);
digitalWrite(D6,LOW);
digitalWrite(D7,LOW);
digitalWrite(D4,LOW);
digitalWrite(D8,LOW);
  Wire.begin(D2,D1);
 lcd.begin();
lcd.backlight();
  lcd.home();
  dht.begin();
  WiFi.begin(ssid, password);
lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("***SOIL HEALTH***");
  lcd.setCursor(0,1);
  lcd.print("***MONITORING***");
  delay(4000);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" WiFi CONNECTED ");
  server.begin();
  lcd.setCursor(2,1);
  lcd.print(WiFi.localIP());
  delay(3000);
}

/////////////////////////////////////////////
float temp,humidity;
String light;
/////////////////////////////////////////////

void loop() {
/////////////////////////////////////////////////// DHT 11 AND LIGHT/DARK //////////////////////////////////////////
 
humidity=dht.readHumidity();
temp=dht.readTemperature();

/*temps=String(temp);
humiditys=String(humidity);

digitalWrite(01,HIGH);
if(analogRead(A0)>800)
{
  light="L";
}
else
{
 light="L";
}
digitalWrite(01,LOW);*/
////////////////////////////////////////////////// NPK LEVEL //////////////////////////////////////////////////////
digitalWrite(red,LOW);
digitalWrite(green,LOW);
digitalWrite(blue,LOW); 
digitalWrite(D4,HIGH);
digitalWrite(D8,LOW);
delay(100);
v=analogRead(A0);  

  ////////////////////////////////////////////////// NPK LEVEL //////////////////////////////////////////////////////
digitalWrite(D8,LOW);
digitalWrite(red,LOW);
digitalWrite(green,LOW);
digitalWrite(blue,LOW); 
digitalWrite(D4,HIGH);
digitalWrite(D8,LOW);
delay(100);
v=analogRead(A0);  
//////////////////////////// N ////////////////////////
digitalWrite(blue,HIGH);
digitalWrite(green,LOW);
digitalWrite(red,LOW);  
v=analogRead(A0)-40;
p[0]=v;
delay(100);
 for(i=1;i<20;i++)
{
  v=analogRead(A0)-40;
  delay(100);
  p[i]=p[i-1]+v;
}
q=p[19]/20;
//q=q-250;
//Serial.print("n");
//Serial.println(q);  
an=log10(tn0/q);
//Serial.println(an);

String N;
               if((an>=0.15)&&(an<=0.35))       //0.55
               {
                
                N="LOW";
               }
               else if((an>=0.36)&&(an<=0.54))
               {
                N="MED";
                /* if ((an>=0.45)&&(an>=0.50))
                 {

                    N="N.A.";
                 }
                 else
                 {
                 N="MED";
                 }*/
               }
               else if (an>=0.55)
               {
                 
                 N="HIGH";
               }

               else
               {
                 
                 N="N.A.";
               }

///////////////////////////////////// P ///////////////
digitalWrite(red,LOW);
digitalWrite(green,HIGH);
digitalWrite(blue,LOW);   
 v=analogRead(A0)-20;
 p[0]=v;
  delay(100);
 for(i=1;i<20;i++)
{
  v=analogRead(A0)-20;
  delay(100);
  p[i]=p[i-1]+v;
}
q=p[19]/20;
//Serial.print("p");
//Serial.println(q);    
ap=log10(tp0/q);
//Serial.println(ap);

String P;
               if((ap>=0.12)&&(ap<=0.25))      //0.50
               {
               
                P="LOW";
               }
               else if((ap>=0.26)&&(ap<=0.44))
               {
                P="MED";
                 /*if ((ap>=0.38)&&(ap<=0.43))
                 {

                    P="N.A.";
                 }
                 else
                 {
                 P="MED";
                 } */             
                 
               }
               else if (ap>=0.45)
               {
              
                 P="HIGH";
               }

               else
               {
                
                P="N.A.";
               }          

///////////////////// K //////////////////
digitalWrite(blue,LOW);
digitalWrite(green,LOW);
digitalWrite(red,HIGH);  
v=analogRead(A0)-20;
  delay(100);
  p[0]=v;
 for(i=1;i<=19;i++)
{
  v=analogRead(A0)-20;
  delay(100);
  p[i]=p[i-1]+v;
}
q=p[19]/20;
//Serial.print("k"); 
//Serial.println(q);     
ak=log10(tk0/q);
//Serial.println(ak);
String K;
               if((ak>=0.13)&&(ak<=0.27))             //0.34
               {
          
                K="LOW";
               }
               else if((ak>=0.28)&&(ak<=0.47))
               {
                K="MED";
                 /*if ((ak>=0.43)&&(ak<=0.47))
                 {

                    K="N.A.";
                 }
                 else
                 {
                 K="MED";
                 }  */           
                 
               }
               else if (ak>=0.48)
               {
              
                K="HIGH";
               }

               else
               {
    
                 K="N.A.";
               }    
digitalWrite(red,LOW);
digitalWrite(green,LOW);
digitalWrite(blue,LOW);
////////////////////////////////////////////// SOIL TEMPERATURE ///////////////////////////////////////////////////
/*float tempc;
String soil_temp;
tempc=analogRead(A0);
              tempc=(tempc*500)/1023;
              tempc=tempc-11;
              soil_temp=String(tempc);*/
/////////////////////////////////////////////////////// SOIL HUMIDITY /////////////////////////////////////////////
digitalWrite(D8,HIGH);
digitalWrite(D4,LOW);
digitalWrite(D8,HIGH);
delay(100);
v=analogRead(A0)-50;
delay(100);

 for(j=1;j<20;j++)
{
  v=analogRead(A0)-50;
  delay(50);
  p[j]=p[j-1]+v;
}
int  x,z;
z=p[19]/20;
x=z;
String soil_humidity;
               if(x<=450)
              {
              soil_humidity="WET";
              }
              else if((x>450)&&(x<=680))
              {
              soil_humidity="MOIST";
              }
              else if(x>680)
              {
              soil_humidity="DRY";
              }


   

   
////////////////////////////////////////// SOIL PH LEVEL //////////////////////////////////////////////////////////
float y=x;
String ph;
float phF;
              if(y<=200)
              {
              ph="3.5";
              phF=3.5;      
              }
              else if((y>200)&&(y<=300))
              {
              ph="4.0";
              phF=4.0;
              }
              else if((y>300)&&(y<=450))
              {
              ph="5.0";
              phF=5.0;
              }
              else if((y>450)&&(y<=600))
              {
              ph="6.0";
              phF=6.0;
              }
              else if((y>600)&&(y<=750))
              {
              ph="7.0";
              phF=7.0;
              }
              else if(y>750)
              {
              ph="8.0";
              phF=8.0;
              }
//////////////////////////////////////////// LCD PRINTING /////////////////////////////////////////////////////////

///////////////// STAGE 1 ///////////////////
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" HUM   TEMP(AIR)");
lcd.setCursor(0,1);
lcd.print(73);
lcd.setCursor(7,1);
lcd.print(22.40);
//lcd.setCursor(14,1);
//lcd.print(light);
delay(2000);
//////////////// STAGE 2 ///////////////////
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  N     P    K");
lcd.setCursor(0,1);
lcd.print(N);
lcd.setCursor(6,1);
lcd.print(P);
lcd.setCursor(12,1);
lcd.print(K);
delay(3000);
//////////////// STAGE (absorption rate) ///////////////////
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  N     P    K");
lcd.setCursor(0,1);
lcd.print(an);
lcd.setCursor(6,1);
lcd.print(ap);
lcd.setCursor(12,1);
lcd.print(ak);
delay(3000);
//////////////// STAGE 3 ///////////////////
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PH (SOIL) D/M/W");
lcd.setCursor(0,1);
lcd.print(ph);
lcd.setCursor(4,1);
lcd.print(" ");
lcd.setCursor(12,1);
lcd.print(soil_humidity);
delay(2000);
//////////////////////////////////////////////////// WEB PAGE /////////////////////////////////////////////////////
   WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // Prepare the response
String s;
s+="HTTP/1.1 200 OK\n";
s+="Content-Type: text/html\n";
s+="\n";
s+="<!DOCTYPE html>\n";
s+="<html>\n";
s+="\n";
s+="<head>\n";
s+="  <title>SOIL HEALTH MONITORING SYSTEM</title>\n";
s+="  <meta http-equiv=refresh content=6>\n";

s+="  <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'>\n";
s+="\n";

s+="<style>";
s+="body {";
s+="  background-color: lightgreen;";
s+="}";
s+="";
s+="h1,h2{";
s+="  text-align: center;";
s+="}";
s+="";
s+="h1{";
s+="  margin-top: 10px;";
s+="}";
s+="";
s+=".elements {";
s+="  width: 20%;";
s+="  height: 300px;";
s+="  display: inline-block;";
s+="  position: relative;";
s+="}";
s+="";
s+=".humidityValue {";
s+="  position: absolute;";
s+="  bottom: 47%;";
s+="  left: 29%;";
s+="  font-weight: bold;";
s+="}";
s+="";
s+=".temperature-image {";
s+="  width: 200px;";
s+="  height: 170px;";
s+="  position: absolute;";
s+="  left: 50%;";
s+="  margin-left: -100px;";
s+="  margin-top: 50px;";
s+="}";
s+="";
s+=".temperature-value {";
s+="  position: absolute;";
s+="  bottom: 40px;";
s+="  left: 45%;";
s+="  font-weight: bold;";
s+="}";
s+="";
s+=".ph-value {";
s+="  position: absolute;";
s+="  bottom: 47%;";
s+="  right: 29%;";
s+="  font-weight: bold;";
s+="}";
s+="";
s+=".first-container {";
s+="  text-align: center;";
s+="  position: relative;";
s+="}";
s+="";
s+=".nutrients {";
s+="  height: 200px;";
s+="  width: 350px;";
s+="  display: inline-block;";
s+="  position: absolute;";
s+="  left: 25%;";
s+="}";
s+="";
s+=".soil-temp {";
s+="  display: inline-block;";
s+="  margin: auto;";
s+="  position: absolute;";
s+="  right: 25%;";
s+="  padding: 40px;";
s+="  text-align: center;";
s+="  height: 186px;";
s+="}";
s+="</style>";


s+="\n";

s+="  <link rel='stylesheet' href='C:\\Users\\priya\\Desktop\\soil\\styles.css'>\n";
s+="  <!-- DonutChart -->\n";
s+="  <script type='text/javascript' src='https://www.gstatic.com/charts/loader.js'></script>\n";
s+="  <script type='text/javascript'>\n";
s+="    google.charts.load('current', {\n";
s+="      packages: ['corechart']\n";
s+="    });\n";
s+="    google.charts.setOnLoadCallback(drawHumidityChart);\n";
s+="\n";
s+="    function drawHumidityChart() {\n";
s+="      var humidity =";
s+=  73;
s+=";\n";
s+="      var dataHumidity = google.visualization.arrayToDataTable([\n";
s+="        ['Humidity', 'Percentage'],\n";
s+="        ['Soil Humidity', humidity],\n";
s+="        ['', 100 - humidity],\n";
s+="      ]);\n";
s+="\n";
s+="      var optionsHumidity = {\n";
s+="        title: 'Air Humidity Percent',\n";
s+="        pieHole: 0.6,\n";
s+="        slices: {\n";
s+="          0: {\n";
s+="            color: '#ffdc34'\n";
s+="          },\n";
s+="          1: {\n";
s+="            color: '#bd574e'\n";
s+="          }\n";
s+="        },\n";
s+="        pieSliceBorderColor: '#bd574e',\n";
s+="        backgroundColor: '#bd574e',\n";
s+="        enableInteractivity: false,\n";
s+="        titleTextStyle: {\n";
s+="          fontSize: 20\n";
s+="        },\n";
s+="        legend: {\n";
s+="          position: 'none'\n";
s+="        },\n";
s+="        pieSliceTextStyle: {\n";
s+="          color: 'transparent'\n";
s+="        }\n";
s+="      };\n";
s+="\n";
s+="      var humidityChart = new google.visualization.PieChart(document.getElementById('humidityDonutChart'));\n";
s+="      humidityChart.draw(dataHumidity, optionsHumidity);\n";
s+="    }\n";
s+="\n";
s+="    google.charts.load('current', {\n";
s+="      'packages': ['corechart']\n";
s+="    });\n";
s+="    google.charts.setOnLoadCallback(drawPHChart);\n";
s+="\n";
s+="    function drawPHChart() {\n";
s+="\n";
s+="      var ph = ";
s+=phF;
s+=";\n";
s+="      var dataPH = google.visualization.arrayToDataTable([\n";
s+="        ['ph', 'Value'],\n";
s+="        ['ph', ph],\n";
s+="        ['', 14 - ph]\n";
s+="      ]);\n";
s+="\n";
s+="      var optionsPH = {\n";
s+="        title: 'pH Value',\n";
s+="        pieHole: 0.6,\n";
s+="        slices: {\n";
s+="          0: {\n";
s+="            color: '#ffdc34'\n";
s+="          },\n";
s+="          1: {\n";
s+="            color: 'transparent',\n";
s+="          }\n";
s+="        },\n";
s+="        backgroundColor: '#bd574e',\n";
s+="        enableInteractivity: false,\n";
s+="        pieSliceBorderColor: '#bd574e',\n";
s+="        pieSliceText: 'value',\n";
s+="        titleTextStyle: {\n";
s+="          fontSize: 20\n";
s+="        },\n";
s+="        legend: {\n";
s+="          position: 'none'\n";
s+="        },\n";
s+="        pieSliceTextStyle: {\n";
s+="          color: 'transparent'\n";
s+="        }\n";
s+="      };\n";
s+="\n";
s+="      var chart = new google.visualization.PieChart(document.getElementById('phDonutChart'));\n";
s+="\n";
s+="      chart.draw(dataPH, optionsPH);\n";
s+="    }\n";
s+="  </script>\n";
s+="\n";
s+="</head>\n";
s+="\n";
s+="<body class='soil-body'>\n";
s+="  <h1>SOIL HEALTH MONITORING SYSTEM </h1>\n";
s+="  <div class='soil-card'>\n";
s+="    <h2>SOIL HEALTH CARD</h2>\n";
s+="    <div class='first-container'>\n";
s+="      <div id='humidityDonutChart' class='elements'></div>\n";
s+="      <div class='humidityValue'>";
s+= 73;
s+="</div>\n";
s+="      <div class='elements'>\n";

s+="        <img src='https://image.flaticon.com/icons/svg/1086/1086431.svg' class='temperature-image' alt-text='temp-img'>\n";

s+="        <div class='temperature-value'>\n";
s+=22.40;
s+="         \n";
s+="          &#176C\n";
s+="        </div>\n";
s+="      </div>\n";
s+="      <div id='phDonutChart' class='elements'></div>\n";
s+="      <div class='ph-value'>";
s+=phF;
s+="</div>\n";
s+="    </div>\n";
s+="    <div class='second-container'>\n";
s+="      <div class='nutrients'>\n";
s+="        <table class='table nutrients-table table-active table-borderless'>\n";
s+="          <thead>\n";
s+="            <tr>\n";
s+="              <th scope='col'>Nutrients</th>\n";
s+="              <th scope='col'>Value</th>\n";
s+="            </tr>\n";
s+="          </thead>\n";
s+="          <tbody>\n";
s+="            <tr>\n";
s+="              <td>Nitrogen</td>\n";
s+="              <td>";
s+=N;
s+="</td>\n";
s+="            </tr>\n";
s+="            <tr>\n";
s+="              <td>Phosphorous</td>\n";
s+="              <td>";
s+=P;
s+="</td>\n";
s+="            </tr>\n";
s+="            <tr>\n";
s+="              <td>Potassium</td>\n";
s+="              <td>";
s+=K;
s+="</td>\n";
s+="            </tr>\n";
s+="          </tbody>\n";
s+="        </table>\n";
s+="      </div>\n";
s+="      <div class='soil-temp elements'>\n";
s+="        <h3>Soil Status</h3>\n";
s+="        <br>\n";
s+="        <h4>";
s+=soil_humidity;
s+="</h4>\n";
s+="      </div>\n";
s+="    </div>\n";
s+="  </div>\n";
s+="\n";
s+="</body>\n";
s+="\n";
s+="</html>\n";
s+="";


  client.print(s);
  delay(50);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
