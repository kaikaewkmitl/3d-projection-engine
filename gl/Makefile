g++14 = g++ -std=c++14
e1 = example1
e2 = example2

powershell: windows

cmd: windows

windows: windows_cleanup build windows_rm
	chcp 65001

windows_cleanup:
	del /f $(e1) $(e2)

windows_rm:
	del $(e1).o $(e2).o gl.o

bash: mac
	export SH=bash

mac: mac_cleanup build mac_rm

mac_cleanup:
	rm -f $(e1) $(e2)

mac_rm:
	rm $(e1).o $(e2).o gl.o

build: gl $(e1) $(e2)

gl:
	$(g++14) -c gl.cpp -o gl.o

$(e1):
	$(g++14) -c $(e1).cpp -o $(e1).o
	$(g++14) -o $(e1) gl.o $(e1).o

$(e2):
	$(g++14) -c $(e2).cpp -o $(e2).o
	$(g++14) -o $(e2) gl.o $(e2).o
	