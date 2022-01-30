# Brief Overview of the Code
####Adam Wang
####USC ID: 7684727576
####adamwang@usc.edu 
####PA2

I added the subclasses which contain statements to be executed. A makefile containing specific instructions.

AddStatement carries out addition after determining whether the input variable is in the map or integer.

DivideStatement carries out division after determining whether the input variable is in the map or integer and whether there is division by 0 problem.

MultiplyStatement carries out multiplication after determining whether the input variable is in the map or integer.

SubtractStatement carries out subtraction after determining whether the input variable is in the map or integer.

dotend behaves like an end statement that terminates the program by setting the line number to 0(where the null_ptr was initially inserted while parsing the program in main)

End has the same function as dotend

IfStatement jumps to the line if comparison returns true， illegal jump instruction is embedded in jump function 

Goto goes to the line number (terminates when line number exceeds maximum line number)

GOSUB haves partially like Goto but push line to stack for return

RETURN returns to the line number after GOSUB was executed


Only issue I have is about curricula submission, here is the screenshot of running tests locally on my computer.


<img width="1436" alt="Screen Shot 2021-09-27 at 1 33 27 AM" src="https://user-images.githubusercontent.com/73175625/134873810-b51996f2-c961-4ead-97d1-b7b22c6d50e5.png">
<img width="1440" alt="Screen Shot 2021-09-27 at 1 33 35 AM" src="https://user-images.githubusercontent.com/73175625/134873828-50fe5146-5610-4174-bf5a-56696a688ad4.png">

