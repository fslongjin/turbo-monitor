from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import device

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 车辆信息
class Car(Base):
    __tablename__ = "car"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 车牌号
    number = Column(String(length=20), nullable=False)
    # 设别本车辆的门禁设备
    device_id = Column(Integer, ForeignKey(device.Device.id, ondelete="RESTRICT"))

    # relationship属性

    # 识别设备
    devices = relationship('Device', backref='cars')
    # 出现的录像
    videos = relationship('Video', backref='cars')


Base.metadata.drop_all(bind=engine)
Base.metadata.create_all(engine)
