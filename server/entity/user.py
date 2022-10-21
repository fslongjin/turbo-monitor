from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, ForeignKey
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, relationship
from dao import get_url

engine = create_engine(get_url.get_db_url())
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

    def __repr__(self):
        _id = self.id
        _account=self.account
        _name=self.name
        _last_time=self.last_time
        return f"User: id:{_id}, account:{_account}, name:{_name},last_time={_last_time}"
