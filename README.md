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

Since the goal of this project is to send signals between different processes , it is important to know well those 2 concepts: 

- <ins>Processes</ins> and <ins>Signals</ins>.

# What is a process

A process is an instance of a program running in a computer.

A process is started when a program is initiated (either by a user entering a shell command or by another program).

A process is a running program with which a particular set of data is associated so that the process can be kept track of.

A process can initiate a subprocess, which is a called a child process (and the initiating process is sometimes referred to as its parent ). 

A child process is a replica of the parent process and shares some of its resources, but cannot exist if the parent is terminated.

Processes can exchange information or synchronize their operation through several methods of interprocess communication ( IPC ).

# The many different ways processes can communicate with each other (IPC - interprocess communication) :


> Processes may need to communicate with each other for a variety of reasons, such as sharing data, coordinating activities, or cooperating on a task. IPC provides a standardized way for processes to exchange messages, signals, or data blocks, allowing them to work together and coordinate their activities :

<ins>Pipes</ins>: 

Pipes are a simple and efficient way of sending data between processes. A pipe is a unidirectional data channel that connects two processes. One process writes to the pipe, while the other process reads from the pipe.

<ins>Message Queues</ins>: 

Message queues provide a mechanism for processes to exchange messages or data blocks in a way that is similar to pipes, but with some additional features such as the ability to queue messages for later retrieval.

<ins>Shared Memory</ins>: 

Shared memory is a technique where two or more processes can share a region of memory that they can read from and write to. This method is fast and efficient since it does not require data to be copied between processes.

<ins>Sockets</ins>: 

Sockets provide a way for processes to communicate with each other over a network. They are a popular method for interprocess communication, particularly for distributed applications.

<ins>Signals<ins>: 
  
  Signals are a software interrupt mechanism used by processes to communicate with each other. A signal is an asynchronous notification that is sent to a process to indicate that a particular event has occurred.

  
  <ins>**This project is all about signals !!**</ins>! 
  
# What Are Signals?

The primary purpose of signals is to notify a process of an event or to interrupt its execution. 

Signals were not designed for data communication, and as such, they don't provide a direct mechanism for sending data between processes.

By their nature, they interrupt whatever the process is doing at this minute, and force it to handle them immediately. 

# Signals vs Pipes (Minitalk vs Pipex)

Signals and pipes are two different mechanisms for interprocess communication in Unix/Linux systems. The main differences between signals and pipes are:

  - **Purpose**: <ins>Signals</ins> are primarily used to notify a process of an event or to interrupt its execution, while <ins>pipes</ins> are used to pass data between processes.

  - **Mechanism**: <ins>Signals</ins> are asynchronous and can be delivered at any time, while <ins>pipes</ins> are synchronous and block until data is read or written.

  - **Data size**: <ins>Signals</ins> have a limited amount of data that can be passed between processes, typically just a small integer value (e.g., signal number). <ins>Pipes</ins> can handle much larger amounts of data.

  - **Directionality**: <ins>Signals</ins> can be sent to any process in the system, while <ins>Pipes</ins> are typically used to pass data between two related processes, where one process writes to the pipe and the other reads from it.

  - **Buffering**: <ins>Signals</ins> are not buffered, and the receiver process must handle them as they arrive. <ins>Pipes</ins>  have an internal buffer, which allows the sending process to write data to the pipe without blocking, and the receiving process to read data from the pipe when it is ready.

In summary, signals are lightweight and primarily used for notifications, while pipes are heavier and designed for data communication.
  
# Identifying Signals

Each signal in C has a corresponding number, which is defined in the ```signal.h``` header file. 
  
The signal number is an integer constant that represents a specific signal.  
    
  | Signal | Number | Description |
|----------|----------|----------|
| SIGINT | 2 | Interrupt signal (Ctrl-C) |
| SIGQUIT | 3 | Quit signal (Ctrl-) |
| SIGILL | 4 | Illegal instruction signal |
| SIGABRT | 6 | Abort signal |
| SIGFPE | 8 | Floating-point exception signal |
| SIGKILL | 9 | Kill signal |
| SIGSEGV | 11 | Segmentation fault signal |
| SIGPIPE | 13 | Broken pipe signal |
| SIGALRM | 13 | Alarm clock signal |
| SIGTERM| 15 | Termination signal |
| SIGUSR1 | 10 | User-defined signal 1 |
| SIGUSR2| 12 | User-defined signal 2 |

