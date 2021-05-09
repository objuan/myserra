# chat/routing.py
from django.urls import re_path

from . import ws_service

websocket_urlpatterns = [
    re_path(r'ws/log/', ws_service.LogConsumer.as_asgi()),
    re_path(r'ws/connection/', ws_service.ConnectionConsumer.as_asgi()),
    re_path(r'ws/switch/', ws_service.SWEventConsumer.as_asgi()),
    re_path(r'ws/var/', ws_service.VarEventConsumer.as_asgi()),
    #re_path(r'ws/log/(?P<room_name>\w+)/$', consumers.LogConsumer.as_asgi()),
]