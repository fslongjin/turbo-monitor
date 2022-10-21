from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

engine = create_engine(get_url.get_db_url())
Base = declarative_base(engine)


# 事件
class Event(Base):
    __tablename__ = 'event'

    # 编号
    id = Column(Integer, primary_key=True, autoincrement=True)
    # 时间
    date = Column(String(length=20), nullable=False)
    # 类型
    type = Column(String(length=20), nullable=False)
    # 描述
    description = Column(String(length=100))

    def __repr__(self):
        _id = self.id
        _date=self.date
        _type=self.type
        _description=self.description
        return f"Event: id:{_id}, date:{_date}, type:{_type}, description:{_description}"