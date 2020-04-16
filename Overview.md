# MD5 Message Digest Algorithm Overview Document

## Introduction
This document includes an overview of the MD5 algorithm and its computation in C. This will look into areas such as how it is run, tested and the algorithm complexity as some examples of topics covered below. This document is intended as a guide for students who would be using this algorithm in the next year and helps outline the understanding of MD5 as a hashing algorithm.
 
### Project Statement
Write a program in the C programming language that calculates the MD5 hash digest of an input. The algorithm is speciﬁed in the Request for Comments 1321 document supplied by the Internet Engineering Task Force. The only prerequisite is that your program performs the algorithm — you are free to decide what input the algorithm should be performed on. It is suggested you allow the user to input some free text or a ﬁlename via the command line.
 
### Repository Introduction
The repository on GitHub was used in order to keep track of progress throughout development. The repository contains a readme which describes the project and how it was carried out. The sections include a how to run section specifying how a user would go about downloading and running the project on their own computer. It also has a section which details how the algorithm works and a research and project progress summary which details the work that has gone into the project as well as research gone into the project throughout the development lifecycle. The repository also contains a gitignore. This is used to prevent unnecessary files from being uploaded to the GitHub repository. This was used to prevent executable files that were compiled from being uploaded to the project throughout. This included test file executables as well as the actual md5 algorithm implementation file executables. The final thing in the repository is the actual c file which contains the implementation of the md5 hashing algorithm. 
 
### Code Overview
This code uses the md5 hashing algorithm to hash an input using a set of options available to the user. The user has the option to hash a string they input. This can be done by running the executable in the command line followed by the --string option and then after specifying the string they wish to hash. An example input would be "MD5.exe --string abc". This would hash the string “abc” using the md5 algorithm to produce an output. The user also has an option to hash a file’s contents using the algorithm. This is done by using the --file parameter option after the executable followed by the name of the file you wish to have its contents hashed. An example of command line input would be “MD5.exe --file filename.txt “. The last input which involves using the algorithm is the testing suite option. This is done by following the executable file with the --test parameter option. This is run using the following parameter in the command line “MD5.exe --test”. This runs a set of test cases which are outlined in the MD5 documentation to ensure that the algorithm carries out the hashing process correctly. 
 
## Running the code
The first step to running the code is to either download or clone the repository from GitHub. This can be done via the command line using “git clone” followed by the repository link or by pressing the download button on GitHub and unzipping the zip file into your desired directory. The next step is to compile the code. This includes opening a terminal in the directory of the cloned/downloaded project, then running the command “gcc -o MD5 md5.c” where MD5 is the name which will be given to your executable file. This executable file can be run in a command terminal by entering the name of the executable or the name of the executable followed by .exe i.e. “MD5” or “MD5.exe”. The parameters mentioned above in the code overview section can then be used to run the application. There is also an additional --help parameter option which displays the options to the user and samples of how to run each.

<p align="center">
  <img src="https://raw.githubusercontent.com/michaelcoleman7/MD5_Message_Digest_Algorithm/master/Images/runningExamplePNG.PNG?token=AGMMKRUTU4F4P2V4CVDMKO26UGXCY">
  <p align="center">Creating MD5.exe Example</p>
</p>
 
