:: first argument:  absolute path to the directory that contains the avrdude folder
:: second argument: absolute path to the project directory
:: third argument:  name of the target (HEX-file, extension excluded)

@echo off
echo ---------------------------------------------------------------------------
echo ---------------------------------------------------------------------------
echo Sensors and Microsystem Electronics
echo Practical assignment: microcontroller design
echo ---------------------------------------------------------------------------
echo ---------------------------------------------------------------------------
echo.
echo This script uploads a program to the microcontroller board.
echo Make sure the microcontroller board is connected to this computer !!!
echo ---------------------------------------------------------------------------

echo Solution directory: "%~1"
echo Project directory:  "%~2"
echo Target name:        "%~3.hex"

:: Get the COM port number.
for /f "usebackq" %%B in (`wmic path Win32_SerialPort Where "Caption LIKE '%%Genuino%%'" Get DeviceID ^| FINDSTR "COM"`) do set comport=%%B
if [%comport%] == [] (
	for /f "usebackq" %%B in (`wmic path Win32_SerialPort Where "Caption LIKE '%%Serial%%'" Get DeviceID ^| FINDSTR "COM"`) do set comport=%%B
)
echo COM port number:    %comport%
echo.

:: Set the first argument (typically the solution directory) as working directory.
set SolDir=%1
%SolDir:~1,2%
cd %1

:: Copy the content of TestPeripherals.hex to the Genuino Uno's program memory.
avrdude\avrdude -C "avrdude\avrdude.conf" -p atmega328p -c arduino -P %comport% -b 115200 -U flash:w:"%~2Debug\%~3.hex":i

:: Wait for a keystroke before terminating this script.
pause

:: Troubleshooting
:: 1) Open the device manager and verify that the Genuino Uno is recognized under the same name. If this is not the case, you can modify its name on rule 22.
:: 2) An alternative for FINDSTR COM is FIND "COM", but this command might be deprecated.