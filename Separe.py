import cv2

capture = cv2.VideoCapture('C:\\Users\\Santiago\\Desktop\\Python\\CP\\video.mp4')   #cambiar
path = 'CP\\frames\\'                                                                #cambiar


for i in range (3500):
    if i < 3000:
        ret, frame = capture.read()
    else:
        ret, frame = capture.read()
        if ret == True:
            cv2.imwrite(path + 'IMG %04d.jpg' % i, frame)
            if cv2.waitKey(1) == ord('s'):
                break
        else:
            break

capture.release()
cv2.destroyAllWindows()