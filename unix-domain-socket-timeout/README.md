# UNIX domain Socket Timeout test

The code has the implementation of client server communication over unix domain socket.

The test performed on is to see if we can set the timeout on the same socket from different processes, and would it reflect on all the processes.

The result is that the time option of socket is specific to the process creating the socket i.e every process can set different timeout on same socket file, but there timeouts apply to their own processes.
