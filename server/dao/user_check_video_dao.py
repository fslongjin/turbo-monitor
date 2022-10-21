from dao import base_bao
from entity import user_check_video
import time
import threading


class UserCheckVideoDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with UserCheckVideoDao.__init_lock:
            if not self.__instance:
                self.__instance = UserCheckVideoDao()
            return self.__instance

    def add_user_check_video(self, _user_id, _video_id):
        new_user_check_video = user_check_video.UserCheckVideo(user_id=_user_id, video_id=_video_id)
        self.session.add(new_user_check_video)
        self.session.commit()

    def query_user_check_video(self, _user_id):
        the_user_check_video = self.session.query(user_check_video.UserCheckVideo).filter(
            user_check_video.UserCheckVideo.user_id == _user_id).first()
        return the_user_check_video

    def delete(self, _user_id, _video_id):
        the_user_check_video = self.query_user_check_video(_user_id)
        self.session.delete(the_user_check_video)
        self.session.commit()


user_check_video_dao = UserCheckVideoDao.get_instance()
