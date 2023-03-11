# Functions
The game provides a friendly user interface with multiple functional buttons to progress the game such as make-a-move button, end-the-game button, show-the-answer button and try-again botton.
There are also various hidden functions to juice it up: setting a gameboard whose hole numbers are totally up to the player, turning on the clock to time your game, saving a game set for later reflection.
# Algorithm
The game is primarily built on an efficient SAT solver which tackles the Boolean Satisfiability (SAT) problem consisting of determining a satisfying variable assignment, V, for a Boolean function, f, or determining that no such V exists. I adopt two different algorithms to fuel the SAT solver in order to present a contrast, and they are the classic Davis-Putnam-Logemann-Loveland (DPLL) algorithm and the Chaff algorithm, with the latter obtaining one to two orders of magnitude performance 
improvement on difficult SAT benchmarks.
