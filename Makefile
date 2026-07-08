# === Config ===

# Board / port
FQBN=esp32-bluepad32:esp32:lolin_c3_mini
PORT = COM10
BAUD = 115200

# Arduino CLI
ARDUINO_CLI = arduino-cli

# === Sketch paths ===
SKETCH = k-is-for-keyboard.ino

# === Commands ===
.PHONY: all keyboard build-keyboard upload-keyboard serial clean info 

keyboard: build-keyboard upload-keyboard monitor

# --- Build targets ---
build-keyboard:
	$(ARDUINO_CLI) compile --fqbn $(FQBN) --libraries lib $(SKETCH)

# --- Upload targets ---
upload-keyboard:
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(FQBN) $(SKETCH)


# --- Monitor serial ---
monitor:
	$(ARDUINO_CLI) monitor -p $(PORT) --fqbn $(FQBN) --config baudrate=$(BAUD)
# --- Cleanup ---
clean:
	rm -rf build .arduino*

# --- Board info ---
info:
	$(ARDUINO_CLI) board list

