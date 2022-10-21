from dao import base_bao
from entity import manager
import time
import threading


class ManagerDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with ManagerDao.__init_lock:
            if not self.__instance:
                self.__instance = ManagerDao()
            return self.__instance

    def add_manager(self, _account, _password, _name, _last_time):
        new_manager = manager.Manager(account=_account, password=_password, name=_name,
                                      last_time=time.strftime('%Y-%m-%d %H:%M:%S', time.localtime()))
        self.session.add(new_manager)
        self.session.commit()

    def query_manager_by_account(self, _account):
        the_manager = self.session.query(manager.Manager).filter(manager.Manager.account == _account).first()
        return the_manager

    def update_manager_last_time(self, _account):
        the_manager = self.query_manager_by_account(_account)
        the_manager.last_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
        self.session.commit()

    def update_manager_name(self, _account, _name):
        the_manager = self.query_manager_by_account(_account)
        the_manager.name = _name
        self.session.commit()

    def update_manager_password(self, _account, _password):
        the_manager = self.query_manager_by_account(_account)
        the_manager.password = _password
        self.session.commit()

    def delete_manager(self, _account):
        the_manager = self.query_manager_by_account(_account)
        self.session.delete(the_manager)
        self.session.commit()

    def check_manager_password(self, _account, _password):
        the_manager = self.query_manager_by_account(_account)
        if the_manager.password == _password:
            return True
        else:
            return False

    def query_manager_id_by_account(self, _account):
        the_manager = self.query_manager_by_account(_account)
        return the_manager.id


manager_dao = ManagerDao.get_instance()
