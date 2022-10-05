import configparser
import os


def get_config(config_file=os.path.join(os.getcwd(), "conf/conf.ini")):
    parser = configparser.ConfigParser()
    # print(config_file)
    parser.read(config_file, encoding='utf-8')
    _conf_strings = [(key, str(value)) for key, value in parser.items('config')]
    _srs_conf_strings = [(key, str(value)) for key, value in parser.items('srs')]
    return {
        'config': dict(_conf_strings),
        'srs': dict(_srs_conf_strings)
    }
