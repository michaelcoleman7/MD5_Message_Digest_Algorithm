# MD5_Message_Digest_Algorithm
4th Year semester 2 project for the Theory of Algorithms module. This project is coded on a Google Cloud Virtual Machine (Linux Debian 10). The project is also coded using VI as an editor.

## Project statement
Write a program in the C programming language that calculates the MD5 hash digest of an input. The algorithm is speciﬁed in the Request for Comments 1321 document supplied by the Internet Engineering Task Force. The only pre-requisite is that your program performs the algorithm — you are free to decide what input the algorithm should be performed on. It is suggested you allow the user to input some free text or a ﬁlename via the command line.

## How to run program
- Clone repository into a folder/location
- cd into project directory
- Run command `gcc -o MD5 MD5.c` in terminal of project directory
- Run `MD5` or `MD5.exe` command in terminal of project directory followed by parameters you wish to execute
- The option parameters available after the above line are:
  - --help: This is used to show the user the list of options they have
  - --string: This is used to MD5 hash a string which the user wishes to hash
  - --file: This is used to enter a File which contents user wishes to hash
  - --test: Run a set of test cases that are provided by the RFC Document to ensure the algorithm is correct
- An example of program execution are "MD5.exe --string abc". This hashes the string "abc".

## MD5 Overview
MD5 message digest algorithm is used to produce a 128-bit message digest. MD5 takes the plain text of 512-bit blocks which is divided into 16 blocks, each of 32 bit and produces the 128-bit message digest which is a set of four blocks, each of 32 bits. MD5 produces the message digest through the following steps:

### Append Padding Bits
MD5 is padded such that its length in bits is agreeable to 448 modulo 512. Padding is done so that the total bits are 64 less being a multiple of 512 bits length. Padding is carried out even If the is already in the form of 448 modulo 512.

 ### Append length
64 bits are inserted at the end representing the length of the original message, modulo 2^64

### Initialise MD Buffer
A four-word buffer (A, B, C, D) is used to compute the values for the message digest. A, B, C, D are 32- bit registers. These are mapped to a set of hexadecimal values
-	word A: 01 23 45 67
-	word B: 89 ab cd ef
-	word C: fe dc ba 98
-	word D: 76 54 32 10

### Process Message in 16-Word Blocks
MD5 uses the auxiliary functions which take the input as three 32-bit number and produces a 32-bit output. 
-	F(X,Y,Z) = XY v not(X) Z
-	G(X,Y,Z) = XZ v Y not(Z)
-	H(X,Y,Z) = X xor Y xor Z
-	I(X,Y,Z) = Y xor (X v not(Z))

The content of the four buffers are mixed with the input using this auxiliary buffer and 16 rounds are performed using 16 basic operations.

### Output
The message digest produced as output is A, B, C, D. Beginning at low-order byte of A and ending with the high-order byte of D.

### Example Input and Results
- MD5 ("") = d41d8cd98f00b204e9800998ecf8427e
- MD5 ("a") = 0cc175b9c0f1b6a831c399e269772661
- MD5 ("abc") = 900150983cd24fb0d6963f7d28e17f72
- MD5 ("message digest") = f96b697d7cb7938d525a2f31aaf161d0
- MD5 ("abcdefghijklmnopqrstuvwxyz") = c3fcd3d76192e4007dfb496cca67e13b


## Research and Project Progress Summary
<b>Week 1:</b> In the first week I watched the video on how to set up my google cloud virtual machine and proceeded to do this myself. I also did some reading into MD5 message Digest Algorithm by reading a document describing the algorithm. [1]. I also watched some videos on the algorithm to further my understanding on the topic. [2]. I also did some basic coding in C and python from the video and as C is the chosen language for this project I looked back over the basics of C as well as projects I had previously coded in the language. I also played around with VI as I hadn't used this since 2nd year.

