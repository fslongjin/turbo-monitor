from dao import base_bao
from entity import person_in_video
import time
import threading


class PersonInVideoDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with PersonInVideoDao.__init_lock:
            if not self.__instance:
                self.__instance = PersonInVideoDao()
            return self.__instance

    def add_person_in_video(self, _video_id, _person_id):
        new_person_in_video=person_in_video.PersonInVideo(video_id=_video_id, person_id=_person_id)
        self.session.add(new_person_in_video)
        self.session.commit()

    def query_person_in_device(self, _video_id):
        the_person_in_video=self.session.query(person_in_video.PersonInVideo).filter(person_in_video.PersonInVideo.video_id==_video_id).first()
        return the_person_in_video

    def update_person_in_video_person_id(self, _video_id, _person_id):
        the_person_in_video=self.session.query(_video_id)
        the_person_in_video.person_id = _person_id
        self.session.commit()

    def delete_person_in_video(self, _video_id):
        the_person_in_video=self.session.query(_video_id)
        self.session.delete(the_person_in_video)
        self.session.commit()

person_in_video_dao = PersonInVideoDao.get_instance()