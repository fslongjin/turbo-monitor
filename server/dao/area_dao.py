import threading

from dao import base_bao
from entity import area


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

    def add_area(self, _name, _monitor_id):
        new_area = area.Area(name=_name, monitor_id=_monitor_id)
        self.session.add(new_area)
        self.session.commit()

    def query_area_by_name(self, _name):
        the_area = self.session.query(area.Area).filter(area.Area.name == _name).first()
        return the_area

    def delete_area_by_name(self, _name):
        the_area = self.query_area_by_name(_name)
        self.session.delete(the_area)
        self.session.commit()

    def get_monitor_obj_by_name(self, _name):
        the_area = self.query_area_by_name(_name)
        return the_area.monitors


area_dao = AreaDao.get_instance()
