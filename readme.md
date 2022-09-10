# Intro
  The DBCProcessor is a library that implements a generic CAN parser, that is configured by the DBC file.
  The library works in two flavors:
  - event dispatcher - it dispatches the events to the subscribed listeners. It's possible to subscribe the CAN Message IDs and the PGNs
                        The event notification delivered fully deserialized logical content + all of the additional properties that are specified in the DBC.
                        It's possible to subscribe the notifications for CAN Messages as well as single CAN Message signals (using the DBC nomenclacture)
  - message processor - which returns a fully deserialized content that was extracted from the CAN message (msgId + data)

  Both event dispatcher and the message processor API can work with can message IDs as well as the PGNs.
# Requirements
  Needed:
  - C++ 14
  - CMAKE
  - GMOCK+GTEST

# How To
## Prepare the workspace
  Use ubuntu 22.04

  ```
  $ sudo apt install -y git cmake build-essential libgmock-dev
  ```

## Build the library in the development environment
  In the root of the DBCProcessor project:
  ```
  $ mkdir build
  $ cd build
  $ cmake ..
  $ make
  ```
  and invoke the unit tests:
  ```
  $ ./test/dbcProcessorTests
  ```
