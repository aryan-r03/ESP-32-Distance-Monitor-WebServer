#include <WiFi.h>
#include <WebServer.h>

// ============ CONFIGURATION ============
// WiFi credentials
const char* ssid = "WiFi-name";   //your Wifi name 
const char* password = "WiFi-password";  // your wifi password

// Ultrasonic sensor pins - CHANGE THESE TO MATCH YOUR WIRING
const int trigPin = 18;    // TRIG pin
const int echoPin = 19;   // ECHO pin

// Detection zone (in cm)
const float MIN_DISTANCE = 1.0;
const float MAX_DISTANCE = 100.0;

// ============ GLOBAL VARIABLES ============
WebServer server(80);
float currentDistance = 0.0;
bool triggerDetected = false;

// ============ HTML PAGE ============
const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Distance Monitor</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: radial-gradient(#01570e 0%, #050308 100%);
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
            padding: 20px;
        }

        .container {
            background: rgba(25, 52, 32, 0.01);
            border-radius: 30px;
            padding: 40px;
            box-shadow: 0 20px 60px rgba(255, 255, 255, 0.3);
            max-width: 600px;
            width: 100%;
            backdrop-filter: blur(0.5px);
        }

        h1 {
            text-align: center;
            color: #fffefe;
            margin-bottom: 10px;
            font-size: 2.5em;
        }

        .subtitle {
            text-align: center;
            color: #d9d0d0;
            margin-bottom: 40px;
            font-size: 1.1em;
        }

        .status {
            text-align: center;
            padding: 15px;
            border-radius: 15px;
            margin-bottom: 30px;
            font-weight: bold;
            font-size: 1.2em;
            transition: all 0.3s ease;
        }

        .status.safe {
            background: #d4edda;
            color: #155724;
        }

        .status.warning {
            background: #fff3cd;
            color: #856404;
        }

        .status.alert {
            background: #f8d7da;
            color: #721c24;
            animation: pulse 1s infinite;
        }

        @keyframes pulse {

            0%,
            100% {
                transform: scale(1);
            }

            50% {
                transform: scale(1.05);
            }
        }

        .distance-display {
            text-align: center;
            margin: 40px 0;
        }

        .distance-value {
            font-size: 5em;
            font-weight: bold;
            color: #bb2442;
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.1);
        }

        .distance-unit {
            font-size: 2em;
            color: #efa9a9;
        }

        .range-indicator {
            margin: 30px 0;
            padding: 20px;
            background: rgb(#e3f2fd23, 0.5);
            border-radius: 30px;
        }

        .range-bar {
            height: 40px;
            background: linear-gradient(to right, #26a646, #be9005, #da0d22);
            border-radius: 20px;
            position: relative;
            overflow: hidden;
        }

        .range-marker {
            position: absolute;
            top: 0;
            width: 4px;
            height: 100%;
            background: white;
            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);
            transition: left 0.3s ease;
        }

        .range-labels {
            display: flex;
            justify-content: space-between;
            margin-top: 10px;
            font-size: 0.9em;
            color: #ffffff;
        }

        .info-box {
            background: #e3f2fd23;
            padding: 15px;
            border-radius: 10px;
            margin-top: 20px;
            border-left: 4px solid #2195f338;
        }

        .info-box h3 {
            color: #ffffff;
            margin-bottom: 10px;
        }

        .info-box p {
        color: white;
        font-size : 0.8em;
        }

        .connection-status {
            text-align: center;
            margin-top: 20px;
            padding: 10px;
            border-radius: 10px;
            font-size: 0.9em;
        }

        .connected {
            background: #00ff3c3e;
            color: #00ff3c;
        }

        .disconnected {
            background: #ff001531;
            color: #ff0019;
        }
    </style>
</head>

<body>
    <div class="container">
        <h1>🛡️ Distance Monitor</h1>
        <p class="subtitle">ESP32 Live Feed</p>

        <div class="status safe" id="status">
            ✓ All Clear
        </div>

        <div class="distance-display">
            <span class="distance-value" id="distance">--</span>
            <span class="distance-unit">cm</span>
        </div>

        <div class="range-indicator">
            <div class="range-bar">
                <div class="range-marker" id="marker"></div>
            </div>
            <div class="range-labels">
                <span>0 cm</span>
                <span>10 cm</span>
                <span>40 cm</span>
                <span>100+ cm</span>
            </div>
        </div>

        <div class="info-box">
            <h3>Obstruction Detection Zone: 1-100 cm</h3>
            <p>Objects detected within this range will trigger an alert.</p>
        </div>

        <div class="connection-status connected" id="connection">
            🟢 Connected to ESP32
        </div>
    </div>

    <script>
        let lastAlertTime = 0;
        const COOLDOWN = 5000;

        function updateDisplay() {
            fetch('/data')
                .then(response => response.json())
                .then(data => {
                    const distance = data.distance;
                    const trigger = data.trigger;

                    document.getElementById('distance').textContent =
                        distance > 0 ? distance.toFixed(1) : '--';

                    const statusDiv = document.getElementById('status');
                    if (trigger) {
                        statusDiv.className = 'status alert';
                        statusDiv.innerHTML = '🚨 ALERT! Object Detected!';
                    } else if (distance > 10 && distance < 40) {
                        statusDiv.className = 'status warning';
                        statusDiv.innerHTML = '⚠️ Warning - Object in Zone';
                    } else {
                        statusDiv.className = 'status safe';
                        statusDiv.innerHTML = '✓ All Clear';
                    }

                    const marker = document.getElementById('marker');
                    const maxRange = 100;
                    const percentage = Math.min((distance / maxRange) * 100, 100);
                    marker.style.left = percentage + '%';

                    document.getElementById('connection').className =
                        'connection-status connected';
                    document.getElementById('connection').innerHTML =
                        '🟢 Connected to ESP32';
                })
                .catch(error => {
                    document.getElementById('connection').className =
                        'connection-status disconnected';
                    document.getElementById('connection').innerHTML =
                        '🔴 Connection Lost';
                });
        }

        setInterval(updateDisplay, 200);
        updateDisplay();
    </script>
</body>

</html>
)rawliteral";


