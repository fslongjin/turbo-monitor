import threading

from dao import base_bao
from entity import user_check_video


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

    def query_users_by_video_id(self, _video_id):
        the_users = self.session.query(user_check_video.UserCheckVideo).filter(
            user_check_video.UserCheckVideo.video_id == _video_id).all()
        return the_users

    def query_videos_by_user_id(self, _user_id):
        the_videos = self.session.query(user_check_video.UserCheckVideo).filter(
            user_check_video.UserCheckVideo.user_id == _user_id).all()
        return the_videos

    def query_record_by_user_and_video(self, _user_id, _video_id):
        the_record = self.session.query(user_check_video.UserCheckVideo).filter(
            user_check_video.UserCheckVideo.user_id == _user_id,
            user_check_video.UserCheckVideo.video_id == _video_id).first()
        return the_record

    def delete_record_by_user_and_video(self, _user_id, _video_id):
        the_record = self.query_record_by_user_and_video(_user_id, _video_id)
        self.session.delete(the_record)
        self.session.commit()


user_check_video_dao = UserCheckVideoDao.get_instance()
