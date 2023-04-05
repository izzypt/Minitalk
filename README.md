# Minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.

# Mandatory Part

You must create a communication program in the form of a client and a server.
- The server must be started first. After its launch, it has to print its PID.
- The client takes two parameters:
  - The server PID.
  - The string to send.
- The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it
- The server has to display the string pretty quickly. Quickly means that if you think
it takes too long, then it is probably too long
- Your server should be able to receive strings from several clients in a row without
needing to restart.
- The communication between your client and your server has to be done only using
UNIX signals
- You can only use these two signals: SIGUSR1 and SIGUSR2.

# What is a process

Since the goal of this project is to send signals between different processes , it is important to know well those 2 concepts: pocess and signal.

A process is an instance of a program running in a computer.

A process is started when a program is initiated (either by a user entering a shell command or by another program).

A process is a running program with which a particular set of data is associated so that the process can be kept track of.

A process can initiate a subprocess, which is a called a child process (and the initiating process is sometimes referred to as its parent ). 

A child process is a replica of the parent process and shares some of its resources, but cannot exist if the parent is terminated.

Processes can exchange information or synchronize their operation through several methods of interprocess communication ( IPC ).

# What Are Signals?

Signals, to be short, are various notifications sent to a process in order to notify it of various "important" events. 

By their nature, they interrupt whatever the process is doing at this minute, and force it to handle them immediately. 

# Handling Signals

Each signal may have a signal handler, which is a function that gets called when the process receives that signal.

The function is called in "asynchronous mode", meaning that no where in your program you have code that calls this function directly. Instead, when the signal is sent to the process, the operating system stops the execution of the process, and "forces" it to call the signal handler function. When that signal handler function returns, the process continues execution from wherever it happened to be before the signal was received, as if this interruption never occurred. 

Programs may setup signal handlers using ```sigaction()```, or its easier-to-use wrapper ```signal()```. The handler functions receive the signal number as an argument.

# List of Signal

There is an easy way to list down all the signals supported by your system. Just issue the kill -l command and it would display all the supported signals 

#
