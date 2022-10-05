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
