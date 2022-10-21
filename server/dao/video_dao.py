from dao import base_bao
from entity import video
import time
import threading


class VideoDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with VideoDao.__init_lock:
            if not self.__instance:
                self.__instance = VideoDao()
            return self.__instance

    def add_video(self, _date, _video_stream, _event_id, _monitor_id):
        new_video = video.Video(date=time.strftime('%Y-%m-%d', time.localtime()), video_stream=_video_stream,
                                event_id=_event_id, monitor_id=_monitor_id)
        self.session.add(new_video)
        self.session.commit()

    def query_video(self, _video_stream):
        the_video = self.session.query(video.Video).filter(video.Video.video_stream == _video_stream).first()
        return the_video

    def delete_video(self, _video_stream):
        the_video = self.session.query(_video_stream)
        self.session.delete(the_video)
        self.session.commit()


video_dao = VideoDao.get_instance()
