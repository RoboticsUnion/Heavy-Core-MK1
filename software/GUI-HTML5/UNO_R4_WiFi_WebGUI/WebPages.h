#pragma once
#include <Arduino.h>

// Generated from the supplied HTML_GUI website. Keep data in flash.

const char PAGE_MAIN[] PROGMEM = R"GUIHTML(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="Author" content="Robotics Union Software ©">
    <title>Robotics Union Control Software (based on HTML5)</title>
    
    <!-- Styling preset-->
    <link rel="stylesheet" href="style.css">

    <script src="/serial_bridge.js"></script>
</head>
<body>

    <div class="button-row">
        <a href="text-editor.html" class="main-options">Text-Editor</a>
        <a href="controls.html" class="main-options">Controls</a>
        <a href="settings.html" class="main-options">Settings</a>
        <a href="rsd.html" class="main-options">RSD</a>
        <a href="chamber.html" class="main-options">Chamber</a>
        <a href="Main_page.html" class="main-options">Main Page</a>
    </div>

    <h1 class="titels">Robotics Union Control Software</h1>

    <h2 class="under_main_titels">Made by Robotics Union Software © </h2>
    <h2 class="under_main_titels">Version 0.1.1 alpha</h2>

    <h2 class="undertitle_text">Heavy-Core-MK1</h2>
    <p class="normal_text">Heavy-Core-MK1 is the development of a modular robotic arm platform. The goal is to create a scalable, affordable robotics ecosystem where hardware and software are engineered together from the ground up.
    The first two axes have already been designed, printed, assembled, and successfully tested. In parallel, we are developing our own control software for precise motion control.</p>

    <h2 class="undertitle_text">Our Vision</h2>
    <p class="normal_text">We aim to build a 6 DOF robotic arm that:</p>
    <p class="normal_text"> -&gt; Is upgradeable with interchangeable end-effectors</p>
    <p class="normal_text"> -&gt; Is structurally optimized for strength-to-weight efficiency</p>
    <p class="normal_text"> -&gt; Includes a custom-developed control software</p>
    <p class="normal_text"> -&gt; Allows future automation features</p>
    <p class="normal_text"> -&gt; Serves as a platform for robotics development</p>

    <h2 class="undertitle_text">Custom Control Software</h2>
    <p class="normal_text">Our robotic arm will not rely solely on position control. We are developing a control application that will include:</p>
    <p class="normal_text"> -&gt; Real-Time position feedback</p>
    <p class="normal_text"> -&gt; Inverse kinematics calculations</p>
    <p class="normal_text"> -&gt; Intuitive controls</p>
    <p class="normal_text"> -&gt; Integrated arm simulation to prevent collisions or overload situations</p>
    <p class="normal_text"> -&gt; Expandable architecture for future features</p>
    
    <h2 class="undertitle_text">Current Development Status</h2>

    <p class="normal_text"><strong>Completed:</strong></p>
    <p class="normal_text"> -&gt; Torque calculations</p>
    <p class="normal_text"> -&gt; CAD design of Axis 1 and 2</p>
    <p class="normal_text"> -&gt; Stepper motor integration</p>
    <p class="normal_text"> -&gt; First tests of the custom designed Gearboxes</p>
    <p class="normal_text"> -&gt; Functional test of both Axis</p>

    <p class="normal_text"><strong>In Progress:</strong></p>
    <p class="normal_text"> -&gt; Development of remaining Axis</p>
    <p class="normal_text"> -&gt; Gearbox optimization</p>
    <p class="normal_text"> -&gt; Software development</p>
    <p class="normal_text"> -&gt; Control hardware integration</p>

    <h2 class="undertitle_text">Preliminary Technical Specifications</h2>

    <p class="normal_text"> -&gt; Target DOF: 6 DOF</p>
    <p class="normal_text"> -&gt; currently functional: 2 DOF</p>
    <p class="normal_text"> -&gt; Actuators: Stepper motors</p>
    <p class="normal_text"> -&gt; Structure: Aluminum & PLA (Stronger 3D-printed material planned)</p>
    <p class="normal_text"> -&gt; Control system: Arduino & ESP32 based</p>
    <p class="normal_text"> -&gt; Software: Custom standalone desktop or mobile application</p>

    <h2 class="undertitle_text">Development Roadmap</h2>
    <table class="roadmap-table">
        <thead>
            <tr>
                <th>Phase</th>
                <th>Description</th>
                <th>Target</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <td>MK1 Alpha</td>
                <td>2 DOF mechanical validation, first project showcase</td>
                <td>Completed</td>
            </tr>
            <tr>
                <td>MK1 Beta</td>
                <td>4-6 DOF mechanical prototype</td>
                <td>Q3 2026 (estimated)</td>
            </tr>
            <tr>
                <td>MK1 Software Alpha</td>
                <td>Basic motion control & UI</td>
                <td>Q3 2026</td>
            </tr>
            <tr>
                <td>MK1 Integrated Demo</td>
                <td>Hardware + software functional for demonstration</td>
                <td>Q1 2027 (January, HTL Open house)</td>
            </tr>
            <tr>
                <td>MK1 Full Prototype</td>
                <td>Fully functional 6 DOF with software improvements</td>
                <td>Post Open House (future milestone)</td>
            </tr>
        </tbody>
    </table>
    
</body>
</html>
)GUIHTML";

const char PAGE_CONTROLS[] PROGMEM = R"GUICONTROLS(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="Author" content="Robotics Union Software ©">
    <title>Robotics Union Control Software (based on HTML5)</title>
    
    <!-- Styling preset-->
    <link rel="stylesheet" href="style.css">

    <script src="/serial_bridge.js"></script>
</head>
<body>

    <div class="button-row">
        <a href="text-editor.html" class="main-options">Text-Editor</a>
        <a href="controls.html" class="main-options">Controls</a>
        <a href="settings.html" class="main-options">Settings</a>
        <a href="rsd.html" class="main-options">RSD</a>
        <a href="chamber.html" class="main-options">Chamber</a>
        <a href="Main_page.html" class="main-options">Main Page</a>
    </div>

    <h1 class="titels">Manual Robot Control</h1>

    <div class="control-container">
        
        <!-- Gruppe 1: System-Befehle -->
        <h3 class="undertitle_text">System Commands</h3>
        <div class="control-group">
            <button class="cmd-btn_send-command" data-cmd="HAA">Home All Axes</button>
            <button class="cmd-btn_send-command" data-cmd="ENAM">Enable Motors</button>
            <button class="cmd-btn_send-command" data-cmd="DISM">Disable Motors</button>
            <button class="cmd-btn_send-command" data-cmd="ENAC">Enable Axis Controller</button>
            <button class="cmd-btn_send-command" data-cmd="DISC">Disable Axis Controller</button>

        </div>

        <h2 class="undertitle_text">Jogging (Manual Motion)</h2>
        <div class="jogging-grid">
            <button class="main-options send-command" data-cmd="MOVE X10">X +10mm</button>
            <button class="main-options send-command" data-cmd="MOVE X-10">X -10mm</button>
            <button class="main-options send-command" data-cmd="MOVE Y10">Y +10mm</button>
            <button class="main-options send-command" data-cmd="MOVE Y-10">Y -10mm</button>
            <button class="main-options send-command" data-cmd="MOVE Z10">Z +10mm</button>
            <button class="main-options send-command" data-cmd="MOVE Z-10">Z -10mm</button>
        </div>



        <!-- Gruppe 3: Sicherheit -->
        <h3 class="undertitle_text" style="color: red;">Safety</h3>
        <div class="control-group">
            <button class="cmd-btn_send-command" data-cmd="XSTOPX" style="background-color: red; color: rgb(0, 0, 0);">EMERGENCY STOP</button>
        </div>

    </div>

    <!-- Statusanzeige für die USB-Verbindung -->
    <p id="response" class="normal_text" style="color: grey; margin-top: 20px; ">Status: Not Connected</p>

    <!-- JavaScript für die serielle USB-Übertragung -->
    <script>

let port = null;
let writer = null;
let reader = null;


// ============================================================
// SERIAL VERBINDUNG
// ============================================================

