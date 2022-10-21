import threading

from dao import base_bao
from entity import person


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

    def add_person(self, _name, _face_information, _device_id):
        new_person = person.Person(name=_name, face_information=_face_information, device_id=_device_id)
        self.session.add(new_person)
        self.session.commit()

    def query_person_by_face_information(self, _face_information):
        the_person = self.session.query(person.Person).filter(
            person.Person.face_information == _face_information).first()
        return the_person

    def update_person_device_id(self, _face_information, _device_id):
        the_person = self.query_person_by_face_information(_face_information)
        the_person.device_id = _device_id
        self.session.commit()

    def delete_person(self, _face_information):
        the_person = self.query_person_by_face_information(_face_information)
        self.session.delete(the_person)
        self.session.commit()

    def get_device_obj_by_face_information(self, _face_information):
        the_person = self.query_person_by_face_information(_face_information)
        return the_person.devices

    def query_person_id_by_face_information(self, _face_information):
        the_person = self.query_person_by_face_information(_face_information)
        return the_person.id


person_dao = PersonDao.get_instance()
