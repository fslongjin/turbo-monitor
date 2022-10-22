import cv2
import paddlehub as hub
import numpy as np

# 定义检测人脸函数，返回识别的图片路径
def face_det(img):
    face_detector = hub.Module(name="pyramidbox_lite_server")
    result = face_detector.face_detection(images=[img], visualization='true', output_dir='face_detection_result')
    return result[0]['path']

# 定义视频处理函数
def video_pro(video_path, save_path):
    cap = cv2.VideoCapture(video_path)
    fourcc = cv2.VideoWriter_fourcc(*'XVID')
    fps = cap.get(cv2.CAP_PROP_FPS)
    frame_count = cap.get(cv2.CAP_PROP_FRAME_COUNT)
    print('帧率：%d'%fps)
    print('帧数：%d'%frame_count)
    size = (int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT)),int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)))
    out = cv2.VideoWriter(save_path, fourcc, fps, size)
    count = 1
    while cap.isOpened():
        ret, frame = cap.read()
        if ret:
            result_path = 'face_detection_result' + '/' + face_det(frame).split('.')[0] + '.jpg'
            old_img = cv2.imread(result_path)
            # 处理保存的图片，旋转
            new_img = np.rot90(old_img)
            new_img = np.rot90(new_img)
            new_img = np.rot90(new_img)
            out.write(new_img)
            k = cv2.waitKey(1) & 0xFF
            if k == 27:
                break
            elif count == frame_count:
                break
            else:
                count += 1
        else:
            break
        
    cap.release()
    out.release()
    cv2.destroyAllWindows()

with open('video_detect_path.txt', 'r') as f:
    test_img_path=[]
    for line in f:
        test_img_path.append(line.strip())
    print(test_img_path)
for path in test_img_path:
    video_pro(path, 'result_'+path+'.avi')

