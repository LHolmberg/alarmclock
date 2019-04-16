import tkinter as tk
from tkinter import *
import os
import sys
import cv2
import numpy as np
import subprocess
import os
import sys
from sys import exit
from PIL import ImageTk, Image


window = tk.Tk()
window.configure(background='#232323')
window.geometry("1232x650")
original = cv2.imread('C:\\Users\\Lukaz\\OneDrive\\Skrivbord\\se.png', cv2.IMREAD_COLOR)
image_to_compare = cv2.imread('C:\\Users\\Lukaz\\OneDrive\\Skrivbord\\fir.png', cv2.IMREAD_COLOR)
lbl = Label(window, text="try again")
img = Image
lbl.pack_forget()
img = ImageTk.PhotoImage(Image.open("se.png"))
panel = Label(window, image = img)
panel.pack(side = "bottom", fill = "both", expand = "yes")




def check():
    if original.shape == image_to_compare.shape:
        print("The images have same size and channels")
        difference = cv2.subtract(original, image_to_compare)
        b, g, r = cv2.split(difference)
        if cv2.countNonZero(b) == 0 and cv2.countNonZero(g) == 0 and cv2.countNonZero(r) == 0:
            print("The images are completely Equal")
        else:
            print("The images are NOT equal")
    sift = cv2.xfeatures2d.SIFT_create()
    kp_1, desc_1 = sift.detectAndCompute(original, None)
    kp_2, desc_2 = sift.detectAndCompute(image_to_compare, None)
    index_params = dict(algorithm=0, trees=5)
    search_params = dict()
    flann = cv2.FlannBasedMatcher(index_params, search_params)
    matches = flann.knnMatch(desc_1, desc_2, k=2)
    good_points = []
    for m, n in matches:
        if m.distance < 0.6*n.distance:
            good_points.append(m)

    number_keypoints = 0
    if len(kp_1) <= len(kp_2):
        number_keypoints = len(kp_1)
    else:
        number_keypoints = len(kp_2)
            
        
    print("Keypoints in the first image: " + str(len(kp_1)))
    print("Keypoints in the second image: " + str(len(kp_2)))
    print("Matches:", len(good_points))
    print("Similarity: ", len(good_points) / number_keypoints * 100)
    
    result = cv2.drawMatches(original, kp_1, image_to_compare, kp_2, good_points, None)
    cv2.imshow("result", cv2.resize(result, None, fx=0.4, fy=0.4))
    cv2.imwrite("feature_matching.jpg", result)
    cv2.imshow("Original", cv2.resize(original, None, fx=0.4, fy=0.4))
    cv2.imshow("Duplicate", cv2.resize(image_to_compare, None, fx=0.4, fy=0.4))
    if len(good_points) / number_keypoints * 100 > 5:
        os.startfile(r'C:\Users\Lukaz\OneDrive\Skrivbord\UI.py')
        os._exit(1)

    else:
        lbl.pack()
        
    cv2.waitKey(0)
    cv2.destroyAllWindows()




btn = Button(window, text = "Check if your image is good enough", command=check)
btn.pack()

window.mainloop()

    


        
    

    
