# Libsocket

Libsocket is a wrapper library around BSD Sockets allowing simple socket creation, connections, and message passing between peers. 

## Build Instructions Linux
- Download the repo
- Extract to your third party library folder `\external\`
- `cd external\libsocket-master`
- Run ``build-linux.sh`

Libraries built into `lib\` directory

## Build Instructions Win32
- Download the repo
- Extract to your third party library folder `\external\`
- `cd external\libsocket-master`
- Run ``build-win32.sh`
- Open `libsocket.sln` in Visual Studio
- Build solution

Libraries built into `lib\` directory. The same process applies for other versions of Windows, use the appropriate build script to create the VS files. Run `clean.sh` before each new build.

## Build Instructions Android
- Download the repo
- Extract to your third party library folder `\external\`
- Update your projects `Android.mk` file to include the `socket.c`
- Build using `NDK`

There are pre-built libraries in the `libs\android` directory

## Dependencies

- CMake   https://cmake.org/