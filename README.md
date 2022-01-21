# ECDLP PoW 

An implementation of a bread pudding PoW protocol, based in the paper https://arxiv.org/abs/1911.11287


### Requirements
- Openssl
- Flint library 2.5.2
- Gmp

### Installation

We recomend first checking if the dependecies needed in the project are already installed, for this run the following in the root project directory.
```properties
$ ./configure.sh
```  
You should see the following output otherwise install the missing libraries.
```properties
Openssl installed
flint-2.5.2 installed
GMP installed
```  

You can now simply execute 
```properties
$ make
```  

this will generate two executables `Main` and `Main_test` ready to be executed.

### Execution

The Main file for a given difficulty ``d`` executes an instance of the PoW algorithm over a random hash and random Transaction data

```properties
$ ./Main [-d] [difficulty number]
```  

if no -d param is provided the program starts with ``-d 10``

The Main_test on the other hand has two type of execution modes:

```properties
$ ./Main_test [-d] [difficulty number] [repetition]
```  

Tests if for a given [difficulty number] executed as much a [repetition] the ECDLP solutions are correct.


```properties
$ ./Main_test [-i] [difficulty number]
```  
Tests if for a given [difficulty number] which has to be bigger than 5 the executions for d = 5 up to [difficulty number] have ECDLP solutions that are correct.


### License

MIT
