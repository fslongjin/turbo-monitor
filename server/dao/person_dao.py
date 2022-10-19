from dao import base_bao
from entity import person
import time
import threading


class PersonDao(base_bao.BaseDao):
    # 单例模式
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    def get_instance(self):
        with PersonDao.__init_lock:
            if not self.__instance:
                self.__instance = PersonDao()
            return self.__instance

    def add_person(self, _face_information, _device_id):
        new_person=person.Person(face_information=_face_information, device_id=_device_id)
        self.session.add(new_person)
        self.session.commit()

    def query_person(self, _face_information):
        the_person=self.session.query(person.Person).filter(person.Person.face_information==_face_information).first()
        return the_person

    def update_person_face_information(self, _face_information):
        the_person=self.session.query(_face_information)
        the_person.face_information=_face_information
        self.session.commit()

    def update_person_device_id(self, _device_id):
        the_person=self.session.query(_device_id)
        the_person.device_id=_device_id
        self.session.commit()

    def delete_person(self, _face_information, _device_id):
        the_person=self.session.query(_device_id)
        self.session.delete(the_person)
        self.session.commit()

person_dao = PersonDao.get_instance()