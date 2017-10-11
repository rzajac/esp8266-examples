## The ESP8266 Example Programs.

The collection of ESP8266 example programs.

## Build and flash the example.

By default Makefile:
- looks for esp-open-sdk in `$HOME/lib/esp-open-sdk/sdk`
- uses `/dev/ttyUSB0` for USB to serial communication
- assumes `esptool.py` exists in user `$PATH`

## Usage.

Change directory to one of the examples and execute:

```
$ make clean && make && make flash 
```

To see the output:

```
$ miniterm.py /dev/ttyUSB0 74880
```

## License.

[Apache License Version 2.0](LICENSE) unless stated otherwise.