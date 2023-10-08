import cv2

img_vid = []


for i in range (3000,3500):
    path = 'C:\\Users\\Santiago\\Desktop\\Python\\CP\\frames\\IMG %04d.jpg' %i
    img = cv2.imread(path)
    img_vid.append(img)

alto, ancho = img.shape[:2]
video_2 = cv2.VideoWriter('video_2.mp4', cv2.VideoWriter_fourcc(*'mp4v'),30,(ancho,alto))


for i in range (0, len(img_vid)):
    video_2.write(img_vid[i])


video_2.release