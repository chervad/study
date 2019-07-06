@rem call ..\..\setvars.cmd
@rem call D:\work\EWDK\SetupBuildEnv.cmd

set APP_ROOT=%CD%
set BUILD_PATH=%APP_ROOT%\_build
set SRC_PATH=%APP_ROOT%\TankStrike

@rem set BUILD_TYPE=Release
@rem set BUILD_TYPE=Debug

rmdir %BUILD_PATH% /q /s
mkdir %BUILD_PATH%
cd %BUILD_PATH%
cmake -G "Visual Studio 15 2017" -DUSE_COCOS_PREBUILT=TRUE %SRC_PATH% -Tv141
@rem cmake -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Debug ..\TankStrike
@rem msbuild TankStrike.sln /p:Configuration=%BUILD_TYPE%
@rem cmake --build . --target TankStrike --config %BUILD_TYPE%