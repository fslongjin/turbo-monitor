from dao import base_bao
from entity import car
import time
import threading


class CarDao(base_bao.CarDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with CarDao.__init_lock:
            if not self.__instance:
                self.__instance = CarDao()
            return self.__instance

    def add_car(self, _number, _device_id):
        new_car = car.Car(number=_number, device_id=_device_id)
        self.session.add(new_car)
        self.session.commit

    def query_car(self, _number):
        the_car = self.session.query(car.Car).filter(car.Car.number == _number).first()
        return the_car

    def update_car_device_id(self, _number, _device_id):
        the_car = self.query_car(_number)
        the_car.device_id=_device_id
        self.session.commit

    def delete_car(self, _number):
        the_car = self.query_car(_number)
        self.session.delete(the_car)
        self.session.commit



car_dao = CarDao.get_instance()