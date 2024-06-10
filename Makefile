# Double tap reset to download

all: Feather9x_RX/buildRx/Feather9x_RX.ino.hex Feather9x_TX/buildTx/Feather9x_TX.ino.hex

clean:
	rm -rf Feather9x_RX/buildRx Feather9x_TX/buildTx

veryclean: clean
	rm -rf ~/Arduino  ~/.arduino15 Feather9x_RX/buildRx Feather9x_TX/buildTx

Feather9x_RX/buildRx/Feather9x_RX.ino.hex: $(HOME)/local/bin/arduino-cli
	make -C Feather9x_RX

Feather9x_TX/buildTx/Feather9x_TX.ino.hex: $(HOME)/local/bin/arduino-cli
	make -C Feather9x_TX

$(HOME)/local/bin/arduino-cli: $(HOME)/Arduino/libraries
	mkdir -p ~/local/bin
	curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | BINDIR=~/local/bin sh
	arduino-cli config init
	arduino-cli core update-index --additional-urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
	sed -i -e 's@  additional_urls: \[]@  additional_urls: https://adafruit.github.io/arduino-board-index/package_adafruit_index.json@' ~/.arduino15/arduino-cli.yaml
	arduino-cli core install adafruit:samd


$(HOME)/Arduino/libraries:
	mkdir -p $(HOME)/Arduino/libraries ; cd ~/Arduino/libraries ; curl http://www.airspayce.com/mikem/arduino/RadioHead/RadioHead-1.121.zip --output RadioHead-1.121.zip ; unzip RadioHead-1.121.zip
