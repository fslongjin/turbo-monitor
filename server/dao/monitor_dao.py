import threading

from dao import base_bao
from entity import monitor


class MonitorDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with MonitorDao.__init_lock:
            if not self.__instance:
                self.__instance = MonitorDao()
            return self.__instance

    def add_monitor(self, _name):
        new_monitor = monitor.Monitor(name=_name)
        self.session.add(new_monitor)
        self.session.commit()

    def query_monitor_by_name(self, _name):
        the_monitor = self.session.query(monitor.Monitor).filter(monitor.Monitor.name == _name).first()
        return the_monitor

    def get_video_list_by_name(self, _name):
        the_monitor = self.query_monitor_by_name(_name)
        return the_monitor.videos

    def get_area_list_by_name(self, _name):
        the_monitor = self.query_monitor_by_name(_name)
        return the_monitor.areas


device_dao = MonitorDao.get_instance()
