from django.urls import path, include
from rest_framework import routers

from . import views

router = routers.DefaultRouter()
router.register(r'boards', views.BoardViewSet)

urlpatterns = [
    path('', include(router.urls)),
 
    path('board/', views.board_list),
    path('board/<int:pk>', views.board_detail),
    path('board/<int:pk>/cmd/<str:cmd>', views.board_command),
    path('board_switchs/<int:pk>', views.board_switchs),
    path('board/<int:pk>/vars', views.board_vars),

    path('switchType/', views.switch_type_list),
    path('switch/<int:pk>', views.switch_detail),
    path('switch/<int:pk>/cmd/<str:cmd>', views.switch_command),
    path('switch/<int:pk>/calibrate', views.switch_calibrate),
    path('seme/', views.semenzario_api),

    path('switch/<int:pk>', views.switch_detail),

    path('var/<int:pk>/cmd/<str:cmd>', views.var_command),
    path('var/<int:pk>', views.var_manage),

    path('lab/<str:cmd>', views.lab_manage),

    

]

#urlpatterns = [
#    path('', views.index, name='index'),
#    path('boards', views.board_list, name='boards'),
#    path('board_set/<int:board_id>', views.board_set, name='board_set'),
#]