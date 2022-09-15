from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from utils import config_parser

engine = create_engine(config_parser.get_db_url())
Base = declarative_base(engine)


# 用户（保安）
class User(Base):
    __tablename__ = "user"

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 账号
    account = Column(String(length=20), nullable=False)
    # 密码
    password = Column(String(length=20), nullable=False)
    # 名字
    name = Column(String(length=20), nullable=False)
    # 最近登录时间
    last_time = Column(String(length=20))


Base.metadata.drop_all(bind=engine)
Base.metadata.create_all(engine)
