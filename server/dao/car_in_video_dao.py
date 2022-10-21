from dao import base_bao
from entity import car_in_video
import time
import threading


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

    def query_car_in_video(self, _video_id):
        the_car_in_video = self.session.query(car_in_video.CarInVideo).filter(
            car_in_video.CarInVideo.video_id == _video_id).first()
        return the_car_in_video

    def delete_car_in_video(self, _video_id, _car_id):
        the_car_in_video = self.query_car_in_video(_car_id)
        self.session.delete(the_car_in_video)
        self.session.commit()


car_in_video_dao = CarInVideoDao.get_instance()
