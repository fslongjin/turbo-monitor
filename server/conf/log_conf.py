import os

LOG_FILE_PATH = "./logs/turbo-monitor-server.log"

# 自动创建日志文件夹
if not os.path.exists(LOG_FILE_PATH):
    if not os.path.exists(os.path.dirname(LOG_FILE_PATH)):
        os.makedirs(os.path.dirname(LOG_FILE_PATH))
    open(LOG_FILE_PATH, 'w').close()

LOG_CONFIG = {
    'version': 1,

    "formatters": {
        "standard": {
            "format": "[%(asctime)s] [%(process)d] [%(thread)d] [%(levelname)s] %(filename)s[%(lineno)d] : %(message)s"
        },
    },
    "handlers": {
        "default": {
            "level": "INFO",
            "class": "logging.StreamHandler",
            "formatter": "standard",
            "stream": "ext://sys.stdout"
        },
    },
    "loggers": {
        "": {
            "handlers": ["default"],
            "level": "INFO"
        },
        "LOG2FILE": {
            "handlers": ["default"],
            "level": "INFO"
        },
    }
}