There is an easy way to list down all the signals supported by your system. Just issue the ```kill -l``` command and it would display all the supported signals 

When a process receives a signal, it can handle the signal using a signal handler function. 
  
  The signal handler is a function that is called when the signal is received. You can set up a signal handler using either the ```signal()``` or ```sigaction()``` function.

Note that the behavior of signals can vary between different operating systems and platforms. For example, some signals may not be available on certain platforms, or their behavior may be slightly different.

# Sending signals

- Processes may send signals using ```kill()```.
- A process only has permission to send a signal if the real or effective user ID match, or the user has super-user privileges.
- The ```kill()``` function allows a process to send a signal to a specific process (ignoring its descendants), to all the processes that belong to the sender’s process group ID, or (given super-user privileges) to all the processes excluding system processes.
- ```kill()``` takes 2 arguments: 
  - The first argument pid is the process ID of the target process. 
  - The second argument sig is the signal to send. The sig argument can be any valid signal number or zero, in which case, it does not send the signal.
    ```
    int kill(pid_t pid, int sig);
    ```

# Handling Signals

Each signal may have a signal handler, which is a function that gets called when the process receives that signal.

The function is called in "asynchronous mode", meaning that no where in your program you have code that calls this function directly. 
  
Instead, when the signal is sent to the process, the operating system stops the execution of the process, and "forces" it to call the signal handler function. When that signal handler function returns, the process continues execution from wherever it happened to be before the signal was received, as if this interruption never occurred. 

Programs may setup signal handlers using ```sigaction()```, or its easier-to-use wrapper ```signal()```. The handler functions receive the signal number as an argument.
  
 - ```signal()``` takes two arguments: 
  
    1. The signal to handle and 
  
    2. A pointer to a signal handler function. 
  
    - When the specified signal is received, the handler function is called to handle the signal. The signal() function has several limitations, including the fact that it may reset the signal handler to its default behavior if a signal is received while the handler is executing.

  - ```sigaction()``` provides greater control over signal handling than the simpler signal() function. You can specify a signal handler that is either a simple signal handler function or a more complex signal handling function that takes additional arguments. 
  
    - Here are the arguments of ```sigaction()``` function:
      - <ins>signum</ins>: This is the signal number for which the signal handler is to be set.
      - <ins>act</ins>: This is a pointer to a sigaction structure that specifies the new signal handler.
      - <ins>oldact</ins>: This is a pointer to a sigaction structure that will be used to return the current signal handler.
  
  ```
  int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  ```
  The sigaction structure looks like this :

  ```
    struct sigaction {
      void     (*sa_handler)(int);
      void     (*sa_sigaction)(int, siginfo_t *, void *);
      sigset_t   sa_mask;
      int        sa_flags;
      void     (*sa_restorer)(void);
  };

  ```
  
  - sa_handler: A pointer to a signal handling function.
  - sa_sigaction: A pointer to a signal handling function that provides additional information about the signal.
  - sa_mask: The set of signals to be blocked while the signal handler is executing.
  - sa_flags: Flags to modify the behavior of the signal.
  - sa_restorer: A pointer to a function used to restore the context after the signal handler returns.

  # Sending Data with signals
  
  As explaind above , the primary purpose of signals is not to send data, rather, it is to notify a process of an event or to interrupt its execution.
  
  So , in order to complete our project and send strings through signals we need a workaround.

One way to send a string using signals is to encode the string as a sequence of bits and send each bit as a signal. This approach is known as <ins>bit-banging</ins>.

Here's a basic idea on how you can implement this approach:

1. Convert the string to binary: Convert each character of the string to its corresponding ASCII value and then convert that value to binary.

2. Send the bits using signals: Send each bit as a signal, using `SIGUSR1` to represent `0` and `SIGUSR2` to represent `1`. You can use the `kill()` function to send the signals.

3. Reconstruct the string: In the receiving process, capture the signals using a signal handler function. Keep track of the bits and reconstruct the original string from the binary values.

Here's a sample code:

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void send_bit(int bit) {
    if (bit == 0) {
        // Send SIGUSR1 signal for bit 0
        kill(getpid(), SIGUSR1);
    } else if (bit == 1) {
        // Send SIGUSR2 signal for bit 1
        kill(getpid(), SIGUSR2);
    }
}

