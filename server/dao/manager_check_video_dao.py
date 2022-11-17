import threading

from dao import base_bao
from entity import manager_check_video


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

    def add_manager_check_video(self, _manager_id, _video_id):
        new_manager_check_video = manager_check_video.ManagerCheckVideo(manager_id=_manager_id, video_id=_video_id)
        self.session.add(new_manager_check_video)
        self.session.commit()

    def query_managers_by_video_id(self, _video_id):
        the_managers = self.session.query(manager_check_video.ManagerCheckVideo).filter(
            manager_check_video.ManagerCheckVideo.video_id == _video_id).all()
        return the_managers

    def query_videos_by_video_id(self, _manager_id):
        the_videos = self.session.query(manager_check_video.ManagerCheckVideo).filter(
            manager_check_video.ManagerCheckVideo.manager_id == _manager_id).all()
        return the_videos

    def query_record_by_manager_and_video(self, _manager_id, _video_id):
        the_record = self.session.query(manager_check_video.ManagerCheckVideo).filter(
            manager_check_video.ManagerCheckVideo.manager_id == _manager_id,
            manager_check_video.ManagerCheckVideo.video_id == _video_id).first()
        return the_record

    def delete_record_by_manager_and_video(self, _manager_id, _video_id):
        the_record = self.query_record_by_manager_and_video(_manager_id, _video_id)
        self.session.delete(the_record)
        self.session.commit()


manager_check_video_dao = ManagerCheckVideoDao.get_instance()
