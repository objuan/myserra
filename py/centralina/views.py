from django.shortcuts import render
from .models import *
from centralina.logic.Semenzario import *
from django.http import HttpResponse, JsonResponse
from centralina.serializers import *
from rest_framework import viewsets
from rest_framework import permissions
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from .logic import *
from .config import *

import urllib.request

#from django_socketio import events

from .runtime_service import BoardManager
from .arduino_service import ArduinoManager,getClient

def index(request):
    latest_question_list = Board.objects.order_by('-name')[:5]
    context = {'latest_question_list': latest_question_list}
    return render(request, 'centralina/index.html', context)

def board_set(request,board_id):
    request.session['board'] = board_id
    return HttpResponse("OK")

def board_list(request):
    latest_board_list = Board.objects.order_by('-name')[:5]
    context = { 'latest_board_list' : latest_board_list }
    return render(request, 'centralina/board_list.html', context)


class BoardViewSet(viewsets.ModelViewSet):
    permission_classes = [permissions.AllowAny]

    """
    API endpoint that allows notes to be viewed or edited.
    """
    queryset = Board.objects.all()
    serializer_class = BoardSerializer

@csrf_exempt
def board_list(request):
    """
    List all code snippets, or create a new snippet.
    """
    if request.method == 'GET':
        boards = Board.objects.all()
        serializer = BoardSerializer(boards, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        #print(data)
        serializer = BoardSerializer(data=data)
        #print(serializer)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)

@csrf_exempt
def board_command(request, pk,cmd):
    #print ("Command", cmd)
    if request.method == 'GET':

        try:
            board = Board.objects.get(pk=pk)
        except Board.DoesNotExist:
            return HttpResponse(status=404)
        board.command(cmd)
        serializer = BoardSerializer(board)
        return JsonResponse(serializer.data)
    else:
        return HttpResponse(status=404)

@csrf_exempt
def board_detail(request, pk):
    """
    Retrieve, update or delete a code snippet.
    """
    try:
        board = Board.objects.get(pk=pk)
    except Board.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = BoardSerializer(board)
        return JsonResponse(serializer.data)

    elif request.method == 'PUT':
        try:
            board = Board.objects.get(pk=pk)
        except Board.DoesNotExist:
            return HttpResponse(status=404)

        data = JSONParser().parse(request)
        #print(board)
        #print(data)
        serializer = BoardSerializer(board, data=data)
        if serializer.is_valid():
            serializer.save()
            #print("dsa")
            return JsonResponse(serializer.data)
        return JsonResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        board.delete()
        return HttpResponse(status=204)



@csrf_exempt
def switch_type_list(request):
    """
   
    """
    if request.method == 'GET':
        sw = SwitchType.objects.all()
        serializer = SwitchTypeSerializer(sw, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        data = JSONParser().parse(request)
        #print(data)
        serializer = SwitchSerializer(data=data)
        #print(serializer)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)

@csrf_exempt
def board_switchs(request,pk):
    """
   
    """
    if request.method == 'GET':
        try:
            board = Board.objects.get(pk=pk)
        except Board.DoesNotExist:
            return HttpResponse(status=404)

        #boards = Switch.objects.filter(board.id=pk)
        serializer = SwitchSerializer(board.switch_set, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        # new switch
              
        data = JSONParser().parse(request)
        try:
            board = Board.objects.get(pk=pk)
        except Board.DoesNotExist:
            return HttpResponse(status=404)

        sw = SwitchType.objects.get(id=1)

        added = board.switch_set.create( name='default' , switchType = sw) 

        serializer = SwitchSerializer(added)

        return JsonResponse(serializer.data)
        '''
        print("kk")
        data = JSONParser().parse(request)
        print(data)
        serializer = SwitchSerializer(data=data)
        #print(serializer)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)
        '''


@csrf_exempt
def switch_detail(request, pk):
    
    """
    Retrieve, update or delete a code snippet.
    """
    try:
        switch = Switch.objects.get(pk=pk)
    except Switch.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = SwitchSerializer(switch)
        return JsonResponse(serializer.data)

    elif request.method == 'PUT':
        print("pu")
        data = JSONParser().parse(request)
        print(str(data))
        serializer = SwitchSerializer(switch, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data)
        return JsonResponse(serializer.errors, status=400)

    elif request.method == 'DELETE':
        switch.delete()
        return HttpResponse(status=204)

@csrf_exempt
def switch_command(request, pk,cmd):
    ("switch "+str(pk)+" " +cmd)
    try:
        switch = Switch.objects.get(pk=pk)
    except Switch.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        switch.command(cmd)
        #switch = Switch.objects.get(pk=pk)
        serializer = SwitchSerializer(switch)
        #if serializer.is_valid():
            #serializer.save()
        return JsonResponse(serializer.data)
        #return JsonResponse(serializer.errors, status=400)
    else:
        return HttpResponse(status=404)

'''
@events.on_message(channel="^light")
def message(request, socket, message):
    #import pdb; pdb.set_trace()
    print("message",message)
'''


@csrf_exempt
def board_vars(request,pk):
    """
    """
    if request.method == 'GET':
        try:
            board = Board.objects.get(pk=pk)
        except Board.DoesNotExist:
            return HttpResponse(status=404)

        serializer = VariableSerializer(board.variable_set, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        # new switch
              
        data = JSONParser().parse(request)
        try:
            board = Board.objects.get(pk=pk)
        except Board.DoesNotExist:
            return HttpResponse(status=404)

     
        added = board.variable_set.create( name='default' ) 

        serializer = VariableSerializer(added)

        return JsonResponse(serializer.data)
      

@csrf_exempt
def var_command(request, pk,cmd):
    print ("var mcd"+str(pk)+" " +cmd)
    try:
        var = Variable.objects.get(pk=pk)
    except Variable.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        var.command(cmd)

        serializer = VariableSerializer(var)
     
        return JsonResponse(serializer.data)

    elif request.method == 'DELETE':
        var.delete()
        return HttpResponse(status=204)
    else:
        return HttpResponse(status=404)

@csrf_exempt
def var_manage(request, pk):
    print ("var "+str(pk))
    try:
        var = Variable.objects.get(pk=pk)
    except Variable.DoesNotExist:
        return HttpResponse(status=404)


    if request.method == 'GET':
        serializer = VariableSerializer(var)

        return JsonResponse(serializer.data)

    if request.method == 'PUT':
        print("put")
        data = JSONParser().parse(request)
      
        if (var.varType=='json'):
            j = str(data["value"])
            #j=j.replace('\'','|')
            print (j)
            data['value'] = j
        print(str(data))
        serializer = VariableSerializer(var, data=data)

        if serializer.is_valid():
            serializer.save()
            var.board.get_controller().write(var.pin,data['value'] )
            return JsonResponse(serializer.data)
        print("bad")
        return JsonResponse(serializer.errors, status=400)
    elif request.method == 'DELETE':
        var.delete()
        return HttpResponse(status=204)
    else:
        return HttpResponse(status=404)


@csrf_exempt
def lab_manage(request, cmd):
    print ("lab "+str(cmd))
   
    if request.method == 'POST':
        data = JSONParser().parse(request)
        print("post ",data)
        print (GetLab())
        GetLab().command(cmd,data)
        return HttpResponse('')


@csrf_exempt
def switch_calibrate(request, pk):
    #print ('ddddddd',pk)
    """
    Retrieve, update or delete a code snippet.
    """
    try:
        cal = LabPumpCalibrate.objects.get(id=pk)
    except LabPumpCalibrate.DoesNotExist:
        cal = LabPumpCalibrate()
        cal.id = pk
        #return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = LabPumpCalibrateSerializer(cal)
        return JsonResponse(serializer.data)

    if request.method == 'PUT': #save
        print("put")
        data = JSONParser().parse(request)
        print("put ",data)

        cal.time_secs =  data['time_secs']
        cal.calibrateType =  data['calibrateType']

        cal.filled_ml =  data['filled_ml']
        cal.ml_at_seconds =  float(cal.filled_ml)  /  float(cal.time_secs )

        #cal.filled_gr =  data['filled_gr']
        #cal.gr_at_seconds =  float(cal.filled_gr)  /  float(cal.time_secs )

        cal.save()
        #c = LabPumpCalibrate()
        # c.id = 

        return HttpResponse('')

    else:
        return HttpResponse(status=404)



@csrf_exempt
def semenzario_api(request,):
    print ('semenzario_api')
 
    try:
        if request.method == 'GET':
            sem =  Semenzario()
            sem.update()
            #serializer = LabPumpCalibrateSerializer(cal)
            return JsonResponse(sem.data, safe=False)
        else:
            return HttpResponse(status=404)
    except Board.DoesNotExist:
            return HttpResponse(status=404)

@csrf_exempt
def config_api(request,):
    print ('config_api')
 
    try:
        if request.method == 'GET':
            cfg =  getConfig()
            print(getConfig())
            #serializer = LabPumpCalibrateSerializer(cal)
            return JsonResponse(cfg, safe=False)
        elif request.method == 'POST': #save
            print("POST")
            data = JSONParser().parse(request)
            print("POST ",data)
            saveConfig(data)
            return HttpResponse('')
        else:
            return HttpResponse(status=404)
    except Board.DoesNotExist:
            return HttpResponse(status=404)


@csrf_exempt
def board_api(request):
    print ('board_api')
 
    try:
        if request.method == 'GET':
            cfg =  getConfig()
         
            print(getConfig())
            #serializer = LabPumpCalibrateSerializer(cal)
            return JsonResponse(cfg, safe=False)
        elif request.method == 'POST': #save
  
            data = JSONParser().parse(request)
            print("POST ",data,getClient())
         
            pin= getPin(data["id"],data["pin"])
           
            if (data["cmd"]== "write"):
                print(pin,str(data["val"]))

                getClient().write_raw(data["id"]+" "+str(data["pin"]),str(data["val"]))
            else:
                getClient().read_raw(data["id"]+" "+str(data["pin"]))

            #if (pin["MODE"] == "D"):
            #    getClient().write_raw(data["id"]+" "+str(data["pin"])," W D "+str(data["val"]))
            #else:
            #    getClient().write_raw(data["id"]+" W A "+ str(data["pin"]),str(data["val"]))
         
            return HttpResponse('OK')
        else:
            return HttpResponse(status=404)
    except Board.DoesNotExist:
            return HttpResponse(status=404)


