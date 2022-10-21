import threading
import time

from dao import base_bao
from entity import video


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

    def add_video(self, _date, _video_stream, _monitor_id, _event_id=-1):
        new_video = video.Video(date=time.strftime('%Y-%m-%d', time.localtime()), video_stream=_video_stream,
                                event_id=_event_id, monitor_id=_monitor_id)
        self.session.add(new_video)
        self.session.commit()

    def query_video_by_id(self, _id):
        the_video = self.session.query(video.Video).filter(video.Video.id == _id).first()
        return the_video

    def delete_video(self, _id):
        the_video = self.query_video_by_id(_id)
        self.session.delete(the_video)
        self.session.commit()

    def get_monitor_obj_by_id(self, _id):
        the_video = self.query_video_by_id(_id)
        return the_video.monitors

    def get_event_obj_by_id(self, _id):
        the_video = self.query_video_by_id(_id)
        return the_video.events


video_dao = VideoDao.get_instance()
