# Generated by Django 3.2.1 on 2021-05-13 09:40

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('centralina', '0012_variable_savemode'),
    ]

    operations = [
        migrations.AlterField(
            model_name='variable',
            name='value',
            field=models.CharField(blank=True, default='', max_length=255),
        ),
    ]
