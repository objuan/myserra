# Generated by Django 3.2.1 on 2021-05-04 20:03

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Board',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
                ('description', models.CharField(blank=True, default='', max_length=100, null=True)),
                ('cpu_type', models.CharField(blank=True, default='', max_length=50, null=True)),
                ('usb_address', models.CharField(blank=True, default='', max_length=200, null=True)),
                ('net_address', models.CharField(blank=True, default='', max_length=200, null=True)),
                ('wifi_name', models.CharField(blank=True, default='', max_length=200, null=True)),
            ],
        ),
        migrations.CreateModel(
            name='SwitchType',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
                ('description', models.CharField(max_length=100)),
                ('voltage', models.IntegerField(default=12)),
            ],
        ),
        migrations.CreateModel(
            name='Switch',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
                ('description', models.CharField(blank=True, max_length=100)),
                ('pin', models.IntegerField(default=1)),
                ('on_hi', models.BooleanField(default=True)),
                ('state', models.CharField(default='', max_length=10)),
                ('board', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='centralina.board')),
                ('switchType', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='centralina.switchtype')),
            ],
        ),
    ]
