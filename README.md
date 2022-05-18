# Wikipedia Hyperlink Network Analyzer

## Final Presentation
https://www.youtube.com/watch?v=K7aZyIvxNAw

## Table of Contents

- [Authors](#authors)
- [Documentation](#documentation)
- [Installation](#installation)
- [Running Tests](#running-tests)
- [Usage/Examples](#usageexamples)
- [Results](#results)


## Authors

- Gagan Kadadevarmath (gagan2)
- Sanjiv Iyer (sanjivi2)
- Sarah Zimmerman (sarahrz2)
- Ritvik Gandesiri (ritvikg2)


## Documentation

All of our functions and codebase have been documented, 
and our weekly progress reports that describe our development 
can be found in our development folder 
[here](development/progress-log.md).


## Installation

First, clone this repository to your local machine with the following command:

```bash
  git clone https://github-dev.cs.illinois.edu/cs225-fa21/gagan2-sarahrz2-sanjivi2-ritvikg2.git
```
Then ``cd`` into the folder where you cloned the repository.


## Running Tests

To run our test suite, which can be found [here](tests/tests.cpp), you must make sure that you are running on EWS servers and then type ``module load llvm/6.0.1`` into their terminal and run it.
Then, run ``make`` to compile our code.
Now, run the following commands to run the test suite:

```bash
  make test
  ./test
```
If you want to only run a speciifc group of tests, you can use:
```bash
  make test
  ./test [kosaraju]
```
or 
```bash
  make test
  ./test "BFS*"
```


## Usage/Examples
To see our traversal and algorithms in action, we have provided a small portion of our dataset to be ran in our ``main.cpp`` file using the following commands

```bash
  make
  ./main ./data/parsed_test.txt 10th_century
```
The format of the CLI input is ``./main [filepath] [starting node for BFS]``

To run our entire dataset, users can run:
```bash
  make
  ./main ./data/parsed.txt X
```
Where X is the starting node that MUST be found within our dataset.


## Results
The full outputs of each algorithm and traversal can be found [here](results).
