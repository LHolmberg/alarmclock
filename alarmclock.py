import tkinter as tk
from tkinter import *
from functools import partial
import time
import datetime
from time import gmtime, strftime
import subprocess
import os
from sys import *

#SETUP WINDOW
window = tk.Tk()
window.resizable=(0, 0)
window.configure(background='#232323')
window.attributes("-fullscreen", True)
window.title("Joylarm clock")

#SETUP THE TIME LABEL, CENTERED ON THE SCREEN
timee = Label(window,fg = "#FFF", bg = "#232323", font=("Helvetica", 20))
timee.pack(side=BOTTOM, anchor=W)

#SETUP THE LABEL THAT CONFIRMS YOUR TIME THAT YOU SET
lbl = Label(window, text= 'wake', bg = "#232323", fg = "#FFFFFF", font=("Helvetica", 100))
lbl.pack(anchor=CENTER, fill = "x", expand = 1)

num_run = 0
btn_funcid = 0
wake = ''

#THE LABELFRAME FOR THE NUMPAD
lf = tk.LabelFrame(window, text="Keypad", bd=5, bg = "#262626", fg="#fff")
lf.pack(anchor=CENTER)

#FUNCTION FOR THE NUMPAD
def numpad():
    global num_run, boot
    btn_list = [
        '7',  '8',  '9',
        '4',  '5',  '6',
        '1',  '2',  '3',
        '0',':',  'Del',]
    r = 1
    c = 0
    n = 0
    btn = list(range(len(btn_list)))
    for label in btn_list:
        cmd = partial(click, label)
        btn[n] = tk.Button(lf, text=label, width=10, height=5, command=cmd, bg="#1c1c1c", fg="#fff")
        btn[n].grid(row=r, column=c)
        n += 1
        c += 1
        if c == 3:
            c = 0
            r += 1

#FUNCTION TO SETUP THE TEXT ENTRY BOX & BUTTON TO SET THE ALARM
def alarm():
    button_alarm.pack_forget()
    textEnter.pack(side= "top")
    textEnter_button.pack(side = BOTTOM)
    textEnter.focus()

#FUNCTION THAT SETS THE ALARM ON THE TIME THAT YOU CHOSE
def set_alarm():
   global wake, wak
   textEnter.pack_forget()
   textEnter_button.pack_forget()
   lf.pack_forget()
   button_alarm.pack()
   wake = textEnter.get()
   b.pack(anchor=S)
   wak = Label(window, text= wake, fg = "#FFFFFF", bg = "#262626")
   wak.pack()
   button_alarm.pack_forget()

#UPDATE
def update():
    global wake
    ct = time.strftime("%a, %d %b %Y", gmtime())
    current_time = time.strftime(datetime.datetime.now().strftime('%H:%M:%S'))
    lbl.config(text=current_time)
    timee.config(text=ct)
    if wake == current_time[:-3]:
        os.startfile(r'C:\Users\Lukas\Desktop\song.wav')
        os.startfile(r'C:\Users\Lukas\Desktop\OPENGL\Debug\OPENGL.exe')
        os._exit(1)
    lbl.after(1000, update)    

#DEFINES THE CLICK OF BUTTONS ON THE NUMPAD
def click(btn):
    global num_run
    text = "%s" % btn
    if not text == "Del" and not text == "Close":
        textEnter.insert(END, text)
    if text == 'Del':
        textEnter.delete(0, END)

#IF YOU WANT TO REMOVE A SET TIME
def removeAlert():
    global wake,wak
    button_alarm.pack()
    wake = "gr"
    b.pack_forget()
    wak.pack_forget()

#THE RUNNING METHOD OF THE NUMPAD
def run(event):
    global num_run, btn_funcid
    if num_run == 1:
        lf.pack(anchor=N)
        textEnter.pack(anchor=CENTER)
        textEnter_button.pack(anchor=S)
        button_alarm.pack_forget()
        numpad()
        btn_funcid = window.bind('<Button-1>')
    if num_run == 0:
        num_run = 1
        numpad()
        btn_funcid = window.bind('<Button-1>')

button_alarm = Button(text = "Alarm", command=alarm, bg="#70ff9b", height=4, width=27)
button_alarm.bind('<Button-1>', run)

textEnter_button = Button(window, height=4, width=27, bg="#70ff9b", text="Set Alarm", command=set_alarm)
textEnter = Entry(window, width=15, background='white', justify=CENTER, font='-weight bold')
b = Button(window,text="Remove alarm", width=27,height=4, command=removeAlert, bg="#70ff9b")
b.pack_forget()
button_alarm.pack()
update()
window.mainloop()
