@echo off

set QT_DIR=C:\Qt\6.11.2\msvc2022_64
set PG_DIR=C:\Program Files\PostgreSQL\18\bin
set OUT=%~dp0..\cmake-build-debug
set EXE=%OUT%\PhoneStoreManagement.exe

echo === Deploy Qt ===
"%QT_DIR%\bin\windeployqt.exe" "%EXE%"

echo === Deploy PostgreSQL ===
copy "%PG_DIR%\*.dll" "%OUT%\" /Y

echo === Deploy QPSQL ===
if not exist "%OUT%\sqldrivers" mkdir "%OUT%\sqldrivers"
copy "%QT_DIR%\plugins\sqldrivers\qsqlpsql.dll" "%OUT%\sqldrivers\" /Y

echo.
echo === DONE ===
pause