from rest_framework import serializers
from centralina.models import Board ,Switch,SwitchType,Variable
from datetime import datetime

class BoardSerializer(serializers.ModelSerializer):
    #name = serializers.CharField(max_length=50, allow_blank=False)
    #description = serializers.CharField(max_length=100, allow_blank=False)

    def create(self, validated_data):
        """
        Create and return a new `Snippet` instance, given the validated data.
        """
        return Board.objects.create(**validated_data)

    def update(self, instance, validated_data):
        """
        Update and return an existing `Snippet` instance, given the validated data.
        """
        print(validated_data)
        instance.name = validated_data.get('name', instance.name)
        instance.description = validated_data.get('description', instance.description)
        instance.usb_address_win = validated_data.get('usb_address_win', instance.usb_address_win)
        instance.usb_address_lx = validated_data.get('usb_address_lx', instance.usb_address_lx)
        instance.net_address = validated_data.get('net_address', instance.net_address)
        instance.wifi_name = validated_data.get('wifi_name', instance.wifi_name)
        instance.cpu_type = validated_data.get('cpu_type', instance.cpu_type)
        instance.enable_cpu = validated_data.get('enable_cpu', instance.enable_cpu)
        instance.save()
        return instance

    class Meta:
        model = Board
        fields = ['id','name','description','cpu_type','usb_address_win','usb_address_lx','net_address','wifi_name','enable_cpu']


class SwitchTypeSerializer(serializers.ModelSerializer):
 
    #open_value = serializers.NullBooleanField()

    class Meta:
        model = SwitchType
        fields = ['id','name','description','voltage','mode']

class SwitchSerializer(serializers.ModelSerializer):
 
    #on_hi = serializers.NullBooleanField()
    #voltage = serializers.CharField(max_length=50, allow_blank=False)
    switchType = SwitchTypeSerializer()

    def update(self, instance, validated_data):
        """
        Update and return an existing `Snippet` instance, given the validated data.
        """
        instance.name = validated_data.get('name', instance.name)
        instance.description = validated_data.get('description', instance.description)
        instance.pin = validated_data.get('pin', instance.pin)
        #instance.on_hi = validated_data.get('on_hi', instance.on_hi)
        _switchType = validated_data.get('switchType')
        #print(validated_data)
        #print(_switchType)
        #nn = s["name"]
        #print(nn)
        
        sw = SwitchType.objects.get(name=_switchType["name"])
        #print(sw.id)
        instance.switchType = sw
        instance.save() 
        
        return instance

    class Meta:
        model = Switch
        fields = ['id','name','description','pin','state','switchType','pin_value']


class VariableSerializer(serializers.ModelSerializer):
 
   
    def update(self, instance, validated_data):
        print (validated_data)
        """
        Update and return an existing `Snippet` instance, given the validated data.
        """
        instance.name = validated_data.get('name', instance.name)
        instance.description = validated_data.get('description', instance.description)
        instance.pin = validated_data.get('pin', instance.pin)
        instance.value = validated_data.get('value', instance.value)
        instance.varType = validated_data.get('varType', instance.varType)
        instance.saveMode = validated_data.get('saveMode', instance.saveMode)
        instance.startupMode = validated_data.get('startupMode', instance.startupMode)
       
        print (instance)
        instance.save() 
        
        return instance

    class Meta:
        model = Variable
        fields = ['id','name','description','pin','value','varType','saveMode','startupMode']

############### LAB ##########
'''class WaterAnalysisSerializer(serializers.ModelSerializer):
    def update(self, instance, validated_data):

class WaterAnalysis(models.Model):
    tank=models.CharField(max_length=20)
    ph =models.FloatField(default=0)
    ec=models.FloatField(default=0)
    temperature = models.FloatField(default=0)
    time = models.DateTimeField(primary_key=True, default=datetime.now)
'''