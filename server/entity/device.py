from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from utils import config_parser

engine = create_engine(config_parser.get_db_url())
Base = declarative_base(engine)


# 门禁设备
class Device(Base):
    __tablename__ = "device"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)


Base.metadata.drop_all(bind=engine)
Base.metadata.create_all(engine)
