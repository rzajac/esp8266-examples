## The ESP8266 Example Programs.

The collection of ESP8266 example programs.

## Build and flash the example.

By default Makefile:
- looks for esp-open-sdk in `$HOME/lib/esp-open-sdk/sdk`
- uses `/dev/ttyUSB0` for USB to serial communication
- assumes `esptool.py` exists in user `$PATH`

```
$ make
$ make flash
```
## Usage.

See example [main.c](../example/main.c).

## License.

[Apache License Version 2.0](LICENSE) unless stated otherwise.