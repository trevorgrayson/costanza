# USB driver: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
# https://arduino.github.io/arduino-cli/getting-started/
# SSD1306 code from: https://github.com/ThingPulse/esp8266-oled-ssd1306
PROJECT=phone.bin
BUILD_DIR=build/esp32.esp32.ttgo-t1
BAUD?=115200
PORT?=/dev/cu.SLAB_USBtoUART
ARDUINO_CONF=arduino-cli.yaml
ACLI=arduino-cli
# --config-file $(ARDUINO_CONF)

SRCS=$(wildcard *.c **/*.c)

OBJS=$(SRCS:.c=.o)
	
upload: compile
	$(ACLI) upload -p $(PORT) --fqbn esp32:esp32:ttgo-t1

compile:
	mkdir -p $(BUILD_DIR)
	$(ACLI) compile --output-dir $(BUILD_DIR) --fqbn esp32:esp32:ttgo-t1

setup:
ifeq (,$(wildcard $(HOME)/.arduino15/arduino-cli.yaml))
	$(ACLI) config init
endif
	$(ACLI) core install esp32:esp32
	# $(ACLI) lib install ssd1306

boards:
	$(ACLI) board list

search:
	# $(ACLI) lib install FTDebouncer
	$(ACLI) lib search SSD1306Wire
	# "ESP8266 and ESP32 OLED driver for SSD1306 displays"

monitor:
	@echo "Ctrl a, Ctrl \ to disconnect"
	screen $(PORT) $(BAUD)

render:
	mogrify -resize 28x28 +dither -format xbm images/*.png
	cat images/*.xbm > DinoRun/images.h

test: compile

clean:
	find . -name '*.o' -delete
	find images -name '*.xbm' -delete
