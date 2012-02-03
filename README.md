# ZNC OfflineMarker

A (very) simple module, which when loaded will insert a "-- MARK --" line
in all channel-logs when a client disconnects.

## Compiling and installing

Run the following on the box where ZNC is installed:

	$ znc-build offlinemarker.cpp
	$ cp offlinemarker.so ~/.zsh/modules/

Run the following from within your IRC program, which should be
connected to ZNC:

	/msg *status loadmod offlinemarker

That's it.

## Bugs/TODO

* Configurable mark-message
* Don't log until all clients have disconnected

## License

This project is licensed under the MIT license.
