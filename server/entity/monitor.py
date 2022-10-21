from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 监控设备
class Monitor(Base):
    __tablename__ = 'monitor'

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 名称
    name = Column(String(length=20), nullable=False, unique=True)

# Base.metadata.drop_all(engine)
# Base.metadata.create_all(engine)