async function connectSerial() {

    const statusText = document.getElementById('response');

    if (!("serial" in navigator)) {
        statusText.innerText = "Status: Web Serial is not supported!";
        statusText.style.color = "red";
        return false;
    }

    if (port) {
        return true;
    }

    try {

        statusText.innerText = "Status: Please select your COM-Port...";
        statusText.style.color = "orange";

        port = await navigator.serial.requestPort();

        await port.open({
            baudRate: 115200
        });

        const textEncoder = new TextEncoderStream();

        textEncoder.readable.pipeTo(port.writable);

        writer = textEncoder.writable.getWriter();


        // ----------------------------------------------------
        // READER STARTEN
        // ----------------------------------------------------

        startSerialReader();


        statusText.innerText = "Status: Connected to Robot!";
        statusText.style.color = "green";

        return true;

    }
    catch (error) {

        console.error(error);

        port = null;
        writer = null;

        statusText.innerText =
            "Connection Error: " + error.message;

        statusText.style.color = "red";

        return false;
    }
}


// ============================================================
// SERIAL READER
// ============================================================

async function startSerialReader() {

    if (!port || !port.readable) {
        return;
    }

    const decoder = new TextDecoderStream();

    port.readable.pipeTo(decoder.writable);

    reader = decoder.readable.getReader();


    let buffer = "";


    try {

        while (true) {

            const { value, done } = await reader.read();

            if (done) {
                break;
            }

            if (value) {

                buffer += value;

                let lines = buffer.split("\n");

                buffer = lines.pop();


                for (let line of lines) {

                    line = line.trim();

                    if (line.length > 0) {

                        console.log("ARDUINO -> WEB:", line);

                        handleArduinoResponse(line);
                    }
                }
            }
        }

    }
    catch (error) {

        console.error(
            "Serial reader error:",
            error
        );
    }
}


// ============================================================
// ARDUINO ANTWORT VERARBEITEN
// ============================================================

function handleArduinoResponse(response) {

    const statusText =
        document.getElementById('response');


    // --------------------------------------------------------
    // NORMALE OK ANTWORT
    // --------------------------------------------------------

    if (response.startsWith("OK:")) {

        statusText.innerText =
            "Robot: " + response;

        statusText.style.color = "green";

        return;
    }


    // --------------------------------------------------------
    // SENSOR DATEN
    // --------------------------------------------------------

    if (response.startsWith("AXIS:")) {

        console.log(
            "Sensor data received:",
            response
        );

        statusText.innerText =
            "Sensor: " + response;

        statusText.style.color = "green";

        return;
    }


    // --------------------------------------------------------
    // CHAMBER TEMPERATUR
    // --------------------------------------------------------

    if (response.startsWith("CHAMBER TEMP:")) {

        statusText.innerText =
            "Chamber Temperature: " +
            response.substring(14);

        statusText.style.color = "green";

        return;
    }


    // --------------------------------------------------------
    // CHAMBER HUMIDITY
    // --------------------------------------------------------

    if (response.startsWith("CHAMBER HUM:")) {

        statusText.innerText =
            "Chamber Humidity: " +
            response.substring(12);

        statusText.style.color = "green";

        return;
    }


    // --------------------------------------------------------
    // CHAMBER PRESSURE
    // --------------------------------------------------------

    if (response.startsWith("CHAMBER PRESS:")) {

        statusText.innerText =
            "Chamber Pressure: " +
            response.substring(14);

        statusText.style.color = "green";

        return;
    }


    // --------------------------------------------------------
    // CONTROLLER TEMPERATURE
    // --------------------------------------------------------

    if (response.startsWith("CHAMBER CONTROLER TEMP:")) {

        statusText.innerText =
            "Controller Temperature: " +
            response.substring(23);

        statusText.style.color = "green";

        return;
    }


    // --------------------------------------------------------
    // UNKNOWN
    // --------------------------------------------------------

    if (response.startsWith("UNKNOWN:")) {

        statusText.innerText =
            "Robot: Unknown command";

        statusText.style.color = "red";

        return;
    }


    // --------------------------------------------------------
    // SONSTIGE ANTWORT
    // --------------------------------------------------------

    statusText.innerText =
        "Robot: " + response;
}


// ============================================================
// BEFEHL SENDEN
// ============================================================

async function sendCommand(command) {

    const statusText =
        document.getElementById('response');


    const connected =
        await connectSerial();

    if (!connected) {
        return;
    }


    if (!writer) {

        statusText.innerText =
            "Transmission Error: Serial writer unavailable";

        statusText.style.color = "red";

        return;
    }


    try {

        console.log(
            "WEB -> ARDUINO:",
            command
        );


        await writer.write(
            command + "\n"
        );


        statusText.innerText =
            `Status: Sent "${command}"`;

        statusText.style.color =
            "green";

    }
    catch (error) {

        console.error(error);

        statusText.innerText =
            "Transmission Error: " +
            error.message;

        statusText.style.color =
            "red";
    }
}


// ============================================================
// ALLE COMMAND-BUTTONS
// ============================================================
//
// WICHTIG:
// Wir nehmen jetzt BEIDE Klassen.
//
// .send-command
// .cmd-btn_send-command
//
// Dadurch funktionieren auch die System Commands.
// ============================================================

const commandButtons =
    document.querySelectorAll(
        '.send-command, .cmd-btn_send-command'
    );


commandButtons.forEach(button => {

    button.addEventListener(
        'click',
        async () => {

            const command =
                button.getAttribute('data-cmd');

            if (!command) {

                console.error(
                    "Button has no data-cmd!"
                );

                return;
            }

            await sendCommand(command);
        }
    );

});

</script>
    
</body>
</html>
)GUICONTROLS";

const char PAGE_SETTINGS[] PROGMEM = R"GUISETTINGS(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">

    <title>Robotics Union - Settings</title>

    <link rel="stylesheet" href="style.css">
    <script src="/serial_bridge.js"></script>
</head>

<body>

<!-- Navigation -->
<div class="button-row">

    <a href="text-editor.html" class="main-options">
        Text-Editor
    </a>

    <a href="controls.html" class="main-options">
        Controls
    </a>

    <a href="settings.html" class="main-options">
        Settings
    </a>

    <a href="rsd.html" class="main-options">
        RSD
    </a>

    <a href="chamber.html" class="main-options">
        Chamber
    </a>

    <a href="Main_page.html" class="main-options">
        Main Page
    </a>

</div>


<!-- Title -->
<h1 class="titels" id="pageTitle">
    Settings
</h1>

<p class="under_main_titels" id="pageSubtitle">
    Robotics Union Control Software
</p>


<!-- Robot Settings -->
<div class="settings-section">

    <h3 class="undertitle_text" id="robotSettingsTitle">
        Robot
    </h3>

    <table class="settings-table">

        <tr>

            <td id="robotNameText">
                Robot Name
            </td>

            <td>

                <input
                    id="robotName"
                    class="settings-input"
                    type="text"
                    maxlength="30"
                    placeholder="Robotics Union"
                >

            </td>

        </tr>


    </table>

</div>



<!-- Configuration -->
<div class="settings-section">

    <h3 class="undertitle_text" id="configurationTitle">
        Configuration
    </h3>


    <button
        id="saveButton"
        class="settings-save"
        type="button"
    >
        Save Settings
    </button>


    <button
        id="resetButton"
        class="settings-save"
        type="button"
    >
        Reset Settings
    </button>


    <p
        id="statusMessage"
        class="normal_text"
    ></p>

</div>


<script>

/* =========================================================
   DEFAULT SETTINGS
   ========================================================= */

const DEFAULT_SETTINGS = {

    robotName: "Robotics Union",

    language: "en",

    autoSave: "yes"

};


/* =========================================================
   HTML ELEMENTS
   ========================================================= */

const robotName =
    document.getElementById("robotName");

const language =
    document.getElementById("language");

const autoSave =
    document.getElementById("autoSave");

const saveButton =
    document.getElementById("saveButton");

const resetButton =
    document.getElementById("resetButton");

const statusMessage =
    document.getElementById("statusMessage");


/* =========================================================
   LOAD SETTINGS
   ========================================================= */

