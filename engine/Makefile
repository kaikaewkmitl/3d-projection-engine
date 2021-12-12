e1 = cube_no_fill
e2 = cube_fill
e3 = spaceship

mac: mac_cleanup mac_build

bash: mac_cleanup mingw_build

powershell: windows

cmd: windows

windows: windows_cleanup mingw_build
	chcp 65001

mac_cleanup:
	rm -f $(e1) $(e2) $(e3)
	rm -rf build

windows_cleanup:
	del /f $(e1) $(e2) $(e3)

mac_build:
	mkdir build && cd build; \
	cmake .. && cmake --build .; \
	mv $(e1) ..; \
	mv $(e2) ..; \
	mv $(e3) ..; \
	cd ..; \

mingw_build:
	mkdir build && cd build; \
	cmake -G "MinGW Makefiles" .. && cmake --build .; \
	mv $(e1) ..; \
	mv $(e2) ..; \
	mv $(e3) ..; \
	cd ..; \
	