BOARD_TAG	= uno
MONITOR_PORT	= /dev/arduino-telnet-0
UPLOAD_PORT	= /dev/arduino-telnet-0
ARDUINO_DIR	= $(realpath ../../arduino-1.8.9/)
RESET_CMD	= systemctl stop serial-getty-arduino.service #&& $(ARDMK_DIR)/bin/ard-reset-arduino --verbose --caterina /dev/arduino-telnet-0

include ../../Arduino.mk



install: upload2
	@echo "Installing udev rules for a fixed /dev/arduino-telnet-0 device"
	cp udev-rules-fixed-arduino-telnet-device/90-arduino-uno.rules /etc/udev/rules.d/
	udevadm control --reload-rules && udevadm trigger
	@echo "Installing systemd service to handle a shell login for our arduino serial<>telnet bridge"
	systemctl stop serial-getty-arduino.service || true
	cp systemd-shell-arduino-serial-over-lan/serial-getty-arduino.service /etc/systemd/system
	systemctl daemon-reload
	systemctl enable serial-getty-arduino.service
	systemctl start serial-getty-arduino.service

upload2: upload
	systemctl start serial-getty-arduino.service

