from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import video, manager

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 管理员查看录像记录
class ManagerCheckVideo(Base):
    __tablename__ = "manager_check_video"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # manager编号
    user_id = Column(Integer, ForeignKey(manager.Manager.id, ondelete="RESTRICT"))
    # 录像编号
    video_id = Column(Integer, ForeignKey(video.Video.id, ondelete="RESTRICT"))

    def __repr__(self):
        _id = self.id
        _user_id=self.user_id
        _video_id=self.video_id
        return f"ManagerCheckVideo: id:{_id}, user_id:{_user_id}, video_id:{_video_id}"