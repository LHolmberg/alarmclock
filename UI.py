import tkinter as tk
from tkinter import *
from functools import partial
import time
import datetime

######################################################
window = tk.Tk()
window.configure(background='#262626')
window.geometry("700x500")
num_run = 0
btn_funcid = 0
window.title("Joylarm clock")
lbl = Label(window, text= 'wake', bg = "#262626", fg = "#FFFFFF", font=("Times", 50))
lbl.pack(side= "top", fill = "both", expand = 1)
wake = ''


#######################################################

def alarm():
    button_alarm.pack_forget()
    textEnter.pack()
    textEnter_button.pack(side = BOTTOM)
    textEnter.focus()

#######################################################

def set_alarm():
   global wake
   textEnter.pack_forget()
   textEnter_button.pack_forget()
   button_alarm.pack()
   wake = textEnter.get()

#######################################################

def tick():
    global wake
    current_time = time.strftime("%I:%M:%S")
    lbl.config(text=current_time)
    if wake == current_time[:-3]:
        lbl.config(bg="red")
    lbl.after(200, tick)
        
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


textEnter = Entry(window, width=10, background='white', justify=CENTER, font='-weight bold')
textEnter.bind('<Button-1>', run)

#######################################################

textEnter_button = Button(window, height=3, width=20, bg="#70ff9b", text="Set Alarm", command=set_alarm)
button_alarm = Button(text = "Alarm", command=alarm, bg="#70ff9b", height=3, width=20)
button_alarm.pack()
tick()
window.mainloop()
