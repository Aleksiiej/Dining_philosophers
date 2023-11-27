# Dining Philosophers Project

## Project Overview
The Dining Philosophers project is a multithreading simulation designed to demonstrate proficiency in coordinating multi-threaded programs. This implementation particularly focuses on resource sharing among five threads, symbolizing the classic Dining Philosophers problem in computer science.

## Key Features:
- Resource Management: Manages shared resources among multiple threads, mimicking the scenario where five philosophers share a limited number of utensils.
- Thread Synchronization: Implements advanced synchronization techniques to ensure smooth operation of concurrent threads without deadlock.
- RAII Wrappers for Mutexes: Utilizes RAII (Resource Acquisition Is Initialization) wrappers, specifically std::lock_guard, to manage mutexes, ensuring thread safety and efficient 
resource handling.
      
## Technical Stack:
- Language: C++
- Concurrency Tools: Standard C++ mutexes, lock guards, and threading libraries.

## Project Goals:
- Demonstrate Multithreading Expertise: Showcases the ability to handle complex threading issues, such as resource sharing and thread synchronization, in a high-level programming language.
- Educational Tool: Serves as an educational reference for understanding common problems and solutions in multithreaded programming.
- Portfolio Enhancement: Acts as a testament to advanced programming skills, particularly in C++, suitable for showcasing in a professional portfolio or CV.

## Getting Started:
- Clone the repository.
- Compile the code using a C++ compiler supporting C++11 or later.
- Run the simulation to observe the coordination of threads representing the philosophers.
