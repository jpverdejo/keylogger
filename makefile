main:
	@gcc -o build/keylogger.exe src/keylogger.c
	@gcc -o build/watchdog.exe src/watchdog.c
	@echo "Compiling finished"

src/keylogger.c:
	@echo "Compiling keylogger"
	@gcc -o build/keylogger.exe src/keylogger.c

src/watchdog.c:
	@echo "Compiling Watchdog"
	@gcc -o build/watchdog.exe src/watchdog.c