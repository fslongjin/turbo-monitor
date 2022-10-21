import threading

from dao import base_bao
from entity import car_in_video


class CarInVideoDao(base_bao.CarInVideoDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with CarInVideoDao.__init_lock:
            if not self.__instance:
                self.__instance = CarInVideoDao()
            return self.__instance

    def add_car_in_video(self, _car_id, _video_id):
        new_car_in_video = car_in_video.CarInVideo(car_id=_car_id, video_id=_video_id)
        self.session.add(new_car_in_video)
        self.session.commit()

    def query_cars_by_video_id(self, _video_id):
        the_cars = self.session.query(car_in_video.CarInVideo).filter(
            car_in_video.CarInVideo.video_id == _video_id).all()
        return the_cars

    def query_videos_by_car_id(self, _car_id):
        the_videos = self.session.query(car_in_video.CarInVideo).filter(
            car_in_video.CarInVideo.car_id == _car_id).all()
        return the_videos

    def query_record_by_car_and_video(self, _car_id, _video_id):
        the_record = self.session.query(car_in_video.CarInVideo).filter(
            car_in_video.CarInVideo.car_id == _car_id, car_in_video.CarInVideo.video_id == _video_id).first()
        return the_record

    def delete_record_by_car_and_video(self, _car_id, _video_id):
        the_record = self.query_record_by_car_and_video(_car_id, _video_id)
        self.session.delete(the_record)
        self.session.commit()


car_in_video_dao = CarInVideoDao.get_instance()