function loadSettings() {

    let settings = DEFAULT_SETTINGS;

    const saved =
        localStorage.getItem(
            "robotics_union_settings"
        );


    if (saved) {

        try {

            settings = {
                ...DEFAULT_SETTINGS,
                ...JSON.parse(saved)
            };

        } catch (error) {

            settings = DEFAULT_SETTINGS;

        }

    }


    robotName.value =
        settings.robotName;

    language.value =
        settings.language;

    autoSave.value =
        settings.autoSave;


    updateLanguage();

}


/* =========================================================
   SAVE SETTINGS
   ========================================================= */

function saveSettings() {

    const settings = {

        robotName:
            robotName.value.trim() ||
            "Robotics Union",

        language:
            language.value,

        autoSave:
            autoSave.value

    };


    localStorage.setItem(

        "robotics_union_settings",

        JSON.stringify(settings)

    );


    showStatus(
        language.value === "de"
            ? "Einstellungen gespeichert."
            : "Settings saved."
    );

}


/* =========================================================
   RESET SETTINGS
   ========================================================= */

function resetSettings() {

    localStorage.removeItem(
        "robotics_union_settings"
    );


    robotName.value =
        DEFAULT_SETTINGS.robotName;

    language.value =
        DEFAULT_SETTINGS.language;

    autoSave.value =
        DEFAULT_SETTINGS.autoSave;


    updateLanguage();


    showStatus(
        language.value === "de"
            ? "Einstellungen zurückgesetzt."
            : "Settings reset."
    );

}


/* =========================================================
   STATUS MESSAGE
   ========================================================= */

function showStatus(message) {

    statusMessage.textContent =
        message;

    statusMessage.style.display =
        "block";


    setTimeout(function () {

        statusMessage.textContent = "";

    }, 2500);

}


/* =========================================================
   LANGUAGE
   ========================================================= */

function updateLanguage() {

    if (language.value === "de") {

        document.documentElement.lang =
            "de";


        document.title =
            "Robotics Union - Einstellungen";


        document.getElementById(
            "pageTitle"
        ).textContent =
            "Einstellungen";


        document.getElementById(
            "pageSubtitle"
        ).textContent =
            "Robotics Union Steuerungssoftware";


        document.getElementById(
            "robotSettingsTitle"
        ).textContent =
            "Roboter";


        document.getElementById(
            "robotNameText"
        ).textContent =
            "Robotername";


        document.getElementById(
            "languageText"
        ).textContent =
            "Sprache";


        document.getElementById(
            "generalSettingsTitle"
        ).textContent =
            "Allgemein";


        document.getElementById(
            "autoSaveText"
        ).textContent =
            "Einstellungen automatisch speichern";


        document.getElementById(
            "configurationTitle"
        ).textContent =
            "Konfiguration";


        saveButton.textContent =
            "Einstellungen speichern";


        resetButton.textContent =
            "Einstellungen zurücksetzen";


        autoSave.options[0].text =
            "Aktiviert";

        autoSave.options[1].text =
            "Deaktiviert";

    }

    else {

        document.documentElement.lang =
            "en";


        document.title =
            "Robotics Union - Settings";


        document.getElementById(
            "pageTitle"
        ).textContent =
            "Settings";


        document.getElementById(
            "pageSubtitle"
        ).textContent =
            "Robotics Union Control Software";


        document.getElementById(
            "robotSettingsTitle"
        ).textContent =
            "Robot";


        document.getElementById(
            "robotNameText"
        ).textContent =
            "Robot Name";


        document.getElementById(
            "languageText"
        ).textContent =
            "Language";


        document.getElementById(
            "generalSettingsTitle"
        ).textContent =
            "General";


        document.getElementById(
            "autoSaveText"
        ).textContent =
            "Auto Save Settings";


        document.getElementById(
            "configurationTitle"
        ).textContent =
            "Configuration";


        saveButton.textContent =
            "Save Settings";


        resetButton.textContent =
            "Reset Settings";


        autoSave.options[0].text =
            "Enabled";

        autoSave.options[1].text =
            "Disabled";

    }

}


/* =========================================================
   EVENTS
   ========================================================= */

saveButton.addEventListener(
    "click",
    saveSettings
);


resetButton.addEventListener(
    "click",
    resetSettings
);


language.addEventListener(
    "change",
    function () {

        updateLanguage();


        if (autoSave.value === "yes") {

            saveSettings();

        }

    }
);


robotName.addEventListener(
    "input",
    function () {

        if (autoSave.value === "yes") {

            saveSettings();

        }

    }
);


autoSave.addEventListener(
    "change",
    function () {

        if (autoSave.value === "yes") {

            saveSettings();

        }

    }
);


/* =========================================================
   START
   ========================================================= */

loadSettings();

</script>

</body>
</html>)GUISETTINGS";

const char PAGE_RSD[] PROGMEM = R"GUIRSD(<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="Author" content="Robotics Union Software ©">
    <title>Robotics Union Control Software (based on HTML5)</title>

    <style>
        /* --- BASIS LAYOUT --- */
        body {
            border: 2px solid #111111;
            border-radius: 6px;
            padding: 35px;
            margin: 20px;
            background-color: #fafafa;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            color: #1e1e1e;
        }

        /* --- NAVIGATION & BUTTONS --- */
        .button-row {
            display: flex;
            justify-content: flex-start;
            gap: 15px;
            margin-bottom: 40px;
            align-items: center;
            flex-wrap: wrap;
        }

        .main-options {
            height: 40px;
            min-width: 140px;
            padding: 0 20px;
            color: #ffffff;
            background-color: #4a4a4a;
            border: 2px solid #111111;
            border-radius: 4px;
            cursor: pointer;
            font-weight: 600;
            text-align: center;
            display: inline-flex;
            align-items: center;
            justify-content: center;
            text-decoration: none;
            box-sizing: border-box;
            transition: background-color 0.2s ease, color 0.2s ease;
        }

        .main-options:hover {
            background-color: #222222;
            color: #ffffff;
        }

        .titels {
            font-size: 28px;
            font-weight: bold;
            margin-bottom: 20px;
            text-align: center;
            letter-spacing: 0.5px;
        }

        /* --- COMMAND BUTTONS & PANEL --- */
        .cmd-btn_send-command {
            height: 40px;
            min-width: 160px;
            padding: 0 25px;
            color: #ffffff;
            background-color: #2b2b2b;
            border: 2px solid #111111;
            border-radius: 4px;
            cursor: pointer;
            font-weight: bold;
            text-align: center;
            display: inline-flex;
            align-items: center;
            justify-content: center;
            text-decoration: none;
            box-sizing: border-box;
            transition: background-color 0.2s ease;
        }

        .cmd-btn_send-command:hover {
            background-color: #555555;
        }

        .control-panel {
            display: flex;
            align-items: center;
            gap: 15px;
            margin-bottom: 35px;
            background: #f0f0f0;
            padding: 15px 20px;
            border: 2px solid #111111;
            border-radius: 4px;
        }

        .control-panel label {
            font-weight: 600;
            font-size: 14px;
        }

        select.main-options {
            width: auto;
            padding: 0 10px;
            background-color: #ffffff;
            color: #111111;
        }

        /* --- SENSOR GRID & CARDS --- */
        .axis-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
            gap: 20px;
        }

        .axis-card {
            border: 2px solid #111111;
            border-radius: 4px;
            padding: 20px;
            background: #ffffff;
        }

        .axis-card h3 {
            margin-top: 0;
            font-size: 18px;
            border-bottom: 2px solid #111111;
            padding-bottom: 6px;
            margin-bottom: 15px;
        }

        .data-field {
            margin: 8px 0;
            font-size: 14px;
            font-family: 'Consolas', 'Courier New', monospace;
            color: #444444;
        }

        .data-field span {
            font-weight: 600;
            color: #111111;
        }
    </style>
    <script src="/serial_bridge.js"></script>
</head>

