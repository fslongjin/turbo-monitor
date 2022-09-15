from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from utils import config_parser

engine = create_engine(config_parser.get_db_url())
Base = declarative_base(engine)


# 车辆信息
class Log(Base):
    __tablename__ = "log"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 等级
    level = Column(Integer, nullable=False)
    # 内容
    content = Column(String(length=100), nullable=False)
    # 创建时间
    created_time = Column(String(length=20), nullable=False)


Base.metadata.drop_all(bind=engine)
Base.metadata.create_all(engine)
