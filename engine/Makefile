e = engine

mac: mac_cleanup mac_build

bash: mac_cleanup mingw_build

powershell: windows

cmd: windows

windows: windows_cleanup mingw_build
	chcp 65001

mac_cleanup:
	rm -f $(e)
	rm -rf build

windows_cleanup:
	del /f $(e)

mac_build:
	mkdir build && cd build; \
	cmake .. && cmake --build .; \
	mv $(e) ..; \
	cd ..; \

mingw_build:
	mkdir build && cd build; \
	cmake -G "MinGW Makefiles" .. && cmake --build .; \
	mv $(e) ..; \
	cd ..; \
	