import threading

from dao import base_bao
from entity import person_in_video


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
        new_person_in_video = person_in_video.PersonInVideo(video_id=_video_id, person_id=_person_id)
        self.session.add(new_person_in_video)
        self.session.commit()

    def query_persons_by_video_id(self, _video_id):
        the_persons = self.session.query(person_in_video.PersonInVideo).filter(
            person_in_video.PersonInVideo.video_id == _video_id).all()
        return the_persons

    def query_videos_by_person_id(self, _person_id):
        the_videos = self.session.query(person_in_video.PersonInVideo).filter(
            person_in_video.PersonInVideo.person_id == _person_id).all()
        return the_videos

    def query_record_by_person_and_video(self, _car_id, _video_id):
        the_record = self.session.query(person_in_video.PersonInVideo).filter(
            person_in_video.PersonInVideo.person_id == _car_id,
            person_in_video.PersonInVideo.video_id == _video_id).first()
        return the_record

    def delete_record_by_car_and_video(self, _person_id, _video_id):
        the_record = self.query_record_by_person_and_video(_person_id, _video_id)
        self.session.delete(the_record)
        self.session.commit()


person_in_video_dao = PersonInVideoDao.get_instance()
