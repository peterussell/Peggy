from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse

def index(request):
	"""
	Displays the main game page.
	"""
	return render(request, 'game/index.html')	

def execCmd(request):
	"""
	Executes a player command.
	"""
	return render(request, 'game/index.html')
