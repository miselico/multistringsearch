# multistringsearch
This repository contains code I wrote for solving the multistring search problem. This is very experimental and not completed.

This is code I refound on a laptop which will be erased. I wrote the code arounf April 2015

The idea was to create a very efficient implementation of multi-string search.
I recall that the ideas were related to designing an automaton with an alpabeth consisting of multiple real characters/logical character such that
* matching would never happen accross memory boundaries and
* a minimal number of charcters would get checked by first attemptin partial mathicng and then go into more steps after partial mathc
The idea was also to use vector operations maximally.

