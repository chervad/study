call D:\work\EWDK\LaunchBuildEnv.cmd

set APP_ROOT=%CD%
set BUILD_PATH=%APP_ROOT%\_build
set SRC_PATH=%APP_ROOT%\TankStrike
set BUILD_TYPE=Debug

cd %BUILD_PATH%
cmake -G "Visual Studio 15" %SRC_PATH%
cmake --build . --target TankStrike --config %BUILD_TYPE%
