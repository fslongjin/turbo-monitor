import configparser
import os


def get_path():
    current_path = os.path.abspath(__file__)
    print(os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep), 'config.ini'))
    return os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep), 'config.ini')


def get_config(config_file=get_path()):
    parser = configparser.ConfigParser()
    parser.read(config_file)
    _conf_strings = [(key, str(value)) for key, value in parser.items('config')]

    return dict(_conf_strings)


def get_db_url():
    HOSTNAME = 'dorm.mysite.ink'  # mysql数据库服务器的地址,这里以本机地址为例
    PORT = '33060'  # 默认端口3306
    USERNAME = 'turbo-monitor-dev'  # 登录数据库的用户,这里以'root'用户为例
    PASSWORD = '147258369'  # 登录数据库的密码 (这里写的是明码,注意在具体开发的时候应该不能这么干,后续想想怎么处理)
    DATABASE = 'turbo-monitor-dev'  # 选中数据库
    DB_URI = 'mysql+pymysql://{}:{}@{}:{}/{}'.format(USERNAME, PASSWORD, HOSTNAME, PORT,
                                                     DATABASE)  # 对数据库配置参数进行结构化(这里的结构适用于sqlalchemy)
    return DB_URI;
