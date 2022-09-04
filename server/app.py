from fastapi import FastAPI, APIRouter
from controller.HelloWorldController import HelloWorldController


app = FastAPI()

# 初始化HelloWorldController实例
helloworld_controller = HelloWorldController(APIRouter(prefix="/helloworld", tags=["custom"]))
# 将HelloWorldController中的路由注册到app中
app.include_router(helloworld_controller.router)


@app.get("/")
async def root():
    return {"message": "This is turbo-monitor's server"}

