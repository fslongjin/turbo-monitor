from fastapi import FastAPI, APIRouter
from controller.HelloWorldController import HelloWorldController
from controller.SrsController import SRSController
from controller.VideoController import VideoController
from service.LogService import log_service

app = FastAPI()

# 初始化Controller实例
helloworld_controller = HelloWorldController(APIRouter(prefix="/api/v1/helloworld", tags=["custom"]))
srs_controller = SRSController(APIRouter(prefix="/api/v1/srs", tags=["custom"]))
video_controller = VideoController(APIRouter(prefix="/api/v1/video", tags=["custom"]))

# 将Controller中的路由注册到app中
app.include_router(helloworld_controller.router)
app.include_router(srs_controller.router)
app.include_router(video_controller.router)

@app.get("/")
async def root():
    log_service.info("Hello World!")
    return {"message": "This is turbo-monitor's server"}

