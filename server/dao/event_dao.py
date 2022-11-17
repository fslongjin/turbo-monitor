import threading
import time

from dao import base_bao
from entity import event


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

    def query_event_by_date_and_type(self, _date, _type):
        the_events = self.session.query(event.Event).filter(event.Event.date == _date, event.Event.type == _type).all()
        return the_events

    def query_event_by_date(self, _date):
        the_events = self.session.query(event.Event).filter(event.Event.date == _date).all()
        return the_events

    def query_event_by_type(self, _type):
        the_events = self.session.query(event.Event).filter(event.Event.type == _type).all()
        return the_events

    def query_event_by_id(self, _id):
        the_event = self.session.query(event.Event).filter(event.Event.id == _id).first()
        return the_event

    def update_description(self, _id, _description):
        the_event = self.query_event_by_id(_id)
        the_event.description = _description
        self.session.commit()

    def delete_event(self, _id):
        the_event = self.query_event_by_id(_id)
        self.session.delete(the_event)
        self.session.commit()

    def get_video_list_by_id(self, _id):
        the_event = self.query_event_by_id(_id)
        return the_event.videos


event_dao = EventDao.get_instance()
