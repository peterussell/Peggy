from django.contrib import admin
from game.models import User
from game.models import ActionRequest
from game.models import ActionResponse

admin.site.register(User)
admin.site.register(ActionRequest)
admin.site.register(ActionResponse)
