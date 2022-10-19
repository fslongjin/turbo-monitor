from dao import base_bao
from entity import area
import time
import threading


class AreaDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with AreaDao.__init_lock:
            if not self.__instance:
                self.__instance = AreaDao()
            return self.__instance

    def add_area(self, _monitor_id):
        new_area = area.Area(monitor_id=_monitor_id)
        self.session.add(new_area)
        self.session.commit()

    def query_area(self, _monitor_id):
        the_area = self.session.query(area.Area).filter(area.Area.monitor_id == _monitor_id).first()
        return the_area

    def delete_area(self, _monitor_id):
        the_area=self.query_area(_monitor_id)
        self.session.delete(the_area)
        self.session.commit

area_dao=AreaDao.get_instance()