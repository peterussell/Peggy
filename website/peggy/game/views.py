from django.shortcuts import render
from django.http import HttpResponse, HttpResponseRedirect
from django.core.urlresolvers import reverse
#from django.core import json
import json

def index( request ):
	"""
	Displays the main game page.
	"""
	return render(request, 'game/index.html')	

def execCmd( request ):
	"""
	Executes a player command.
	"""

	msg = ""
	errorMsg = ""
	if request.method == u'GET':
		if request.GET['cmdValue']:
			msg = request.GET['cmdValue']
		else:
			errorMsg = "Specify a command"
	else:	
		msg = "This is not a get request"

	data = json.dumps( { 'message': msg, 'errorMessage': errorMsg });
	return HttpResponse( data, mimetype='application/json' ) 
