call ..\..\setvars.cmd
call D:\work\EWDK\SetupBuildEnv.cmd

set APP_ROOT=%CD%
set BUILD_PATH=%APP_ROOT%\_build
set SRC_PATH=%APP_ROOT%\TankStrike
@rem почемуто ломается сборка на EWDK set BUILD_TYPE=Release
set BUILD_TYPE=Debug

rmdir %BUILD_PATH% /q /s
mkdir %BUILD_PATH%
cd %BUILD_PATH%
cmake -G "Visual Studio 15" %SRC_PATH%
cmake --build . --target TankStrike --config %BUILD_TYPE%
pause