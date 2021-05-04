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
        instance.save()
        return instance

    class Meta:
        model = Board
        fields = ['id','name','description','cpu_type','usb_address','net_address','wifi_name']


class SwitchTypeSerializer(serializers.ModelSerializer):
 
    class Meta:
        model = SwitchType
        fields = ['id','name','description','voltage']

class SwitchSerializer(serializers.ModelSerializer):
 
    on_hi = serializers.NullBooleanField()
    #voltage = serializers.CharField(max_length=50, allow_blank=False)
    switchType = SwitchTypeSerializer()

    def update(self, instance, validated_data):
        """
        Update and return an existing `Snippet` instance, given the validated data.
        """
        instance.name = validated_data.get('name', instance.name)
        instance.description = validated_data.get('description', instance.description)
        instance.pin = validated_data.get('pin', instance.pin)
        instance.on_hi = validated_data.get('on_hi', instance.on_hi)
        s = validated_data.get('switchType')
        print(validated_data)
        print(validated_data.pop('switchType'))
  
        sw = SwitchType.objects.get(name=s.name)
        print(sw.id)
        instance.switchType = sw
        instance.save()
        return instance

    class Meta:
        model = Switch
        fields = ['id','name','description','pin','on_hi','state','switchType']