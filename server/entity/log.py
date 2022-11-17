from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 日志信息
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

    def __repr__(self):
        _id = self.id
        _level = self.level
        _content = self.content
        _created_time = self.created_time
        return f"Log: id:{_id}, level:{_level}, content:{_content}, created_time:{_created_time}"
