from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import event, monitor

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 录像
class Video(Base):
    __tablename__ = "video"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 日期
    date = Column(String(length=20), nullable=False)
    # 视频流
    video_stream = Column(String(length=1000), nullable=False)
    # 所包含的事件
    event_id = Column(Integer, ForeignKey(event.Event.id, ondelete="RESTRICT"), nullable=True)
    # 所来自的monitor
    monitor_id = Column(Integer, ForeignKey(monitor.Monitor.id, ondelete="RESTRICT"), nullable=False)

    # relationship属性

    # 来自的视频流
    monitors = relationship('Monitor', backref='videos')
    # 包含的事件
    events = relationship('Event', backref='videos')
    # 查看的保安
    users = relationship('User', backref='videos')
    # 查看的管理员
    managers = relationship('Manager', backref='videos')
