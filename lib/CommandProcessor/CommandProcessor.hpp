#pragma once

// Hier soll irgendwie SCPI ähnliches implementiert werden also ein parser
// eine Ideee wäre ein string cmd mit einer methode zu verheiraten. Allerdings weiß ich nicht ob das überhaupt möglich ist :( da das ding ja extrem wiedervewendbar sein soll.
//  #include <ArduinoSTL.h>

#include <map>
#include <vector>
#include <string>
//ToDo: prototype need some improvements and putting in a class
//  using void(*CommandHandler)(conststd::vector<string>&);
using CommandHandler = void (*)(const std::vector<std::string> &);
std::map<std::string, CommandHandler> commandMap;

void registerCommand(const std::string &cmd, CommandHandler handler)
{
    commandMap[cmd] = handler;
}

void registerCommand(const std::string &input)
{
    std::vector<std::string> parts;
    int start = 0;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == ' ')
        {
            parts.push_back(input.substr(start, i));
            start = i+1;
        }
    }
    parts.push_back(input.substr(start));
    if(!parts.empty()){
        std::string cmd = parts[0];
        parts.erase(parts.begin());// Entferne Befehl aus den Parametern
        
        if(commandMap.find(cmd)!=commandMap.end()){
            commandMap[cmd](parts);//Rufe Callback mit Parametern auf
        }
    }

}

//Example:
#if defined(ARDUINO)
#include <Arduino.h>

void handleLED(const std::vector<std::string>& params){
    if(params.size() >= 1){
        int state = std::stoi(params[0]);//ist nicht schöhn da hier exceptions geworfen werden können wens nicht klapt und atoi() ist auch nicht gut da es eine 0 zurück gibt wenn es nicht geklapt hat :(
        digitalWrite(LED_BUILTIN, state);
    }
}

// void setup() {
//     Serial.begin(9600);
//     pinMode(LED_BUILTIN, OUTPUT);
    
//     // Befehle registrieren
//     registerCommand("led", handleLED);
//     // Füge hier weitere Befehle hinzu
//   }
  
//   void loop() {
//     if (Serial.available()) {
//       String input = Serial.readStringUntil('\n');
//       input.trim();
//       parseCommand(input);
//     }
//   }

//verwendung:
// led 1  // LED einschalten
// led 0  // LED ausschalten
#endif