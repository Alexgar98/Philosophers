# Philosophers
Philosophers is a classic concurrency problem in which a number of philosopher seat around a table, bringing with them one fork each, and must avoid dying of hunger. The problem is that they need two forks to eat. The routine will always be take forks, then eat, then sleep, then think. You can find the subject <a href="https://github.com/0xTo/All-42-subject/blob/main/pdf/Part..%20-%3E%20Pro../Philosophers.pdf">here</a>.
This project was validated on 23rd September 2024.

<h3>Things to improve:</h3>
In case of only one philosopher, the program exits before the thread, resulting in a "possibly lost" warning by Valgrind. Might be very easy to fix; the evaluators allowed this to me.