<body>

    <!-- NAVIGATION -->
    <div class="button-row">
        <a href="text-editor.html" class="main-options">Text-Editor</a>
        <a href="controls.html" class="main-options">Controls</a>
        <a href="settings.html" class="main-options">Settings</a>
        <a href="rsd.html" class="main-options">RSD</a>
        <a href="chamber.html" class="main-options">Chamber</a>
        <a href="Main_page.html" class="main-options">Main Page</a>
    </div>

    <!-- TITLE -->
    <div class="titels">
        Raw Sensor Data (RSD)
    </div>

    <!-- CONTROL PANEL -->
    <div class="control-panel">

        <button
            id="connectBtn"
            class="cmd-btn_send-command"
            style="background-color: #2e7d32;">
            Connect Serial
        </button>

        <button
            id="readSensorBtn"
            class="cmd-btn_send-command">
            Read Sensor Data
        </button>

        <div
            style="
                display: flex;
                align-items: center;
                gap: 10px;
                margin-left: auto;
            ">

            <label for="axisSelect">
                Achsen:
            </label>

            <select
                id="axisSelect"
                class="main-options"
                style="height: 40px; min-width: 100px;">

                <option value="ALL">ALL</option>
                <option value="1">1</option>
                <option value="2">2</option>
                <option value="3">3</option>
                <option value="4">4</option>
                <option value="5">5</option>
                <option value="6">6</option>

            </select>
        </div>
    </div>

    <!-- AXIS DATA -->
    <div class="axis-grid">

        <!-- Achse 1 -->
        <div class="axis-card">
            <h3>Achse 1</h3>

            <div class="data-field">
                Position:
                <span id="a1-pos">-</span>
            </div>

            <div class="data-field">
                Motor Temp:
                <span id="a1-temp">-</span> °C
            </div>

            <div class="data-field">
                Load Cell:
                <span id="a1-load">-</span> N
            </div>

            <div class="data-field">
                MPU/IMU:
                <span id="a1-mpu">-</span>
            </div>
        </div>

        <!-- Achse 2 -->
        <div class="axis-card">
            <h3>Achse 2</h3>

            <div class="data-field">
                Position 1:
                <span id="a2-pos1">-</span>
            </div>

            <div class="data-field">
                Position 2:
                <span id="a2-pos2">-</span>
            </div>

            <div class="data-field">
                Motor Temp 1:
                <span id="a2-temp1">-</span> °C
            </div>

            <div class="data-field">
                Motor Temp 2:
                <span id="a2-temp2">-</span> °C
            </div>

            <div class="data-field">
                Load Cell:
                <span id="a2-load">-</span> N
            </div>
        </div>

        <!-- Achse 3 -->
        <div class="axis-card">
            <h3>Achse 3</h3>

            <div class="data-field">
                Position:
                <span id="a3-pos">-</span>
            </div>

            <div class="data-field">
                Motor Temp:
                <span id="a3-temp">-</span> °C
            </div>

            <div class="data-field">
                Load Cell:
                <span id="a3-load">-</span> N
            </div>
        </div>

        <!-- Achse 4 -->
        <div class="axis-card">
            <h3>Achse 4</h3>

            <div class="data-field">
                Position:
                <span id="a4-pos">-</span>
            </div>

            <div class="data-field">
                Motor Temp:
                <span id="a4-temp">-</span> °C
            </div>

            <div class="data-field">
                Load Cell:
                <span id="a4-load">-</span> N
            </div>

            <div class="data-field">
                MPU/IMU:
                <span id="a4-mpu">-</span>
            </div>
        </div>

        <!-- Achse 5 -->
        <div class="axis-card">
            <h3>Achse 5</h3>

            <div class="data-field">
                Position:
                <span id="a5-pos">-</span>
            </div>

            <div class="data-field">
                Motor Temp:
                <span id="a5-temp">-</span> °C
            </div>

            <div class="data-field">
                Load Cell:
                <span id="a5-load">-</span> N
            </div>
        </div>

        <!-- Achse 6 -->
        <div class="axis-card">
            <h3>Achse 6</h3>

            <div class="data-field">
                Position:
                <span id="a6-pos">-</span>
            </div>

            <div class="data-field">
                Motor Temp:
                <span id="a6-temp">-</span> °C
            </div>

            <div class="data-field">
                Load Cell:
                <span id="a6-load">-</span> N
            </div>

            <div class="data-field">
                MPU/IMU:
                <span id="a6-mpu">-</span>
            </div>
        </div>

    </div>

    <!-- JAVASCRIPT -->
    <script>

        let port = null;
        let writer = null;
        let reader = null;


        /* =========================================================
           SERIAL VERBINDUNG
           ========================================================= */

        document
            .getElementById("connectBtn")
            .addEventListener("click", async () => {

                try {

                    // Prüfen, ob Web Serial unterstützt wird
                    if (!("serial" in navigator)) {
                        alert(
                            "Web Serial wird von diesem Browser nicht unterstützt."
                        );
                        return;
                    }

                    // Serial Port auswählen
                    port = await navigator.serial.requestPort();

                    // Verbindung öffnen
                    await port.open({
                        baudRate: 115200
                    });

                    // Writer holen
                    writer = port.writable.getWriter();

                    // Button ändern
                    const btn = document.getElementById("connectBtn");

                    btn.textContent = "Connected";
                    btn.style.backgroundColor = "#1b5e20";

                    // Automatisches Lesen starten
                    readLoop();

                } catch (error) {

                    console.error(
                        "Verbindungsfehler:",
                        error
                    );

                    alert(
                        "Serielle Verbindung fehlgeschlagen."
                    );
                }
            });


        /* =========================================================
           SENSOR-DATEN ANFORDERN
           ========================================================= */

        document
            .getElementById("readSensorBtn")
            .addEventListener("click", async () => {

                const selectedVal =
                    document.getElementById("axisSelect").value;

                const command =
                    `READ SENSOR DATA ${selectedVal}\n`;

                if (writer) {

                    try {

                        const encoder =
                            new TextEncoder();

                        await writer.write(
                            encoder.encode(command)
                        );

                    } catch (error) {

                        console.error(
                            "Fehler beim Senden:",
                            error
                        );

                    }

                } else {

                    alert(
                        `Nicht verbunden! Befehl: "${command.trim()}"`
                    );
                }
            });


        /* =========================================================
           SERIAL READ LOOP
           ========================================================= */

        async function readLoop() {

            if (!port || !port.readable) {
                console.error(
                    "Kein lesbarer Serial-Port vorhanden."
                );
                return;
            }

            const textDecoder =
                new TextDecoderStream();

            const readableStreamClosed =
                port.readable.pipeTo(
                    textDecoder.writable
                );

            reader =
                textDecoder.readable.getReader();

            let buffer = "";

            try {

                while (true) {

                    const {
                        value,
                        done
                    } = await reader.read();

                    if (done) {
                        break;
                    }

                    if (!value) {
                        continue;
                    }

                    // Neue Daten an den Buffer anhängen
                    buffer += value;


                    /*
                     * Verarbeitet vollständige Zeilen.
                     *
                     * Beispiel:
                     *
                     * AXIS:1,125.4,42,15.3,OK
                     *
                     */

                    while (buffer.includes("\n")) {

                        const lineIndex =
                            buffer.indexOf("\n");

                        const currentLine =
                            buffer
                                .substring(0, lineIndex)
                                .trim();

                        // Bereits verarbeitete Zeile entfernen
                        buffer =
                            buffer.substring(
                                lineIndex + 1
                            );


                        // Nur AXIS-Daten verarbeiten
                        if (
                            currentLine.startsWith("AXIS:")
                        ) {

                            parseAxisData(
                                currentLine
                            );
                        }
                    }
                }

            } catch (error) {

                console.error(
                    "Fehler beim Lesen der seriellen Daten:",
                    error
                );

            } finally {

                if (reader) {
                    reader.releaseLock();
                    reader = null;
                }

                console.log(
                    "Serial Reader beendet."
                );
            }
        }


        /* =========================================================
           ACHSEN-DATEN VERARBEITEN
           ========================================================= */

        function parseAxisData(line) {

            /*
             * "AXIS:" entfernen
             *
             * Beispiel:
             *
             * AXIS:1,125.4,42,15.3,OK
             *
             * wird zu:
             *
             * 1,125.4,42,15.3,OK
             */

            const rawData =
                line.replace("AXIS:", "");

            // Daten am Komma trennen
            const parts =
                rawData.split(",");

            // Erste Zahl ist die Achs-ID
            const axisNum =
                parts[0].trim();


            /* =====================================================
               ACHSE 1 / 4 / 6

               Erwartetes Format:

               AXIS:1,Position,MotorTemp,LoadCell,MPUData

               bzw.

               AXIS:4,Position,MotorTemp,LoadCell,MPUData

               AXIS:6,Position,MotorTemp,LoadCell,MPUData
               ===================================================== */

            if (
                axisNum === "1" ||
                axisNum === "4" ||
                axisNum === "6"
            ) {

                const position =
                    document.getElementById(
                        `a${axisNum}-pos`
                    );

                const temperature =
                    document.getElementById(
                        `a${axisNum}-temp`
                    );

                const load =
                    document.getElementById(
                        `a${axisNum}-load`
                    );

                const mpu =
                    document.getElementById(
                        `a${axisNum}-mpu`
                    );


                if (position) {
                    position.textContent =
                        parts[1] || "-";
                }

                if (temperature) {
                    temperature.textContent =
                        parts[2] || "-";
                }

                if (load) {
                    load.textContent =
                        parts[3] || "-";
                }

                if (mpu) {
                    mpu.textContent =
                        parts[4] || "-";
                }
            }


            /* =====================================================
               ACHSE 2

               Erwartetes Format:

               AXIS:2,
               Position1,
               Position2,
               MotorTemp1,
               MotorTemp2,
               LoadCell
               ===================================================== */

            else if (axisNum === "2") {

                const pos1 =
                    document.getElementById(
                        "a2-pos1"
                    );

                const pos2 =
                    document.getElementById(
                        "a2-pos2"
                    );

                const temp1 =
                    document.getElementById(
                        "a2-temp1"
                    );

                const temp2 =
                    document.getElementById(
                        "a2-temp2"
                    );

                const load =
                    document.getElementById(
                        "a2-load"
                    );


                if (pos1) {
                    pos1.textContent =
                        parts[1] || "-";
                }

                if (pos2) {
                    pos2.textContent =
                        parts[2] || "-";
                }

                if (temp1) {
                    temp1.textContent =
                        parts[3] || "-";
                }

                if (temp2) {
                    temp2.textContent =
                        parts[4] || "-";
                }

                if (load) {
                    load.textContent =
                        parts[5] || "-";
                }
            }


            /* =====================================================
               ACHSE 3 / 5

               Erwartetes Format:

               AXIS:3,Position,MotorTemp,LoadCell

               bzw.

               AXIS:5,Position,MotorTemp,LoadCell
               ===================================================== */

            else if (
                axisNum === "3" ||
                axisNum === "5"
            ) {

                const position =
                    document.getElementById(
                        `a${axisNum}-pos`
                    );

                const temperature =
                    document.getElementById(
                        `a${axisNum}-temp`
                    );

                const load =
                    document.getElementById(
                        `a${axisNum}-load`
                    );


                if (position) {
                    position.textContent =
                        parts[1] || "-";
                }

                if (temperature) {
                    temperature.textContent =
                        parts[2] || "-";
                }

                if (load) {
                    load.textContent =
                        parts[3] || "-";
                }
            }
        }

    </script>

