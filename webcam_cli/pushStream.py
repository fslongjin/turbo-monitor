import subprocess as sp
import time

import cv2 as cv

# 这个用的是直播＋的推流地址，建议换一个
rtmpUrl = "rtmp://175.178.85.36/live/1589251892504494081"

cap = cv.VideoCapture(0)

# Get video information
fps = int(cap.get(cv.CAP_PROP_FPS))
width = int(cap.get(cv.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv.CAP_PROP_FRAME_HEIGHT))

localtime = time.asctime(time.localtime(time.time()))
# 打水印
reconstruct='ffmpeg  -i src.mp4 -vf "drawtext=fontsize=160:text=localtime" -c:v libx264 -an -f mp4 output.mp4 -y'


# ffmpeg command
command = ['ffmpeg',
           '-y',
           '-f', 'rawvideo',
           '-vcodec', 'rawvideo',
           '-pix_fmt', 'bgr24',
           '-s', "{}x{}".format(width, height),
           '-r', str(fps),
           '-i', '-',
           "-vf", "drawtext=fontsize=50:text='%{localtime}",  # 添加时间水印
           '-c:v', 'libx264',
           "-an",
           '-pix_fmt', 'yuv420p',
           '-preset', 'ultrafast',
           '-f', 'flv',
           rtmpUrl]

# 管道配置
p = sp.Popen(command, stdin=sp.PIPE)

# # read webcamera
while (cap.isOpened()):
    ret, frame = cap.read()
    if not ret:
        print("Opening camera is failed")
        break

    # process frame
    # your code
    # process frame

    # write to pipe
    p.stdin.write(frame.tostring())