<b>Week 2:</b> In the second week I watched the video on SHA Standard. I then read over the document covered in the video a few days after watching it. [3]. I then read some sites talking about the differences between MD5 and SHA hash algorithms to improve my knowledge of the algorithms. [4] [5]. These sites compare them in many areas such as speed and security (i.e. SHA is more secure but slower, MD5 is faster but less secure). They also explain how each in them work in very simplistic terms which was very helpful for me to visualise the algorithms in comparison with the large documents read previously. 

<b>Week 3:</b> In the third week, I read over the MD5 and SHA documents [1][3] from previous weeks as I felt I understood them better and that now the documents would make more sense now that my understanding had improved. I then watched the video on bit operations in C. I then played around with the bits in C to help understand how they work. When finished the video, I had a look over the recommended documentation in the video [6] [7] as suggested by the lecturer.

<b>Week 4-5:</b> In the fourth week, I looked at the video on functions and constants in SHA and followed along with the coding recommended in the video. I also read over the paragraph in the SHA documentation in section 4.1.2 on functions to help understand it. [3]. 
In the fifth week, I looked at the padding video on the SHA padding and how it works, as well as reading into the padding in SHA. I also did some research as to how the padding works in MD5 by reading the sections on padding in the RFC document about MD5 in section 3.1 and 3.2. [1].

<b>Week 5-7:</b> In week 5, I watched the video on unions that was put up on Moodle and coded up the unions file. After watching this, I then went and looked up the comparisons of a union vs a struct as I was already familiar with these. [8]. The sixth week involved watching the merging of padding with the hashing, I then carried out this in my own code. In the seventh week, I watched both the hash function video and finalising the padding videos and again followed along in my own repository. 

<b>Week 8:</b> In week 8, I followed the video on testing and refactoring the code and carried this out in my project. I then looked back at the code I had previously written and looked at the comparisons to see the scale of changes that the refactoring of the code had done to the project. 

<b>Week 9:</b> In week 9, Production began on the MD5 algorithm, this entailed adding some of the functions and definitions needed for the algorithm which were got from the RFC Document. These include F, G, H and I functions as well as defining the context etc. Later focus began on the initialization method used for initialising the MD5 context values as well as the MD5 transform method which focuses on the transformation of state based on a block. This involves a process of 4 rounds being carried out using the functions defined in week 9. These methods are also outlined in the RFC Document in section A.3. These were started with due to being more simplistic than the rest of the methods left in the algorithm, as well as being needed for the next methods.

<b>Week 10:</b> In week 10, An update was made to the transform method as well as updating many values which used UINT4 values.  The MD5 update method was then added. This can also be found in Section A.3 of the RFC document. This requires processing another message block, and updating the context

<b>Week 11:</b> In week 11, The final method was added which is available in section A.3 of the RFC Document. This method completes the digest value and updates it in the context structure. Then a sample menu was added and a test of a string ‘abc’ was tested to ensure correct functionality. Later in the week, methods to exit application, hash user entered strings and files were added. Also test cases were added to ensure functionality by using the Test suite located in the RFC Document in section A.5.

<b>Week 13:</b> After an update with the project specifications, changes were made to the menu system as this was replaced with entering command line parameters as inputs for user options. This involves using argc and argv, these allow the program to grab values from the command line and use them in the program execution.

### References
[1] RFC Document: https://tools.ietf.org/html/rfc1321

[2] MD5 Explanation video: https://www.youtube.com/watch?v=-uRpRMpvdm0

[3] SHA256 Documentation: https://www.nist.gov/publications/secure-hash-standard

[4] MD5 vs SHA 1: http://www.differencebetween.net/technology/difference-between-sha-and-md5/

[5] MD5 vs SHA 2: https://www.geeksforgeeks.org/difference-between-md5-and-sha1/

[6] C Expressions and Operators: https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Expressions-and-Operators

[7] Bit Twiddling Tips: https://graphics.stanford.edu/~seander/bithacks.html

[8] Struct vs Union: https://www.geeksforgeeks.org/difference-structure-union-c/