</body>

</html>)GUIRSD";

const char PAGE_CHAMBER[] PROGMEM = R"GUICHAMBER(
<!DOCTYPE html>
<html lang="en">
<head>

    <meta charset="UTF-8">
    <meta name="Author" content="Robotics Union Software ©">

    <title>Robotics Union Control Software (based on HTML5)</title>

    <!-- Styling preset -->
    <link rel="stylesheet" href="style.css">

    <script src="/serial_bridge.js"></script>
</head>


<body>


    <!-- =========================================================
         NAVIGATION
    ========================================================== -->

    <div class="button-row">

        <a href="text-editor.html" class="main-options">
            Text-Editor
        </a>

        <a href="controls.html" class="main-options">
            Controls
        </a>

        <a href="settings.html" class="main-options">
            Settings
        </a>

        <a href="rsd.html" class="main-options">
            RSD
        </a>

        <a href="chamber.html" class="main-options">
            Chamber
        </a>

        <a href="Main_page.html" class="main-options">
            Main Page
        </a>

    </div>


    <!-- =========================================================
         TITLE
    ========================================================== -->

    <h1 class="titels">
        Manual Robot Control
    </h1>


    <div class="control-container">


        <!-- =====================================================
             FAN CONTROL
        ====================================================== -->

        <h3 class="undertitle_text">
            Fan Control
        </h3>


        <div
            class="control-group"
            style="display: flex; gap: 15px; align-items: center; margin-bottom: 20px;"
        >

            <select
                id="fan-select"
                class="main-options"
                style="width: auto; padding: 0 15px; background-color: white; color: black; border: 2px solid #111111;"
            >

                <option value="1">
                    Fan 1
                </option>

                <option value="2">
                    Fan 2
                </option>

                <option value="3">
                    Fan 3
                </option>

                <option value="4">
                    Fan 4
                </option>

            </select>


            <button
                class="main-options fan-command"
                data-base-cmd="CHAMBER FAN ON"
            >
                Fan On
            </button>


            <button
                class="main-options fan-command"
                data-base-cmd="CHAMBER FAN OFF"
            >
                Fan Off
            </button>


            <button
                class="main-options fan-command"
                data-base-cmd="CHAMBER FAN SPEED +"
            >
                Speed +
            </button>


            <button
                class="main-options fan-command"
                data-base-cmd="CHAMBER FAN SPEED -"
            >
                Speed -
            </button>


            <button
                class="main-options fan-command"
                data-base-cmd="CHAMBER FAN AUTO"
            >
                Automatic Speed Control
            </button>

        </div>



        <!-- =====================================================
             OTHER CHAMBER CONTROLS
        ====================================================== -->

        <h3 class="undertitle_text">
            Other Chamber Controls
        </h3>


        <div
            class="control-group"
            style="display: flex; gap: 15px; margin-bottom: 20px;"
        >

            <button
                class="main-options send-command"
                data-cmd="CHAMBER LIGHTS ON"
            >
                Lights On
            </button>


            <button
                class="main-options send-command"
                data-cmd="CHAMBER LIGHTS OFF"
            >
                Lights Off
            </button>


            <button
                class="main-options send-command"
                data-cmd="CHAMBER PSU OFF +"
            >
                Power down PSU
            </button>


            <button
                class="main-options send-command"
                data-cmd="CHAMBER PSU ON -"
            >
                Power up PSU
            </button>

        </div>



        <!-- =====================================================
             SENSOR READINGS
        ====================================================== -->

        <h2 class="undertitle_text">
            Sensor Readings
        </h2>


        <div
            class="control-group"
            style="display: flex; gap: 15px; margin-bottom: 20px; flex-wrap: wrap;"
        >

            <!-- TEMPERATURE -->

            <button
                class="main-options send-command"
                data-cmd="CHAMBER READ TEMP"
            >
                Read Temperature ONLY AIR
            </button>


            <!-- HUMIDITY -->

            <button
                class="main-options send-command"
                data-cmd="CHAMBER READ HUM"
            >
                Read Humidity
            </button>


            <!-- PRESSURE -->

            <button
                class="main-options send-command"
                data-cmd="CHAMBER READ PRESS"
            >
                Read Pressure
            </button>


            <!-- CONTROLLER TEMPERATURE -->

            <button
                class="main-options send-command"
                data-cmd="CHAMBER READ CONTROLER TEMP"
            >
                Read Controller Temperature
            </button>

        </div>



        <!-- =====================================================
             SENSOR DATA
        ====================================================== -->

        <h2 class="undertitle_text">
            Chamber Data
        </h2>


        <div class="axis-grid">


            <!-- AIR TEMPERATURE -->

            <div class="axis-card">

                <h3>
                    Air Temperature
                </h3>

                <div class="data-field">

                    Temperature:
                    <span id="chamber-temp">
                        ---
                    </span>

                </div>

            </div>



            <!-- HUMIDITY -->

            <div class="axis-card">

                <h3>
                    Humidity
                </h3>

                <div class="data-field">

                    Humidity:
                    <span id="chamber-hum">
                        ---
                    </span>

                </div>

            </div>



            <!-- PRESSURE -->

            <div class="axis-card">

                <h3>
                    Pressure
                </h3>

                <div class="data-field">

                    Pressure:
                    <span id="chamber-press">
                        ---
                    </span>

                </div>

            </div>



            <!-- CONTROLLER TEMPERATURE -->

            <div class="axis-card">

                <h3>
                    Controller Temperature
                </h3>

                <div class="data-field">

                    Temperature:
                    <span id="chamber-controller-temp">
                        ---
                    </span>

                </div>

            </div>


        </div>


    </div>


    <!-- =========================================================
         CONNECTION STATUS
    ========================================================== -->

    <p
        id="response"
        class="normal_text"
        style="color: grey; margin-top: 20px;"
    >
        Status: Not Connected
    </p>



    <!-- =========================================================
         JAVASCRIPT
    ========================================================== -->

    <script>


        /* =========================================================
           SERIAL VARIABLES
        ========================================================== */

        let port = null;

        let writer = null;

        let reader = null;



        /* =========================================================
           CONNECT SERIAL
        ========================================================== */

        async function connectSerial() {

            const statusText =
                document.getElementById("response");


            if (!port) {

                try {

                    statusText.innerText =
                        "Status: Please select your COM-Port...";


                    port =
                        await navigator.serial.requestPort();


                    await port.open({
                        baudRate: 115200
                    });


                    /* ---------------------------------------------
                       WRITER
                    --------------------------------------------- */

                    const textEncoder =
                        new TextEncoderStream();


                    textEncoder.readable.pipeTo(
                        port.writable
                    );


                    writer =
                        textEncoder.writable.getWriter();


                    /* ---------------------------------------------
                       START READER
                    --------------------------------------------- */

                    startSerialReader();


                    statusText.innerText =
                        "Status: Connected to Robot!";


                    statusText.style.color =
                        "green";


                    return true;

                }

                catch (error) {

                    statusText.innerText =
                        "Connection Error: "
                        + error.message;


                    statusText.style.color =
                        "red";


                    return false;

                }

            }


            return true;

        }



        /* =========================================================
           SERIAL READER
        ========================================================== */

        async function startSerialReader() {

            if (!port || !port.readable) {

                return;

            }


            const textDecoder =
                new TextDecoderStream();


            port.readable.pipeTo(
                textDecoder.writable
            );


            reader =
                textDecoder.readable.getReader();


            let buffer = "";


            try {

                while (true) {

                    const {
                        value,
                        done
                    } = await reader.read();


                    if (done) {

                        break;

                    }


                    if (value) {

                        buffer += value;


                        /*
                         * Eine Nachricht endet mit \n
                         */

                        while (buffer.includes("\n")) {

                            const newlineIndex =
                                buffer.indexOf("\n");


                            const line =
                                buffer
                                    .substring(
                                        0,
                                        newlineIndex
                                    )
                                    .trim();


                            buffer =
                                buffer.substring(
                                    newlineIndex + 1
                                );


                            if (line.length > 0) {

                                handleChamberData(
                                    line
                                );

                            }

                        }

                    }

                }

            }

            catch (error) {

                console.error(
                    "Serial reader error:",
                    error
                );

            }

        }



        /* =========================================================
           CHAMBER DATA AUSWERTEN
        ========================================================== */

        function handleChamberData(line) {

            console.log(
                "Robot -> Web:",
                line
            );


            /*
             * -----------------------------------------------------
             * TEMPERATURE
             *
             * Erwartet:
             *
             * CHAMBER TEMP:24.6
             * -----------------------------------------------------
             */

            if (
                line.startsWith(
                    "CHAMBER TEMP:"
                )
            ) {

                const value =
                    line.substring(
                        "CHAMBER TEMP:".length
                    );


                document.getElementById(
                    "chamber-temp"
                ).textContent =
                    value + " °C";


                return;

            }


            /*
             * -----------------------------------------------------
             * HUMIDITY
             *
             * Erwartet:
             *
             * CHAMBER HUM:42.3
             * -----------------------------------------------------
             */

            if (
                line.startsWith(
                    "CHAMBER HUM:"
                )
            ) {

                const value =
                    line.substring(
                        "CHAMBER HUM:".length
                    );


                document.getElementById(
                    "chamber-hum"
                ).textContent =
                    value + " %";


                return;

            }


            /*
             * -----------------------------------------------------
             * PRESSURE
             *
             * Erwartet:
             *
             * CHAMBER PRESS:1013.2
             * -----------------------------------------------------
             */

            if (
                line.startsWith(
                    "CHAMBER PRESS:"
                )
            ) {

                const value =
                    line.substring(
                        "CHAMBER PRESS:".length
                    );


                document.getElementById(
                    "chamber-press"
                ).textContent =
                    value + " hPa";


                return;

            }


            /*
             * -----------------------------------------------------
             * CONTROLLER TEMPERATURE
             *
             * Erwartet:
             *
             * CHAMBER CONTROLER TEMP:38.7
             * -----------------------------------------------------
             */

            if (
                line.startsWith(
                    "CHAMBER CONTROLER TEMP:"
                )
            ) {

                const value =
                    line.substring(
                        "CHAMBER CONTROLER TEMP:".length
                    );


                document.getElementById(
                    "chamber-controller-temp"
                ).textContent =
                    value + " °C";


                return;

            }


            /*
             * -----------------------------------------------------
             * UNBEKANNTE NACHRICHT
             * -----------------------------------------------------
             */

            console.log(
                "Unknown chamber response:",
                line
            );

        }



        /* =========================================================
           STANDARD COMMAND BUTTONS
        ========================================================== */

        const commandButtons =
            document.querySelectorAll(
                ".send-command"
            );


        commandButtons.forEach(
            button => {

                button.addEventListener(
                    "click",
                    async () => {

                        const isConnected =
                            await connectSerial();


                        if (!isConnected) {

                            return;

                        }


                        const command =
                            button.getAttribute(
                                "data-cmd"
                            );


                        try {

                            await writer.write(
                                command + "\n"
                            );


                            document.getElementById(
                                "response"
                            ).innerText =
                                `Status: Sent "${command}"`;


                            document.getElementById(
                                "response"
                            ).style.color =
                                "green";

                        }

                        catch (error) {

                            document.getElementById(
                                "response"
                            ).innerText =
                                "Transmission Error: "
                                + error.message;


                            document.getElementById(
                                "response"
                            ).style.color =
                                "red";

                        }

                    }
                );

            }
        );



        /* =========================================================
           FAN COMMAND BUTTONS
        ========================================================== */

        const fanButtons =
            document.querySelectorAll(
                ".fan-command"
            );


        fanButtons.forEach(
            button => {

                button.addEventListener(
                    "click",
                    async () => {

                        const isConnected =
                            await connectSerial();


                        if (!isConnected) {

                            return;

                        }


                        const baseCmd =
                            button.getAttribute(
                                "data-base-cmd"
                            );


                        const fanNumber =
                            document.getElementById(
                                "fan-select"
                            ).value;


                        const finalCommand =
                            baseCmd + fanNumber;


                        try {

                            await writer.write(
                                finalCommand + "\n"
                            );


                            document.getElementById(
                                "response"
                            ).innerText =
                                `Status: Sent "${finalCommand}"`;


                            document.getElementById(
                                "response"
                            ).style.color =
                                "green";

                        }

                        catch (error) {

                            document.getElementById(
                                "response"
                            ).innerText =
                                "Transmission Error: "
                                + error.message;


                            document.getElementById(
                                "response"
                            ).style.color =
                                "red";

                        }

                    }
                );

            }
        );


    </script>


