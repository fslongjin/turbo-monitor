from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import user, video

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 车辆信息
class UserCheckVideo(Base):
    __tablename__ = "user_check_video"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # user编号
    user_id = Column(Integer, ForeignKey(user.User.id, ondelete="RESTRICT"))
    # 录像编号
    video_id = Column(Integer, ForeignKey(video.Video.id, ondelete="RESTRICT"))


Base.metadata.drop_all(bind=engine)
Base.metadata.create_all(engine)