void send_char(char c) {
    int i;
    for (i = 0; i < 8; i++) {
        // Get the i-th bit of the character
        int bit = (c >> i) & 1;
        send_bit(bit);
        usleep(1000);  // Sleep for 1 millisecond to avoid flooding the signal queue
    }
}

void send_string(char* str) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        send_char(str[i]);
    }
    // Signal end of transmission with 8 SIGUSR1 signals
    for (i = 0; i < 8; i++) {
        send_bit(0);
        usleep(1000);
    }
}

void signal_handler(int sig) {
    static char received_char = 0;
    static int bit_count = 0;
    if (sig == SIGUSR1) {
        // Received a 0 bit
        received_char |= (0 << bit_count);
    } else if (sig == SIGUSR2) {
        // Received a 1 bit
        received_char |= (1 << bit_count);
    }
    bit_count++;
    if (bit_count == 8) {
        // Received a full character, print it to stdout
        putchar(received_char);
        fflush(stdout);
        bit_count = 0;
        received_char = 0;
    }
}

int main() {
    // Set up signal handler for SIGUSR1 and SIGUSR2
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    
    // Send the string "Simao" over signals
    send_string("Simao");
    
    return 0;
}
```

Here, the `send_string()` function takes a process ID and a string as arguments, converts the string to binary, and sends each bit as a signal using `send_bit()` function. The binary message is terminated with a null byte to indicate the end of the message.

Note that this is just a basic idea, and there are many optimizations that can be done to make the code more efficient and robust. Also, the receiver process must implement a signal handler function to capture the signals and reconstruct the original string from the binary values.
                          
 # Bitwise Operations
                          
In order to send our string in it's binary representation , it's important to know bitwise operations which we have used in the code :

Here are some references and links for furhter information :

![image](https://user-images.githubusercontent.com/73948790/230652129-1096f84d-266d-48a7-9bdf-63716fb4d2a0.png)

Check this link for further information on bitwise operations :
https://iq.opengenus.org/addition-using-bitwise-operations/

Bitwise Operator Basics :

https://www.youtube.com/watch?v=jlQmeyce65Q



**Now let's take a look at the code snippet that sends a message from one process to another using signals throught binary representation.**

```
while (*str) // loop through each character in the string
{
    i = 8; // initialize a counter to 8 bits
    c = *str++; // get the next character from the string and increment the pointer
    while (i--) // loop through each bit of the character (from MSB to LSB)
    {
        if (c >> i & 1) // if the i-th bit of the character is 1
            kill(pid, SIGUSR2); // send a SIGUSR2 signal to the receiving process
        else // otherwise, the bit must be 0
            kill(pid, SIGUSR1); // send a SIGUSR1 signal to the receiving process
        usleep(100); // wait for 100 microseconds before sending the next signal
    }
}
```

Let's say the current character being processed is 'A' (which has an ASCII value of 65 or binary value of 01000001). Here is a step-by-step breakdown of how the code sends the signals to the receiving process:

1. `i` is initialized to 8.
2. `c` is set to the binary value of 'A', which is 01000001.
3. The outer loop begins. Since `*str` is not null, the loop body is executed.
4. The inner loop begins. `i` is currently 8, so the loop body is executed 8 times.
5. In the first iteration of the inner loop, `i` is 7. `c >> i` shifts the binary value of 'A' to the right by 7 bits, resulting in 0. `0 & 1` is 0, so a SIGUSR1 signal is sent to the receiving process.
6. The program waits for 100 microseconds.
7. In the second iteration of the inner loop, `i` is 6. `c >> i` shifts the binary value of 'A' to the right by 6 bits, resulting in 1. `1 & 1` is 1, so a SIGUSR2 signal is sent to the receiving process.
8. The program waits for 100 microseconds.
9. This process continues for the remaining bits of the character, resulting in a sequence of signals that represents the binary value of the character.
10. The outer loop repeats for the next character in the string, if any.

In this way, the code is able to encode a string of characters into a series of signals that can be sent to the receiving process, which can then decode the signals back into the original string of characters.
  
  
**Now let's take a look at how we handl receiving those signals and bits**

Here is a step-by-step breakdown of how the code works:

```
static void handle_signal(int sig, siginfo_t *info, void *context)
{
    static int bit_count; // initialize a counter for the number of bits received
    static unsigned char c; // initialize a variable to store the decoded character

    (void)context; // suppress unused variable warning

    c |= (sig == SIGUSR2); // set the LSB of `c` based on the signal received
    if (++bit_count == 8) // if we've received 8 bits
    {
        bit_count = 0; // reset the bit counter
        if (!c) // if `c` is null, we've reached the end of the message
        {
            kill(info->si_pid, SIGUSR2); // send a confirmation signal to the sending process
            info->si_pid = 0; // reset the process ID to indicate that the message has been fully received
            return; // exit the function
        }
        ft_putchar_fd(c, 1); // print the decoded character to the console
        c = 0; // reset `c` to prepare for the next character
    }
    else // if we haven't received 8 bits yet
        c <<= 1; // shift `c` to the left to make room for the next bit
}
```

Let's say the receiving process has received a sequence of signals that represent the character 'A'. Here is a step-by-step breakdown of how the code decodes the signals and reconstructs the original character:

1. The signal handler function is called with the signal number (`sig`), signal information (`info`), and context information (`context`).
2. The bit counter (`bit_count`) is initialized to 0 and the decoded character variable (`c`) is initialized to 0.
3. The first signal is received, and `sig` is set to the signal number (either SIGUSR1 or SIGUSR2).
4. The bitwise OR (`|`) operator is used to set the least significant bit (LSB) of `c` based on the signal received. If `sig` is SIGUSR2, the LSB of `c` is set to 1; otherwise, the LSB of `c` remains 0.
5. The bit counter is incremented to 1.
6. This process continues for the remaining 7 signals, with the LSB of `c` being set based on each signal received and the bit counter being incremented each time.
7. When the bit counter reaches 8, it means that we have received all 8 bits of the character. The bit counter is reset to 0.
8. If `c` is null, it means we have reached the end of the message. The receiving process sends a confirmation signal to the sending process (`kill(info->si_pid, SIGUSR2)`), resets the process ID (`info->si_pid = 0`), and exits the function.
9. If `c` is not null, it means we have decoded a complete character. The character is printed to the console (`ft_putchar_fd(c, 1)`) and `c` is reset to 0 to prepare for the next character.
10. The bit shifting operation (`c <<= 1`) is used to make room for the next bit in `c`.
11. This process continues until all signals have been received and the entire message has been reconstructed.

In this way, the code is able to decode a sequence of signals into a string of characters that was originally sent by the sending

# Allowed functions for the project

Here's a small explanation on each of the allowed functions for this project :

- **write**
- **ft_printf** and any equivalent YOU coded
- **signal()**
  - The signal function is used to register a signal handler for a particular signal. The goal of this function is to set up a function to be called when a specific signal is received by the program. The parameters for this function are: the signal number, and the signal handler function.
- **sigemptyset()**
  - The sigemptyset function is used to initialize an empty signal set. The goal of this function is to create an empty signal set that can be used to add or remove signals. The parameters for this function are: a pointer to a signal set that will be initialized.
- **sigaddset()**
  - The sigaddset function is used to add a signal to a signal set. The goal of this function is to add a signal to an existing signal set. The parameters for this function are: a pointer to a signal set, and the signal number to add.
- **sigaction()**
  - The sigaction function is used to set up a signal handler for a specific signal. The goal of this function is to register a function to be called when a particular signal is received. The parameters for this function are: the signal number, a pointer to a struct containing information about the signal handler, and a pointer to a struct to store the previous signal handler.
- **kill()**
  - The kill function is used to send a signal to a process or a group of processes. The goal of this function is to send a signal to a particular process or group of processes. The parameters for this function are: the process ID or process group ID to send the signal to, and the signal number to send.
- **getpid()**
  -  The getpid function is used to get the process ID of the current process. The goal of this function is to retrieve the process ID of the current process.
- **malloc()**
- **free()**
- **pause()**
  - The pause function is used to suspend the execution of the calling process until a signal is received. The goal of this function is to block the process until a signal is received. The function does not have any parameters.
- **sleep()**
  - The sleep function is used to suspend the execution of the calling thread for a specified number of seconds. The goal of this function is to make the thread sleep for a specified time. The parameter for this function is: the number of seconds to sleep.
- **usleep()**
  - The usleep function is used to suspend the execution of the calling thread for a specified number of microseconds. The goal of this function is to make the thread sleep for a specified time. The parameter for this function is: the number of microseconds to sleep.
- **exit()**
  - The exit function is used to terminate the program
