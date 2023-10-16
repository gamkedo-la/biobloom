setlocal
FOR /F "tokens=*" %%i in ('type .env') do SET %%i
call "%UE51_DIR%\Engine\Build\BatchFiles\Build.bat" BioBloomEditor Win64 Development -Project="%~dp0\BioBloom.uproject" -WaitMutex -FromMsBuild
endlocal