</body>
</html>

)GUICHAMBER";

const char PAGE_TEXT_EDITOR[] PROGMEM = R"GUITEXTEDIT(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="Author" content="Robotics Union Software ©">
    <title>Robotics Union Control Software (based on HTML5)</title>
    
    <!-- Styling preset-->
    <link rel="stylesheet" href="style.css">
    <script src="/serial_bridge.js"></script>
</head>

<body>

    <div class="button-row">

        <a href="text-editor.html" class="main-options">
            Text-Editor
        </a>

        <a href="controls.html" class="main-options">
            Controls
        </a>

        <a href="settings.html" class="main-options">
            Settings
        </a>

        <a href="rsd.html" class="main-options">
            RSD
        </a>

        <a href="chamber.html" class="main-options">
            Chamber
        </a>

        <a href="Main_page.html" class="main-options">
            Main Page
        </a>

    </div>


    <h2 class="undertitle_text">
        G-Code Editor
    </h2>


    <!-- =====================================================
         G-CODE EDITOR
    ====================================================== -->

    <textarea
        id="gcode-input"
        rows="20"
        style="
            width: 100%;
            font-family: 'Courier New', Courier, monospace;
            font-size: 14px;
            padding: 10px;
            box-sizing: border-box;
            resize: vertical;
            border: 2px solid #111111;
            border-radius: 5px;
        "
    ></textarea>


    <!-- =====================================================
         SEND BUTTON
    ====================================================== -->

    <button
        id="send-gcode"
        class="main-options"
        style="margin-top: 15px; width: auto; padding: 0 20px;"
    >
        Send G-Code
    </button>


    <!-- =====================================================
         SAVE BUTTON
    ====================================================== -->

    <button
        id="save-gcode"
        class="main-options"
        style="margin-top: 15px; width: auto; padding: 0 20px;"
    >
        Save G-Code
    </button>


    <button
        id="save-gcode->PC"
        class="main-options"
        style="margin-top: 15px; width: auto; padding: 0 20px;"
    >
        Save G-Code to arm
    </button>


    <!-- =====================================================
         FILE NAME
    ====================================================== -->

    <input
        type="text"
        id="gcode-name"
        size="10"
        placeholder="G-Code Name"
        style="
            height: 40px;
            margin-top: 15px;
            padding: 0 10px;
            border: 2px solid #111111;
            border-radius: 4px;
            font-size: 14px;
            box-sizing: border-box;
        "
    >


    <!-- =====================================================
         CLEAR BUTTON
    ====================================================== -->

    <button
        id="clear-gcode"
        class="main-options"
        style="margin-top: 15px; width: auto; padding: 0 20px;"
    >
        Clear G-Code
    </button>


    <!-- =====================================================
         STATUS
    ====================================================== -->

    <p
        id="response"
        class="normal_text"
        style="color: grey; margin-top: 5px;"
    >
        Status: Not Connected
    </p>


    <p
        class="normal_text"
        style="color: grey; margin-top: 5px;"
    >
        Note: Please code in DialogiXMove there is no check for correct writing.©
    </p>



     <!-- =====================================================
         JAVASCRIPT
    ====================================================== -->

    <script>

        let port;
        let writer;
        let textEncoder;


        /* =====================================================
           HILFSFUNKTION: PORT ÖFFNEN
        ====================================================== */
        async function stelleVerbindungHer(status) {
            if (!port) {
                status.innerText = "Status: Warte auf Port-Auswahl...";
                status.style.color = "orange";

                port = await navigator.serial.requestPort();
                await port.open({ baudRate: 115200 });
                
                // Direkter und stabiler Aufbau des Writers ohne Streams-Pipe
                textEncoder = new TextEncoder();
                writer = port.writable.getWriter();
            }
        }


        /* =====================================================
           SEND G-CODE
        ====================================================== */

        document
            .getElementById('send-gcode')
            .addEventListener('click', async () => {

                const status =
                    document.getElementById('response');

                const gcodeText =
                    document.getElementById('gcode-input').value;


                try {

                    // Nutzt die zentrale Verbindungsfunktion
                    await stelleVerbindungHer(status);


                    status.innerText =
                        "Status: Sende G-Code...";

                    status.style.color =
                        "orange";


                    // Text in Byte-Array umwandeln und senden
                    const daten = textEncoder.encode(gcodeText + "\n");
                    await writer.write(daten);


                    status.innerText =
                        "Status: G-Code erfolgreich gesendet!";

                    status.style.color =
                        "green";

                }


                catch (error) {

                    status.innerText =
                        "Status Fehler: "
                        + error.message;

                    status.style.color =
                        "red";

                }

            });



        /* =====================================================
           SAVE G-CODE (Lokal auf PC herunterladen)
        ====================================================== */

        document
            .getElementById('save-gcode')
            .addEventListener('click', () => {

                const gcodeText =
                    document.getElementById('gcode-input').value;


                const fileNameInput =
                    document.getElementById('gcode-name');


                let fileName =
                    fileNameInput.value.trim();


                /* ---------------------------------------------
                   Prüfen ob ein Dateiname vorhanden ist
                --------------------------------------------- */

                if (fileName === "") {

                    fileName = "G-Code";

                }


                /* ---------------------------------------------
                   .gcode automatisch hinzufügen
                --------------------------------------------- */

                if (
                    !fileName.toLowerCase().endsWith(".gcode")
                ) {

                    fileName += ".gcode";

                }


                /* ---------------------------------------------
                   Datei erstellen
                --------------------------------------------- */

                const blob =
                    new Blob(
                        [gcodeText],
                        {
                            type: "text/plain"
                        }
                    );


                const downloadURL =
                    URL.createObjectURL(blob);


                /* ---------------------------------------------
                   Download-Link erstellen
                --------------------------------------------- */

                const downloadLink =
                    document.createElement("a");


                downloadLink.href =
                    downloadURL;


                downloadLink.download =
                    fileName;


                document.body.appendChild(
                    downloadLink
                );


                downloadLink.click();


                document.body.removeChild(
                    downloadLink
                );


                URL.revokeObjectURL(
                    downloadURL
                );


                /* ---------------------------------------------
                   Status aktualisieren
                --------------------------------------------- */

                const status =
                    document.getElementById('response');


                status.innerText =
                    'Status: "' + fileName + '" gespeichert.';


                status.style.color =
                    "green";

            });



        /* =====================================================
           SAVE G-CODE -> PC / ARM (Über USB Senden)
        ====================================================== */

        document
            .getElementById('save-gcode->PC')
            .addEventListener('click', async () => {

                const status =
                    document.getElementById('response');

                const fileNameInput =
                    document.getElementById('gcode-name');

                let fileName =
                    fileNameInput.value.trim();


                if (fileName === "") {

                    fileName = "G-Code";

                }


                // Der Befehl: SAVE "NAME" mit Zeilenumbruch
                const befehl = 'SAVE "' + fileName + '"\n';


                try {

                    // Nutzt die zentrale Verbindungsfunktion
                    await stelleVerbindungHer(status);


                    status.innerText =
                        "Status: Sende Speicherbefehl...";

                    status.style.color =
                        "orange";


                    // Text in Byte-Array umwandeln und senden
                    const daten = textEncoder.encode(befehl);
                    await writer.write(daten);


                    status.innerText =
                        'Status: Befehl erfolgreich gesendet: ' + befehl.trim();

                    status.style.color =
                        "green";

                }


                catch (error) {

                    status.innerText =
                        "Status Fehler: "
                        + error.message;

                    status.style.color =
                        "red";

                }

            });



        /* =====================================================
           CLEAR G-CODE
        ====================================================== */

        document
            .getElementById('clear-gcode')
            .addEventListener('click', () => {

                const gcodeInput =
                    document.getElementById('gcode-input');


                gcodeInput.value =
                    "";


                const status =
                    document.getElementById('response');


                status.innerText =
                    "Status: G-Code Editor geleert.";


                status.style.color =
                    "grey";

            });

    </script>



