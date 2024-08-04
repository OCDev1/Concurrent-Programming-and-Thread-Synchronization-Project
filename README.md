# Concurrent News Broadcasting Simulation

## Project Description

This project is a concurrent programming simulation of a news broadcasting system. The system produces and processes different types of news stories using multiple threads and synchronization mechanisms. The implementation demonstrates the use of unbounded buffers to manage the flow of news stories through various components: Producers, Dispatcher, Co-Editors, and the Screen Manager.

## Features

- **Producers**: Generate news stories of different types (`SPORTS`, `NEWS`, `WEATHER`) and send them to the Dispatcher.
- **Dispatcher**: Receives stories from Producers and dispatches them to the appropriate Co-Editor queues based on their type.
- **Co-Editors**: Process the stories and forward them to the Screen Manager.
- **Screen Manager**: Displays the stories in the order they are received and prints a final `DONE` message when processing is complete.

## Components

1. **Producer**: Generates and sends news stories to the Dispatcher.
2. **Dispatcher**: Distributes news stories to the appropriate Co-Editor.
3. **Co-Editor**: Processes and edits news stories before sending them to the Screen Manager.
4. **Screen Manager**: Displays the final news stories.

## Flow chart
![alt text](https://github.com/OCDev1/Concurrent-Programming-and-Thread-Synchronization-Project/blob/main/flow.png)

## File Structure

- `main.cpp`: Entry point of the application.
- `Producer.h`, `Producer.cpp`: Producer class definition and implementation.
- `Dispatcher.h`, `Dispatcher.cpp`: Dispatcher class definition and implementation.
- `CoEditor.h`, `CoEditor.cpp`: Co-Editor class definition and implementation.
- `ScreenManager.h`, `ScreenManager.cpp`: Screen Manager class definition and implementation.
- `UnboundedBuffer.h`, `UnboundedBuffer.cpp`: Unbounded buffer class definition and implementation.
- `Makefile`: Script to compile and build the project.

## Configuration File

The configuration file specifies the number of products each producer generates and the queue size for each component. Example:

PRODUCER 1
30
queue size = 5

PRODUCER 2
25
queue size = 3

PRODUCER 3
16
queue size = 30

Co-Editor queue size = 17


## How to Build and Run

1. **Clone the repository**:
   ```sh
   git clone https://github.com/your-username/news-broadcasting-simulation.git
   cd news-broadcasting-simulation
2. **Build the project**:
   `make`
3. **Run the executable**:
   `./ex3.out config.txt`

4. **Clean the build**:
   `make clean`

Requirements:
- C++11 or later
- POSIX thread library (pthread)