## Testing
Testing is carried out as specified in the above sections by running the --test parameter option in the command line. This uses the selection of test cases given in the [RFC document](https://tools.ietf.org/html/rfc1321) in section A.5, page 21. This automatically runs all these tests by hashing them and displaying the hashing algorithms results. As stated in the code section above the command line input for executing these tests is “MD5.exe --test” where MD5 is the executable name.

<p align="center">
  <img src="https://raw.githubusercontent.com/michaelcoleman7/MD5_Message_Digest_Algorithm/master/Images/testsuite.PNG?token=AGMMKRT5IDJSO3CSRDAEQ4C6UGXIM">
  <p align="center">Example of running test suite</p>
</p>

## Algorithm
This section details an overview of the MD5 algorithm and gives an explanation of its implementation within my code. The first part of the explanation will give a brief overview of the algorithm before going into specific details about the implementation. MD5 hashing is an algorithm which is used to produce a 128-bit message digest. A text of 512-bit blocks is divided into 16 blocks. Each of these 16-bit blocks consist of 32 bits. This results in a 128-bit message digest made up of 4 32-bit blocks.
<p align="center">
  <img src="https://raw.githubusercontent.com/michaelcoleman7/MD5_Message_Digest_Algorithm/master/Images/md5hashing.png?token=AGMMKRRJ4D2QOENKSCGFASC6UCMYI">
  <p align="center">Basic overview of hashing process</p>
</p>

In my algorithm, I chose that I would try to do the algorithm without the use of external libraries besides the library used for input and output (stdio.h). This was to reduce the reliance of my algorithm on external libraries which would do many parts of the implementation for me were they to be used. Throughout this explanation I will provide reasoning for the choices made in my implementation. 

The first part of the algorithm implementation includes the creation of the auxiliary functions. These functions are used during the transformation rounds later in the algorithm. These include functions for F, G, H and I. These functions use logical operators like OR, XOR, NOR to produce an output. There are also four functions FF,GG,HH and II which use the previously defined F,G,H and I as well as taking a block and constants given in the [RFC document](https://tools.ietf.org/html/rfc1321). There are also many constants defined which are used throughout the code which are defined at the beginning in order to give the code a clean look e.g. The padding and constants used in the transformation rounds which will be explained later. The constants are located in the [RFC document](https://tools.ietf.org/html/rfc1321) in section A.3.

The next part of the algorithm is the MD5 context. This contains the states, number of bits, modulo 2^64 (count) as well as the input buffer. These are all specified again in the [RFC document](https://tools.ietf.org/html/rfc1321). I also add the final digest value to this context as it is what is used to carry out the process of the MD5 algorithm, I felt this would be the best place to put it, rather than have a created variable which would just store the result outside of the algorithm as displayed in the RFC Document. This context is defined as a struct and is used in the initialisation of the MD5 algorithm. A variable of this is created at the very beginning of the MD5 hashing process.

The next section in the algorithm is the MD5 initialisation method. This is used to set up all the variables which need initialisation in the previously defined MD5 context struct. This initialises the counts of the context to 0. It also loads magic initialization constants into the state values. These values are stated in the [RFC document](https://tools.ietf.org/html/rfc1321) in section A.3 page 11. This method is called at the very beginning of the process and is given a pointer value to the context variable created in the previous section whose values are updated.

The next stage defined in my algorithm is the MD5 transform method. This is the method which is used to carry out transformations on the states of the context. This method takes in 2 parameters for a state and a block. Each of the 4 states within the state pointer are assigned to a, b, c and d respectively. These 4 states along with the block are then put through a series of 4 rounds. This uses the FF function in the first round and runs for 16 iterations. Each iteration includes a block input (starting at block [0] and running to block [15] - 16 operations on the block). The states a, b, c and d are also used in the transformations and are placed in different orders in the FF method as displayed in the [RFC document](https://tools.ietf.org/html/rfc1321) under section A.3 pages 13 and 14. Another 16 rounds are carried out for the GG, HH and II  functions using the different constants and different ordering of the blocks though the ordering of a, b, c and d are the same for all 4 rounds. The states are then updated with a, b, c and d after all rounds have been completed. This method is called inside both the update and final MD5 methods.

The next method defined is the MD5 update method. This method continues an MD5 message-digest operation, processing another message block, and updating the context. The method takes in a pointer to the md5 context, an input block, and the length of that input block. The first thing the method does is compute the number of bytes mod 64 to compute an index. Then the bits are updated, that is the context’s count values are updated using the input length as well as right and left bit shifting. While the input length decrements down to zero, a process takes place within this while loop. The buffer value in the context is updated and the index is incremented. Before the transform is called I populate the blocks by looping over them, this process can be seen in the decoding section of the [RFC document](https://tools.ietf.org/html/rfc1321). This process is carried out in the document during the transform method. This includes the shifting of bits which populate into each bit of a 16-bit block, I incorporated it here before the transform method is called. I chose this as a design decision as I like to keep methods using the single responsibility principle design architecture. This also allowed me to change up the code structure in comparison with the code given in the RFC document. Prior to this, the MD5 transform method mentioned above is called using the context state and the 16-bit block just populated.

The last method which is used to carry out a part in the process of calculating the MD5 hash is the MD5 final method. This method is used to calculate the final digest and ends an MD5 message-digest operation. The final method takes a pointer to the context as a parameter. The first operation that is carried out is assigning the last 2 bits of a 16-bit block to the values stored in the contexts count (i.e the number of bits). The next step involves a padding process to 56 modules 64. This process involves creating an index which is used to calculate the padding length, when this is calculated the MD5 update method is called using the context, padding constant initialised at the beginning of the algorithm and the padding length just calculated. The rest of the block (14 bits) is then populated (i.e the last 2 blocks have already been populated from the first part of the method). Then the same encoding as mentioned in the update is used here also before calling the transform method with the context and block (same as update’s call to transform method). Finally, the final value of the digest is then calculated. It was at this point I decided to put the final digest value into the context for convenience.  This value can then be accessed by the context at any time (e.g. for printing result).

The next method is the first method which has nothing to do with the physical implementation of the MD5 hash. This method is the method to print the digest out. It is a simplistic method which outputs the digests final value by looping over the final digest outputting each character contained in the 16-bit digest. This along with printing out the result, also displays the string they entered.

The next method in my algorithm is used to get the MD5 hash result of a string value. This has a character pointer which is the string value (character array) which is to be hashed. Firstly, the method creates a context, calls the MD5 initialise method using the context. This is then followed by the Md5 Update method sending in the context, input string and its length as parameters. The method used in the hashing process is the MD5 final method sending with it the context. The final part of this method, then displays the result by calling the print digest method.

The next method is the MD5 file method. This is used to read in the contents of a file and produce the MD5 hash result of its contents. If unable to read the file, a message is displayed to the user informing them of this. The MD5 init method is called using the context. Then a while loop is used to allow the calling of the MD5 update method which uses the files contents until it is finished reading all the file contents. When complete the MD5 final method is called, followed by the print method to display the results. 

The final method excluding the main is the testing method. This method calls the MD5 string method on a number of test cases from the [RFC document](https://tools.ietf.org/html/rfc1321). These can be found in section A.5 on page 21.

The last method in the algorithm is the main method. This is used in order to allow the user to select the options they wish to use. This is done by allowing the user to enter command line parameters in order to carry out actions on their desired input. The first option is run when the user runs the executable and enters no parameters. This displays that they should run the command --help in order to get details on the options available to them. Upon running the executable with this command, a list of possible options is displayed to the user. This option is recognised by comparing the string using “strcmp” to compare the values in the command line to the command. This compares the text in the command line to the exact term --help. This is also done using the same method to run the tests with the --test command. The MD5 string and file options use the “strncmp” option as they need to select the user input which is to be hashed using the selected option. --string and --file are called to run tests of a string and file contents, respectively. The user must leave a space between the option to get their input to be hashed correctly. This is due to when the option is detected the “strncmp” skips over the length of the input e.g. --string, then a space and takes the next user input option. 

<p align="center">
  <img src="https://raw.githubusercontent.com/michaelcoleman7/MD5_Message_Digest_Algorithm/master/Images/algorithmDiagram.png?token=AGMMKRUTQ6LZCDGD632OYFC6UCNKK">
  <p align="center">Diagram of Algorithm Methods Cycle</p>
</p>

## Complexity
This section goes into detail about the complexity of the MD5 algorithm and how it works. It also talks about how the MD5 algorithm may be reversed e.g. the pursuit of finding an input for a given output of a hashed MD5 digest.
 
### MD5 Overview
Firstly, I will give a basic intro into MD5 and its inception. MD5 message-digest algorithm is used to produce a 128-bit hash value. It was designed by Ronald Rivest in 1991 to be a predecessor to MD4. In its original creation it was designed to be a cryptographic hash function. However, this is now not the case as it has been declared “cryptographically broken and unsuitable for further use.” [1]. MD5 consists of many vulnerabilities which have been exposed, for example, a cryptographic hash function should result in it being computationally infeasible to find two distinct messages that hash the same value, however with MD5 this is not the case, that is two inputs may both hash to the same output. Later in this section I will go into more detail on this topic.
 
### MD5 Complexity
As stated, the goal of MD5 hashing algorithm is to produce a 128-bit hash value. The input message is broken up into chunks of 512-bit blocks (16 32-bit words). In the event that the input is not a multiple of 512-bit blocks, the message is padded such that its length in bits is agreeable to 448 modulo 512. Padding is done so that the total bits are 64 less than a multiple of 512 bits length. Padding is carried out even if it is already in the form of 448 modulo 512. Padding is carried out as follows, A single 1 is appended to the message, then a series of 0’s is added until the message is congruent to 448, modulo 512. The least one bit must be padded and at most 512 bits are appended to the message [2].

The next step is appending the length where 64 bits are inserted at the end representing the length of the original message, modulo 2^64. In the event that this is greater than 2^64, then only the low order byte of the original length is used. After this the message should be an exact multiple of 512 bits. This also means that the message is a multiple of 16 32-bit words [3].

The MD5 algorithm operates on a 128-bit state, this is divided into four 32-bit words, represented as A, B, C, and D. These are initialized into fixed constants. These constants are:



| 32-bit words        | Constants           | Hexadecimal Value  |
| :-------------: |:-------------:|:-------------:|
| A     | 0x67452301 | 01 23 45 67 |
| B      | 0xEFCDAB89      |   89 ab cd ef |
| C | 0x98BADCFE     |    fe dc ba 98 |
| D | 0x10325376      |    76 54 32 10 |

The next step in the algorithm is to process the message into 16-word blocks. To carry out this process four auxiliary functions are needed. These take inputs as three individual 32-bit words and produce a single 32-bit word output. They apply the logical operators AND, OR, NOT and XOR to the input bits. These are defined as follows:

- F (X,Y,Z) = XY v not(X) Z
- G (X,Y,Z) = XZ v Y not(Z)
- H (X,Y,Z) = X xor Y xor Z
- I (X,Y,Z) = Y xor (X v not(Z))

The algorithm then uses each 512-bit message block in turn to modify the state. The processing of a message block consists of four similar rounds. each round is composed of 16 similar operations based on the above auxiliary functions. One of the functions F, G, H and I used per round [4].
[Below MD5 Process image source](https://www.researchgate.net/profile/Dipesh_Vaya/publication/320477119/figure/fig1/AS:550995438182400@1508378957589/Process-of-MD5-Algorithm.png)
<p align="center">
  <img src="https://www.researchgate.net/profile/Dipesh_Vaya/publication/320477119/figure/fig1/AS:550995438182400@1508378957589/Process-of-MD5-Algorithm.png">
  <p align="center">MD5 Process</p>
</p>


After all rounds have been performed, the buffers A, B, C, D contain the MD5 output starting with lower bit A and ending with higher bit D.

## Reversing the algorithm
The algorithm is theoretically impossible to reverse directly, i.e. it is not possible to retrieve the original string from a given hash using only mathematical operations. The way many attackers use to “decrypt” the algorithm is that they use large dictionaries with millions of entries which acts as a look up table for discovering the value of a hash. Many algorithms try to prevent this through the use of a "salt", however with MD5, this is not the case. With MD5 there are many different methods of “breaking” the algorithm. In this section I will discuss some of the methods of showcasing the vulnerabilities of MD5 as a hashing algorithm explaining what they are and delving into algorithms which were used to "break" MD5.

### Dictionary Attack
This is a method of brute force attacking an algorithm in order to determine its original input or decryption. This technique involves running through a list of likely possibilities, often a list of words from a dictionary, hence the name. These are often successful due to many people chasing poor easy to guess passwords. Dictionary attacks are carried out by precomputing hash values for a given dictionary file and comparing target password hashes to the precomputed tables looking for a match, or a dictionary file of words is hashed and then compared against a target password hash to try find a match [5].

### Brute force attacks
This is perhaps the most basic of all algorithm attacks, this involves trying every possible value to try and get a matching value. This is very expensive for a potential attacker as testing every possibility is an expensive task. 

### Collision Attacks
A collision attack on a cryptographic hash tries to find two inputs producing the same hash value. As a result of hash functions allowing infinite input length and compute a predefined output length, there will be a possibility that two or more inputs produce the same output from a hashing operation. When this occurs, a collision has taken place. The collision then results in a possible exploitation of the hashing algorithm. An example of this would be seen through the downloading of a file which used a hash function as an integrity verification method. If an attacker was aware of a collision matching the hash, then they could swap the file without the user’s knowledge [6]. An example of this was discovered in MD5 in 2004 by Xiaoyun Wang. It describes a manually found differential path for MD5 and showcases the concept of near collision blocks: a pair of input blocks that results in specifically targeted output differences [7]. It allows computation of a new collision in a couple of hours of CPU time. Dan Kaminsky published a paper showing that the file transfer mentioned above was possible using MD5 based on the discoveries by Wang [8]. 

#### Chosen-prefix collision attack
This is an extension of the aforementioned collision attack. This allows an attacker to choose two different documents, and then append different calculated values that result in the documents having an equal hash value. An example of this in MD5 can be seen by an algorithm produced by Marc Stevens, Arjen Lenstra and Benne de Weger [9]. This algorithm uses chosen-prefix collisions to find an automated way to find differential paths for MD5. This algorithm shows that approximately 2^39 calls to the MD5 compression function it is possible, for any chosen m1 and m2 to construct s1 and s2 such that MD5(m1 || s1) == MD5(m2 || s2). This was due to using a more powerful birthday search (Attack based on the exploitation of the mathematics behind the birthday problem in probability theory i.e. a certain number of students in a class reveal their birthday and the likelihood of a collision of birthdays is calculated). In short, they use two arbitrary messages and run them through their designed algorithm such that the extended messages collide under MD5. A breakdown of the algorithm can be found in [Chosen-prefix collisions for MD5 and applications](https://documents.epfl.ch/users/l/le/lenstra/public/papers/lat.pdf) under section 3 on pages 327 and 328.

<p align="center">
  <img src="https://cdn.arstechnica.net/wp-content/uploads/2012/06/collision_attack_overview.png">
  <p align="center">Chosen-Prefix Collision Overview</p>
</p>

#### Tunnelling
Tunnelling in hash functions is a concept which was introduced by Vlastimil Kilma in 2006. These tunnels replace multi-message modification methods and exponentially accelerate collision search. Kilma created a document in which he describes an algorithm used to find MD5 collisions within a minute [10]. This document details how the solution to the tunnelling was produced and it explains how the tunnelling is carried out. The algorithm uses nested for loops to iteratively check through all possible combinations for the tunnels within the first block, if probabilistic conditions are met, then it calls the block 2 function. The block 2 function is similar to block ones but using new conditions and vectors for initialisation. If a colliding message is found, then they are displayed. This tunneling can find a collision in less than a minute, which is a massive difference in multi-message modification attacks which can take many hours to find a collision in MD5.

### Conclusion to reversing MD5
Though not possible to reverse directly as stated before I hope that the few areas I have highlighted have shed some light on how the algorithm is considered “unsuitable” for use and how alternative hashing algorithms such as SHA-256 should be used in real world implementations as an alternative. Though I have only scratched the surface here as there are many more ways in which MD5 has shown vulnerabilities, for example preimage attacks, single-block collision attacks etc are possible on MD5. These areas are certainly worth looking into and understanding as a student who would be undertaking this project if you wish to truly grasp the vulnerabilities of MD5 as a hashing algorithm.


## References
[1] [Reversing an MD5 hash - John Cook](https://www.johndcook.com/blog/2019/01/24/reversing-an-md5-hash/): Talks about how the algorithm used to be used until it was declared "cryptographically broken and unsuitable for further use." It also explains some of the security issues posed by the MD5 hashing algorithm. Helps in my explanation of the downfall of MD5 in the cryptography industry.
 
[2] [Cryptographic Hashing Functions - MD5- Farhad Ahmed Sagar](https://cs.indstate.edu/~fsagar/doc/paper.pdf): Breaks down the padding process of MD5 into a very readable and understandable format. Helps validate my points made in the document.
 
[3] [RFC Document](https://tools.ietf.org/html/rfc1321): The RFC document which outlines MD5’s implementation, Does the best job of properly explaining the action of appending the length from my research. Used to verify points made on reasoning for appending length.
 
[4] [A review of Comparative Study of MD5 and SHA Security Algorithm - Surbhi Aggarwal, Neha Goyal and Kirti Aggarwal](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.736.1789&rep=rep1&type=pdf): Explains the processing of the blocks in great detail with a very readable diagram helping understanding of the process carried out by the functions. Supplements my points made on the block processing and the 4 sets of 16 rounds carried out during the transform.

[5] [Dictionary Attack on MD5 Hash](https://pdfs.semanticscholar.org/5988/011e62a6c6ae7bc849bc422bd4132e9dde73.pdf): Explains the process of dictionary attacks for the MD5 algorithm. This helps verify the definition made about what dictionary attacks are in the context of the MD5 hashing algorithm.
 
[6] [Hash Collision Attack - Privacy Canada](https://privacycanada.net/hash-functions/hash-collision-attack/):
This gives an explanation of collision attacks and how they could be used to exploit a vulnerable hashing algorithm. This supplements my points on hash collisions and the vulnerabilities they possess.
 
[7] [How to Break MD5 and Other Hash Functions - Xiaoyun Wang and Hongbo Yu](http://merlot.usc.edu/csac-f06/papers/Wang05a.pdf):
Explains the process that was used to carry out collision attacks on the MD5 algorithm. This is the document Wang published about his research and the process of his work on MD5 which was mentioned in the overview discussing in greater detail than in this overview.
 
[8] [MD5 To Be Considered Harmful Someday - Dan Kaminsky](https://eprint.iacr.org/2004/357.pdf):
Paper by Kaminsky which explains how it is possible for the MD5 algorithm to be harmful as two files could be swapped. Highlighting the danger of the algorithm. Explains in detail how my point about file swapping could be carried out by an attacker exploiting the MD5 hashing algorithm.
 
[9] [Chosen-prefix collisions for MD5 and applications - Marc Stevens, Arjen K. Lenstra, Benne de Weger](https://documents.epfl.ch/users/l/le/lenstra/public/papers/lat.pdf):
Document on the breakdown of an algorithm of chosen-prefix collisions for MD5. Showcases the complexity of the algorithm discussed in the overview and how it was achieved.
 
[10] [Tunnels in Hash Functions: MD5 Collisions Within a Minute - Vlastimil Klima](https://eprint.iacr.org/2006/105.pdf):
Document describing tunneling in MD5. This document details how the task was undertaken and the complexity of the algorithm which was mentioned in the overview expanding on my points.
