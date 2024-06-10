all:
	~/local/bin/arduino-cli compile --build-path buildTx -v -b adafruit:samd:adafruit_feather_m0 Feather9x_TX.ino

clean:
	rm -rf buildTx

Download:
	arduino-cli upload -p /dev/ttyACM0 --fqbn adafruit:samd:adafruit_feather_m0 --input-dir buildTx/
