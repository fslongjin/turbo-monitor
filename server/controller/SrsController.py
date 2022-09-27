from fastapi import APIRouter
from service.SrsService import srs_service

class SRSController:
    def __init__(self, router: APIRouter):
        self.router = router
        self.router.add_api_route("/", self.GET, methods=["GET"])

    def GET(self):
        return {"message": "Hello World"}
