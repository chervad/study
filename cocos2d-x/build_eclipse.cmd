set APP_ROOT=%CD%
set BUILD_PATH=%APP_ROOT%\_build
set SRC_PATH=%APP_ROOT%\TankStrike
@rem �������� �������� ������ �� EWDK set BUILD_TYPE=Release
set BUILD_TYPE=Debug

rmdir %BUILD_PATH% /q /s
mkdir %BUILD_PATH%
cd %BUILD_PATH%
cmake -G "Eclipse CDT4 - NMake Makefiles" %SRC_PATH%
@rem cmake --build . --target TankStrike --config %BUILD_TYPE%
pause