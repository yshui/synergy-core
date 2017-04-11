@echo off

if exist C:\Python27\python.exe (
	C:\Python27\python.exe hm.py %*
	
) else if exist C:\Python35\python.exe (
	C:\Python35\python.exe hm.py %*
) else (
	python hm.py %*
)

exit /b %errorlevel%