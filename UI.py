import tkinter as tk
from tkinter import *
from functools import partial
import time
import winsound
import datetime
from time import gmtime, strftime
import subprocess
import os
import sys
from sys import exit


######################################################
window = tk.Tk()
window.resizable=(0, 0)
window.configure(background='#232323')
window.geometry("1024x600")
timee = Label(window,fg = "#FFF", bg = "#232323", font=("Helvetica", 20))

timee.pack(side=BOTTOM, anchor=W
           )
lbl = Label(window, text= 'wake', bg = "#232323", fg = "#FFFFFF", font=("Helvetica", 100))
lbl.pack(anchor=CENTER, fill = "x", expand = 1)
#frame = Frame(width=50, height=400, bg="#232323", colormap="new")
#frame.pack(side=TOP, fill=X)
num_run = 0
btn_funcid = 0
window.title("Joylarm clock")

wake = ''




#######################################################

def alarm():
    button_alarm.pack_forget()
    textEnter.pack(side= "top")
    textEnter_button.pack(side = BOTTOM)
    textEnter.focus()

#######################################################

def set_alarm():
   global wake
   textEnter.pack_forget()
   textEnter_button.pack_forget()
   button_alarm.pack()
   wake = textEnter.get()
   
   wak = Label(window, text= wake, fg = "#FFFFFF", bg = "#262626")
   wak.pack()
   button_alarm.config(state = DISABLED)
   

#######################################################

def tick():
  
    
    global wake
    ct = time.strftime("%a, %d %b %Y", gmtime())
    current_time = time.strftime("%H:%M:%S", gmtime())
    lbl.config(text=current_time)
    timee.config(text=ct)
    #pdf ="path/to/pdf"
    #a = r'C:\Desktop\fonts'

    
    if wake == current_time[:-3]:
        
        os.system(r'C:\Users\Lukas\Desktop\LukASS.mp3')
        os.system(r'C:\Users\Lukas\Desktop\fred.py')
        os._exit(1)

        
    lbl.after(1000, tick)



    
        
#######################################################



def click(btn):
    global num_run
    text = "%s" % btn
    if not text == "Del" and not text == "Close":
        textEnter.insert(END, text)
    if text == 'Del':
        textEnter.delete(0, END)
    if text == 'Close':
        boot.destroy()
        num_run = 0
        window.unbind('<Button-1>', btn_funcid)

#######################################################

def numpad():

    global num_run, boot
    boot = tk.Tk()
   
    lf = tk.LabelFrame(boot, text=" keypad ", bd=3)
    lf.pack(padx=15, pady=10)
    btn_list = [
        '7',  '8',  '9',
        '4',  '5',  '6',
        '1',  '2',  '3',
        '0',':',  'Del',  'Close']
    r = 1
    c = 0
    n = 0
    btn = list(range(len(btn_list)))
    for label in btn_list:
        cmd = partial(click, label)
        btn[n] = tk.Button(lf, text=label, width=10, height=5, command=cmd)
        btn[n].grid(row=r, column=c)
        n += 1
        c += 1
        if c == 3:
            c = 0
            r += 1


#######################################################

def close(event):
    global num_run, btn_funcid
    if num_run == 1:
        boot.destroy()
        num_run = 0
        window.unbind('<Button-1>', btn_funcid)



#######################################################

def run(event):
    global num_run, btn_funcid
    if num_run == 0:
        num_run = 1
        numpad()
        btn_funcid = window.bind('<Button-1>', close)



button_alarm = Button(text = "Alarm", command=alarm, bg="#70ff9b", height=3, width=20)

button_alarm.bind('<Button-1>', run)

#######################################################

textEnter_button = Button(window, height=3, width=20, bg="#70ff9b", text="Set Alarm", command=set_alarm)
textEnter = Entry(window, width=10, background='white', justify=CENTER, font='-weight bold')
button_alarm.pack()
tick()
window.mainloop()
