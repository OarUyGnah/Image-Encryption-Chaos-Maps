from PIL import Image
import numpy as np
import os
if os.name == "nt":
    import msvcrt
else:
    import tty
    import termios
from matplotlib.pyplot import imshow
import matplotlib.pyplot as plt
import cv2 as cv
import random
from math import log
import pandas
# from tqdm import tqdm


def get_image_color(imageName):
    return cv.imread(imageName,cv.IMREAD_COLOR)
def get_image_gray(imageName):
    return cv.imread(imageName,cv.IMREAD_GRAYSCALE)
def get_image_matrix_color(imageName):
    # 顺序为B G R
    return cv.imread(imageName,cv.IMREAD_COLOR)
def get_image_matrix_gray(imageName):
    return cv.imread(imageName,cv.IMREAD_GRAYSCALE)

def get_image_matrix(imageName,color):
    if color:
        return get_image_matrix_color(imageName)
    else:
        return get_image_matrix_gray(imageName)

def get_image_rgb(imageName):
    img = cv.imread(imageName)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            img[i][j][0],img[i][j][2] = img[i][j][2],img[i][j][0]
    return img
def get_image_bgr(imageName):
    return get_image_color(imageName)

# 一维rgb数组
def get_rgb_arr(img):
    rows,cols,n = img.shape
    r = []
    g = []
    b = []
    for i in range(0,rows):
        for j in range(0,cols):
            r.append(img[i][j][2])
            g.append(img[i][j][1])
            b.append(img[i][j][0])
    return r,g,b

# 二维rgb数组
def get_rgb_arr2(img,fmt):
    rows,cols,n = img.shape
    r = []
    g = []
    b = []
    for i in range(0,rows):
        rtmp = []
        gtmp = []
        btmp = []
        for j in range(0,cols):
            if(fmt == 'bgr'):
                rtmp.append(img[i][j][2])
                gtmp.append(img[i][j][1])
                btmp.append(img[i][j][0])
            else:
                rtmp.append(img[i][j][0])
                gtmp.append(img[i][j][1])
                btmp.append(img[i][j][2])
        r.append(rtmp)
        g.append(gtmp)
        b.append(btmp)
    return r,g,b
def rgb_to_img(rows,cols,r,g,b):
    img = []
    for i in range(rows):
        curr = []
        for j in range(cols):
            curr.append([r[i][j],g[i][j],b[i][j]])
        img.append(curr)
    return img

# 确定一维和二维数组数据相同
def assert_arr1_eq_arr2(arr1,arr2):
    idx1 = 0
    for i in range(0,250):
        for j in range(0,250):
            if arr2[i][j] != arr1[idx1]:
                return False
            idx1 += 1    
    return True


def assert_img_equal(name1,name2,color):
    times = 0
    img1 = get_image_matrix(name1,color)
    img2 = get_image_matrix(name2,color)
    assert(img1.shape == img2.shape)
    if color:
        width,length,_ = img1.shape
    else:
        width,length = img1.shape
    if color:
        for i in range(width):
            for j in range(length):
                if(img1[i][j][0] != img2[i][j][0] or img1[i][j][1] != img2[i][j][1] or img1[i][j][2] != img2[i][j][2]):
                    # print('{img1[{0}][{1}] == {2} img2[{0}][{1}] == {3}}'.format(i,j,img1[i][j],img2[i][j]))
                    print('img1[{0}][{1}] == {2} img2[{0}][{1}] == {3}'.format(i,j,img1[i][j],img2[i][j]))
                    # return False
                    times += 1
    else:
        for i in range(width):
            for j in range(length):
                if(img1[i][j] != img2[i][j]):
                    print('img1[{0}][{1}] == {2} img2[{0}][{1}] == {3}'.format(i,j,img1[i][j],img2[i][j]))
                    # return False
                    times += 1
    return times