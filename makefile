main: build/keylogger.exe build/watchdog.exe
	@echo "Starting compile"

build/keylogger.exe:
	@echo "Compiling keylogger"
	@gcc -o build/keylogger.exe src/keylogger.c

build/watchdog.exe:
	@echo "Compiling Watchdog"
	@gcc -o build/watchdog.exe src/watchdog.c