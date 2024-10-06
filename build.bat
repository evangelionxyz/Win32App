@echo off
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"

rem
if %errorlevel% NEQ 0 (
    powershell -Command "Start-Process -Filepath '%0' -Verb RunAs"
    exit /b
)

rem
pushd %~dp0\Scripts
call .\premake\premake5 vs2022
pause