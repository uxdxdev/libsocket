# Libsocket

Libsocket is a wrapper library around BSD Sockets allowing simple socket creation, connections, and message passing between peers. 

## Build

```
$ cmake .
$ make
```
## Instructions
- Download the repo
- Extract to your third party library folder
- `cd path/to/libsocket-folder`
- Build
- Link against the `libsocket` dynamic library in the `lib/` folder. 

To use the API don't forget to include the header file `include/socket.h`.

# Use cases

Libsocket is currently being used in the following projects:

- libhangman  https://github.com/damorton/libhangman.git
- ngproject   https://github.com/damorton/ngproject.git
- libraig        https://github.com/damorton/libraig.git
