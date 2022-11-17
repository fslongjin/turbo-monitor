import threading
import time

from dao import base_bao
from entity import log


class LogDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with LogDao.__init_lock:
            if not self.__instance:
                self.__instance = LogDao()
            return self.__instance

    def add_log(self, _level, _content, _created_time):
        new_log = log.Log(level=_level, content=_content,
                          create_time=time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
        self.session.add(new_log)
        self.session.commit()

    def query_log_by_id(self, _id):
        the_log = self.session.query(log.Log).filter(log.Log.id == _id).first()
        return the_log

    def query_logs_by_level(self, _level):
        the_logs = self.session.query(log.Log).filter(log.Log.level == _level).all()
        return the_logs

    def delete_log(self, _id, _create_time):
        the_log = self.query_log_by_id(_id)
        self.session.delete(the_log)
        self.session.commit()


log_dao = LogDao.get_instance()
