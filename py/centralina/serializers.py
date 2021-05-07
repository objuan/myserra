from rest_framework import serializers
from centralina.models import Board ,Switch,SwitchType

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
        instance.name = validated_data.get('name', instance.name)
        instance.description = validated_data.get('description', instance.description)
        instance.usb_address = validated_data.get('usb_address', instance.usb_address)
        instance.net_address = validated_data.get('net_address', instance.net_address)
        instance.wifi_name = validated_data.get('wifi_name', instance.wifi_name)
        instance.cpu_type = validated_data.get('cpu_type', instance.cpu_type)
        instance.save()
        return instance

    class Meta:
        model = Board
        fields = ['id','name','description','cpu_type','usb_address','net_address','wifi_name']


class SwitchTypeSerializer(serializers.ModelSerializer):
 
    open_value = serializers.NullBooleanField()

    class Meta:
        model = SwitchType
        fields = ['id','name','description','voltage','open_value','mode']

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