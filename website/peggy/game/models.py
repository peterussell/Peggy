from django.db import models

class User(models.Model):
	username = models.CharField(max_length=200)
	password = models.CharField(max_length=50)
	score = models.IntegerField(default=0)
	location = models.CharField(max_length=200)

class ActionRequest(models.Model):
	request = models.CharField(max_length=2048)
	time = models.DateTimeField()
	ipv4 = models.CharField(max_length=15)
	ipv6 = models.CharField(max_length=20)
	securityToken = models.CharField(max_length=200)
	player_id = models.ForeignKey(User)

class ActionResponse(models.Model):
	success = models.BooleanField()
	response = models.CharField(max_length=2048)
	player_state = models.CharField(max_length=2048)
	player_id = models.ForeignKey(User)
