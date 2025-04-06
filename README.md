# Philosophers Project

This project simulates the well-known "Dining Philosophers Problem," which is a classic synchronization problem used to demonstrate the challenges of concurrent programming. The simulation is implemented using threads and mutexes for the mandatory part and semaphores for the bonus part.

## Problem Overview

The simulation models philosophers sitting around a round table with a bowl of spaghetti in the center. There are as many philosophers as there are forks. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must pick up two forks: one to the left and one to the right. Once they are done eating, they put the forks down and sleep before starting the cycle again.

The objective is to prevent any philosopher from starving while ensuring that the system runs efficiently.

## Features

- **Thinking**: Philosophers think when they are not eating or sleeping.
- **Eating**: Philosophers can only eat when they have both forks.
- **Sleeping**: After eating, philosophers sleep before starting the cycle again.
- **Starvation Prevention**: The simulation ensures that no philosopher will starve.
- **Concurrency**: The simulation uses threads and mutexes (mandatory part) to manage concurrency and semaphores (bonus part) for additional synchronization.
- **Philosophers' Safety**: The system prevents deadlocks and ensures that every philosopher gets to eat.

## Requirements

- POSIX threads (pthreads)
- Mutexes and Semaphores for synchronization

