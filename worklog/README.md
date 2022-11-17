# Cloud Computing project

This report is for the Cloud Computing course at ENSIMAG. The project notes were divided in two parts (Week1Notes and Week2Notes).  

For a better visualisation of this README, please read it on my Github (https://github.com/henriqueconte/CloudComputing/tree/Week2Step1/worklog).

## Testing the project

This project was developed in a Macbook Pro 2018 and wasn't tested in any other operating systems. However, there shouldn't be any problems related to that. 

1. Open a terminal at the workspace/arm.boot folder.  
2. Run `make run`.    
3. Write `echo testing` and press enter. It should echo "testing".  
4. Enter two or three random commands, like "abc", "pizza pizza", etc.  
5. Try using arrow up and arrow down to scroll on a history of commands, just like a normal console.  
6. Try running the command `reset`. It should clear the screen and put the cursor at the very top on the left of the terminal.  

## Branches/tags

The project was developed in different branches separated by step of development, in order to separate implemented features and to provide a better versioning strategy. Therefore, we have the following branches:

* main  
* Week1Step1  
* Week1Step2  
* Week1Step3  
* Week1Step4  
* Week2Step1  

However, I have to confess that there were some code changes on the Week2Step1 branch that should have been implemented on the branches related to the Week1, like fixing problems with  `echo` and command line history.  

That happens because I discovered some bugs in those features after starting the Week2, and I didn't want to go back to the previous branches, make the change there, merge them to main and finally merge them to Week2. Therefore, I just made the changes directly at Week2Step1, that saved me time. 

Besides, there are tags that mark the last commit of each branch, called: 

* week1.step1  
* week1.step2 
* week1.step3  
* week1.step4  
* week2.step1

Finally, if you want to check the commits, they are available at https://github.com/henriqueconte/CloudComputing/commits/main. They make it easier to understand how I developed the project, step-by-step on my thoughts. 

I started the project the 6th of October, and commited almost every week, specially on the files "Week1Notes" and "Week2Notes", that are related to the studies I did related to the project. 


## Working features

The project is almost done. You can use the console with its basic features, such as echo, reset and command history. I completed all steps related to week 1 as far as I know, even though they might not be perfect.

You can verify the working features by following the *Testing the project* section. On the file "Week1Notes", I gave all my answers related to the theoretical questions on the Week1 assignment. 

![Echo demostration](/worklog/images/echo.jpeg?raw=true "Echo demonstration")
![Before reseting](/worklog/images/multipleCommands.jpeg?raw=true "Before reseting")
![After reseting](/worklog/images/reset.jpeg?raw=true "After reseting")

Besides, regarding the Week 2 assignments, I implemented the use of wfi() instead of the busy waiting, and then interruptions to read characters only when we have an input. 

## Not working (yet!) features

The circular buffer with the FIFO is quite unclear for me. I enabled the VIC and IRQ, but I seem to fail at identifying the correct interruptions. Everytime I type something on my keyboard, the program reads it as a timeout masked interrupt status, so I never use the RX and TX interruptions. Therefore, I think I'm not proprely using the defined circular buffers. 

I believe that happens because I'm using masks in the wrong manner. I never used them before, and they are quite confusing to me. 

## My background

I come from a Computer Science background from Brazil, and I always opted for software engineering or mathematical courses. I'm currently doing Double Degree at ENSIMAG, and I'm still trying to opt for high level programming classes.  

When I chose the Cloud Computing course, I was expecting it to focus on technologies like Docker, AWS, Google Cloud, etc, so I was a bit shocked by the actual content of the course. Nowadays, my focus is to work with software development, but on a higher level than what we are seeing in class. 

## Challenges

I had a really hard time with this project. For me, the hardest part was to understand what was supposed to be implemented, especially on the week 2 step. I liked that week 1 had steps and you could guide yourself based on them.

In addition, I don't understand low level programming very well, and this was my first time doing something related to embedded systems development. Thus, sometimes I didn't know if what I was doing was right or wrong, because I didn't know what to expect from the code execution and at some points had no idea on how to debug them!  


