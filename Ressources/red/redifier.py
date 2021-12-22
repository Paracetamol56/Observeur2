import cv2
import numpy as np
import os

directory = "C:\\Users\\utilisateur\\Desktop\\Observeur2\\Ressources\\red\\rc"
for filename in os.listdir(directory):
    if filename.endswith(".png"):
        completeFilename = os.path.join(directory, filename)
        print(completeFilename)
        # read image
        src = cv2.imread(
            completeFilename,
            cv2.IMREAD_UNCHANGED,
        )
        print(src.shape)

        # create a new image
        red_img = src

        # replace blue and green chanels by zero
        red_img[:, :, 0] = 0
        red_img[:, :, 1] = 0

        # create a new directory
        new_directory = (
            "C:\\Users\\utilisateur\\Desktop\\Observeur2\\Ressources\\red\\rc_red"
        )
        if not os.path.exists(new_directory):
            os.makedirs(new_directory)

        # save image
        cv2.imwrite(
            os.path.join(new_directory, filename),
            red_img,
        )
    else:
        continue
