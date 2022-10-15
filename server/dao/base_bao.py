from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from dao import get_url


class BaseDao(object):

    def __init__(self):
        self.engine = create_engine(get_url.get_db_url())
        self.Base = declarative_base(self.engine)
        self.Session = sessionmaker(bind=self.engine)
        self.session = self.Session()

    # 异常处理
