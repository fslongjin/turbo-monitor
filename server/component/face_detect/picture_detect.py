import matplotlib.pyplot as plt 
import matplotlib.image as mpimg 

with open('picture_detect_path.txt', 'r') as f:
    test_img_path=[]
    for line in f:
        test_img_path.append(line.strip())
print(test_img_path)

import paddlehub as hub
module = hub.Module(name="ultra_light_fast_generic_face_detector_1mb_640")
# module = hub.Module(name="ultra_light_fast_generic_face_detector_1mb_320")

#
input_dict = {"image": test_img_path}
# execute predict and print the result
results = module.face_detection(data=input_dict, visualization=True)
for result in results:
    print(result)
    
# 预测结果展示
for path in test_img_path:
    img = mpimg.imread("face_detector_640_predict_output/"+path)
    plt.figure(figsize=(10, 10))
    plt.imshow(img)

plt.axis('off')
plt.show()
