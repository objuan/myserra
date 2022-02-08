"""serra URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/3.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import include, path
from django.http import HttpResponse
from django.shortcuts import render
from serra import views

vue_urls = [
  path('', views.frontend),
  path('boardlist', views.frontend),
  path('hello', views.frontend),
  path('centralina', views.frontend),
  path('giardino', views.frontend),
  path('semenzario', views.frontend),

  path('another-path/', views.frontend),
  path('admin/', admin.site.urls),
  #path('', lambda request: HttpResponse(render(request, 'vue_index.html'))),
  #path('another-path/', lambda request: HttpResponse(render(request, 'vue_index.html'))),
]

urlpatterns = [
    path('', include(vue_urls)),
    path('api/', include('centralina.urls')),
    path('admin/', admin.site.urls),
	#path('ws/', include('django_socketio.urls')),
]
