from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

from entity import car, video

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 记录人员出现在录像中的数据
class CarInVideo(Base):
    __tablename__ = "car_in_video"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 车辆信息
    car_id = Column(Integer, ForeignKey(car.Car.id, ondelete="RESTRICT"))
    # 录像编号
    video_id = Column(Integer, ForeignKey(video.Video.id, ondelete="RESTRICT"))

    def __repr__(self):
        _id = self.id
        _car_id=self.car_id
        _video_id=self.video_id
        return f"CarInVideo: id:{_id}, car_id:{_car_id}, video_id:{_video_id}"