from django.contrib import admin

from .models import Board,Switch,SwitchType,Variable

admin.site.register(Board)
admin.site.register(Switch)
admin.site.register(SwitchType)
admin.site.register(Variable)
