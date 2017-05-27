@echo off
SETLOCAL

mkdir %~dp0\exampleBuildLogs 2> NUL
del %~dp0\exampleBuildLogs\*.log

set boards=engimusing_efm32zgusb ^
engimusing_efm32zg108 ^
engimusing_efm32zg222 ^
engimusing_efm32tg110 ^
engimusing_efm32tg222 ^
engimusing_efm32g232 ^
engimusing_efm32wg840 ^
engimusing_efm32wg842


pushd %~dp0
for %%a in (%boards%) do (
    for /R %%f in (*.ino) do (
        Call :BuildExample %%f %%a
    )
    del C:\Users\Tim\AppData\Local\Temp\buildAllExampels\* /S /q > NUL
)
popd

pause
Exit /B 0


:BuildExample 

pushd D:\emus2016\Arduino1-6-9

echo Building Example %~n1 for %~2

mkdir %LOCALAPPDATA%\Temp\buildAllExampels 2> NUL

arduino-builder ^
-dump-prefs ^
-logger=machine ^
-hardware "D:\emus2016\Arduino1-6-9\hardware" ^
-hardware "C:\Users\Tim\AppData\Local\Arduino15\packages" ^
-tools "D:\emus2016\Arduino1-6-9\tools-builder" ^
-tools "D:\emus2016\Arduino1-6-9\hardware\tools\avr" ^
-tools "C:\Users\Tim\AppData\Local\Arduino15\packages" ^
-built-in-libraries "D:\emus2016\Arduino1-6-9\libraries" ^
-libraries "C:\Users\Tim\Documents\Arduino\libraries" ^
-fqbn=engimusing:efm32:%~2 ^
-ide-version=10609 ^
-build-path "C:\Users\Tim\AppData\Local\Temp\buildAllExampels" ^
-warnings=none ^
-prefs=build.warn_data_percentage=75 "%~1" 2>&1 > NUL 

arduino-builder ^
-compile -logger=machine ^
-hardware "D:\emus2016\Arduino1-6-9\hardware" ^
-hardware "C:\Users\Tim\AppData\Local\Arduino15\packages" ^
-tools "D:\emus2016\Arduino1-6-9\tools-builder" ^
-tools "D:\emus2016\Arduino1-6-9\hardware\tools\avr" ^
-tools "C:\Users\Tim\AppData\Local\Arduino15\packages" ^
-built-in-libraries "D:\emus2016\Arduino1-6-9\libraries" ^
-libraries "C:\Users\Tim\Documents\Arduino\libraries" ^
-fqbn=engimusing:efm32:%~2 ^
-ide-version=10609 ^
-build-path "C:\Users\Tim\AppData\Local\Temp\buildAllExampels" ^
-warnings=none ^
-prefs=build.warn_data_percentage=75 "%~1" 2>&1 > NUL | findstr /i "error" >  %~dp0\exampleBuildLogs\temp.log 
findstr /i /v "Incorrect Board" %~dp0\exampleBuildLogs\temp.log >  %~dp0\exampleBuildLogs\temp_2.log

Call :CheckFile %~dp0\exampleBuildLogs\temp_2.log %~1 %~2

popd

EXIT /B 0

:CheckFile
if %~z1 GTR 0 (
    echo %~n2 for board %~3 failed
    copy %~1 %~d1%~p1\%~n2-%~3.log
)

Exit /B 0