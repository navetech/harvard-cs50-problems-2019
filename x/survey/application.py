import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Disable caching
@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Main page function
@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


# Form page function
@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


# Post form function
@app.route("/form", methods=["POST"])
def post_form():

    # Get form data
    name = request.form.get("name")
    house = request.form.get("house")
    position = request.form.get("position")

    # Validate form data
    if not name:
        message = "missing name"
    elif not house:
        message = "missing house"
    elif not position:
        message = "missing position"
    else:
        message = ""

    if not message:

        # Register data
        with open('survey.csv', 'a', newline='') as csvfile:
            spamwriter = csv.writer(csvfile)

            spamwriter.writerow([name, house, position])

        # Show sheet page
        return redirect("/sheet")
    else:
        return render_template("error.html", message=message)


@app.route("/sheet", methods=["GET"])
def get_sheet():
    with open('survey.csv', newline='') as csvfile:
        spamreader = csv.reader(csvfile)

        if not spamreader:
            return render_template("error.html", message="missing file: survey.csv")
        else:
            rows = []
            for row in spamreader:
                rows.append(row)

            return render_template("table.html", rows=rows)