// ============ FUNCTIONS ============

// Measure distance using ultrasonic sensor
float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000);
  float distance = duration * 0.034 / 2;
  
  if (distance > 400 || distance < 2) {
    return 0;
  }
  
  return distance;
}

// Handle root page request
void handleRoot() {
  server.send_P(200, "text/html", htmlPage);
}

// Handle data API endpoint
void handleData() {
  String json = "{";
  json += "\"distance\":" + String(currentDistance, 1);
  json += ",\"trigger\":" + String(triggerDetected ? "true" : "false");
  json += "}";
  
  triggerDetected = false;
  server.send(200, "application/json", json);
}

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // Setup sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Connect to WiFi
  Serial.println("\n========== CONNECTING ==========");
  Serial.print("SSID: ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  Serial.print("Connecting");
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 60) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n\n✓✓✓ SUCCESS! ✓✓✓");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Signal: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    
    // Setup web server
    server.on("/", handleRoot);
    server.on("/data", handleData);
    server.begin();
    
    Serial.println("\n🌐 Web Server Started!");
    Serial.print("📱 Visit: http://");
    Serial.println(WiFi.localIP());
    Serial.println("================================\n");
  } else {
    Serial.println("\n\n✗✗✗ FAILED ✗✗✗");
    Serial.println("Could not connect to WiFi");
  }
}

// ============ MAIN LOOP ============
void loop() {
  server.handleClient();
  
  currentDistance = measureDistance();
  
  if (currentDistance >= MIN_DISTANCE && currentDistance <= MAX_DISTANCE) {
    triggerDetected = true;
  }
  
  delay(50);
}
