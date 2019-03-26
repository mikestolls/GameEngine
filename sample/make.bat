@echo OFF

set HOME_DIR=%~dp0
set CONFIGURATION=%1
set OUT_DIR=%HOME_DIR%\_bin\%CONFIGURATION%

if not exist %OUT_DIR% (
    mkdir %OUT_DIR%
)

echo  "%HOME_DIR%..\submodule\assimp\bin\%CONFIGURATION%\assimp-vc140-mt.dll"

xcopy /E /Y /I "%HOME_DIR%..\data" "%OUT_DIR%"
xcopy /E /Y /I "%HOME_DIR%data" "%OUT_DIR%"
copy /Y "%HOME_DIR%..\submodule\assimp\bin\%CONFIGURATION%\assimp-vc140-mt.dll" "%OUT_DIR%"