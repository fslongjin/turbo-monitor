import threading

from dao import base_bao
from entity import device


class DeviceDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with DeviceDao.__init_lock:
            if not self.__instance:
                self.__instance = DeviceDao()
            return self.__instance

    def add_device(self, _name):
        new_device = device.Device(name=_name)
        self.session.add(new_device)
        self.commit()

    def query_device_by_name(self, _name):
        the_device = self.session.query(device.Device).filter(device.Device.name == _name).first()
        return the_device

    def get_persons_list_by_name(self, _name):
        the_device = self.query_device_by_name(_name)
        return the_device.persons

    def get_cars_list_by_name(self, _name):
        the_device = self.query_device_by_name(_name)
        return the_device.cars


device_dao = DeviceDao.get_instance()
