from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import person, video

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 记录人员出现在录像中的数据
class PersonInVideo(Base):
    __tablename__ = "person_in_video"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 人员信息
    person_id = Column(Integer, ForeignKey(person.Person.id, ondelete="RESTRICT"))
    # 录像编号
    video_id = Column(Integer, ForeignKey(video.Video.id, ondelete="RESTRICT"))

    def __repr__(self):
        _id = self.id
        _person_id = self.person_id
        _video_id = self.video_id
        return f"PersonInVideo: id:{_id}, person_id:{_person_id}, video_id:{_video_id}"
