@rem call ..\..\setvars.cmd
@rem call D:\work\EWDK\SetupBuildEnv.cmd

@rem https://yadi.sk/d/v9xPRkKC7ZLGTQ

@rem set COCOS2DX_HOME=%COCOS2DX_HOME%
set APP_ROOT=%CD%
set COCOS2DX_HOME=%APP_ROOT%\..\..\cocos2d-x-3.17.2
set BUILD_PATH=%APP_ROOT%\_build
set SRC_PATH=%APP_ROOT%\TankStrike

@rem set BUILD_TYPE=Release
@rem set BUILD_TYPE=Debug

rmdir %BUILD_PATH% /q /s
mkdir %BUILD_PATH%
cd %BUILD_PATH%
cmake -G "Visual Studio 15 2017" %SRC_PATH%
@rem -DUSE_COCOS_PREBUILT=TRUE %SRC_PATH% -Tv141
@rem cmake -G "Visual Studio 15 2017" -DCMAKE_BUILD_TYPE=Debug ..\TankStrike
@rem msbuild TankStrike.sln /p:Configuration=%BUILD_TYPE%
cmake --build . --target TankStrike --config %BUILD_TYPE%