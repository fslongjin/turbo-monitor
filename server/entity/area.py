from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey, Table
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import monitor

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 检测区域
class Area(Base):
    __tablename__ = 'area'

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 名称
    name = Column(String(length=20), nullable=False, unique=True)
    # 所在的视频源monitor编号
    monitor_id = Column(Integer, ForeignKey(monitor.Monitor.id))

    # relationship属性

    # 所在的monitor
    monitors = relationship('Monitor', backref='areas')

    def __repr__(self):
        _id = self.id
        _monitor_id = self.monitor_id
        return f"Area: id:{_id}, monitor_id:{_monitor_id}"