</body>
</html>

)GUITEXTEDIT";

const char PAGE_CSS[] PROGMEM = R"GUICSS(/* --- BASIS LAYOUT --- */
body {
    border: 2px solid #111111;
    border-radius: 6px;
    padding: 35px;
    margin: 20px;
    background-color: #fafafa;
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    color: #1e1e1e;
}

/* --- NAVIGATION & BUTTONS --- */
.button-row {
    display: flex;
    justify-content: flex-start; 
    gap: 15px;                   
    margin-bottom: 40px;
    align-items: center;
    flex-wrap: wrap; /* Verhindert das Herausragen auf kleineren Bildschirmen */
}         

.main-options {
    height: 40px;                
    min-width: 140px; /* Nutzt eine stabile Mindestbreite statt starrer % */
    padding: 0 20px;
    color: #ffffff;
    background-color: #4a4a4a; /* Etwas weicheres, moderneres Dunkelgrau */
    border: 2px solid #111111;
    border-radius: 4px;
    cursor: pointer;
    font-weight: 600;
    text-align: center;
    
    display: inline-flex;
    align-items: center;
    justify-content: center;
    text-decoration: none; 
    box-sizing: border-box;
    transition: background-color 0.2s ease, color 0.2s ease;
}

.main-options:hover {
    background-color: #222222;
    color: #ffffff;
}

