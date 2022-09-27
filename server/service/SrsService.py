import threading

import utils.config_parser
from service.LogService import log_service


class SrsService(object):
    """
    SRS服务类（单例）
    """
    __instance = None

    # 初始化锁
    __init_lock = threading.Lock()

    @classmethod
    def get_instance(cls):
        with SrsService.__init_lock:
            if not cls.__instance:
                cls.__instance = SrsService()
            return cls.__instance

    def __init__(self):
        pass

    def generate_srs_config(self):
        log_service.info("Generating SRS config file")
        conf = utils.config_parser.get_config()["srs"]
        srs_config = r"""
# 该文件由Turbo-Monitor自动生成，请勿手动修改
listen              %s;
max_connections     1000;
# For docker, please use docker logs to manage the logs of SRS.
# See https://docs.docker.com/config/containers/logging/
srs_log_tank        console;
daemon              off;
http_api {
    enabled         on;
    listen          1985;
}
http_server {
    enabled         on;
    listen          8080;
    dir             ./objs/nginx/html;
}
rtc_server {
    enabled on;
    listen 8000;
    # @see https://ossrs.net/lts/zh-cn/docs/v4/doc/webrtc#config-candidate
    candidate $CANDIDATE;
}
vhost __defaultVhost__ {
    hls {
        enabled         on;
    }
    http_remux {
        enabled     on;
        mount       [vhost]/[app]/[stream].flv;
    }
    rtc {
        enabled     on;
        # @see https://ossrs.net/lts/zh-cn/docs/v4/doc/webrtc#rtmp-to-rtc
        rtmp_to_rtc on;
        # @see https://ossrs.net/lts/zh-cn/docs/v4/doc/webrtc#rtc-to-rtmp
        rtc_to_rtmp on;
    }

    dvr{
        enabled	%s; # 是否开启录制
        dvr_apply       all;
        dvr_plan        segment;
        #推流结束后生成flv
        #dvr_path        ./objs/nginx/html/[app]/[stream].[timestamp].flv;
        dvr_path ./objs/nginx/html/[app]/[stream]/[2006]/[01]/[02]/[15].[04].[05].[999].flv;
         dvr_duration    %s;
         dvr_wait_keyframe       on;
        time_jitter             full;
    }		

    http_hooks {
        enabled         %s;
        on_publish      https://127.0.0.1:8085/api/v1/streams;
        on_unpublish    https://127.0.0.1:8085/api/v1/streams;
        on_play         https://127.0.0.1:8085/api/v1/sessions;
        on_stop         https://127.0.0.1:8085/api/v1/sessions;
        on_dvr          https://127.0.0.1:8085/api/v1/dvrs;
        on_hls          https://127.0.0.1:8085/api/v1/hls;
        on_hls_notify   https://127.0.0.1:8085/api/v1/hls/[app]/[stream]/[ts_url][param];
    }
}

        """ % (conf['port'], conf['dvr'], conf['dvr_duration'], conf['http_hooks'])

        with open("./conf/srs.conf", "w") as f:
            f.write(srs_config)
        log_service.info("SRS config file generated")


srs_service = SrsService.get_instance()
