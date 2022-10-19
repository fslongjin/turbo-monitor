from dao import base_bao
from entity import event
import time
import threading


class EventDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with EventDao.__init_lock:
            if not self.__instance:
                self.__instance = EventDao()
            return self.__instance

    def add_event(self, _date, _type, _description):
        new_event = event.Event(type=_type, description=_description,
                                date=time.strftime('%Y-%m-%d ', time.localtime()))
        self.session.add(new_event)
        self.session.commit()

    def query_event(self, _date, _type):
        the_event=self.session.query(event.Event).filter(event.Event.date==_date, event.Event.type==_type).first()
        return the_event

    def update_description(self, _date, _type, _description):
        the_event=self.query_event(_date, _type)
        the_event.description=_description
        self.session.commit()

    def delete_event(self, _date, _type, _description):
        the_event=self.query_event(_date, _type)
        self.session.delete(the_event)
        self.session.commit()

event_dao = EventDao.get_instance()