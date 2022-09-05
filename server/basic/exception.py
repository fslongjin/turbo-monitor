import functools
import cherrypy

def exception_decoratord(func):
    @functools.wraps(func)
    def wrapper(*args, **kw):
        try:
            return func(*args, **kw)
        except ServiceException as e:
            raise cherrypy.HTTPError(e.code, e.message)

    return wrapper


class DaoException(Exception):
    def __init__(self, code, message):
        self.code = code
        self.message = message

    def __str__(self):
        return self.message


class ServiceException(Exception):
    def __init__(self, code, message):
        self.code = code
        self.message = message

    def __str__(self):
        return self.message

class ControllerException(Exception):
    def __int__(self, code, message):
        self.code = code
        self.message = message

    def __str__(self):
        return self.message