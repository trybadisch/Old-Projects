from flask import Flask, request, session, redirect, render_template, make_response, send_from_directory, render_template_string
from flask_session import Session
import subprocess
import requests
import threading
import json

import chromium
import connect

import os
import sys
sys.dont_write_bytecode = True
import urllib3
urllib3.disable_warnings()

from flask_limiter import Limiter
from flask_limiter.util import get_remote_address

root = os.getcwd()

app = Flask(__name__, static_url_path='/static')
app.debug = True
app.config['TEMPLATES_AUTO_RELOAD'] = True

app.config["SESSION_PERMANENT"] = True
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

limiter = Limiter(
    get_remote_address,
    app=app,
    default_limits=["50 per second"],
    storage_uri="memory://",
)

# Name, Points
challenges = {
"Challenge 1": {'P':1},
"Challenge 2": {'P':2},
"Challenge 3": {'P':3}
}

def get_flag(flag):
	alert = None
	pass

@app.errorhandler(Exception)
def internal(error):
	print(error)
	return render_template("error.html", error=error)

@app.route("/", methods = ["GET", "POST"])
def index():
	if request.method == "POST":
		flag = request.form.get("flag")
		alert = get_flag(flag)
	else:
		alert = None
	return render_template("index.html", challenges=challenges, alert=alert)

from bs4 import BeautifulSoup
@app.route("/challenge1", methods = ["GET", "POST"])
def challenge1():
	if request.method == "POST":
		form = request.form.get("url")
		if ("169.254.169.254" in form or "168.63.129.16" in form):
			alert = "This is not a Cloud challenge."
			return render_template("challenge1.html", challenge="Challenge 1", alert=alert)
		def get_url():
			try:
				req = requests.get(form).content
			except requests.exceptions.MissingSchema:
				req = requests.get("http://"+form).content
			# except requests.exceptions.ConnectionError:
			return req
		try:
			req = get_url()
			parsed = BeautifulSoup(req, "html.parser").find("body")
			alert = parsed
		except requests.exceptions.ConnectionError:
			alert = form+" is not online"
	else:
		alert = None
	return render_template("challenge1.html", challenge="Challenge 1", alert=alert)
@app.route("/admin")
def admin():
	if request.remote_addr == "127.0.0.1":
		if request.args.get("username") == "admin" and request.args.get("password") == "1234":
			alert = "FLAG{9f55bcb190f1ab1256322be541ad27ee}"
		elif request.args.get("username") or request.args.get("password"):
			alert = "INCORRECT CREDENTIALS"
		else:
			alert = None
		return render_template("admin.html", alert=alert)
	else:
		return "NOT AUTHORIZED"

@app.route("/challenge2", methods = ["GET", "POST"])
def challenge2():
	if request.method == "POST":
		username = request.form.get("username")
		subject = request.form.get("subject")
		try:
			# chromium.run_driver(subject)
			threading.Thread(target=chromium.run_driver(subject), daemon=True).start()
		except Exception as e:
			print(e)
		alert = "Your message will be reviewed shortly."
	else:
		alert = None
	return render_template("challenge2.html", challenge="Challenge 2", alert=alert)

@app.route("/challenge3")
def challenge3():
	if request.args.get("blog") != None:
		alert = request.args.get("blog")
		# Solution: CASE WHEN (SELECT SUBSTR(password,1,1) FROM users WHERE id=1) LIKE 'F' THEN 2 ELSE 1 END
		# Blacklist UNION & RANDOMBLOB since they allow sqlmap detection
		if "UNION" not in alert.upper() and "RANDOM" not in alert.upper():
			try:
				alert = connect.execute(alert)
			except:
				alert = connect.execute("1")
		else:
			alert = "UNION and RANDOM not allowed"
	else:
		alert = connect.execute("1")
	return render_template("challenge3.html", challenge="Challenge 3", alert=alert)
