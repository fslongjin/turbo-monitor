import logging
import logging.config
import threading
import functools

from conf.log_conf import LOG_CONFIG

# 从字典中导入日志配置
logging.config.dictConfig(LOG_CONFIG)


def stack_level_decorator(func):
    """
    The decorator to set the stack level
    """

    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        # Set the stack frame depth which begins to traceback
        if 'stacklevel' not in kwargs.keys():
            kwargs['stacklevel'] = 3
        return func(*args, **kwargs)

    return wrapper


class LogService(object):
    """
    日志服务类（单例）
    """
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    @classmethod
    def get_instance(cls):
        with LogService.__init_lock:
            if not cls.__instance:
                cls.__instance = LogService("LOG2FILE")
            return cls.__instance

    def __init__(self, name: str):
        self.log = logging.getLogger(name)

    @stack_level_decorator
    def debug(self, msg, *args, **kwargs):
        self.log.debug(msg, *args, **kwargs)

    @stack_level_decorator
    def info(self, msg, *args, **kwargs):
        self.log.info(msg, *args, **kwargs)

    @stack_level_decorator
    def warning(self, msg, *args, **kwargs):
        self.log.warning(msg, *args, **kwargs)

    @stack_level_decorator
    def error(self, msg, *args, **kwargs):
        self.log.error(msg, *args, **kwargs)

    @stack_level_decorator
    def critical(self, msg, *args, **kwargs):
        self.log.critical(msg, *args, **kwargs)

    @stack_level_decorator
    def fatal(self, msg, *args, **kwargs):
        self.log.fatal(msg, *args, **kwargs)


log_service = LogService.get_instance()
