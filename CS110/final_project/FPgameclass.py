from tkinter import *

class Game:


    # set total = 0
    def __init__(self):
        self.__total = 0
        
    # for appropiate card, add numbers
    def card1(self):
        self.__total += 1

    def card2(self):
        self.__total += 2

    def card3(self):
        self.__total += 4

    def card4(self):
        self.__total += 8

    def card5(self):
        self.__total += 15

    def card6(self):
        self.__total += 28

    def card7(self):
        self.__total += 56
            
    # add the total
    def gettotal(self):
        return self.__total

    # set total to 0 again
    def reset(self):
        self.__total = 0
        
        
        
