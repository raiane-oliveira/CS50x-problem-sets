# CS50x Problem Sets
These are the problem sets from each lecture in CS50's Introduction to Computer Science course from Harvard University, the 2022 version of the course.

- Some problem sets codes have already been distributed to students, but with missing functions for us to implement.

You can find the link to the course website <a target="_blank" href="https://www.edx.org/course/introduction-computer-science-harvardx-cs50x">here</a>.
Partnered with edX.

## What does each problem set do?

### pset0 

Implementation of your own project in <a target="_blank" href="https://scratch.mit.edu">Scratch</a>.
  - `Piano.sb3` is a program that simulates the keys and sounds of a piano.
  
### pset1
-   `hello` is a program that asks for your name in the terminal and prints a greeting in the C language.
  
-   `mario-less` recreate Mario's pyramid in C by printing hashes (#) in the terminal to simulate the bricks.

    <img src="https://cs50.harvard.edu/x/2022/psets/1/mario/less/pyramid.png" alt="Mario's pyramid" width="200">

-   `mario-more` recreates two opposing Mario pyramids in C by printing hashes (#) in the terminal to simulate the bricks.

     <img src="https://cs50.harvard.edu/x/2022/psets/1/mario/more/pyramids.png" alt="Two Mario's pyramid">
     
-   `cash` asks the user how much he owes and returns the minimum amount of coins that will be used for change.
  
-   `credit` implements Luhn's algorithm, which checks whether a credit card is valid by means of a calculation, and prints the brand of that card on the terminal from 3 options: VISA, MasterCard, AMEX. If it's not valid or doesn't match any of the options above, print INVALID.

### pset2
  - `readability` implements the Coleman-Liau index, a readability test that grades text by its level of complexity based on school years.
  
  - `caesar` implements a program that encrypts messages using Caesar's cipher, an algorithm that rotates each letter of the alphabet based on a key which is the position of the next letter in the alphabet (i.e. say A is 0 and D is 3, if the chosen key is 3 then A becomes D).
  
  - `substitution` implements a program that substitutes all the letters of the alphabet with a key chosen by the user. (i.e. if the key is `NQXPOMAFTRHLZGECYJIUWSKDVB` then A will become N and so on)
  
### pset3
  - `plurality` simulates an election poll where the user writes who the candidates will be and the number of voters and prints who is the winner based on the highest number of votes received. I implemented only the functions: `vote` and `print_winner`.
  
  - `runoff` implements a ranked choice election where voters can vote for more than one candidate in order of preference. When a candidate is eliminated, the second option after him enters the round and continues like this until two candidates remain and one wins the election. 
I implemented only the functions: `vote`, `tabulate`, `print_winner`, `find_min`, `is_tie` and `eliminate`.

### pset4
  - `filter-less` implements a program that applies grayscale, sepia, reflection and blur filters to BMP images.
I implemented only the functions from the `helpers.c` file.

  - `filter-more` implements a program that applies grayscale, reflection, blur and edges filters to BMP images.
I implemented only the functions from the `helpers.c` file.

  - `recover` implements a program that recovers JPEGs from a forensic image on a memory card.
  
### pset5
  - `speller` implements a program that spell-checks a file using a hash table. I implemented only the functions from `dictionary.c` file.
  
### pset6
  - implements the same problems as before but in Python.
  - `DNA` implements a program that identifies a person based on their DNA. The `longest_match` function is a distribution code.
  
### pset7
  - `movies` are SQL query files answering questions about a movie database.
  - `fiftyville` It's a theft mystery solved with SQL queries.
  
### pset8
  - `homepage` It's a simple home page with a little bit about who I am, what I like to do and some projects I've developed.
  
### pset9
  - `finance` implements a web app where the user can buy and sell stocks by querying the IEX for stock prices through its API. It is necessary to create an IEX account and create a token (an API key) to export in the terminal. I implemented only the funcions `register`, `quote`, `buy`, `index`, `sell`, `history` and `cash` from `app.py` file.

## 

©<a href="https://creativecommons.org/licenses/by-nc-sa/4.0/legalcode">License Harvad University</a>
