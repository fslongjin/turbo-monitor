from dao import base_bao
from entity import log
import time
import threading


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

    def query_log(self, _level):
        the_log=self.session.query(log.Log).filter(log.Log.level==_level).first()
        return the_log

    def delete_log(self, _level, _content, _create_time):
        the_log=self.query_log(_level)
        self.session.delete(the_log)
        self.session.commit()

log_dao = LogDao.get_instance()