/* --- TEXTE & TITEL --- */
.titels {
    font-size: 28px;
    font-weight: bold;
    margin-bottom: 20px;
    text-align: center;
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; /* Einheitliche Schriftart */
    letter-spacing: 0.5px;
}

.under_main_titels {
    font-size: 18px;
    color: #555555;
    margin-bottom: 15px;
    text-align: center;
}

.undertitle_text {
    font-size: 18px;
    font-weight: 600;
    margin-top: 30px;
    margin-bottom: 10px;
    text-align: left;
}

.normal_text {
    font-size: 15px;
    color: #333333;
    margin-bottom: 12px;
    text-align: left;
    line-height: 1.6;
}

/* --- COMMAND / BEFEHLS BUTTONS --- */
.cmd-btn_send-command {
    height: 40px; /* Auf Standardhöhe mit .main-options gebracht für Symmetrie */               
    min-width: 160px;                  
    padding: 0 25px;
    color: #ffffff;
    background-color: #2b2b2b;
    border: 2px solid #111111;
    border-radius: 4px;
    cursor: pointer;
    font-weight: bold;
    text-align: center;
    
    display: inline-flex;
    align-items: center;
    justify-content: center;
    text-decoration: none; 
    box-sizing: border-box; 
    transition: background-color 0.2s ease;
}

.cmd-btn_send-command:hover {
    background-color: #555555;
}

/* --- TABELLEN --- */
.roadmap-table {
    width: 100%; 
    border-collapse: collapse; 
    border: 2px solid #111111;
    margin-top: 15px;
    margin-bottom: 20px;
    background-color: #ffffff;
}

.roadmap-table th, .roadmap-table td {
    border: 1px solid #cccccc; /* Dünnere Innenlinien für einen cleanen Look */
    padding: 12px 16px;
    text-align: left;
}

.roadmap-table th {
    background-color: #4a4a4a;
    color: white;
    font-weight: 600;
    border-bottom: 2px solid #111111;
}

.roadmap-table tr:nth-child(even) {
    background-color: #f8f9fa; /* Moderneres, leichteres Grau */
}

/* --- LAYOUTS & GRIDS (JOGGING & ACHSEN) --- */
.control-group {
    margin-bottom: 20px;
}

.jogging-grid {
    display: grid;
    grid-template-columns: repeat(2, max-content); 
    gap: 15px 30px; 
    margin-bottom: 40px;
}

.jogging-grid .main-options {
    width: auto;          
    padding: 0 25px;      
    white-space: nowrap;  
}

/* --- NEU: ERGÄNZUNG FÜR DAS RSD (SENSOR) GRID --- */
.control-panel {
    display: flex;
    align-items: center;
    gap: 15px;
    margin-bottom: 35px;
    background: #f0f0f0;
    padding: 15px 20px;
    border: 2px solid #111111;
    border-radius: 4px;
}

.axis-grid {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
    gap: 20px;
}

.axis-card {
    border: 2px solid #111111;
    border-radius: 4px;
    padding: 20px;
    background: #ffffff;
}

.axis-card h3 {
    margin-top: 0;
    font-size: 18px;
    border-bottom: 2px solid #111111;
    padding-bottom: 6px;
    margin-bottom: 15px;
}

.data-field {
    margin: 8px 0;
    font-size: 14px;
    font-family: 'Consolas', 'Courier New', monospace; /* Professioneller für Sensordaten */
    color: #444444;
}

.data-field span {
    font-weight: 600;
    color: #111111;
}

select.main-options {
    width: auto;
    padding: 0 10px;
    background-color: #ffffff;
    color: #111111;
}

/* =========================================================
   DARK THEME
========================================================= */

body.dark-theme {
    background-color: #1b1b1b;
    color: #eeeeee;
}

body.dark-theme .normal_text {
    color: #eeeeee;
}

body.dark-theme .undertitle_text {
    color: #ffffff;
}

body.dark-theme .settings-section {
    background-color: #242424;
}

body.dark-theme .settings-table {
    color: #eeeeee;
}

body.dark-theme .settings-table th {
    background-color: #333333;
}

body.dark-theme .settings-table td {
    border-color: #444444;
}

body.dark-theme .settings-input,
body.dark-theme .settings-select {
    background-color: #333333;
    color: #ffffff;
    border-color: #555555;
}


/* ========================================================= BASIS LAYOUT ========================================================= */ body { border: 2px solid #111111; border-radius: 6px; padding: 35px; margin: 20px; background-color: #fafafa; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; color: #1e1e1e; } /* ========================================================= NAVIGATION & BUTTONS ========================================================= */ .button-row { display: flex; justify-content: flex-start; gap: 15px; margin-bottom: 40px; align-items: center; flex-wrap: wrap; } .main-options { height: 40px; min-width: 140px; padding: 0 20px; color: #ffffff; background-color: #4a4a4a; border: 2px solid #111111; border-radius: 4px; cursor: pointer; font-weight: 600; text-align: center; display: inline-flex; align-items: center; justify-content: center; text-decoration: none; box-sizing: border-box; transition: background-color 0.2s ease, color 0.2s ease; } .main-options:hover { background-color: #222222; color: #ffffff; } /* ========================================================= TEXTE & TITEL ========================================================= */ .titels { font-size: 28px; font-weight: bold; margin-bottom: 20px; text-align: center; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; letter-spacing: 0.5px; } .under_main_titels { font-size: 18px; color: #555555; margin-bottom: 15px; text-align: center; } .undertitle_text { font-size: 18px; font-weight: 600; margin-top: 30px; margin-bottom: 10px; text-align: left; } .normal_text { font-size: 15px; color: #333333; margin-bottom: 12px; text-align: left; line-height: 1.6; } /* ========================================================= SETTINGS ========================================================= */ .settings-section { margin-bottom: 35px; } .settings-table { width: 100%; border-collapse: collapse; border: 2px solid #111111; margin-top: 15px; margin-bottom: 20px; background-color: #ffffff; } .settings-table th, .settings-table td { border: 1px solid #cccccc; padding: 12px 16px; text-align: left; vertical-align: middle; } .settings-table th { background-color: #4a4a4a; color: #ffffff; font-weight: 600; border-bottom: 2px solid #111111; } .settings-table tr:nth-child(even) { background-color: #f8f9fa; } /* ========================================================= SETTINGS INPUTS ========================================================= */ .settings-input, .settings-select { height: 40px; min-width: 220px; padding: 0 10px; background-color: #ffffff; color: #111111; border: 2px solid #111111; border-radius: 4px; font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; font-size: 15px; box-sizing: border-box; } .settings-input:focus, .settings-select:focus { outline: none; border-color: #4a4a4a; } /* ========================================================= SETTINGS BUTTON ========================================================= */ .settings-save { height: 40px; min-width: 180px; padding: 0 20px; color: #ffffff; background-color: #2b2b2b; border: 2px solid #111111; border-radius: 4px; cursor: pointer; font-weight: bold; font-size: 15px; display: inline-flex; align-items: center; justify-content: center; transition: background-color 0.2s ease; } .settings-save:hover { background-color: #555555; } /* ========================================================= STATUS ========================================================= */ .settings-status { margin-top: 15px; padding: 10px 15px; border: 2px solid #111111; border-radius: 4px; background-color: #f0f0f0; font-size: 15px; display: none; } .settings-status.visible { display: block; } /* ========================================================= RESPONSIVE ========================================================= */ @media (max-width: 700px) { body { padding: 20px; margin: 10px; } .settings-table { display: block; overflow-x: auto; } .settings-input, .settings-select { min-width: 180px; } })GUICSS";
