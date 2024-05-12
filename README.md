# Minecraft Random Proxy

## Why & How?

First choose a port to expose the app, e.g `25565`.
Then make a file named `servers.txt` containing different Minecraft servers in this format:

```txt
IPv4:port
IPv4:port
IPv4:port
...
```

(`servers.txt` must be at the same level, or next to the binary.)

When that is ready, run the app, and you are able to connect to it from your Minecraft client.
Let's say you're running it on the same machine as your client: connect to `127.0.0.1:<the_port_you_chose_earlier>`.
At each new connection, you'll connect to a random server on the specified file `servers.txt`.


And for the how, the program uses Asio (a networking library in C++) to route all the incoming packets from you (the client)
to some server chose at random, and forward all packets coming from the random server to the client (you).

This also means that every packet exchanged can be read and also modified by the program, although currently that is not
the case.

## Installation

### Linux 🐧

There is a prebuilt binary for x64 systems.

As for other architectures, you must build it yourself.

### Windows 🪟

There is a prebuilt binary for x64 systems.

Please to have Microsoft Visual C++ Redistributable (vcredist)

Useful links:

- [Download](https://aka.ms/vs/17/release/vc_redist.x86.exe)

- [Download Page](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170#visual-studio-2015-2017-2019-and-2022)

### MacOS 🍎

There is **no** prebuilt binary yet. You must build it yourself.

### Docker 🐳

*Yet to be done.*