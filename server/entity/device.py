from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 门禁设备
class Device(Base):
    __tablename__ = "device"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 名称
    name = Column(String(length=20), unique=True)

# Base.metadata.drop_all(engine)
# Base.metadata.create_all(engine)

    def __repr__(self):
        _id = self.id
        _name=self.name
        return f"Device: id:{_id}, name{_name}"