from fastapi import APIRouter


class HelloWorldController:
    def __init__(self, router: APIRouter):
        self.router = router
        self.router.add_api_route("/", self.GET, methods=["GET"])

    def GET(self):
        return {"message": "Hello World"}
