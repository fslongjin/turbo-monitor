from dao import base_bao
from entity import manager_check_video
import time
import threading


class ManagerCheckVideoDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with ManagerCheckVideoDao.__init_lock:
            if not self.__instance:
                self.__instance = ManagerCheckVideoDao()
            return self.__instance

    def add_manager_check_video(self, _user_id, _video_id):
        new_manager_check_video = manager_check_video.ManagerCheckVideo(user_id=_user_id, video_id=_video_id)
        self.session.add(new_manager_check_video)
        self.session.commit()

    def query_manager_check_video(self, _user_id):
        the_manager_check_video = self.session.query(manager_check_video.ManagerCheckVideo).filter(
            manager_check_video.ManagerCheckVideo.user_id == _user_id).first()
        return the_manager_check_video

    def delete(self, _user_id, _video_id):
        the_manager_check_video = self.query_manager_check_video(_user_id)
        self.session.delete(the_manager_check_video)
        self.session.commit()


manager_check_video_dao = ManagerCheckVideoDao.get_instance()
