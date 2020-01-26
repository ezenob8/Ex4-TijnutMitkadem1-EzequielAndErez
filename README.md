# Ex4-TijnutMitkadem1-EzequielAndErez
This is the Homework 4 which is a project that we, Ezequiel Glocer and Erez Rizegvsky, did together in C++, in which consisted in an implementation of a number of searching algorithms, comparing between them for knowing the most efficient, and choosing the winner for solving the problem as a server. In the project we worked with sockets, threads, design patterns and other features.
## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

[FlightGear](https://www.flightgear.org/download/) (Flight Simulator): Version 2019.1.1

Versions c++14 and below are allowed for the project

### Installing

#### Step 1:
As we see in the prerequisites, first of all we need to download the Flight Gear in our computer. For doing that, we will go to the page of the Flight Gear, which is: https://www.flightgear.org/download/main-program/ . There, we choose the appropriate download for our computer, and we follow the steps of the download. We recommend to download the Flight Gear for Linux but if you prefered the Windows version, we add here a video of communication between Windows and your Linux virtual machine with the simulator: https://drive.google.com/file/d/1Hn2pse_LFLGliL5lF6xQm9vHV6xEAYSg/view 

#### Step 2:
Download the "ex3" folder where are all the documents of the Flight Simulator Interpret program.

#### Step 3:

#### If you want to use CLion:

***A)*** Enter to CLion, go to File, and then to New CMake Project from Sources.

***B)*** After that select the ex3 folder and mark OK.

***C)*** Choose the option: Import as a new CMake project, mark the cmake-build-debug folder and open the file called      CMakeLists.txt. 

***D)*** Select OK, and then choose the option of New Window. 

***E)*** Now that we have the project opened, select ex3 folder, and open the CMakeLists.txt file for editting it.

***F)*** In CMakeLists.txt, paste this below the line 4: set(CMAKE_CXX_FLAGS -pthread)

***G)*** Then, go to the upper bar to Run, and select EditConfigurations...

***H)*** Finally, write in Program arguments: fly.txt , and select OK.



#### If you want to do it by Command Line:

***A)*** Open a Terminal.

***B)*** Change to (cd) ex3 folder.

***C)*** Paste this in the Terminal and do enter:

you@yourhost:~$ g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o FGinterpreter.out -pthread

***D)*** Write in Terminal this to run the program:

you@yourhost:~$ ./FGinterpreter.out cmake-build-debug/fly.txt

## Built With
* **[Ubuntu](https://ubuntu.com/download/desktop) - Version "buster/sid"** - 5.0.0-37-generic #40~18.04.1-Ubuntu SMP UTC 2019 x86_64 x86_64 x86_64 GNU/Linux

* **[CLion](https://www.jetbrains.com/es-es/clion/download/#section=linux)** - Version 2019.2.5

## Authors

* **Ezequiel Glocer**
* **Erez Rigevsky**

## License

This project is licensed under the Apache License 2.0

## Thanks to:
(The TA Michael from 2018/19)

http://wiki.flightgear.org/New_to_FlightGear

http://wiki.flightgear.org/Autostart
