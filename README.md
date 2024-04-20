Names: Kelly Nguyen, Brandon Nolan, Drashti Mehta
 
Emails: nguyenkelly21@csu.fullerton.edu, brandonnolan@csu.fullerton.edu, dumehta@csu.fullerton.edu

Contributation: 

Kelly Nguyen - worked on part 2 overview, worked on readme file

Brandon Nolan - worded on part 1 overview, worked on part 2 overview

Drashti Mehta - worked on part 2 overview, worked on bonus

All team members are familiar with all functionality in the assignment.

Programming Languages: C

How to execute: 

 1. Git clone the code https://github.com/nguyenkelly21/CPSC-351.git
  
 2. Compile the files with these commands
    gcc -o shell shell.c
    gcc -o serial serial.c
    gcc -o parallel parallel.c
    
 3. Execute the program with these commands
    ./shell
    ./serial locations.txt
    ./parallel locations.txt

Executation Times:

Serial Fetcher 
  Real Time = 0m0.002s
  User Time = 0m0.001s
  Sys Time = 0m0.000s
                 
Parallel Fetcher
  Real Time = 0m0.003s
  User Time = 0m0.002s
  Sys Time = 0m0.001s

Answers to questions: 
  1. In the output of time, what is the difference between real, user, and sys times?

Real time is the wall clock time. The user time is measured by the how long the CPU spends outside the kernel. Sys time is how long the CPU spends inside the kernal.

  2. Which is longer: user time or sys time? Use your knowledge to explain why.

The user time was longer for serial fetcher and parallel fetcher. For serial fetcher, the user time was 0m0.002s while sys time was 0m0.001s. For parallel fetcher, the user time was 0m0.001s while sys time was 0m0.000s. The user time is longer because most of the time is spent in the user-mode code to do the tasks and execute the process.

  3. When fetching all of the locations in the file, which fetcher finishes faster? Why do you think that is?

The parallel fetcher finishes faster because multiple locations are being fetched at the same time. The serial fetcher gets the locations one by one so it is slower.

  4. Suppose one of the fetcher children crashes. Will this affect other children? Explain.
  What is your conclusion regarding the benefits or disadvantages of isolating each fetch
  task within a different process?

If one of the fetcher children crashes, it would not affect the other children because it uses fork() to create a new process and has its own copy. The benefits of isolating each fetch task within a different process is that the task will not affect the others. The disadvantage is that overhead may occur as there is multiple processes going on in memory.

Extra Credit: Yes
