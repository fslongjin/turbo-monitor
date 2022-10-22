安装Paddlehub库
pip install paddlehub==1.6.2 -i https://pypi.tuna.tsinghua.edu.cn/simple

添加需要人脸检测的视频路径
在video_detect_path中加入(多个需换行)

执行video_detect.py
python video_detect.py

检测结果会返回为avi视频格式，名称为(result_+path+.avi)