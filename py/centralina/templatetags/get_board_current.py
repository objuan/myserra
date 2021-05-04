from django import template

register = template.Library()

@register.simple_tag
def get_board_current(queryset, **filters):
    return request.session['board']