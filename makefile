main: build/keylogger.exe build/watchdog.exe
	@echo "Compiling finished"

build/keylogger.exe: src/keylogger.c src/keylogger.h
	@echo "Compiling keylogger"
	@gcc -o build/keylogger.exe src/keylogger.c

build/watchdog.exe: src/watchdog.c src/watchdog.h
	@echo "Compiling Watchdog"
	@gcc -o build/watchdog.exe src/watchdog.c