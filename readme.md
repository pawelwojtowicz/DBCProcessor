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

  # Reference

  - Initalization of the DBC

  - Cascade DBC Loading
    The engine can be initialized by more than one dbc file. If the intialization procedure is executed with a list of the DBC files, the internal model of the parser will be built as an union of models stored in all of the files on the list. The files are processed in a FIFO way (we start with the first element in the vector and progress to the end).
      The unionizing process follows couple of simple rules, that providing reasonable control over the process.
      * if CAN Message ID can be found in the model and the name of the message matches to the message name, that is being introduced on the lower level - the messsage existing in the model will be enriched with the message, that is incomming from the parser.
      * if CAN Message ID can be found in the model but the name of the message does not match to the parsed message record - the message, all of its signals and properties of the message and it's signals will be removed. New record will start from scratch.

  - Processing CAN messages

  - Dispatching CAN Events



  # Todo

  - cascade dbc loading ( loading multiple dbc files into the processor - with overwriting the properties )
  - Detailed DBC Processor Logging - provide detailed logging of the processing
  - DBC validation - procedure, that checks the correctness of the  DBC model loaded from the file
    1. is there single multiplexing ID in multiplexed messages
    2. does each message have a message processor
    3. does the signal fit into the message sizes
  - Optimize the processing for littleEndian/bigEndian ( throw out the byte shitfting from signal)
  - review/reconsider the internal structure of the implementation 

