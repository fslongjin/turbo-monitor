from utils import config_parser


def get_db_url():
    config = config_parser.get_config()
    DB_URI = 'mysql+pymysql://{}:{}@{}:{}/{}'.format(config['config']['mysql_user'],
                                                     config['config']['mysql_password'],
                                                     config['config']['mysql_host'],
                                                     config['config']['mysql_port'],
                                                     config['config']['mysql_database'])
    return DB_URI;
