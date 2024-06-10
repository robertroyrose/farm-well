
FQBN=adafruit:samd:adafruit_feather_m0 
BUILD=buildRx

all:
	~/local/bin/arduino-cli compile --build-path $(BUILD) -v -b $(FQBN) Feather9x_RX.ino

clean:
	rm -rf $(BUILD)

Download:
	arduino-cli upload -p /dev/ttyACM0 --fqbn $(FQBN) --input-dir $(BUILD)
