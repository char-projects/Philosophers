<div align="center">
  <a href="https://github.com/char-projects/Philosophers">
  <img src="logo.png" alt="Logo" width="80" height="80">
  </a>
  <h1>The Dining Philosophers Problem</h1>
</div>

The project explores concurrent programming and shared memory synchronization with threads and mutexes, processes and semaphores. It's designed around Edsger Dijkstra's famous problem, originally formulated in 1965, that is stated as follows:

```
X amount of philosophers sit at a round table with bowls of food.
Forks are placed in front of each philosopher.
There are as many forks as philosophers.
All day the philosophers take turns eating, sleeping, and thinking.
A philosopher must have two forks in order to eat, and each fork
may only be used by one philosopher at a time.
At any time a philosopher can pick up or set down a fork,
but cannot start eating until picking up both forks.
The philosophers alternatively eat, sleep, or think.
While they are eating, they are not thinking nor sleeping,
while thinking, they are not eating nor sleeping,
and, of course, while sleeping, they are not eating nor thinking.
```
#### The program takes the following arguments:

```
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat>
<time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

* **```number_of_philosophers```**: the number of philosophers around the table (between 1 and 200)
* **```time_to_die```**: a number representing the time in milliseconds a philosopher has to live after a meal. If a philosopher hasn’t started eating time_to_die milliseconds after the beginning of his last meal or the beginning of the simulation, he will die
* **```time_to_eat```**: a number representing the time in milliseconds a philosopher takes to finish his meal. During that time, the philosopher keeps his two forks in hand
* **```time_to_sleep```**: the time in milliseconds that a philosopher spends sleeping
* **```number_of_times_each_philosopher_must_eat```**: an optional argument that allows the program to stop if all the philosophers have eaten at least that many times. If this argument is not specified, the simulation carries on unless a philosopher dies

The arguments must be integers between 0 and INT_MAX representing a time in milliseconds. For example:

```
./philosophers 5 800 200 200 3
```

#### Program logs philosophers actions in this format. X is philosopher ID:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
If the arguments are valid, the program will output the actions of each philosopher until one of them dies or until all of them have eaten `number_of_times_each_philo_must_eat`, if specified.
