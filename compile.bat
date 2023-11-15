@set OLDPATH=%PATH%
@set VRXSDK=C:\eVoAps\SDK\1.2.0\VvSDK386
@set EVOACT=C:\eVoAps\ACT2000\1.2.0\
@set RVCTDIR=C:\Program Files\ARM\RVCT\Programs\4.0\400\win_32-pentium
@set PATH=%VRXSDK%\bin;%RVCTDIR%;C:\vrxsrc\bin

@del *.so
@del *.axf
@del *.vsl
@del *.vsa
@del *.s
@del *.o
@del *.map
@del *.p7s
@del *.crt

vrxcc -armcc,--c99 -IC:\eVoAps\ACT2000\1.2.0\include -p app.c C:\eVoAps\ACT2000\1.2.0\OutPut\RV\Files\Static\Release\ACT2000.a
vrxhdr -s 1048576 -h 8388608 app.out
pause