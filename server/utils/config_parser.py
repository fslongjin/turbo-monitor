import configparser
import os

def get_path():
    current_path=os.path.abspath(__file__)
    print(os.path.join(os.path.abspath(os.path.dirname(current_path)+os.path.sep),'config.ini'))
    return os.path.join(os.path.abspath(os.path.dirname(current_path)+os.path.sep),'config.ini')

def get_config(config_file=get_path()):
    parser = configparser.ConfigParser()
    parser.read(config_file)
    _conf_strings = [(key, str(value)) for key, value in parser.items('config')]

    return dict(_conf_strings )