from tkinter import *
import FPgameclass

class GUI:
    
    def __init__ (self):

        # create the main window widget and title and game class
        self.root = Tk()
        self.root.title('Guessing Game')
        self.game = FPgameclass.Game()

        # the number of click
        self.click = 0

        
        # create each widget and place it in the main window
        self.first_frame = Frame()
        self.second_frame = Frame()
        self.third_frame = Frame()
        self.forth_frame = Frame()
        self.fifth_frame = Frame()
        self.sixth_frame = Frame()
        self.seventh_frame = Frame()
        self.eighth_frame=Frame()


        # instructions
        self.instruction_label1=Label(self.first_frame,\
                                     text ='Instructions' , font =('Times',30,'bold'), fg='orange')
        self.instruction_label2=Label(self.first_frame,\
                                      text = 'In this game, the computer will guess the number you are thinking.\n If you\'r number is in the card list, check the checkbox. \n The range of numbers would be 1~100')
        self.star_0 = Label(self.first_frame,\
                             text = '********************************************************************************************')
        self.instruction_label1.pack()
        self.instruction_label2.pack()
        self.star_0.pack()


        # the start up list    
        self.img1 = PhotoImage(file ='card1.gif')

        self.img1_label = Label(self.second_frame,\
                                image = self.img1)
        self.img1_label.pack()


        # the previuos and next button
        self.previous_button = Button(self.third_frame,\
                                 text = 'Previous', command = self.previous)
        self.previous_button.pack(side='left')

        self.next_button = Button(self.third_frame,\
                                  text = 'Next', command=self.nexts)
        self.next_button.pack(side='right')

        # disable the previous button
        self.previous_button.config(state='disable')

        # check box
        self.c1_var = IntVar()
        self.c1_var.set(0)
        self.c1 = Checkbutton(self.forth_frame,\
                              text = 'Card 1', variable =self.c1_var)
        
        self.c2_var = IntVar()
        self.c2_var.set(0)
        self.c2 = Checkbutton(self.forth_frame,\
                              text = 'Card 2', variable =self.c2_var)

        self.c3_var = IntVar()
        self.c3_var.set(0)
        self.c3 = Checkbutton(self.forth_frame,\
                              text = 'Card 3', variable =self.c3_var)
    
        self.c4_var = IntVar()
        self.c4_var.set(0)
        self.c4 = Checkbutton(self.forth_frame,\
                              text = 'Card 4', variable =self.c4_var)

        self.c5_var = IntVar()
        self.c5_var.set(0)
        self.c5 = Checkbutton(self.forth_frame,\
                              text = 'Card 5', variable =self.c5_var)

        self.c6_var = IntVar()
        self.c6_var.set(0)
        self.c6 = Checkbutton(self.forth_frame,\
                              text = 'Card 6', variable =self.c6_var)

        self.c7_var = IntVar()
        self.c7_var.set(0)
        self.c7 = Checkbutton(self.forth_frame,\
                              text = 'Card 7', variable =self.c7_var)


        # pack the check box
        self.c1.pack(side='left')
        self.c2.pack(side='left')
        self.c3.pack(side='left')
        self.c4.pack(side='left')
        self.c5.pack(side='left')
        self.c6.pack(side='left')
        self.c7.pack(side='left')


        # answer button to give answer
        self.answer_button = Button(self.fifth_frame,\
                                 text = 'Get Answer', fg='blue', command = self.choice)
        self.answer_button.pack()


        # display the user's number
        self.answer_label = Label(self.sixth_frame,\
                                  text ='Your number is: ')
        self.answer_label.pack()
        self.value = StringVar()
        self.answer_output = Label(self.sixth_frame,\
                                   textvariable = self.value, fg='purple')
        self.answer_output.pack()

        
        # reset button to reset program
        self.reset_button = Button(self.seventh_frame,\
                                   text ='Reset',bg='red',command = self.reset)
        self.reset_button.pack()


        # pack the frames
        self.first_frame.pack()
        self.second_frame.pack()
        self.third_frame.pack()
        self.forth_frame.pack()
        self.fifth_frame.pack()
        self.sixth_frame.pack()
        self.seventh_frame.pack()
        self.eighth_frame.pack()


        # display the main window and start the event processing loop
        self.root.mainloop()


   

    # the nexts function in which well swith image    
    def nexts(self):
        self.click += 1
        if self.click == 1:
            self.img1_label.destroy()
            self.img2 = PhotoImage(file ='card2.gif')
            self.img2_label = Label(self.second_frame,\
                                 image = self.img2)
            self.img2_label.pack()
            self.previous_button.config(state='normal')
            return self.click

        elif self.click == 2:
            self.img2_label.destroy()
            self.img3 = PhotoImage(file ='card3.gif')
            self.img3_label = Label(self.second_frame,\
                                 image = self.img3)
            self.img3_label.pack()
            self.previous_button.config(state='normal')
            return self.click

        elif self.click == 3:
            self.img3_label.destroy()
            self.img4 = PhotoImage(file ='card4.gif')
            self.img4_label = Label(self.second_frame,\
                                 image = self.img4)
            self.img4_label.pack()
            self.previous_button.config(state='normal')
            return self.click

        elif self.click == 4:
            self.img4_label.destroy()
            self.img5 = PhotoImage(file ='card5.gif')
            self.img5_label = Label(self.second_frame,\
                                 image = self.img5)
            self.img5_label.pack()
            self.previous_button.config(state='normal')
            return self.click

        elif self.click == 5:
            self.img5_label.destroy()
            self.img6 = PhotoImage(file ='card6.gif')
            self.img6_label = Label(self.second_frame,\
                                 image = self.img6)
            self.img6_label.pack()
            self.previous_button.config(state='normal')
            return self.click

        elif self.click == 6:
            self.img6_label.destroy()
            self.img7 = PhotoImage(file ='card7.gif')
            self.img7_label = Label(self.second_frame,\
                                 image = self.img7)
            self.img7_label.pack()
            self.next_button.config(state='disabled')
            return self.click


        
    # the previous function in which well swith image    
    def previous(self):
        self.click -= 1
        if self.click == 5:
            self.img7_label.destroy()
            self.img6 = PhotoImage(file ='card6.gif')
            self.img6_label = Label(self.second_frame,\
                                 image = self.img6)
            self.img6_label.pack()
            self.next_button.config(state='normal')
            return self.click

        elif self.click == 4:
            self.img6_label.destroy()
            self.img5 = PhotoImage(file ='card5.gif')
            self.img5_label = Label(self.second_frame,\
                                 image = self.img5)
            self.img5_label.pack()
            self.next_button.config(state='normal')
            return self.click

        elif self.click == 3:
            self.img5_label.destroy()
            self.img4 = PhotoImage(file ='card4.gif')
            self.img4_label = Label(self.second_frame,\
                                 image = self.img4)
            self.img4_label.pack()
            self.next_button.config(state='normal')
            return self.click

        elif self.click == 2:
            self.img4_label.destroy()
            self.img3 = PhotoImage(file ='card3.gif')
            self.img3_label = Label(self.second_frame,\
                                 image = self.img3)
            self.img3_label.pack()
            self.next_button.config(state='normal')
            return self.click

        elif self.click == 1:
            self.img3_label.destroy()
            self.img2 = PhotoImage(file ='card2.gif')
            self.img2_label = Label(self.second_frame,\
                                 image = self.img2)
            self.img2_label.pack()
            self.next_button.config(state='normal')
            return self.click

        elif self.click == 0:
            self.img2_label.destroy()   
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.img1_label.pack()
            self.previous_button.config(state='disabled')
            return self.click


    # the answer function in which adds the checked boxes     
    def choice(self):
        if self.c1_var.get() == 1:
            self.game.card1()

        if self.c2_var.get()==1:
            self.game.card2()

        if self.c3_var.get() ==1:
            self.game.card3()

        if self.c4_var.get()==1:
            self.game.card4()

        if self.c5_var.get()==1:
            self.game.card5()

        if self.c6_var.get()==1:
            self.game.card6()

        if self.c7_var.get()==1:
            self.game.card7()


        # if user didn't check any boxes: show error
        if self.game.gettotal() == 0:
            messagebox.showerror('error', 'You didn\'t check any boxes!\nREMEMBER:\nThe range of numbers are 1~100!')
            self.answer_output.destroy()
            self.answer_output = Label(self.sixth_frame,\
                                        text = 'N/A')
            self.answer_output.pack()


        # if the user doesn't have range of 1~100: show error
        if self.game.gettotal() >= 101:
            messagebox.showerror('error','You made a mistake!\nYou may have misclicked a box when the number you are thinking is not in the list.')
            self.answer_output.destroy()
            self.answer_output = Label(self.sixth_frame,\
                                        text = 'N/A')
            self.answer_output.pack()


        # add a side error of if the user didn't get the number they were expecting
        if self.game.gettotal() >= 1 and self.game.gettotal() <= 100:
            self.stars_1 = Label(self.eighth_frame,\
                             text = '********************************************************************************************', fg='red')
            self.error = Label(self.eighth_frame,\
                                  text ='If that is not your answer, please look back at the list. You misclicked the box by accident.', fg='red')
            self.stars_2 = Label(self.eighth_frame,\
                             text = '********************************************************************************************',fg='red')
            self.stars_1.pack()
            self.error.pack()
            self.stars_2.pack()

        # display the number
        self.value.set(self.game.gettotal())


        # disable checkboxes,  answer , next, and previous buttons
        self.c1.config(state = 'disabled')
        self.c2.config(state = 'disabled')
        self.c3.config(state = 'disabled')
        self.c4.config(state = 'disabled')
        self.c5.config(state = 'disabled')
        self.c6.config(state = 'disabled')
        self.c7.config(state = 'disabled')
        self.answer_button.config(state = 'disabled')
        self.next_button.config(state='disabled')
        self.previous_button.config(state='disabled')
                

    # resets by: deselecting check box, total, buttons, and others to orginal state
    def reset(self):
        
        # deselect all the checkboxes
        self.c1.deselect()
        self.c2.deselect()
        self.c3.deselect()
        self.c4.deselect()
        self.c5.deselect()
        self.c6.deselect()
        self.c7.deselect()


        # put back checkboxes to normal state
        self.c1.config(state = 'normal')
        self.c2.config(state = 'normal')
        self.c3.config(state = 'normal')
        self.c4.config(state = 'normal')
        self.c5.config(state = 'normal')
        self.c6.config(state = 'normal')
        self.c7.config(state = 'normal')

        # delete the image of whatever number they are on and put back card 1
        if self.click == 6:
            self.img7_label.destroy()
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.click = 0
            self.img1_label.pack()

        elif self.click == 5:
            self.img6_label.destroy()
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.click = 0
            self.img1_label.pack()

        elif self.click == 4:
            self.img5_label.destroy()
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.click = 0
            self.img1_label.pack()

        elif self.click == 3:
            self.img4_label.destroy()
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.click = 0
            self.img1_label.pack()

        elif self.click == 2:
            self.img3_label.destroy()
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.click = 0
            self.img1_label.pack()

        elif self.click == 1:
            self.img2_label.destroy()   
            self.img1 = PhotoImage(file ='card1.gif')
            self.img1_label = Label(self.second_frame,\
                                 image = self.img1)
            self.click = 0
            self.img1_label.pack()
        
        # disable the previous button, and put back normal for next and answer
        self.previous_button.config(state='disable')
        self.next_button.config(state='normal')
        self.answer_button.config(state = 'normal')

        # delete the notice for it isn't necessarry until given answer
        self.eighth_frame.destroy()
        self.eighth_frame = Frame()
        self.eighth_frame.pack()

        # delete the answer to the orginal state of game
        self.answer_label.destroy()
        self.answer_output.destroy()
        self.value = StringVar()
        self.answer_label = Label(self.sixth_frame,\
                                  text ='Your number is: ')
        self.answer_label.pack()
        self.answer_output = Label(self.sixth_frame,\
                                   textvariable = self.value, fg='purple')
        self.answer_output.pack()

        # call the function reset
        self.game.reset()


# run the program
GUI()
