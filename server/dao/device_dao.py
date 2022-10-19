from dao import base_bao
from entity import device
import time
import threading


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




device_dao = DeviceDao.get_instance()